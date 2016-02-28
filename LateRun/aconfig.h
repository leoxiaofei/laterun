#ifndef __ACONFIG_H__
#define __ACONFIG_H__

#include <wx\datetime.h>
#include <wx\hashset.h>
#include <memory>


WX_DECLARE_HASH_SET(wxString, wxStringHash, wxStringEqual, DaySet);

class ExceptDayData
{
public:
	DaySet dsHoliday;
	DaySet dsWorkday;

	bool IsHoliday(const wxString& strDay) const;
	bool IsWorkday(const wxString& strDay) const;
};

class AConfig
{
public:
	wxDateTime dtBeginDate;
	wxDateTime dtEndDate;
	bool bSpecialWeek;
	ExceptDayData edExceptDay;
	int nThrOmit;				///Â©¿¨ãÐÖµ

	wxDateTime dtBeginTime;
	wxDateTime dtEndTime;

	int GetWorkdayCount();
	int GetHolidayCount();

	bool IsHoliday(const wxDateTime& dtDay) const;
};

class DateTimeCalcor
{
public:
	DateTimeCalcor(const AConfig& aConfig);
	~DateTimeCalcor();

	bool OutOfLimits(const wxDateTime& dtDay) const;
	bool IsHoliday(const wxString& strDay) const;
	int GetWorkdayCount() const;
	const wxDateTime& GetBeginDate() const;
	const wxDateTime& GetEndDate() const;

	enum BeginTimeType {
		BTT_NORMAL, BTT_30MIN, BTT_180MIN, BTT_MORE
	};

	enum EndTimeType {
		ETT_NORMAL, ETT_30MIN, ETT_MORE
	};

	BeginTimeType CalcBeginTime(const wxTimeSpan& tsTime) const;
	EndTimeType CalcEndTime(const wxTimeSpan& tsTime) const;

protected:
	void InitDate(const AConfig& aConfig);
	void InitTime(const AConfig& aConfig);

private:
	class Impl;
	std::tr1::shared_ptr<Impl> m_pImpl;
};


#endif // __ACONFIG_H__
