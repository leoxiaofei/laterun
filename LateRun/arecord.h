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
	AT_3HOUR,			///3小时带薪
	AT_ANNUAL,			///年假
	AT_DUTY,			///加班
	AT_SICK,			///病假
	AT_PRIVATE,			///事假
	AT_MARITAL,			///婚假
	AT_MATERNITY,		///产假
	AT_PATERNITY,		///陪产假
	AT_SWAP,			///调休
	AT_BIZTRIP,			///出差
	AT_BIZOUT,			///外出
	AT_FUNERAL,			///丧假
	AT_INJURY,			///工伤假

	_AT_TOTAL_,
};

AbsentType GetAbsentType(const wxString& strAbsentType);

typedef std::map<AbsentType, double> AbsentTime;				///类型，时间
WX_DECLARE_STRING_HASH_MAP(AbsentTime, HsAbsentTime);			///<wxString, AbsentTime> 员工ID，缺席时间

WX_DECLARE_STRING_HASH_MAP(AbsentType, AbsentDate);				///日期，类型
WX_DECLARE_STRING_HASH_MAP(AbsentDate, HsAbsentDate);			///<wxString, AbsentDate> 员工ID，缺席日期 

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
	PHT_LAST_SWAP,		///上次剩余调休
	PHT_LAST_ANNUAL,	///上次剩余年假
};

typedef std::map<PaidHolidayType, double> PaidHoliday;			///类型，时间
WX_DECLARE_STRING_HASH_MAP(PaidHoliday, HsPaidHoliday);			///<wxString, AbsentTime> 员工ID，缺席时间

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
