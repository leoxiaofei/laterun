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
	*/

	class _OneUse_
	{
	public:
		_OneUse_()
		{
			hsAbsentType[wxT("����")]	= AT_SICK;
			hsAbsentType[wxT("���")]	= AT_MARITAL;
			hsAbsentType[wxT("����")]	= AT_MATERNITY;
			hsAbsentType[wxT("�����")]	= AT_PATERNITY;
			hsAbsentType[wxT("ɥ��")]	= AT_FUNERAL;
			hsAbsentType[wxT("���˼�")]	= AT_INJURY;
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
