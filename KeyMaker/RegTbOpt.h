//--------------------------------------------------------------------------------//
//                                                                                //
//                         ͷ�ļ���: RegTbOpt.h                                   //
//                     Դ�����ļ���: RegTbOpt.cpp                                 //
//                             ����: CRegTbOpt                                    //
//                             ����: ��װ��ע���Ĳ���                           //
//                             ����: Ҷ����                                       //
//                             ����: 2006.9.6                                     //
//                           �汾��: v1.00                                        //
//                                                                                //
//   ��ʾ: Ĭ�ϲ�ʹ��Debugģʽ, ���Ҫʹ��Debugģʽ, ��Debug��������TRUE��OK��.   //
//                                                                                //
//--------------------------------------------------------------------------------// 

#if !defined(AFX_REGTBOPT_H__7C393DE1_7C0A_4736_BF2D_C93111445B37__INCLUDED_)
#define AFX_REGTBOPT_H__7C393DE1_7C0A_4736_BF2D_C93111445B37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRegTbOpt  
{
public:
	CRegTbOpt();
	virtual ~CRegTbOpt();

public:
	void SetDebugMode( BOOL bDebug );                         // ����Debugģʽ

	BOOL CreateRegKey( HKEY hKey, LPCTSTR lpKeyName );        // �����Ӽ�
	
	BOOL OpenRegTable( HKEY hKey, LPCSTR lpSubKey );          // ��ָ�����Ӽ�

	BOOL ReadRegTable( LPTSTR lpValueName, LPBYTE lpData );   // ��ע���
	
	BOOL WriteRegTable( LPCTSTR lpValueName, DWORD dwType, 
		CONST BYTE *lpData );                                 // дע���

	void CloseRegTable();                                     // �ر�ע���

	BOOL RegTbIsOpen();                                       // �ж�ע����Ƿ��

// ˽�г�Ա����
private:
	HKEY   m_hKey;         // ���ľ��
	BOOL   m_bDebug;       // ����ΪDebugģʽ

// ˽�г�Ա����
private:
	void ErrorMessageBox( DWORD dwErrCode );    // ������Ϣ����
	

};

#endif // !defined(AFX_REGTBOPT_H__7C393DE1_7C0A_4736_BF2D_C93111445B37__INCLUDED_)
