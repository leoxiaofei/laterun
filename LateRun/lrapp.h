#ifndef LRAPP_H__
#define LRAPP_H__

#include <wx/app.h>

class LrApp : public wxApp
{
public:

	virtual bool OnInit() override;


private:
	wxLocale m_locale;
};

#endif // LRAPP_H__
