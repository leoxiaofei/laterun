#include "lrapp.h"
#include "laterunframe.h"
#include <wx\intl.h>
#include <wctype.h>

bool LrApp::OnInit()
{
	wxLocale::AddCatalogLookupPathPrefix("./locale");

	m_locale.Init(wxLANGUAGE_CHINESE_SIMPLIFIED);
	m_locale.AddCatalog(wxT("runlate"));

	// 实例化窗口框架类
	LateRunFrame *lrFrame = new LateRunFrame(0);
#ifdef __WXMSW__
	lrFrame->SetIcon(wxICON(app));
#else
	lrFrame->SetIcon(wxICON(main));
#endif // __WXMSW__

	lrFrame->Show();

	return true;
}
