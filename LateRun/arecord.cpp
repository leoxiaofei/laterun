#include "arecord.h"
#include <ctype.h>



wxString ARecord::GetJobId(const wxString& strName) const
{
	wxString strRet;
	wxString strTName = strName;
	
	while (!strTName.IsEmpty() && strTName.Last() < 256)
	{
		strTName.RemoveLast(1);
	}

	if (!strTName.IsEmpty())
	{
		for (HsUserInfo::const_iterator citor = hsUserInfo.begin();
			citor != hsUserInfo.end(); ++citor)
		{
			if (citor->second.strName == strTName)
			{
				strRet = citor->first;
				break;
			}
		}
	}

	return strRet;
}

WX_DECLARE_STRING_HASH_MAP(AbsentType, HsAbsentType);

namespace
{
	HsAbsentType hsAbsentType;

	/*
	AT_3HOUR,			///3Ð¡Ê±´øÐ½
	AT_ANNUAL,			///Äê¼Ù
	AT_DUTY,			///¼Ó°à
	AT_SICK,			///²¡¼Ù
	AT_PRIVATE,			///ÊÂ¼Ù
	AT_MARITAL,			///»é¼Ù
	AT_MATERNITY,		///²ú¼Ù
	AT_PATERNITY,		///Åã²ú¼Ù
	AT_SWAP,			///µ÷ÐÝ
	AT_BIZTRIP,			///³ö²î
	AT_BIZOUT,			///Íâ³ö
	AT_FUNERAL,			///É¥¼Ù
	AT_INJURY,			///¹¤ÉË¼Ù
	*/

	class _OneUse_
	{
	public:
		_OneUse_()
		{
			hsAbsentType[wxT("²¡¼Ù")]	= AT_SICK;
			hsAbsentType[wxT("»é¼Ù")]	= AT_MARITAL;
			hsAbsentType[wxT("²ú¼Ù")]	= AT_MATERNITY;
			hsAbsentType[wxT("Åã²ú¼Ù")]	= AT_PATERNITY;
			hsAbsentType[wxT("É¥¼Ù")]	= AT_FUNERAL;
			hsAbsentType[wxT("¹¤ÉË¼Ù")]	= AT_INJURY;
		}

		~_OneUse_()
		{

		}

	};
}

AbsentType GetAbsentType(const wxString& strAbsentType)
{
	static _OneUse_ oneuse;

	AbsentType eRet(_AT_TOTAL_);

	HsAbsentType::const_iterator ciFind = hsAbsentType.find(strAbsentType);
	if (ciFind != hsAbsentType.end())
	{
		eRet = ciFind->second;
	}

	return eRet;
}
