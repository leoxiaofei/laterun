#include "aconfig.h"
#include <iostream>


bool ExceptDayData::IsHoliday(const wxString& strDay) const
{
	return dsWorkday.find(strDay) == dsWorkday.end()
		&& dsHoliday.find(strDay) != dsHoliday.end();
}

bool ExceptDayData::IsWorkday(const wxString& strDay) const
{
	return dsHoliday.find(strDay) == dsHoliday.end()
		&& dsWorkday.find(strDay) != dsWorkday.end();
}

int AConfig::GetWorkdayCount()
{
	int nCount(0);
	for (wxDateTime dt = dtBeginDate; !dt.IsLaterThan(dtEndDate); dt.Add(wxDateSpan(0,0,0,1)))
	{
		if (!IsHoliday(dt))
		{
			++nCount;
		}
	}
	return nCount;
}

int AConfig::GetHolidayCount()
{
	int nCount(0);
	for (wxDateTime dt = dtBeginDate; !dt.IsLaterThan(dtEndDate); dt.Add(wxDateSpan::Day()))
	{
		if (IsHoliday(dt))
		{
			std::cout << dt.FormatISODate() << std::endl;
			++nCount;
		}
	}
	return nCount;
}

bool AConfig::IsHoliday(const wxDateTime& dtDay) const
{
	bool bHoliday(false);

	do
	{
		wxDateTime::WeekDay eWeekDay = dtDay.GetWeekDay();
		if (eWeekDay != wxDateTime::Sun && eWeekDay != wxDateTime::Sat)
		{
			 break;
		}

		if (bSpecialWeek)
		{
			///公司实行大小周工作制，每月的第二个、第四个周六为正常工作日。
			if (eWeekDay == wxDateTime::Sat && dtDay.GetWeekOfMonth(wxDateTime::Monday_First) % 2 == 0)
			{
				break;
			}
		}

		bHoliday = true;

	} while (0);

	return bHoliday ? !edExceptDay.IsWorkday(dtDay.FormatISODate()) : edExceptDay.IsHoliday(dtDay.FormatISODate());

}



class DateTimeCalcor::Impl
{
public:
	DaySet dsHoliday;
	int    nWorkdayCount;

	wxDateTime dtBeginDate;
	wxDateTime dtEndDate;

	wxTimeSpan tsBeginTime;
	wxTimeSpan tsEndTime;

};

DateTimeCalcor::DateTimeCalcor(const AConfig& aConfig)
: m_pImpl(new Impl)
{
	InitDate(aConfig);
	InitTime(aConfig);
}

DateTimeCalcor::~DateTimeCalcor()
{

}

bool DateTimeCalcor::IsHoliday(const wxString& strDay) const
{
	return m_pImpl->dsHoliday.find(strDay) != m_pImpl->dsHoliday.end();
}

DateTimeCalcor::BeginTimeType DateTimeCalcor::CalcBeginTime(
	const wxTimeSpan& tsTime) const
{
	DateTimeCalcor::BeginTimeType eRet(BTT_NORMAL);

	wxTimeSpan tSpan = tsTime.Subtract(m_pImpl->tsBeginTime);

	if (tSpan.IsPositive())
	{
		int nMin = tSpan.GetMinutes();
		if (nMin < 10)
		{
			///10分钟以内，不处理
		}
		else if (nMin > 10 && nMin <= 30)
		{
			///30分钟以内
			eRet = BTT_30MIN;
		}
		else if (nMin > 30 && nMin <= 180)
		{
			///3小时以内
			eRet = BTT_180MIN;
		}
		else if (nMin > 180 /*&& nMin <= 450*/)
		{
			///7.5小时以内
			eRet = BTT_MORE;
		}
	}

	return eRet;
}


DateTimeCalcor::EndTimeType DateTimeCalcor::CalcEndTime(
	const wxTimeSpan& tsTime) const
{
	DateTimeCalcor::EndTimeType eRet(ETT_NORMAL);

	wxTimeSpan tSpan = tsTime.Subtract(m_pImpl->tsEndTime);

	if (tSpan.IsNegative())
	{
		int nMin = tSpan.Negate().GetMinutes();
		if (nMin > 0 && nMin <= 30)
		{
			///30分钟以内
			eRet = ETT_30MIN;
		}
		else if (nMin > 30)
		{
			///30分钟以上
			eRet = ETT_MORE;
		}
	}

	return eRet;
}

void DateTimeCalcor::InitDate(const AConfig& aConfig)
{
	DaySet dsRet;
	int nWorkdayCount(0);
	wxDateSpan dsOne(0, 0, 0, 1);

	for (wxDateTime dt = aConfig.dtBeginDate; !dt.IsLaterThan(aConfig.dtEndDate); dt.Add(dsOne))
	{
		if (aConfig.IsHoliday(dt))
		{
			std::cout << dt.FormatISODate() << std::endl;
			dsRet.insert(dt.FormatISODate());
		}
		else
		{
			++nWorkdayCount;
		}
	}

	m_pImpl->dsHoliday = dsRet;
	m_pImpl->nWorkdayCount = nWorkdayCount;

	m_pImpl->dtBeginDate = aConfig.dtBeginDate.GetDateOnly();
	m_pImpl->dtEndDate = aConfig.dtEndDate.GetDateOnly();
}

int DateTimeCalcor::GetWorkdayCount() const
{
	return m_pImpl->nWorkdayCount;
}

void DateTimeCalcor::InitTime(const AConfig& aConfig)
{
	m_pImpl->tsBeginTime = aConfig.dtBeginTime - aConfig.dtBeginTime.GetDateOnly();
	m_pImpl->tsEndTime = aConfig.dtEndTime - aConfig.dtEndTime.GetDateOnly();
}

bool DateTimeCalcor::OutOfLimits(const wxDateTime& dtDay) const
{
	return !dtDay.IsBetween(m_pImpl->dtBeginDate, m_pImpl->dtEndDate);
}

const wxDateTime& DateTimeCalcor::GetBeginDate() const
{
	return m_pImpl->dtBeginDate;
}

const wxDateTime& DateTimeCalcor::GetEndDate() const
{
	return m_pImpl->dtEndDate;
}
