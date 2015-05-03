// FileOpt.cpp: implementation of the CFileOpt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../Easson2d.h"
#include "FileOpt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileOpt::CFileOpt()
{
}

CFileOpt::~CFileOpt()
{
//	if ( m_hFile )
//	{
//		Close();           // �ر��ļ�
// 	}
}

BOOL CFileOpt::CreateFile( LPCTSTR lpFile )
{
	// �ж��ļ��Ƿ����
	if ( isExistFile( lpFile ) )
	{
		if ( IDOK == MessageBox( NULL, "�ļ��Ѵ���, �Ƿ񸲸�?", "��ʾ", MB_OKCANCEL 
			| MB_ICONINFORMATION ) )
		{
			// �����������ļ�
			Open( lpFile, CFile::modeCreate );
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	// �����ļ�
	Open( lpFile, CFile::modeCreate );
	return TRUE;
}

BOOL CFileOpt::OpenFile( LPCTSTR lpFile )
{
	DWORD    dwErrCode = 0;                // �������

	Open( lpFile, CFile::modeReadWrite );
	dwErrCode = GetLastError();

	if ( 0 == dwErrCode )        // ����ļ������Ҵ��ļ��ɹ�(���ܲ���)
	{
		return TRUE;
	}

	if ( m_bDebug )                        // �ǵ���ģʽ
	{
		ErrorMessageBox( dwErrCode );
	}

	return FALSE;                // �ļ�������
}

BOOL CFileOpt::FilePointerSeek( UINT nMethod, LONG nCurrent )
{
	DWORD dwErrCode = 0;

	if ( 0 == nCurrent )
	{
		switch ( nMethod )
		{
		case 1:                    // �ļ���
			SeekToBegin();
			break;
		case 2:                    // �ļ�β
			SeekToEnd();
			break;
		}
		dwErrCode = GetLastError();
	}
	else
	{
		switch ( nMethod )
		{
		case 1:
			Seek( nCurrent, CFile::begin );
			break;
		case 2:
			Seek( nCurrent, CFile::end );
			break;
		}
		dwErrCode = GetLastError();
	}

	if ( 0 == dwErrCode )   // �����ļ��ɹ�
	{
		return TRUE;
	}

	if ( m_bDebug )                     // �ǵ���ģʽ
	{
		ErrorMessageBox( dwErrCode );
	}
	
	return FALSE;
}

BOOL CFileOpt::ReadFile( LPTSTR lpData )
{
	Read( lpData, MAX_BUFF );
	return TRUE;
}

void CFileOpt::CloseFile()
{
	Close();
}

void CFileOpt::SetDebugMode( BOOL bDebug )
{
	m_bDebug = bDebug;
}

BOOL CFileOpt::isExistFile( LPCTSTR lpFile )
{
	DWORD    dwErrCode = 0;                // �������

	Open( lpFile, CFile::modeRead );
	dwErrCode = GetLastError();

	if ( 0 == dwErrCode )        // ����ļ������Ҵ��ļ��ɹ�(���ܲ���)
	{
		Close();
		return TRUE;
	}

	if ( m_bDebug )                        // �ǵ���ģʽ
	{
		ErrorMessageBox( dwErrCode );
	}

	return FALSE;                // �ļ�������
}

void CFileOpt::ErrorMessageBox( DWORD dwErrCode )
{
	HLOCAL hLocal = NULL;     // �ڴ����

	// ��ʽ������Ĵ������
	FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER , 
		NULL, dwErrCode, MAKELANGID( LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED ),
		(LPTSTR)&hLocal, 0, NULL );

	if ( hLocal != NULL )
	{
		MessageBox( NULL, (LPCTSTR)LocalLock(hLocal), "�ļ�����", MB_OK | MB_ICONERROR );
		LocalFree( hLocal );
	}
	else
	{
		MessageBox( NULL, "һ��δ֪�Ĵ���", "�ļ�����", MB_OK | MB_ICONERROR );
	}
}

BOOL CFileOpt::WriteFile( LPTSTR lpData )
{
	DWORD dwErrCode = 0;


	Write( lpData, strlen(lpData) );
	dwErrCode = GetLastError();

	if ( 0 == dwErrCode )      // д��ɹ�
	{
		return TRUE;
	}

	if ( m_bDebug )                        // �ǵ���ģʽ
	{
		ErrorMessageBox( dwErrCode );
	}

	return FALSE;              // д��ʧ��
}