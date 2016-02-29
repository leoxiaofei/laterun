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
	T_3HOUR,			///3Сʱ��н
	T_ANNUAL,			///���
	T_DUTY,				///�Ӱ�
	T_SICK,				///����
	T_PRIVATE,			///�¼�
	T_MARITAL,			///���
	T_MATERNITY,		///����
	T_PATERNITY,		///�����
	T_SWAP,				///����
	T_BIZTRIP,			///����
	T_BIZOUT,			///���
	T_FUNERAL,			///ɥ��
	T_INJURY,			///���˼�
	T_SURPLUS_SWAP,		///ʣ�µ���
	T_SURPLUS_ANNUAL,	///ʣ�����
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
