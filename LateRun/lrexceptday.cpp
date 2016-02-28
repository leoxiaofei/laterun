#include "lrexceptday.h"
#include "aconfig.h"
#include <algorithm>
#include <wx\vector.h>

LrExceptDay::LrExceptDay( wxWindow* parent )
: LrExceptDayBase( parent )
{
	lcHoliday->InsertColumn(0, _("Date"), 0, wxLIST_AUTOSIZE_USEHEADER);
	lcWorkday->InsertColumn(0, _("Date"), 0, wxLIST_AUTOSIZE_USEHEADER);
}

void LrExceptDay::SetExceptDay(const ExceptDayData& edData)
{
	lcHoliday->DeleteAllItems();
	wxVector<wxString> vecHoliday;
	vecHoliday.assign(edData.dsHoliday.begin(), edData.dsHoliday.end());
	std::sort(vecHoliday.begin(), vecHoliday.end());

	for (wxVector<wxString>::size_type ix = 0;
		ix != vecHoliday.size(); ++ix)
	{
		lcHoliday->InsertItem(ix, vecHoliday[ix]);
	}

	lcWorkday->DeleteAllItems();
	wxVector<wxString> vecWorkday;
	vecWorkday.assign(edData.dsWorkday.begin(), edData.dsWorkday.end());
	std::sort(vecWorkday.begin(), vecWorkday.end());
	for (wxVector<wxString>::size_type ix = 0;
		ix != vecWorkday.size(); ++ix)
	{
		lcWorkday->InsertItem(ix, vecWorkday[ix]);
	}
}

void LrExceptDay::GetExceptDay(ExceptDayData& edData) const
{
	int nCount = lcHoliday->GetItemCount();
	edData.dsHoliday.clear();
	for (int ix = 0; ix != nCount; ++ix)
	{
		edData.dsHoliday.insert(lcHoliday->GetItemText(ix));
	}

	nCount = lcWorkday->GetItemCount();
	edData.dsWorkday.clear();
	for (int ix = 0; ix != nCount; ++ix)
	{
		edData.dsWorkday.insert(lcWorkday->GetItemText(ix));
	}
}

void LrExceptDay::OnBtnAddHolidayClick(wxCommandEvent& event)
{
	wxString strDate = cale->GetDate().FormatISODate();

	//////////////////////////////////////////////////////////////////////////
	long lFind = lcWorkday->FindItem(-1, strDate);
	if (wxNOT_FOUND != lFind)
	{
		lcWorkday->DeleteItem(lFind);
	}

	//////////////////////////////////////////////////////////////////////////
	lFind = lcHoliday->FindItem(-1, strDate);
	if (wxNOT_FOUND == lFind)
	{
		lcHoliday->InsertItem(lcHoliday->GetItemCount(), strDate);
	}
}

void LrExceptDay::OnBtnDelHolidayClick(wxCommandEvent& event)
{
	long item = -1;
	item = lcHoliday->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	if (wxNOT_FOUND != item)
	{
		lcHoliday->DeleteItem(item);
	}
}

void LrExceptDay::OnBtnAddWorkdayClick(wxCommandEvent& event)
{
	wxString strDate = cale->GetDate().FormatISODate();

	//////////////////////////////////////////////////////////////////////////
	long lFind = lcHoliday->FindItem(-1, strDate);
	if (wxNOT_FOUND != lFind)
	{
		lcHoliday->DeleteItem(lFind);
	}

	//////////////////////////////////////////////////////////////////////////
	lFind = lcWorkday->FindItem(-1, strDate);
	if (wxNOT_FOUND == lFind)
	{
		lcWorkday->InsertItem(lcWorkday->GetItemCount(), strDate);
	}
}

void LrExceptDay::OnBtnDelWorkdayClick(wxCommandEvent& event)
{
	long item = -1;
	item = lcWorkday->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	if (wxNOT_FOUND != item)
	{
		lcWorkday->DeleteItem(item);
	}
}
