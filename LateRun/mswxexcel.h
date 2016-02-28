#ifndef MISSQTEXCEL_H
#define MISSQTEXCEL_H

#include <wx/string.h>
#include <memory>

class wxVariant;

class MsWxExcel
{
public:
    MsWxExcel();
    ~MsWxExcel();

	enum XlHAlign {
		xlHAlignCenter = -4108,
		xlHAlignCenterAcrossSelection = 7,
		xlHAlignDistributed = -4117,
		xlHAlignFill = 5,
		xlHAlignGeneral = 1,
		xlHAlignJustify = -4130,
		xlHAlignLeft = -4131,
		xlHAlignRight = - 4152,
	};

	enum XlVAlign {
		xlVAlignBottom = -4107,
		xlVAlignCenter = -4108,
		xlVAlignDistributed = -4117,
		xlVAlignJustify = -4130,
		xlVAlignTop = -4160,
	};

public:
    bool Init();
    bool Open(const wxString& strFileName);
    bool NewBook();
	bool Save(const wxString& strFileName);
	void Close();
	void Quit();

    void ShowExcel();
	bool OpenSheet(short sNo);
	bool OpenSheet(const wxString& strSheetName);
	wxVariant GetValue();
	wxString GetText();

    int GetUsedMaxRowCount();
    int GetUsedMaxColumnCount();

	bool SetValue(const wxVariant& strValue);
	bool SetValue(int nRow, int nColumn, const wxVariant& strValue);

	bool SetFormula(const wxVariant& strValue);

	bool SetRange(const wxString& strCell);
	bool SetRange(const wxString& strCellBegin, const wxString& strCellEnd);

    void Merge(bool bAcross = false);
	void AutoFitRow();
	void AutoFitColumn();
	void SetHorizontalAlignment(XlHAlign eType = xlHAlignCenter);
	void SetVerticalAlignment(XlVAlign eType = xlVAlignCenter);

	wxVariant GetValue(int nRow, int nColumn);
	wxString GetText(int nRow, int nColumn);

public:
    static wxString GetCellName(int nRow, int nColumn);
    static wxString GetColumnName(int nColumn);

private:
	class Impl;
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // MISSQTEXCEL_H
