#include "loadthread.h"
#include "FastDelegate.h"
#include "loadsrctask.h"
#include <objbase.h>

wxDEFINE_EVENT(wxEVT_COMMAND_LOAD_START, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_LOAD_UPDATE, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_LOAD_COMPLETED, wxThreadEvent);

LoadSrcThread::LoadSrcThread(wxEvtHandler* pHandler)
	: wxThread()
	, m_pHandler(pHandler)
{
	Create();
}

LoadSrcThread::~LoadSrcThread()
{

}

bool LoadSrcThread::Start(std::shared_ptr<LoadSrcTask> pLoadSrcTask)
{
	m_pLoadSrcTask = pLoadSrcTask;
	m_pLoadSrcTask->SetCancelDelegate(fastdelegate::MakeDelegate(this, &LoadSrcThread::TestDestroy));
	m_pLoadSrcTask->SetUpdateDelegate(fastdelegate::MakeDelegate(this, &LoadSrcThread::NotifyUpdate));

	return Run() == wxTHREAD_NO_ERROR;
}

LoadSrcThread::ExitCode LoadSrcThread::Entry()
{
	CoInitialize(NULL);

	wxThreadEvent* p = new wxThreadEvent(wxEVT_COMMAND_LOAD_START);
	p->SetInt(m_pLoadSrcTask->GetTotal());
	wxQueueEvent(m_pHandler, p);

	m_pLoadSrcTask->StartLoad();

	wxQueueEvent(m_pHandler, new wxThreadEvent(wxEVT_COMMAND_LOAD_COMPLETED));

	CoUninitialize();

	return 0;
}

void LoadSrcThread::NotifyUpdate()
{
	wxThreadEvent* p = new wxThreadEvent(wxEVT_COMMAND_LOAD_UPDATE);
	p->SetInt(m_pLoadSrcTask->GetProgress());
	wxQueueEvent(m_pHandler, p);
}
