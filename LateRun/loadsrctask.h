#ifndef __LOADSRCTASK_H__
#define __LOADSRCTASK_H__

#include <wx/string.h>
#include <memory>
#include "FastDelegate.h"

class ATemplate;
class AConfig;
class ARecord;
class MsWxExcel;

typedef fastdelegate::FastDelegate0<bool> CancelDelegate;
typedef fastdelegate::FastDelegate0<> UpdateDelegate;

class LogSrcData
{
public:
	wxString strRoster;
	wxString strPunchLog;
	wxString strDutyLog;
	wxString strLeaveLog;
	wxString strBiztripLog;
	wxString strOutLog;
	wxString strSurplusTable;
};

class LoadSrcTask
{
public:
	LoadSrcTask();
	~LoadSrcTask();
	
	void SetTemplate(const ATemplate& aTemplate);
	void SetConfig(const AConfig& aConfig);
	void SetLogSrcData(const LogSrcData& sdFileName);

	bool StartLoad();

	void SetCancelDelegate(const CancelDelegate& dgCancel);
	void SetUpdateDelegate(const UpdateDelegate& dgUpdate);

	int GetTotal() const;
	int GetProgress() const;

protected:
	void StatRecord(std::shared_ptr<ARecord> ptARecord);
	bool OutputRecord(MsWxExcel& msExcel, std::shared_ptr<ARecord> ptARecord);
	bool OutputStatistics(MsWxExcel& msExcel, std::shared_ptr<ARecord> ptARecord);

	bool LoadRoster(const wxString& strFileName, ARecord& aRecord);
	bool LoadPunchLog(const wxString& strFileName, ARecord& aRecord);
	bool LoadDutyLog(const wxString& strFileName, ARecord& aRecord);
	bool LoadLeaveLog(const wxString& strFileName, ARecord& aRecord);
	bool LoadBiztripLog(const wxString& strFileName, ARecord& aRecord);
	bool LoadOutLog(const wxString& strFileName, ARecord& aRecord);
	bool LoadSurplusTable(const wxString& strFileName, ARecord& aRecord);

private:
	class Impl;
	std::shared_ptr<Impl> m_pImpl;
};

#endif // __LOADSRCTASK_H__
