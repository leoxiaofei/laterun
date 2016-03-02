#ifndef __ARECORD_H__
#define __ARECORD_H__

#include <wx/string.h>
#include <wx/hashmap.h>
#include <wx/datetime.h>
#include <map>

typedef std::map<int, int> StatisticInfo;
WX_DECLARE_STRING_HASH_MAP(StatisticInfo, HsStatisticInfo);

enum AbsentType
{
	AT_3HOUR,			///3Сʱ��н
	AT_ANNUAL,			///���
	AT_DUTY,			///�Ӱ�
	AT_SICK,			///����
	AT_PRIVATE,			///�¼�
	AT_MARITAL,			///���
	AT_MATERNITY,		///����
	AT_PATERNITY,		///�����
	AT_SWAP,			///����
	AT_BIZTRIP,			///����
	AT_BIZOUT,			///���
	AT_FUNERAL,			///ɥ��
	AT_INJURY,			///���˼�

	_AT_TOTAL_,
};

AbsentType GetAbsentType(const wxString& strAbsentType);

typedef std::map<AbsentType, double> AbsentTime;				///���ͣ�ʱ��
WX_DECLARE_STRING_HASH_MAP(AbsentTime, HsAbsentTime);			///<wxString, AbsentTime> Ա��ID��ȱϯʱ��

WX_DECLARE_STRING_HASH_MAP(AbsentType, AbsentDate);				///���ڣ�����
WX_DECLARE_STRING_HASH_MAP(AbsentDate, HsAbsentDate);			///<wxString, AbsentDate> Ա��ID��ȱϯ���� 

class UserInfo
{
public:
	wxString strName;
	wxString strDepartment;
};

WX_DECLARE_STRING_HASH_MAP(UserInfo, HsUserInfo);

class TimeInfo
{
public:
	wxDateTime dtStart;
	wxDateTime dtEnd;
};

WX_DECLARE_STRING_HASH_MAP(TimeInfo, DateTimeInfo);
WX_DECLARE_STRING_HASH_MAP(DateTimeInfo, HsTimeInfo);


enum PaidHolidayType
{
	PHT_LAST_SWAP,		///�ϴ�ʣ�����
	PHT_LAST_ANNUAL,	///�ϴ�ʣ�����
};

typedef std::map<PaidHolidayType, double> PaidHoliday;			///���ͣ�ʱ��
WX_DECLARE_STRING_HASH_MAP(PaidHoliday, HsPaidHoliday);			///<wxString, AbsentTime> Ա��ID��ȱϯʱ��

class ARecord
{
public:
	HsUserInfo hsUserInfo;
	HsTimeInfo hsTimeInfo;
	HsStatisticInfo hsStatisticInfo;

	HsAbsentTime hsAbsentTime;
	HsAbsentDate hsAbsentDate;

	HsPaidHoliday hsPaidHoliday;

public:
	wxString GetJobId(const wxString& strName) const;

};


#endif // __ARECORD_H__
