#include "loadsrctask.h"
#include "mswxexcel.h"
#include "arecord.h"
#include <wx/variant.h>
#include <wx/tokenzr.h>
#include "atemplate.h"
#include "aconfig.h"

class LoadSrcTask::Impl
{
public:
	ATemplate aTemplate;
	AConfig aConfig;
	LogSrcData sdFileName;
	CancelDelegate dgCancel;
	UpdateDelegate dgUpdate;

	int nProgress;
};

LoadSrcTask::LoadSrcTask()
: m_pImpl(new Impl)
{

}

LoadSrcTask::~LoadSrcTask()
{

}

bool LoadSrcTask::StartLoad()
{
	bool bRet(false);

	m_pImpl->nProgress = 0;

	do 
	{
		const LogSrcData& sdFileName = m_pImpl->sdFileName;

		std::shared_ptr<ARecord> ptARecord(new ARecord);

		///通知更新
		++(m_pImpl->nProgress);
		m_pImpl->dgUpdate();

		LoadPunchLog(sdFileName.strPunchLog, *ptARecord);

		///用户退出
		if (m_pImpl->dgCancel())
		{
			break;
		}

		///通知更新
		++(m_pImpl->nProgress);
		m_pImpl->dgUpdate();

		if (!sdFileName.strDutyLog.IsEmpty())
		{
			LoadDutyLog(sdFileName.strDutyLog, *ptARecord);
		}

		///用户退出
		if (m_pImpl->dgCancel())
		{
			break;
		}

		///通知更新
		++(m_pImpl->nProgress);
		m_pImpl->dgUpdate();

		if (!sdFileName.strOutLog.IsEmpty())
		{
			LoadOutLog(sdFileName.strOutLog, *ptARecord);
		}

		///用户退出
		if (m_pImpl->dgCancel())
		{
			break;
		}

		///通知更新
		++(m_pImpl->nProgress);
		m_pImpl->dgUpdate();

		if (!sdFileName.strLeaveLog.IsEmpty())
		{
			LoadLeaveLog(sdFileName.strLeaveLog, *ptARecord);
		}
		
		///用户退出
		if (m_pImpl->dgCancel())
		{
			break;
		}
		
		///通知更新
		++(m_pImpl->nProgress);
		m_pImpl->dgUpdate();

		if (!sdFileName.strBiztripLog.IsEmpty())
		{
			LoadBiztripLog(sdFileName.strBiztripLog, *ptARecord);
		}

		///用户退出
		if (m_pImpl->dgCancel())
		{
			break;
		}
		
		///通知更新
		++(m_pImpl->nProgress);
		m_pImpl->dgUpdate();

		StatRecord(ptARecord);

		///用户退出
		if (m_pImpl->dgCancel())
		{
			break;
		}

		///通知更新
		++(m_pImpl->nProgress);
		m_pImpl->dgUpdate();

		MsWxExcel msExcel;

		if (!msExcel.Init())
		{
			break;
		}

		if (!msExcel.Open(m_pImpl->aTemplate.strPath))
		{
			break;
		}

		if (!OutputRecord(msExcel, ptARecord))
		{
			break;
		}

		if (!OutputStatistics(msExcel, ptARecord))
		{
			break;
		}

		///用户退出
		if (m_pImpl->dgCancel())
		{
			break;
		}

		///通知更新
		++(m_pImpl->nProgress);
		m_pImpl->dgUpdate();

		msExcel.ShowExcel();

		bRet = true;

	} while (0);

	

	return bRet;
}

void LoadSrcTask::SetTemplate(const ATemplate& aTemplate)
{
	m_pImpl->aTemplate = aTemplate;
}

void LoadSrcTask::SetConfig(const AConfig& aConfig)
{
	m_pImpl->aConfig = aConfig;
}

void LoadSrcTask::StatRecord(std::shared_ptr<ARecord> ptARecord)
{
	DateTimeCalcor dtCalcor(m_pImpl->aConfig);

	StatisticInfo si;
	si[T_LATE_30MIN];
	si[T_LATE_180MIN];
	si[T_LATE_MORE];
	si[T_FORGET_TIMES];
	si[T_LEAVE_30MIN];
	si[T_LEAVE_MORE];
	si[T_PRESENT];
	si[T_ABSENT];

	const wxDateTime& dtBeginDate = dtCalcor.GetBeginDate();
	const wxDateTime& dtEndDate = dtCalcor.GetEndDate();
	wxDateSpan dsOne = wxDateSpan::Day();
	wxString strTheDate;

	for (HsTimeInfo::const_iterator citorID = ptARecord->hsTimeInfo.begin();
		citorID != ptARecord->hsTimeInfo.end(); ++citorID)
	{
		///用户退出
		if (m_pImpl->dgCancel())
		{
			break;
		}

		///ID = citorID->first
		HsStatisticInfo::iterator iFindStat =
			ptARecord->hsStatisticInfo.find(citorID->first);
		if (iFindStat == ptARecord->hsStatisticInfo.end())
		{
			ptARecord->hsStatisticInfo.insert(HsStatisticInfo::value_type(citorID->first, si));
			iFindStat = ptARecord->hsStatisticInfo.find(citorID->first);
		}

		StatisticInfo& statInfo = iFindStat->second;
		const AbsentDate& adDate = ptARecord->hsAbsentDate[citorID->first];

		for (wxDateTime dt = dtBeginDate; !dt.IsLaterThan(dtEndDate); dt.Add(dsOne))
		{
			///用户退出
			if (m_pImpl->dgCancel())
			{
				break;
			}

			strTheDate = dt.FormatISODate();
			if (dtCalcor.IsHoliday(strTheDate))
			{
				continue;
			}

			DateTimeInfo::const_iterator iFindDate = citorID->second.find(strTheDate);
			if (iFindDate != citorID->second.end())
			{
				///Date = citor->first

				///出席了
				++statInfo[T_PRESENT];

				if (iFindDate->second.dtStart.IsValid())
				{
					DateTimeCalcor::BeginTimeType eType =
						dtCalcor.CalcBeginTime(iFindDate->second.dtStart.Subtract(dt));

					if (	eType != DateTimeCalcor::BTT_NORMAL 
						&&	adDate.find(strTheDate) == adDate.end())
					{
						switch (eType)
						{
						case DateTimeCalcor::BTT_30MIN:
							++statInfo[T_LATE_30MIN];
							break;
						case DateTimeCalcor::BTT_180MIN:
							++statInfo[T_LATE_180MIN];
							break;
						case DateTimeCalcor::BTT_MORE:
							++statInfo[T_LATE_MORE];
							break;
						default:
							break;
						}
					}
				}
				else
				{
					if (adDate.find(strTheDate) == adDate.end())
					{
						++statInfo[T_FORGET_TIMES];
					}
				}

				if (iFindDate->second.dtEnd.IsValid())
				{
					DateTimeCalcor::EndTimeType eType =
						dtCalcor.CalcEndTime(iFindDate->second.dtEnd.Subtract(dt));

					if (	eType != DateTimeCalcor::ETT_NORMAL 
						&&	adDate.find(strTheDate) == adDate.end())
					{
						switch (eType)
						{
						case DateTimeCalcor::ETT_30MIN:
							++statInfo[T_LEAVE_30MIN];
							break;
						case DateTimeCalcor::ETT_MORE:
							++statInfo[T_LEAVE_MORE];
							break;
						default:
							break;
						}
					}
				}
				else
				{
					if (adDate.find(strTheDate) == adDate.end())
					{
						++statInfo[T_FORGET_TIMES];
					}
				}
			}
			else
			{
				///当天缺席，查数据表
				if (adDate.find(strTheDate) == adDate.end())
				{
					///如果数据表都不存在该记录，那么算缺席
					++statInfo[T_ABSENT];
				}
			}
		}

	}
}

bool LoadSrcTask::OutputRecord(MsWxExcel& msExcel, std::shared_ptr<ARecord> ptARecord)
{
	msExcel.OpenSheet(1);

	const wxDateTime& dtBeginDate = m_pImpl->aConfig.dtBeginDate.GetDateOnly();
	const wxDateTime& dtEndDate = m_pImpl->aConfig.dtEndDate.GetDateOnly();
	wxDateSpan dsOne = wxDateSpan::Day();

	int ixColumn(1);
	int ixRow(0);

	for (HsTimeInfo::const_iterator citorID = ptARecord->hsTimeInfo.begin();
		citorID != ptARecord->hsTimeInfo.end(); ++citorID)
	{
		for (wxDateTime dt = dtBeginDate; !dt.IsLaterThan(dtEndDate); dt.Add(dsOne))
		{
			DateTimeInfo::const_iterator citor = citorID->second.find(dt.FormatISODate());
			if (citor != citorID->second.end())
			{
				msExcel.SetValue(++ixRow, 1, citorID->first);

				msExcel.SetValue(ixRow, 2, citor->first);
				msExcel.AutoFitColumn();

				if (citor->second.dtStart.IsValid())
				{
					msExcel.SetValue(ixRow, 3, citor->second.dtStart.Format("%H:%M"));
				}

				if (citor->second.dtEnd.IsValid())
				{
					msExcel.SetValue(ixRow, 4, citor->second.dtEnd.Format("%H:%M"));
				}
			}
		}
	}

	return true;
}

bool LoadSrcTask::OutputStatistics(MsWxExcel& msExcel, std::shared_ptr<ARecord> ptARecord)
{
	msExcel.OpenSheet(2);

	int ixColumn(1);
	int ixRow = m_pImpl->aTemplate.uStartRow;

	HsAColumn& hsAColumn = m_pImpl->aTemplate.hsAColumn;
	
	for (HsStatisticInfo::const_iterator citorID = ptARecord->hsStatisticInfo.begin();
		citorID != ptARecord->hsStatisticInfo.end(); ++citorID, ++ixRow)
	{
		///用户退出
		if (m_pImpl->dgCancel())
		{
			break;
		}

		for (HsAColumn::const_iterator citorColumn = hsAColumn.begin();
			citorColumn != hsAColumn.end(); ++citorColumn)
		{
			///用户退出
			if (m_pImpl->dgCancel())
			{
				break;
			}

			msExcel.SetRange(citorColumn->first + wxString::Format(wxT("%d"), ixRow));

			if (citorColumn->second.eTempValueType <= T_DEPARTMENT)
			{
				switch (citorColumn->second.eTempValueType)
				{
				case T_ORDER:
					msExcel.SetValue(wxVariant(ixRow - (long)m_pImpl->aTemplate.uStartRow + 1));
					break;
				case T_NAME:
					msExcel.SetValue(ptARecord->hsUserInfo[citorID->first].strName);
					break;
				case T_JOB_ID:
					msExcel.SetValue(citorID->first);
					break;
				case T_DEPARTMENT:
					msExcel.SetValue(ptARecord->hsUserInfo[citorID->first].strDepartment);
					break;
				default:
					break;
				}
			}
			else if (citorColumn->second.eTempValueType <= T_ABSENT)
			{
				StatisticInfo::const_iterator ciFind =
					citorID->second.find(citorColumn->second.eTempValueType);
				if (ciFind != citorID->second.end())
				{
					msExcel.SetValue(ciFind->second);
				}
			}
			else if (citorColumn->second.eTempValueType < _T_TOTAL_)
			{
				const AbsentTime& atTime = ptARecord->hsAbsentTime[citorID->first];
				AbsentTime::const_iterator ciFind =	atTime.find(
					static_cast<AbsentType>(citorColumn->second.eTempValueType - T_3HOUR));
				if (ciFind != atTime.end())
				{
					msExcel.SetValue(ciFind->second);
				}
				else
				{
					msExcel.SetValue(0);
				}
			}
			else
			{
				wxString strAttach = citorColumn->second.strAttach;
				strAttach.Replace("%R", wxString::Format("%d", ixRow));
				msExcel.SetFormula(strAttach);
			}
		}

	}

	return true;
}

bool LoadSrcTask::LoadPunchLog(const wxString& strFileName, ARecord& aRecord)
{
	enum ARecordColumn { ARC_DEPARTMENT = 1, ARC_ID, ARC_NAME, ARC_DATE, ARC_TIME };

	bool bRet(false);

	do
	{
		MsWxExcel msExcel;

		if (!msExcel.Init())
		{
			break;
		}

		if (!msExcel.Open(strFileName))
		{
			break;
		}

		msExcel.OpenSheet(1);

		int nMaxColumn = msExcel.GetUsedMaxColumnCount() + 1;
		int nMaxRow = msExcel.GetUsedMaxRowCount() + 1;

		for (int ixRow = 2; ixRow < nMaxRow; ++ixRow)
		{
			///用户退出
			if (m_pImpl->dgCancel())
			{
				break;
			}

			///取员工编号
			wxString strID = msExcel.GetText(ixRow, ARC_ID);
			if (strID.Trim().IsEmpty())
			{
				continue;
			}

			HsUserInfo::const_iterator ciFind = aRecord.hsUserInfo.find(strID);
			if (ciFind == aRecord.hsUserInfo.end())
			{
				UserInfo& userInfo = aRecord.hsUserInfo[strID];
				userInfo.strDepartment = msExcel.GetText(ixRow, ARC_DEPARTMENT);
				userInfo.strDepartment.Trim();
				userInfo.strName = msExcel.GetText(ixRow, ARC_NAME);
				userInfo.strName.Trim();
			}

			wxString strDate = msExcel.GetText(ixRow, ARC_DATE);
			strDate.Trim();
			TimeInfo& timeInfo = aRecord.hsTimeInfo[strID][strDate];

			for (int ixColumn = ARC_TIME; ixColumn < nMaxColumn; ++ixColumn)
			{
				///用户退出
				if (m_pImpl->dgCancel())
				{
					break;
				}

				wxString strTime = msExcel.GetText(ixRow, ixColumn);
				if (!strTime.Trim().IsEmpty())
				{
					strTime = strDate + " " + strTime;
					if (!timeInfo.dtStart.IsValid())
					{

						timeInfo.dtStart.ParseDateTime(strTime);
					}
					else
					{
						timeInfo.dtEnd.ParseDateTime(strTime);
						if (!timeInfo.dtEnd.IsValid())
						{
							//手动处理错误的时间 24:55:00
							strTime = msExcel.GetText(ixRow, ixColumn);
							wxStringTokenizer tokenizer(strTime, ":");
							long lHour, lMin;
							if (!tokenizer.HasMoreTokens() || !tokenizer.GetNextToken().ToLong(&lHour))
							{
								continue;
							}
							if (!tokenizer.HasMoreTokens() || !tokenizer.GetNextToken().ToLong(&lMin))
							{
								continue;
							}
							timeInfo.dtEnd.ParseDate(strDate);
							timeInfo.dtEnd.Add(wxDateSpan(0, 0, 0, lHour / 24));
							timeInfo.dtEnd.SetHour(lHour % 24);
							timeInfo.dtEnd.SetMinute(lMin);
						}
					}
				}
			}

			if (!timeInfo.dtEnd.IsValid())
			{
				if (timeInfo.dtStart.GetHour() >= 14)
				{
					timeInfo.dtEnd = timeInfo.dtStart;
					timeInfo.dtStart = wxDateTime();
				}
			}
		}

		///
		msExcel.Close();
		msExcel.Quit();

		bRet = true;

	} while (0);

	return bRet;
}

bool LoadSrcTask::LoadDutyLog(const wxString& strFileName, ARecord& aRecord)
{
	enum DutyLogColumn { DLC_NAME = 1, DLC_DATE, DLC_TIME, DLC_DEPARTMENT };

	bool bRet(false);

	do
	{
		MsWxExcel msExcel;

		if (!msExcel.Init())
		{
			break;
		}

		if (!msExcel.Open(strFileName))
		{
			break;
		}

		msExcel.OpenSheet(1);

		int nMaxColumn = msExcel.GetUsedMaxColumnCount() + 1;
		int nMaxRow = msExcel.GetUsedMaxRowCount() + 1;

		double dTempTime(0);

		for (int ixRow = 2; ixRow < nMaxRow; ++ixRow)
		{
			///用户退出
			if (m_pImpl->dgCancel())
			{
				break;
			}

			///取员工姓名
			wxString strName = msExcel.GetText(ixRow, DLC_NAME);
			if (strName.Trim().IsEmpty())
			{
				continue;
			}

			///取员工编号
			wxString strJobId = aRecord.GetJobId(strName);
			if (strJobId.IsEmpty())
			{
				continue;
			}

			wxString strDate = msExcel.GetValue(ixRow, DLC_DATE).GetDateTime().FormatISODate();
			aRecord.hsAbsentDate[strJobId][strDate] = AT_DUTY;

			wxString strTime = msExcel.GetText(ixRow, DLC_TIME);
			if (strTime.Trim().ToDouble(&dTempTime))
			{
				aRecord.hsAbsentTime[strJobId][AT_DUTY] += dTempTime;
			}
		}

		///
		msExcel.Close();
		msExcel.Quit();

		bRet = true;

	} while (0);

	return bRet;
}

bool LoadSrcTask::LoadLeaveLog(const wxString& strFileName, ARecord& aRecord)
{
	enum LeaveLogColumn { LLC_NAME = 1, LLC_BEGIN_DATE, LLC_END_DATE, LLC_3HOUR, LLC_PRIVATE, LLC_SWAP, LLC_ANNUAL, LLC_OTHER_TYPE, LLC_OTHER_TIME };

	bool bRet(false);

	do
	{
		MsWxExcel msExcel;

		if (!msExcel.Init())
		{
			break;
		}

		if (!msExcel.Open(strFileName))
		{
			break;
		}

		msExcel.OpenSheet(1);

		int nMaxColumn = msExcel.GetUsedMaxColumnCount() + 1;
		int nMaxRow = msExcel.GetUsedMaxRowCount() + 1;

		double dTempTime(0);

		for (int ixRow = 2; ixRow < nMaxRow; ++ixRow)
		{
			///用户退出
			if (m_pImpl->dgCancel())
			{
				break;
			}

			///取员工姓名
			wxString strName = msExcel.GetText(ixRow, LLC_NAME);
			if (strName.Trim().IsEmpty())
			{
				continue;
			}

			///取员工编号
			wxString strJobId = aRecord.GetJobId(strName);
			if (strJobId.IsEmpty())
			{
				continue;
			}

			wxDateTime dtBegin = msExcel.GetValue(ixRow, LLC_BEGIN_DATE).GetDateTime();
			wxDateTime dtEnd = msExcel.GetValue(ixRow, LLC_END_DATE).GetDateTime();

			for (wxDateTime dt = dtBegin; !dt.IsLaterThan(dtEnd); dt.Add(wxDateSpan::Day()))
			{
				aRecord.hsAbsentDate[strJobId][dt.FormatISODate()] = AT_PRIVATE;
			}

			wxString strTime = msExcel.GetText(ixRow, LLC_3HOUR);
			if (strTime.Trim().ToDouble(&dTempTime))
			{
				aRecord.hsAbsentTime[strJobId][AT_3HOUR] += dTempTime;
			}

			strTime = msExcel.GetText(ixRow, LLC_PRIVATE);
			if (strTime.Trim().ToDouble(&dTempTime))
			{
				aRecord.hsAbsentTime[strJobId][AT_PRIVATE] += dTempTime;
			}

			strTime = msExcel.GetText(ixRow, LLC_SWAP);
			if (strTime.Trim().ToDouble(&dTempTime))
			{
				aRecord.hsAbsentTime[strJobId][AT_SWAP] += dTempTime;
			}

			strTime = msExcel.GetText(ixRow, LLC_ANNUAL);
			if (strTime.Trim().ToDouble(&dTempTime))
			{
				aRecord.hsAbsentTime[strJobId][AT_ANNUAL] += dTempTime;
			}

			AbsentType eAbsentType = GetAbsentType(msExcel.GetText(ixRow, LLC_OTHER_TYPE));
			if (eAbsentType != _AT_TOTAL_)
			{
				strTime = msExcel.GetText(ixRow, LLC_OTHER_TIME);
				if (strTime.Trim().ToDouble(&dTempTime))
				{
					aRecord.hsAbsentTime[strJobId][eAbsentType] += dTempTime;
				}
			}

		}

		///
		msExcel.Close();
		msExcel.Quit();

		bRet = true;

	} while (0);

	return bRet;
}

bool LoadSrcTask::LoadBiztripLog(const wxString& strFileName, ARecord& aRecord)
{
	enum BiztripLogColumn { BLC_NAME = 1, BLC_DEPARTMENT, BLC_BEGIN_DATE = 5, BLC_END_DATE, BLC_COMPANION = 8};

	bool bRet(false);
	do
	{
		MsWxExcel msExcel;

		if (!msExcel.Init())
		{
			break;
		}

		if (!msExcel.Open(strFileName))
		{
			break;
		}

		msExcel.OpenSheet(1);

		int nMaxColumn = msExcel.GetUsedMaxColumnCount() + 1;
		int nMaxRow = msExcel.GetUsedMaxRowCount() + 1;

		wxVector<wxString> listName;
		wxVector<wxString> listJobId;

		for (int ixRow = 2; ixRow < nMaxRow; ++ixRow)
		{
			///用户退出
			if (m_pImpl->dgCancel())
			{
				break;
			}

			listName.clear();
			listJobId.clear();

			///取员工姓名
			wxString strName = msExcel.GetText(ixRow, BLC_NAME);
			if (strName.Trim().IsEmpty())
			{
				continue;
			}

			listName.push_back(strName);

			strName = msExcel.GetText(ixRow, BLC_COMPANION);
			if (!strName.Trim().IsEmpty())
			{
				wxStringTokenizer tokenizer(strName, ";");
				while (tokenizer.HasMoreTokens())
				{
					strName = tokenizer.GetNextToken();
					listName.push_back(strName);
				}
			}

			///取员工编号
			for (wxVector<wxString>::const_iterator citorName = listName.begin();
				citorName != listName.end(); ++citorName)
			{
				wxString strJobId = aRecord.GetJobId(*citorName);
				if (strJobId.IsEmpty())
				{
					listJobId.push_back(strJobId);
					continue;
				}
			}

			if (listJobId.empty())
			{
				continue;
			}

			wxDateTime dtBegin = msExcel.GetValue(ixRow, BLC_BEGIN_DATE).GetDateTime();
			wxDateTime dtEnd = msExcel.GetValue(ixRow, BLC_END_DATE).GetDateTime();

			for (wxDateTime dt = dtBegin; !dt.IsLaterThan(dtEnd); dt.Add(wxDateSpan::Day()))
			{
				///用户退出
				if (m_pImpl->dgCancel())
				{
					break;
				}

				for (wxVector<wxString>::const_iterator citorJobId = listJobId.begin();
					citorJobId != listJobId.end(); ++citorJobId)
				{
					aRecord.hsAbsentDate[*citorJobId][dt.FormatISODate()] = AT_BIZTRIP;
				}
			}
		}

		///
		msExcel.Close();
		msExcel.Quit();

		bRet = true;

	} while (0);

	return bRet;
}

bool LoadSrcTask::LoadOutLog(const wxString& strFileName, ARecord& aRecord)
{
	enum OuttripLogColumn { OLC_BEGIN_DATE = 1, OLC_END_DATE = 3, OLC_NAME = 5, OLC_COMPANION = 7 };

	bool bRet(false);

	do
	{
		MsWxExcel msExcel;

		if (!msExcel.Init())
		{
			break;
		}

		if (!msExcel.Open(strFileName))
		{
			break;
		}

		msExcel.OpenSheet(1);

		int nMaxColumn = msExcel.GetUsedMaxColumnCount() + 1;
		int nMaxRow = msExcel.GetUsedMaxRowCount() + 1;

		double dTempTime(0);

		wxVector<wxString> listName;
		wxVector<wxString> listJobId;

		for (int ixRow = 2; ixRow < nMaxRow; ++ixRow)
		{
			///用户退出
			if (m_pImpl->dgCancel())
			{
				break;
			}

			listName.clear();
			listJobId.clear();

			///取员工姓名
			wxString strName = msExcel.GetText(ixRow, OLC_NAME);
			if (strName.Trim().IsEmpty())
			{
				continue;
			}

			listName.push_back(strName);

			strName = msExcel.GetText(ixRow, OLC_COMPANION);
			if (!strName.Trim().IsEmpty())
			{
				wxStringTokenizer tokenizer(strName, ";");
				while (tokenizer.HasMoreTokens())
				{
					strName = tokenizer.GetNextToken();
					listName.push_back(strName);
				}
			}

			///取员工编号
			for (wxVector<wxString>::const_iterator citorName = listName.begin();
				citorName != listName.end(); ++citorName)
			{
				wxString strJobId = aRecord.GetJobId(*citorName);
				if (strJobId.IsEmpty())
				{
					listJobId.push_back(strJobId);
					continue;
				}
			}

			if (listJobId.empty())
			{
				continue;
			}

			wxDateTime dtBegin = msExcel.GetValue(ixRow, OLC_BEGIN_DATE).GetDateTime();
			wxDateTime dtEnd = msExcel.GetValue(ixRow, OLC_END_DATE).GetDateTime();

			for (wxDateTime dt = dtBegin; !dt.IsLaterThan(dtEnd); dt.Add(wxDateSpan::Day()))
			{
				///用户退出
				if (m_pImpl->dgCancel())
				{
					break;
				}

				for (wxVector<wxString>::const_iterator citorJobId = listJobId.begin();
					citorJobId != listJobId.end(); ++citorJobId)
				{
					aRecord.hsAbsentDate[*citorJobId][dt.FormatISODate()] = AT_BIZOUT;
				}
			}
		}


		///
		msExcel.Close();
		msExcel.Quit();

		bRet = true;

	} while (0);
	return bRet;
}

void LoadSrcTask::SetCancelDelegate(const CancelDelegate& dgCancel)
{
	m_pImpl->dgCancel = dgCancel;
}

void LoadSrcTask::SetLogSrcData(const LogSrcData& sdFileName)
{
	m_pImpl->sdFileName = sdFileName;
}

int LoadSrcTask::GetTotal() const
{
	return 8;
}

int LoadSrcTask::GetProgress() const
{
	return m_pImpl->nProgress;
}

void LoadSrcTask::SetUpdateDelegate(const UpdateDelegate& dgUpdate)
{
	m_pImpl->dgUpdate = dgUpdate;
}

