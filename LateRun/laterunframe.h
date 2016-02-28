#ifndef __laterunframe__
#define __laterunframe__

/**
@file
Subclass of LateRunFrame, which is generated by wxFormBuilder.
*/

#include "laterunui.h"
#include <memory>

//// end generated include

/** Implementing LateRunFrame */
class LateRunFrame : public LateRunFrameBase
{
protected:
	virtual void OnSize(wxSizeEvent& event) override;

	virtual void OnMnuAboutSelection(wxCommandEvent& event) override;

	virtual void OnBtnRunClick(wxCommandEvent& event) override;

	virtual void OnBtnExceptDateClick(wxCommandEvent& event) override;

	virtual void OnClose(wxCloseEvent& event) override;

public:
	/** Constructor */
	LateRunFrame( wxWindow* parent );
	//// end generated class members

	void LoadParam();
	void SaveParam() const;

	virtual void OnBtnPunchLogClick(wxCommandEvent& event) override;

	virtual void OnBtnDutyLogClick(wxCommandEvent& event) override;

	virtual void OnBtnLeaveLogClick(wxCommandEvent& event) override;

	virtual void OnBtnBiztripLogClick(wxCommandEvent& event) override;

	virtual void OnBtnOutLogClick(wxCommandEvent& event) override;

	virtual void OnSbMainSize(wxSizeEvent& event) override;

	virtual void OnLoadStart(wxThreadEvent& event);

	virtual void OnLoadUpdate(wxThreadEvent& event);

	virtual void OnLoadCompleted(wxThreadEvent& event);

	virtual void OnBtnAnnualTableClick(wxCommandEvent& event) override;


private:
	class Impl;
	std::shared_ptr<Impl> m_pImpl;
};

#endif // __laterunframe__