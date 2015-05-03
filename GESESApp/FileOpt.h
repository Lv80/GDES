// FileOpt.h: interface for the CFileOpt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEOPT_H__B3894791_C188_4455_A0DB_A911F67D3F32__INCLUDED_)
#define AFX_FILEOPT_H__B3894791_C188_4455_A0DB_A911F67D3F32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define MAX_BUFF 255

#include <afx.h>
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

};;

#endif // !defined(AFX_FILEOPT_H__B3894791_C188_4455_A0DB_A911F67D3F32__INCLUDED_)
