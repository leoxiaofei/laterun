#ifndef __ATEMPLATE_H__
#define __ATEMPLATE_H__

#include <wx\hashmap.h>

class wxString;

enum TempValueType{
	T_ORDER,
	T_NAME,
	T_JOB_ID,
	T_DEPARTMENT,
	T_LATE_30MIN,
	T_LATE_180MIN,
	T_LATE_MORE,
	T_FORGET_TIMES,
	T_LEAVE_30MIN,
	T_LEAVE_MORE,
	T_PRESENT,
	T_ABSENT,
	T_3HOUR,			///3小时带薪
	T_ANNUAL,			///年假
	T_DUTY,				///加班
	T_SICK,				///病假
	T_PRIVATE,			///事假
	T_MARITAL,			///婚假
	T_MATERNITY,		///产假
	T_PATERNITY,		///陪产假
	T_SWAP,				///调休
	T_BIZTRIP,			///出差
	T_BIZOUT,			///外出
	T_FUNERAL,			///丧假
	T_INJURY,			///工伤假
	T_SURPLUS_SWAP,		///剩下调休
	T_SURPLUS_ANNUAL,	///剩下年假
	_T_TOTAL_,
};

class AColumn
{
public:
	TempValueType eTempValueType;
	wxString	  strAttach;

};

WX_DECLARE_STRING_HASH_MAP(AColumn, HsAColumn);

class ATemplate
{
public:
	void AddColumn(const wxString& strIdx, const wxString& strValue);
	
	bool LoadTemplate(const wxString& strFile);

public:
	wxString		strPath;
	unsigned long	uStartRow;
	HsAColumn		hsAColumn;
};


#endif // __ATEMPLATE_H__
