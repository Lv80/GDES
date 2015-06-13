#include "stdafx.h"

#include "DataInitHelper.h"

// �����ļ�
#include "../LoadConfig.h"

CString GetAppPathDir()
{
    TCHAR szModulePath[_MAX_PATH];
    GetModuleFileName( _hdllInstance, szModulePath, _MAX_PATH );

    TCHAR drive[_MAX_DRIVE];
    TCHAR dir[_MAX_DIR];
    _tsplitpath( szModulePath, drive, dir, NULL, NULL );

    TCHAR szPath[_MAX_PATH] = {0};
    _tmakepath( szPath, drive, dir, NULL, NULL );

    return CString( szPath );
}

CString BuildPath( const CString& dir, const CString& fileName )
{
    CString path;
    path.Format( _T( "%s%s" ), dir, fileName );
    return path;
}

void InitAllData( const CString& dirPath )
{
#if INCLUDE_TVNS_MODULE
	DataInitHelper::InitDataField( BuildPath( dirPath, _T( "ʯ�Ž�ú-�ֶ�-ͼԪ����.txt" ) ) );
	DataInitHelper::InitDataFieldWithMoreInfo( BuildPath( dirPath, _T( "��˹���-�ֶ�-ͼԪ����.txt" ) ) );
	DataInitHelper::InitIntStrList( BuildPath( dirPath, _T( "��˹���-�ַ���-�����б�.txt" ) ) );
	DataInitHelper::InitDataFieldWithMoreInfo( BuildPath( dirPath, _T( "��˹���-�ֶ�-���ݶ���.txt" ) ) );
	DataInitHelper::InitSingleDataObject( BuildPath( dirPath, _T( "��˹���-ȫ����Ϣ�����б�.txt" ) ) );
#endif

#if INCLUDE_EVAL_MODULE
    DataInitHelper::InitDataFieldWithMoreInfo( BuildPath( dirPath, _T( "ͨ������-�ֶ�-���ݶ���.txt" ) ) );
    DataInitHelper::InitStrList( BuildPath( dirPath, _T( "ͨ������-�ַ����б�.txt" ) ) );
    DataInitHelper::InitIntStrList( BuildPath( dirPath, _T( "ͨ������-�ַ���-�����б�.txt" ) ) );
    DataInitHelper::InitDataObjectList( BuildPath( dirPath, _T( "ͨ������-�ַ���-���ݶ����б�.txt" ) ) );
    DataInitHelper::InitSingleDataObject( BuildPath( dirPath, _T( "ͨ������-ȫ����Ϣ�����б�.txt" ) ) );
#endif

#if INCLUDE_VNC_MODULE
    DataInitHelper::InitDataFieldWithMoreInfo( BuildPath( dirPath, _T( "VNC-�ֶ�-ͨ��ͼԪ.txt" ) ) );
#endif

#if INCLUDE_MVSS_MODULE
    // ������������ֶ�
    DataInitHelper::InitDataFieldWithMoreInfo( BuildPath( dirPath, _T( "MVSS-�ֶ�-ͨ��ͼԪ.txt" ) ) );
#endif

#if INCLUDE_GAS_MODULE
    // ������������ֶ�
    DataInitHelper::InitDataFieldWithMoreInfo( BuildPath( dirPath, _T( "��˹����ͼ-�ֶ�-��˹ͼԪ.txt" ) ) );
#endif

#if INCLUDE_VNG_GEN_MODULE
    // ������������ֶ�
    DataInitHelper::InitDataFieldWithMoreInfo( BuildPath( dirPath, _T( "ͨ������ͼ-�ֶ�-����ͼԪ.txt" ) ) );
#endif

}