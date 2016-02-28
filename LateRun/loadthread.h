#ifndef __LOADTHREAD_H__
#define __LOADTHREAD_H__

#include <wx/thread.h>
#include <memory>
#include <wx/event.h>

class LoadSrcTask;
class wxEvtHandler;

wxDECLARE_EVENT(wxEVT_COMMAND_LOAD_START, wxThreadEvent);
wxDECLARE_EVENT(wxEVT_COMMAND_LOAD_UPDATE, wxThreadEvent);
wxDECLARE_EVENT(wxEVT_COMMAND_LOAD_COMPLETED, wxThreadEvent);

class LoadSrcThread : public wxThread
{
public:
	LoadSrcThread(wxEvtHandler* pHandler);
	~LoadSrcThread();

	bool Start(std::shared_ptr<LoadSrcTask> pLoadSrcTask);

	virtual ExitCode Entry() override;
	
protected:
	void NotifyUpdate();

private:
	wxEvtHandler* m_pHandler;
	std::shared_ptr<LoadSrcTask> m_pLoadSrcTask;
};


#endif // __LOADTHREAD_H__
