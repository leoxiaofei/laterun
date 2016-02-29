///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/timectrl.h"

#include "laterunui.h"

///////////////////////////////////////////////////////////////////////////

LateRunFrameBase::LateRunFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNFACE ) );
	
	mbMain = new wxMenuBar( 0 );
	mnuHelp = new wxMenu();
	wxMenuItem* mnuAbout;
	mnuAbout = new wxMenuItem( mnuHelp, wxID_ANY, wxString( _("&About") ) , wxEmptyString, wxITEM_NORMAL );
	mnuHelp->Append( mnuAbout );
	
	mbMain->Append( mnuHelp, _("&Help") ); 
	
	this->SetMenuBar( mbMain );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("DataSrc") ), wxVERTICAL );
	
	wxBoxSizer* bSizer132;
	bSizer132 = new wxBoxSizer( wxHORIZONTAL );
	
	lblRoster = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("Roster:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblRoster->Wrap( -1 );
	bSizer132->Add( lblRoster, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	edtRoster = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer132->Add( edtRoster, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnRoster = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer132->Add( btnRoster, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer1->Add( bSizer132, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	lblPunchLog = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("Punch Log:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblPunchLog->Wrap( -1 );
	bSizer13->Add( lblPunchLog, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	edtPunchLog = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( edtPunchLog, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnPunchLog = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer13->Add( btnPunchLog, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer1->Add( bSizer13, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	lblDutyLog = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("Duty Log:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblDutyLog->Wrap( -1 );
	bSizer14->Add( lblDutyLog, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	edtDutyLog = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( edtDutyLog, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnDutyLog = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer14->Add( btnDutyLog, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer1->Add( bSizer14, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer131;
	bSizer131 = new wxBoxSizer( wxHORIZONTAL );
	
	lblLeaveLog = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("Leave Log:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblLeaveLog->Wrap( -1 );
	bSizer131->Add( lblLeaveLog, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	edtLeaveLog = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer131->Add( edtLeaveLog, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnLeaveLog = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer131->Add( btnLeaveLog, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer1->Add( bSizer131, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1311;
	bSizer1311 = new wxBoxSizer( wxHORIZONTAL );
	
	lblBiztripLog = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("BizTrip Log:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBiztripLog->Wrap( -1 );
	bSizer1311->Add( lblBiztripLog, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	edtBiztripLog = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1311->Add( edtBiztripLog, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnBiztripLog = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer1311->Add( btnBiztripLog, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer1->Add( bSizer1311, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer13111;
	bSizer13111 = new wxBoxSizer( wxHORIZONTAL );
	
	lblOutLog = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("Out Log:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblOutLog->Wrap( -1 );
	bSizer13111->Add( lblOutLog, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	edtOutLog = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13111->Add( edtOutLog, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnOutLog = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer13111->Add( btnOutLog, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer1->Add( bSizer13111, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer131111;
	bSizer131111 = new wxBoxSizer( wxHORIZONTAL );
	
	lblSurplusTable = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("Surplus Table:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblSurplusTable->Wrap( -1 );
	bSizer131111->Add( lblSurplusTable, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	edtSurplusTable = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer131111->Add( edtSurplusTable, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnAnnualTable = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer131111->Add( btnAnnualTable, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer1->Add( bSizer131111, 1, wxEXPAND, 5 );
	
	
	bSizer2->Add( sbSizer1, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Param") ), wxVERTICAL );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	lblBeginDate = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("Begin Date:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBeginDate->Wrap( -1 );
	bSizer5->Add( lblBeginDate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	dpBeginDate = new wxDatePickerCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT );
	bSizer5->Add( dpBeginDate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	lblEndDate = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("End Date:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblEndDate->Wrap( -1 );
	bSizer5->Add( lblEndDate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	dpEndDate = new wxDatePickerCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT );
	bSizer5->Add( dpEndDate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	cbtnSpecialWeek = new wxCheckBox( sbSizer2->GetStaticBox(), wxID_ANY, _("Special Week"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( cbtnSpecialWeek, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnExceptDate = new wxButton( sbSizer2->GetStaticBox(), wxID_ANY, _("Exception"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( btnExceptDate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer2->Add( bSizer5, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	lblBeginTime = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("Begin Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBeginTime->Wrap( -1 );
	bSizer6->Add( lblBeginTime, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	tpBeginTime = new wxTimePickerCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT );
	bSizer6->Add( tpBeginTime, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	lblEndTime = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("End Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblEndTime->Wrap( -1 );
	bSizer6->Add( lblEndTime, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	tpEndTime = new wxTimePickerCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT );
	bSizer6->Add( tpEndTime, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer2->Add( bSizer6, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	
	sbSizer2->Add( bSizer12, 1, wxEXPAND, 5 );
	
	
	bSizer2->Add( sbSizer2, 1, wxEXPAND|wxALL, 5 );
	
	btnRun = new wxButton( this, wxID_ANY, _("Run"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( btnRun, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( bSizer2 );
	this->Layout();
	sbMain = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( LateRunFrameBase::OnClose ) );
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( LateRunFrameBase::OnSize ) );
	this->Connect( mnuAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( LateRunFrameBase::OnMnuAboutSelection ) );
	btnRoster->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LateRunFrameBase::OnBtnRosterClick ), NULL, this );
	btnPunchLog->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LateRunFrameBase::OnBtnPunchLogClick ), NULL, this );
	btnDutyLog->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LateRunFrameBase::OnBtnDutyLogClick ), NULL, this );
	btnLeaveLog->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LateRunFrameBase::OnBtnLeaveLogClick ), NULL, this );
	btnBiztripLog->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LateRunFrameBase::OnBtnBiztripLogClick ), NULL, this );
	btnOutLog->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LateRunFrameBase::OnBtnOutLogClick ), NULL, this );
	btnAnnualTable->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LateRunFrameBase::OnBtnSurplusTableClick ), NULL, this );
	btnExceptDate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LateRunFrameBase::OnBtnExceptDateClick ), NULL, this );
	btnRun->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LateRunFrameBase::OnBtnRunClick ), NULL, this );
	sbMain->Connect( wxEVT_SIZE, wxSizeEventHandler( LateRunFrameBase::OnSbMainSize ), NULL, this );
}

LateRunFrameBase::~LateRunFrameBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( LateRunFrameBase::OnClose ) );
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( LateRunFrameBase::OnSize ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( LateRunFrameBase::OnMnuAboutSelection ) );
	btnRoster->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LateRunFrameBase::OnBtnRosterClick ), NULL, this );
	btnPunchLog->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LateRunFrameBase::OnBtnPunchLogClick ), NULL, this );
	btnDutyLog->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LateRunFrameBase::OnBtnDutyLogClick ), NULL, this );
	btnLeaveLog->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LateRunFrameBase::OnBtnLeaveLogClick ), NULL, this );
	btnBiztripLog->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LateRunFrameBase::OnBtnBiztripLogClick ), NULL, this );
	btnOutLog->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LateRunFrameBase::OnBtnOutLogClick ), NULL, this );
	btnAnnualTable->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LateRunFrameBase::OnBtnSurplusTableClick ), NULL, this );
	btnExceptDate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LateRunFrameBase::OnBtnExceptDateClick ), NULL, this );
	btnRun->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LateRunFrameBase::OnBtnRunClick ), NULL, this );
	sbMain->Disconnect( wxEVT_SIZE, wxSizeEventHandler( LateRunFrameBase::OnSbMainSize ), NULL, this );
	
}

LrAboutBase::LrAboutBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	bmIcon = new wxStaticBitmap( this, wxID_ANY, wxICON( app ), wxDefaultPosition, wxSize( 80,80 ), 0 );
	bSizer6->Add( bmIcon, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	bSizer5->SetMinSize( wxSize( 280,-1 ) ); 
	lblSoftName = new wxStaticText( this, wxID_ANY, _("LateRun"), wxDefaultPosition, wxDefaultSize, 0 );
	lblSoftName->Wrap( -1 );
	lblSoftName->SetFont( wxFont( 26, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer5->Add( lblSoftName, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	lblVersion = new wxStaticText( this, wxID_ANY, _("Version 0.0.3.ZS 2016.02.29"), wxDefaultPosition, wxDefaultSize, 0 );
	lblVersion->Wrap( -1 );
	bSizer5->Add( lblVersion, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	lblAuthor = new wxStaticText( this, wxID_ANY, _("soft@leoxiaofei.com"), wxDefaultPosition, wxDefaultSize, 0 );
	lblAuthor->Wrap( -1 );
	bSizer5->Add( lblAuthor, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer6->Add( bSizer5, 1, wxEXPAND, 5 );
	
	
	bSizer4->Add( bSizer6, 1, wxEXPAND, 5 );
	
	btnClose = new wxButton( this, wxID_OK, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( btnClose, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	
	this->SetSizer( bSizer4 );
	this->Layout();
	bSizer4->Fit( this );
	
	this->Centre( wxBOTH );
}

LrAboutBase::~LrAboutBase()
{
}

LrExceptDayBase::LrExceptDayBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Holiday") ), wxVERTICAL );
	
	lcHoliday = new wxListCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxSize( 50,-1 ), wxLC_HRULES|wxLC_REPORT );
	sbSizer4->Add( lcHoliday, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer8->Add( sbSizer4, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Workday") ), wxVERTICAL );
	
	lcWorkday = new wxListCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxSize( 40,-1 ), wxLC_HRULES|wxLC_REPORT );
	sbSizer5->Add( lcWorkday, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer8->Add( sbSizer5, 1, wxEXPAND, 5 );
	
	
	bSizer7->Add( bSizer8, 1, wxEXPAND|wxALL, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer9->Add( 0, 0, 1, wxEXPAND, 5 );
	
	btnAddHoliday = new wxButton( this, wxID_ANY, _("<<"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer9->Add( btnAddHoliday, 0, wxALL, 5 );
	
	btnDelHoliday = new wxButton( this, wxID_ANY, _(">>"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer9->Add( btnDelHoliday, 0, wxALL, 5 );
	
	
	bSizer9->Add( 0, 0, 1, wxEXPAND, 5 );
	
	btnAddWorkday = new wxButton( this, wxID_ANY, _("<<"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer9->Add( btnAddWorkday, 0, wxALL, 5 );
	
	btnDelWorkday = new wxButton( this, wxID_ANY, _(">>"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer9->Add( btnDelWorkday, 0, wxALL, 5 );
	
	
	bSizer9->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizer7->Add( bSizer9, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer10->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Calendar") ), wxVERTICAL );
	
	cale = new wxCalendarCtrl( sbSizer6->GetStaticBox(), wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxCAL_SHOW_HOLIDAYS );
	sbSizer6->Add( cale, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer10->Add( sbSizer6, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer10->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer11->Add( 0, 0, 1, wxEXPAND, 5 );
	
	btnOK = new wxButton( this, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( btnOK, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnCancel = new wxButton( this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( btnCancel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer10->Add( bSizer11, 0, wxEXPAND, 5 );
	
	
	bSizer7->Add( bSizer10, 1, wxEXPAND|wxALL, 5 );
	
	
	this->SetSizer( bSizer7 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	btnAddHoliday->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LrExceptDayBase::OnBtnAddHolidayClick ), NULL, this );
	btnDelHoliday->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LrExceptDayBase::OnBtnDelHolidayClick ), NULL, this );
	btnAddWorkday->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LrExceptDayBase::OnBtnAddWorkdayClick ), NULL, this );
	btnDelWorkday->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LrExceptDayBase::OnBtnDelWorkdayClick ), NULL, this );
}

LrExceptDayBase::~LrExceptDayBase()
{
	// Disconnect Events
	btnAddHoliday->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LrExceptDayBase::OnBtnAddHolidayClick ), NULL, this );
	btnDelHoliday->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LrExceptDayBase::OnBtnDelHolidayClick ), NULL, this );
	btnAddWorkday->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LrExceptDayBase::OnBtnAddWorkdayClick ), NULL, this );
	btnDelWorkday->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LrExceptDayBase::OnBtnDelWorkdayClick ), NULL, this );
	
}
