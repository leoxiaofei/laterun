#include "laterunframe.h"
#include "lrabout.h"
#include "mswxexcel.h"
#include <wx/filedlg.h>
#include "loadsrctask.h"
#include "lrexceptday.h"
#include "aconfig.h"
#include <wx/msgdlg.h>
#include <wx/fileconf.h>
#include <wx/tokenzr.h>
#include <wx/timectrl.h>
#include "atemplate.h"
#include "loadthread.h"
#include <wx/gauge.h>


class LateRunFrame::Impl
{
public:
	ExceptDayData edData;
	LoadSrcThread* pLoadSrcThread;

	wxGauge* pGauge;
};

LateRunFrame::LateRunFrame( wxWindow* parent )
: LateRunFrameBase( parent )
, m_pImpl(new Impl())
{
	m_pImpl->pLoadSrcThread = 0;
	m_pImpl->pGauge = new wxGauge(sbMain, wxID_ANY, 0);
	m_pImpl->pGauge->Hide();

	Bind(wxEVT_COMMAND_LOAD_COMPLETED, &LateRunFrame::OnLoadCompleted, this, wxID_ANY);
	Bind(wxEVT_COMMAND_LOAD_UPDATE, &LateRunFrame::OnLoadUpdate, this, wxID_ANY);
	Bind(wxEVT_COMMAND_LOAD_START, &LateRunFrame::OnLoadStart, this, wxID_ANY);

	LoadParam();
}


void LateRunFrame::OnBtnExceptDateClick(wxCommandEvent& event)
{
	LrExceptDay dlgExceptDate(this);
	dlgExceptDate.SetExceptDay(m_pImpl->edData);
	if (dlgExceptDate.ShowModal() == wxID_OK)
	{
		dlgExceptDate.GetExceptDay(m_pImpl->edData);
	}
}

void LateRunFrame::OnSize(wxSizeEvent& event)
{
	event.Skip();
}

void LateRunFrame::OnMnuAboutSelection(wxCommandEvent& event)
{
	LrAbout about(this);
	about.ShowModal();
}

void LateRunFrame::OnBtnRunClick(wxCommandEvent& event)
{
	btnRun->Enable(false);

	if (m_pImpl->pLoadSrcThread == 0)
	{
		m_pImpl->pLoadSrcThread = new LoadSrcThread(this);

		std::shared_ptr<LoadSrcTask> ptLoadSrcTask(new LoadSrcTask);

		AConfig aConfig;
		aConfig.edExceptDay = m_pImpl->edData;
		aConfig.dtBeginDate = dpBeginDate->GetValue();
		aConfig.dtEndDate = dpEndDate->GetValue();
		aConfig.dtBeginTime = tpBeginTime->GetValue();
		aConfig.dtEndTime = tpEndTime->GetValue();
		aConfig.bSpecialWeek = cbtnSpecialWeek->GetValue();

		ptLoadSrcTask->SetConfig(aConfig);

		ATemplate aTemplate;
		aTemplate.LoadTemplate(wxT("template/output.xml"));

		ptLoadSrcTask->SetTemplate(aTemplate);

		LogSrcData lsData;
		lsData.strRoster = edtRoster->GetValue();
		lsData.strPunchLog = edtPunchLog->GetValue();
		lsData.strBiztripLog = edtBiztripLog->GetValue();
		lsData.strDutyLog = edtDutyLog->GetValue();
		lsData.strLeaveLog = edtLeaveLog->GetValue();
		lsData.strOutLog = edtOutLog->GetValue();
		lsData.strSurplusTable = edtSurplusTable->GetValue();

		ptLoadSrcTask->SetLogSrcData(lsData);

		if (!m_pImpl->pLoadSrcThread->Start(ptLoadSrcTask))
		{
			delete m_pImpl->pLoadSrcThread;
			m_pImpl->pLoadSrcThread = 0;
			btnRun->Enable(true);
		}
	}
	else
	{
		m_pImpl->pLoadSrcThread->Delete();
	}
}

void LateRunFrame::OnClose(wxCloseEvent& event)
{
	SaveParam();
	event.Skip();
}

void LateRunFrame::SaveParam() const
{
	wxFileConfig file("LateRun", "MissStuido", "LateRun.ini", 
		"LateRun.ini", wxCONFIG_USE_RELATIVE_PATH);

	file.Write(wxT("History/PunchLog"), edtPunchLog->GetValue());
	file.Write(wxT("History/DutyLog"), edtDutyLog->GetValue());
	file.Write(wxT("History/LeaveLog"), edtLeaveLog->GetValue());
	file.Write(wxT("History/BiztripLog"), edtBiztripLog->GetValue());
	file.Write(wxT("History/OutLog"), edtOutLog->GetValue());
	file.Write(wxT("History/Roster"), edtRoster->GetValue());
	file.Write(wxT("History/SurplusTable"), edtSurplusTable->GetValue());

	file.Write(wxT("Param/BeginDate"), dpBeginDate->GetValue().FormatISODate());
	file.Write(wxT("Param/EndDate"), dpEndDate->GetValue().FormatISODate());
	file.Write(wxT("Param/BeginTime"), tpBeginTime->GetValue().FormatISOTime());
	file.Write(wxT("Param/EndTime"), tpEndTime->GetValue().FormatISOTime());
	file.Write(wxT("Param/SpecialWeek"), cbtnSpecialWeek->GetValue());


	wxString strHoliday;
	for (DaySet::const_iterator citor = m_pImpl->edData.dsHoliday.begin();
		citor != m_pImpl->edData.dsHoliday.end(); ++citor)
	{
		strHoliday.append(*citor);
		strHoliday.append(';');
	}
	file.Write(wxT("Param/Holiday"), strHoliday);

	wxString strWorkday;
	for (DaySet::const_iterator citor = m_pImpl->edData.dsWorkday.begin();
		citor != m_pImpl->edData.dsWorkday.end(); ++citor)
	{
		strWorkday.append(*citor);
		strWorkday.append(';');
	}
	
	file.Write(wxT("Param/Workday"), strWorkday);

}

void LateRunFrame::LoadParam()
{
	wxFileConfig file("LateRun", "MissStuido", "LateRun.ini", 
		"LateRun.ini", wxCONFIG_USE_RELATIVE_PATH);

	edtPunchLog->SetValue(file.Read(wxT("History/PunchLog")));
	edtDutyLog->SetValue(file.Read(wxT("History/DutyLog")));
	edtLeaveLog->SetValue(file.Read(wxT("History/LeaveLog")));
	edtBiztripLog->SetValue(file.Read(wxT("History/BiztripLog")));
	edtOutLog->SetValue(file.Read(wxT("History/OutLog")));
	edtRoster->SetValue(file.Read(wxT("History/Roster")));
	edtSurplusTable->SetValue(file.Read(wxT("History/SurplusTable")));
	
	wxDateTime dtBeginDate;
	dtBeginDate.ParseISODate(file.Read(wxT("Param/BeginDate")));
	if (dtBeginDate.IsValid())
	{
		dpBeginDate->SetValue(dtBeginDate);
	}
	
	wxDateTime dtEndDate;
	dtEndDate.ParseISODate(file.Read(wxT("Param/EndDate")));
	if (dtEndDate.IsValid())
	{
		dpEndDate->SetValue(dtEndDate);
	}

	wxDateTime dtBeginTime;
	dtBeginTime.ParseISOTime(file.Read(wxT("Param/BeginTime"), wxT("09:00:00")));
	if (dtBeginTime.IsValid())
	{
		tpBeginTime->SetValue(dtBeginTime);
	}

	wxDateTime dtEndTime;
	dtEndTime.ParseISOTime(file.Read(wxT("Param/EndTime"), wxT("17:30:00")));
	if (dtEndTime.IsValid())
	{
		tpEndTime->SetValue(dtEndTime);
	}

	bool bSpecialWeek(true);
	file.Read(wxT("Param/SpecialWeek"), &bSpecialWeek);
	cbtnSpecialWeek->SetValue(bSpecialWeek);

	wxString strHoliday = file.Read(wxT("Param/Holiday"));
	wxStringTokenizer tokenizerHoliday(strHoliday, ";");
	while (tokenizerHoliday.HasMoreTokens())
	{
		m_pImpl->edData.dsHoliday.insert(tokenizerHoliday.GetNextToken());
	}
	
	wxString strWorkday = file.Read(wxT("Param/Workday"));
	wxStringTokenizer tokenizerWorkday(strWorkday, ";");
	while (tokenizerWorkday.HasMoreTokens())
	{
		m_pImpl->edData.dsWorkday.insert(tokenizerWorkday.GetNextToken());
	}

}

void LateRunFrame::OnBtnPunchLogClick(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, _("Open Excel file"), "", "",
		_("Excel files (*.xls;*.xlsx)|*.xls;*.xlsx"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_OK)
	{
		edtPunchLog->SetValue(openFileDialog.GetPath());
	}
}

void LateRunFrame::OnBtnDutyLogClick(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, _("Open Excel file"), "", "",
		_("Excel files (*.xls;*.xlsx)|*.xls;*.xlsx"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_OK)
	{
		edtDutyLog->SetValue(openFileDialog.GetPath());
	}
}

void LateRunFrame::OnBtnLeaveLogClick(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, _("Open Excel file"), "", "",
		_("Excel files (*.xls;*.xlsx)|*.xls;*.xlsx"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_OK)
	{
		edtLeaveLog->SetValue(openFileDialog.GetPath());
	}
}

void LateRunFrame::OnBtnBiztripLogClick(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, _("Open Excel file"), "", "",
		_("Excel files (*.xls;*.xlsx)|*.xls;*.xlsx"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_OK)
	{
		edtBiztripLog->SetValue(openFileDialog.GetPath());
	}
}

void LateRunFrame::OnBtnOutLogClick(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, _("Open Excel file"), "", "",
		_("Excel files (*.xls;*.xlsx)|*.xls;*.xlsx"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_OK)
	{
		edtOutLog->SetValue(openFileDialog.GetPath());
	}
}

void LateRunFrame::OnLoadStart(wxThreadEvent& event)
{
	m_pImpl->pGauge->SetRange(event.GetInt());
	m_pImpl->pGauge->SetValue(0);
	m_pImpl->pGauge->Show();

	btnRun->SetLabelText(_("Cancel"));
	btnRun->Enable(true);
}

void LateRunFrame::OnLoadUpdate(wxThreadEvent& event)
{
	m_pImpl->pGauge->SetValue(event.GetInt());
}

void LateRunFrame::OnLoadCompleted(wxThreadEvent& event)
{
	m_pImpl->pLoadSrcThread = 0;
	m_pImpl->pGauge->Hide();

	btnRun->SetLabelText(_("Run"));
	btnRun->Enable(true);
}

void LateRunFrame::OnSbMainSize(wxSizeEvent& event)
{
	wxRect rect;
	sbMain->GetFieldRect(0, rect);
	m_pImpl->pGauge->SetPosition(rect.GetPosition());
	m_pImpl->pGauge->SetSize(rect.GetSize());
}

void LateRunFrame::OnBtnRosterClick(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, _("Open Excel file"), "", "",
		_("Excel files (*.xls;*.xlsx)|*.xls;*.xlsx"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_OK)
	{
		edtRoster->SetValue(openFileDialog.GetPath());
	}
}

void LateRunFrame::OnBtnSurplusTableClick(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, _("Open Excel file"), "", "",
		_("Excel files (*.xls;*.xlsx)|*.xls;*.xlsx"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_OK)
	{
		edtSurplusTable->SetValue(openFileDialog.GetPath());
	}
}

