#include "mswxexcel.h"


#include <wx/msw/ole/automtn.h>
#include <wx/variant.h>
#include <vector>

class MsWxExcel::Impl
{
public:
	wxAutomationObject m_App;
	wxAutomationObject m_Books;
    wxAutomationObject m_Book;
    wxAutomationObject m_Sheets;
    wxAutomationObject m_Sheet;
    wxAutomationObject m_Range;
};

MsWxExcel::MsWxExcel()
: m_pImpl(new Impl)
{

}

MsWxExcel::~MsWxExcel()
{

}

bool MsWxExcel::Init()
{
	bool bRet(false);
	do 
	{
		if (!m_pImpl->m_App.CreateInstance("Excel.Application"))
		{
			break;
		}

		if (!m_pImpl->m_App.GetObject(m_pImpl->m_Books, "Workbooks"))
		{
			break;
		}

		bRet = true;

	} while (0);

	return bRet;
}

bool MsWxExcel::Open( const wxString& strFileName )
{
	bool bRet(false);
	do
	{
		std::vector<wxVariant> vecOpenParam;
		vecOpenParam.push_back(strFileName);
		if (!m_pImpl->m_Books.GetObject(m_pImpl->m_Book, "Open", vecOpenParam.size(), &vecOpenParam[0]))
		{
			break;
		}

		if (!m_pImpl->m_Book.GetObject(m_pImpl->m_Sheets, "Worksheets"))
		{
			break;
		}

		if (!m_pImpl->m_App.GetObject(m_pImpl->m_Sheet, "ActiveSheet"))
		{
			break;
		}

		bRet = true;
	} while (0);

	return bRet;
}

bool MsWxExcel::NewBook()
{
	bool bRet(false);
	do
	{
		std::vector<wxVariant> vecAddParam;
		vecAddParam.push_back("");
		if (!m_pImpl->m_Books.GetObject(m_pImpl->m_Book, "Add", vecAddParam.size(), &vecAddParam[0]))
		{
			break;
		}

		if (!m_pImpl->m_Book.GetObject(m_pImpl->m_Sheets, "Worksheets"))
		{
			break;
		}

		if (!m_pImpl->m_App.GetObject(m_pImpl->m_Sheet, "ActiveSheet"))
		{
			break;
		}

	} while (0);
	return bRet;
}

bool MsWxExcel::Save( const wxString & strFileName )
{
    return true;
}

void MsWxExcel::ShowExcel()
{
	std::vector<wxVariant> vecShowParam;
	vecShowParam.push_back(true);
	m_pImpl->m_App.PutProperty("Visible", vecShowParam.size(), &vecShowParam[0]);
	m_pImpl->m_App.PutProperty("UserControl", vecShowParam.size(), &vecShowParam[0]);
}

bool MsWxExcel::OpenSheet( short sNo )
{
	bool bRet(false);

	std::vector<wxVariant> vecItemParam;
	vecItemParam.push_back(sNo);
	bRet = m_pImpl->m_Sheets.GetObject(m_pImpl->m_Sheet, "Item", vecItemParam.size(), &vecItemParam[0]);
	
	return bRet;
}

bool MsWxExcel::OpenSheet(const wxString& strSheetName)
{
	bool bRet(false);

	std::vector<wxVariant> vecItemParam;
	vecItemParam.push_back(strSheetName);
	bRet = m_pImpl->m_Sheets.GetObject(m_pImpl->m_Sheet, "Item", vecItemParam.size(), &vecItemParam[0]);

	return bRet;
}

int MsWxExcel::GetUsedMaxRowCount()
{
	wxVariant vaRet = m_pImpl->m_Sheet.GetProperty("UsedRange.Rows.Count");
	return vaRet.GetLong();
}

int MsWxExcel::GetUsedMaxColumnCount()
{
	wxVariant vaRet = m_pImpl->m_Sheet.GetProperty("UsedRange.Columns.Count");
	return vaRet.GetLong();
}

wxVariant MsWxExcel::GetValue()
{
	return m_pImpl->m_Range.GetProperty("Value");
}

wxVariant MsWxExcel::GetValue(int nRow, int nColumn)
{
	SetRange(GetCellName(nRow, nColumn));
	return GetValue();
}

wxString MsWxExcel::GetText()
{
	wxVariant vaRet = m_pImpl->m_Range.GetProperty("Text");
	return vaRet.GetString();
}

wxString MsWxExcel::GetText(int nRow, int nColumn)
{
	SetRange(GetCellName(nRow, nColumn));
	return GetText();
}

bool MsWxExcel::SetValue(const wxVariant& strValue)
{
	return m_pImpl->m_Range.PutProperty("Value", 1, const_cast<wxVariant *>(&strValue));
}

bool MsWxExcel::SetValue(int nRow, int nColumn, const wxVariant& strValue)
{
	SetRange(GetCellName(nRow, nColumn));
	return SetValue(strValue);
}

// void MsWxExcel::SetValue( int nValue )
// {
// 	m_pImpl->m_Range.PutProperty("Value", 1, &strValue);
// 	m_pImpl->m_Range->dynamicCall("SetValue(int)", nValue);
// }

bool MsWxExcel::SetRange( const wxString& strCell )
{
	std::vector<wxVariant> vecParam;
	vecParam.push_back(strCell);
	vecParam.push_back(strCell);
	return m_pImpl->m_Sheet.GetObject(m_pImpl->m_Range, "Range", vecParam.size(), &vecParam[0]);
}

bool MsWxExcel::SetRange(const wxString& strCellBegin, const wxString& strCellEnd)
{
	std::vector<wxVariant> vecParam;
	vecParam.push_back(strCellBegin);
	vecParam.push_back(strCellEnd);
	return m_pImpl->m_Sheet.GetObject(m_pImpl->m_Range, "Range", vecParam.size(), &vecParam[0]);
}

wxString MsWxExcel::GetCellName( int nRow, int nColumn )
{
    assert(nRow > 0);
	assert(nColumn > 0);
    wxString strRet = GetColumnName(nColumn);
	strRet += wxString::Format("%d", nRow);
    return strRet;
}

wxString MsWxExcel::GetColumnName( int nColumn )
{
	assert(nColumn > 0);
    wxString strRet;
    if (nColumn > 26)
    {
        strRet += ('A' + (nColumn - 1) / 26 - 1);
    }
    strRet += ('A' + (nColumn - 1) % 26 );
    return strRet;
}

void MsWxExcel::Merge( bool bAcross /*= false*/ )
{
    m_pImpl->m_Range.CallMethod("Merge", bAcross);
	SetHorizontalAlignment(bAcross ? xlHAlignCenter : xlHAlignGeneral);
}

void MsWxExcel::AutoFitRow()
{
	m_pImpl->m_Range.CallMethod("EntireRow.AutoFit");
}

void MsWxExcel::AutoFitColumn()
{
	m_pImpl->m_Range.CallMethod("EntireColumn.AutoFit");
}

//Ä¬ÈÏ£½1,¾ÓÖÐ£½-4108,×ó£½-4131,ÓÒ£½-4152
void MsWxExcel::SetHorizontalAlignment( XlHAlign eType /*= xlHAlignCenter*/ )
{
	m_pImpl->m_Range.PutProperty("HorizontalAlignment", eType);
}

//Ä¬ÈÏ£½2,¾ÓÖÐ£½-4108,×ó£½-4160,ÓÒ£½-4107
void MsWxExcel::SetVerticalAlignment( XlVAlign eType /*= xlVAlignCenter*/ )
{
	m_pImpl->m_Range.PutProperty("VerticalAlignment", eType);
}

void MsWxExcel::Close()
{
	std::vector<wxVariant> vecParam;
	vecParam.push_back(false);
	m_pImpl->m_Book.CallMethod("Close", vecParam.size(), &vecParam[0]);
}

void MsWxExcel::Quit()
{
	m_pImpl->m_App.CallMethod("Quit");
}

bool MsWxExcel::SetFormula(const wxVariant& strValue)
{
	return m_pImpl->m_Range.PutProperty("Formula", 1, const_cast<wxVariant *>(&strValue));
}
