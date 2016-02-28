///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __LATERUNUI_H__
#define __LATERUNUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
class wxTimePickerCtrl;

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/checkbox.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/statbmp.h>
#include <wx/dialog.h>
#include <wx/listctrl.h>
#include <wx/calctrl.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class LateRunFrameBase
///////////////////////////////////////////////////////////////////////////////
class LateRunFrameBase : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* mbMain;
		wxMenu* mnuHelp;
		wxStaticText* lblPunchLog;
		wxTextCtrl* edtPunchLog;
		wxButton* btnPunchLog;
		wxStaticText* lblDutyLog;
		wxTextCtrl* edtDutyLog;
		wxButton* btnDutyLog;
		wxStaticText* lblLeaveLog;
		wxTextCtrl* edtLeaveLog;
		wxButton* btnLeaveLog;
		wxStaticText* lblBiztripLog;
		wxTextCtrl* edtBiztripLog;
		wxButton* btnBiztripLog;
		wxStaticText* lblOutLog;
		wxTextCtrl* edtOutLog;
		wxButton* btnOutLog;
		wxStaticText* lblAnnualTable;
		wxTextCtrl* edtAnnualTable;
		wxButton* btnAnnualTable;
		wxStaticText* lblBeginDate;
		wxDatePickerCtrl* dpBeginDate;
		wxStaticText* lblEndDate;
		wxDatePickerCtrl* dpEndDate;
		wxCheckBox* cbtnSpecialWeek;
		wxButton* btnExceptDate;
		wxStaticText* lblBeginTime;
		wxTimePickerCtrl* tpBeginTime;
		wxStaticText* lblEndTime;
		wxTimePickerCtrl* tpEndTime;
		wxButton* btnRun;
		wxStatusBar* sbMain;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnSize( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnMnuAboutSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBtnPunchLogClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBtnDutyLogClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBtnLeaveLogClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBtnBiztripLogClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBtnOutLogClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBtnAnnualTableClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBtnExceptDateClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBtnRunClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSbMainSize( wxSizeEvent& event ) { event.Skip(); }
		
	
	public:
		
		LateRunFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("LateRun"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 557,506 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~LateRunFrameBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class LrAboutBase
///////////////////////////////////////////////////////////////////////////////
class LrAboutBase : public wxDialog 
{
	private:
	
	protected:
		wxStaticBitmap* bmIcon;
		wxStaticText* lblSoftName;
		wxStaticText* lblVersion;
		wxStaticText* lblAuthor;
		wxButton* btnClose;
	
	public:
		
		LrAboutBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("About..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~LrAboutBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class LrExceptDayBase
///////////////////////////////////////////////////////////////////////////////
class LrExceptDayBase : public wxDialog 
{
	private:
	
	protected:
		wxListCtrl* lcHoliday;
		wxListCtrl* lcWorkday;
		wxButton* btnAddHoliday;
		wxButton* btnDelHoliday;
		wxButton* btnAddWorkday;
		wxButton* btnDelWorkday;
		wxCalendarCtrl* cale;
		wxButton* btnOK;
		wxButton* btnCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnBtnAddHolidayClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBtnDelHolidayClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBtnAddWorkdayClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBtnDelWorkdayClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		LrExceptDayBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("ExceptDay"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 592,568 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~LrExceptDayBase();
	
};

#endif //__LATERUNUI_H__
