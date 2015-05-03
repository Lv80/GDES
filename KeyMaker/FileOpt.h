//--------------------------------------------------------------------------------//
//                                                                                //
//                         ͷ�ļ���: FileOpt.h                                    //
//                     Դ�����ļ���: FileOpt.cpp                                  //
//                             ����: CFileOpt                                     //
//                             ����: ��װ���ļ��Ĳ���                             //
//                             ����: Ҷ����                                       //
//                             ����: 2006.9.6                                     //
//                           �汾��: v1.00                                        //
//                                                                                //
//   ��ʾ: Ĭ�ϲ�ʹ��Debugģʽ, ���Ҫʹ��Debugģʽ, ��Debug��������TRUE��OK��.   //
//                                                                                //
//--------------------------------------------------------------------------------// 

#if !defined(AFX_FILEOPT_H__3CA90917_1AAB_4221_A2D1_FD9452F26904__INCLUDED_)
#define AFX_FILEOPT_H__3CA90917_1AAB_4221_A2D1_FD9452F26904__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_BUFF 255

class CFileOpt : public CStdioFile 
{
public:
	CFileOpt();
	virtual ~CFileOpt();

public:
	void SetDebugMode( BOOL bDebug );        // �����Ƿ�Ϊ����ģʽ
	void CloseFile();                        // �ر��ļ�
	BOOL isExistFile( LPCTSTR lpFile );      // �ļ����ڷ�����,�����ڷ��ؼ�
	BOOL CreateFile( LPCTSTR lpFile );       // �����ļ�
	BOOL OpenFile( LPCTSTR lpFile );         // �Զ�/д��ʽ���ļ�
	BOOL WriteFile( LPTSTR lpData );         // д�ļ�
	BOOL ReadFile( LPTSTR lpData );          // ���ļ�
	BOOL FilePointerSeek( UINT nMethod, 
		LONG nCurrent = 0 );                 // �ڴ��ļ��������ļ�ָ��λ��

private:
	BOOL     m_bDebug;    // ����ģ��

private:
	void ErrorMessageBox( DWORD dwErrCode );

};

#endif // !defined(AFX_FILEOPT_H__3CA90917_1AAB_4221_A2D1_FD9452F26904__INCLUDED_)
