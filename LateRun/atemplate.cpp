#include "atemplate.h"

#include <wx/string.h>
#include <wx/xml/xml.h>
#include <wx/filename.h>


namespace
{
	const wxString strTempValueType[] = {
		"T_ORDER",
		"T_NAME",
		"T_JOB_ID",
		"T_DEPARTMENT",
		"T_LATE_30MIN",
		"T_LATE_180MIN",
		"T_LATE_MORE",
		"T_FORGET_TIMES",
		"T_LEAVE_30MIN",
		"T_LEAVE_MORE",
		"T_PRESENT",
		"T_ABSENT",
		"T_3HOUR",
		"T_ANNUAL",
		"T_DUTY",
		"T_SICK",
		"T_PRIVATE",
		"T_MARITAL",
		"T_MATERNITY",
		"T_PATERNITY",
		"T_SWAP",
		"T_BIZTRIP",
		"T_BIZOUT",
		"T_FUNERAL",
		"T_INJURY",
		"T_SURPLUS_SWAP",
		"T_SURPLUS_ANNUAL",
		""
	};

	TempValueType FindType(const wxString& strType)
	{
		TempValueType eRet(_T_TOTAL_);

		for (int ix = T_ORDER; ix != _T_TOTAL_; ++ix)
		{
			if (strType.compare(strTempValueType[ix]) == 0)
			{
				eRet = static_cast<TempValueType>(ix);
			}
		}

		return eRet;
	}
}


void ATemplate::AddColumn(const wxString& strIdx, const wxString& strValue)
{
	AColumn& aColumn = hsAColumn[strIdx];
	aColumn.eTempValueType = FindType(strValue);
	aColumn.strAttach = strValue;
}

bool ATemplate::LoadTemplate(const wxString& strFile)
{
	bool bRet(false);

	do 
	{
		wxXmlDocument doc;
		if (!doc.Load(strFile))
		{
			break;
		}

		wxXmlNode* pRootNode = doc.GetRoot();
		if (!pRootNode)
		{
			break;
		}

		wxXmlNode* pTemplateNode = pRootNode->GetChildren();
		while (pTemplateNode)
		{
			if (pTemplateNode->GetName() == wxT("Template"))
			{
				break;
			}

			pTemplateNode = pTemplateNode->GetNext();
		} 

		if (!pTemplateNode)
		{
			break;
		}

		///获取模板属性
		wxFileName fn(pTemplateNode->GetAttribute(wxT("path"), wxT("output.xltx")));
		fn.MakeAbsolute();
		strPath = fn.GetFullPath();
		pTemplateNode->GetAttribute(wxT("startRow"), wxT("3")).ToULong(&uStartRow);

		///获取列属性
		wxString strIdx;
		AColumn aColumn;
		for (wxXmlNode* pColumnNode = pTemplateNode->GetChildren(); pColumnNode;
			pColumnNode = pColumnNode->GetNext())
		{
			if (pColumnNode->GetName() != wxT("Column"))
			{
				continue;
			}

			strIdx = pColumnNode->GetAttribute(wxT("idx"), wxT(""));
			aColumn.strAttach = pColumnNode->GetAttribute(wxT("value"), wxT(""));
			aColumn.eTempValueType = FindType(aColumn.strAttach);
			hsAColumn[strIdx] = aColumn;
		}

		bRet = true;

	} while (0);

	return bRet;
}
