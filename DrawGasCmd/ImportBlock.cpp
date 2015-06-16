#include "stdafx.h"

#include <ctime>
#include "../ArxHelper/HelperClass.h"

// ������˹����ͼ�鶨��
// �ӵ�ǰģ�����Ŀ¼�¼���
void UpdateDwgBlock()
{
    //CString dwgFilePath = _T("C:\\Users\\anheihb03dlj\\Desktop\\��˹����ͼ�鶨��.dwg");
	CString dwgFilePath = ArxUtilHelper::BuildPath(ArxUtilHelper::GetAppPathDir(_hdllInstance), _T( "Datas\\��˹����ͼ�鶨��.dwg" ));
	if( ArxDwgHelper::InsertDwg( dwgFilePath ) )
    {
        acutPrintf( _T( "\n���¿�ɹ�!\n" ) );
		ArxDwgHelper::UpdateDwg(); // ����ͼ��
    }
    else
    {
        acutPrintf( _T( "\n���¿�ʧ��!\n" ) );
    }
}