
// RegTbOpt.cpp: implementation of the CRegTbOpt class.
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>
//#include "SoftWarwREG.h"
#include "RegTbOpt.h"


CRegTbOpt::CRegTbOpt()
{
	m_bDebug = FALSE;
	m_hKey = NULL;
}

CRegTbOpt::~CRegTbOpt()
{
}

// ����ע����ֵ
BOOL CRegTbOpt::CreateRegKey( HKEY hKey, LPCTSTR lpKeyName )
{
	LONG   nErrCode = 0;             // �������

	nErrCode = RegCreateKey( hKey, lpKeyName, &m_hKey );

	if ( ERROR_SUCCESS == nErrCode )
	{
		return TRUE;
	}

	//if ( m_bDebug )                    // ���Ϊ����ģʽ
	//{
	//	ErrorMessageBox( nErrCode );
	//}
	
	return FALSE;                    // �򿪼�ʧ��
}

// ��ע���
BOOL CRegTbOpt::OpenRegTable( HKEY hKey, LPCSTR lpSubKey )
{
	LONG   nErrCode = 0;             // �������
	
	nErrCode = RegOpenKey( hKey, lpSubKey, &m_hKey );

	if ( ERROR_SUCCESS == nErrCode )
	{
		return TRUE;                 // �򿪼��ɹ�
	}

	//if ( m_bDebug )                    // ���Ϊ����ģʽ
	//{
	//	ErrorMessageBox( nErrCode );
	//}
	
	return FALSE;                    // �򿪼�ʧ��
}

// ��ע���
BOOL CRegTbOpt::ReadRegTable( LPTSTR lpValueName, LPBYTE lpData )
{
	DWORD  dwType;                   // �������ն������ݵ�����, ��: REG_SZ
	DWORD  dwSize;                   // �������ն��������ݴ�С
	LONG   nErrCode = 0;             // �������

	nErrCode = RegQueryValueEx( m_hKey, lpValueName, NULL, &dwType, lpData, 
		&dwSize );                   // ��ע����ֵ

	if ( ERROR_SUCCESS == nErrCode )
	{
		return TRUE;
	}

	//if ( m_bDebug )                            // ���Ϊ����ģʽ
	//{
	//	ErrorMessageBox( nErrCode );
	//}
	
	return FALSE;
}

// дע���(�ַ���)
BOOL CRegTbOpt::WriteRegTable( LPCTSTR lpValueName, DWORD dwType, CONST BYTE *lpData )
{
	LONG   nErrCode = 0;             // �������
	int    nLen = 0;

	nLen = strlen((const char*)lpData);
	nErrCode = RegSetValueEx( m_hKey, lpValueName, NULL, dwType, 
		lpData, nLen );            // ����ע����ֵ

	if ( ERROR_SUCCESS == nErrCode )
	{
		return TRUE;
	}

	if ( m_bDebug )
	{
		ErrorMessageBox( nErrCode );
	}

	return FALSE;
}

// дע���(����)
BOOL CRegTbOpt::WriteRegTable( LPCTSTR lpValueName, DWORD dwType, int nData )
{
	LONG   nErrCode = 0;             // �������

	nErrCode = RegSetValueEx( m_hKey, lpValueName, NULL, dwType, 
				(CONST BYTE*)&nData, sizeof(int) );            // ����ע����ֵ

	if ( ERROR_SUCCESS == nErrCode )
	{
		return TRUE;
	}

	if ( m_bDebug )
	{
		ErrorMessageBox( nErrCode );
	}

	return FALSE;
}

// �ر�ע���
void CRegTbOpt::CloseRegTable()
{
	if ( m_hKey )
	{
		RegCloseKey( m_hKey );       // �ر�ע���
		m_hKey = NULL;               // ע�վ��ֵ
	}
}

// ������ʽ���󲶻�Ĵ������
void CRegTbOpt::ErrorMessageBox( DWORD dwErrCode )
{
	HLOCAL hLocal = NULL;     // �ڴ����

	// ��ʽ������Ĵ������
	FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER , 
		NULL, dwErrCode, MAKELANGID( LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED ),
		(LPTSTR)&hLocal, 0, NULL );

	if ( hLocal != NULL )
	{
		MessageBox( NULL, (LPCTSTR)LocalLock(hLocal), "ע������", MB_OK | MB_ICONERROR );
		LocalFree( hLocal );
	}
	else
	{
		MessageBox( NULL, "һ��δ֪�Ĵ���", "ע������", MB_OK | MB_ICONERROR );
	}
}

void CRegTbOpt::SetDebugMode( BOOL bDebug )
{
	m_bDebug = bDebug;
}

BOOL CRegTbOpt::RegTbIsOpen()
{
	if ( m_hKey )
	{
		return TRUE;
	}
	return FALSE;
}
