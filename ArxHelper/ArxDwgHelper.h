#pragma once

#include "dlimexp.h"

/**
* dwg���ݿ⸨��������.
*/
class ARXHELPER_DLLIMPEXP ArxDwgHelper
{
public:
	//����dwg�ļ�
	static bool InsertDwg( const CString& dwgFilePath);

	//����ͼ��
	static void UpdateDwg();

	//��ȡģ������·��
	static CString GetAppPathDir(HINSTANCE hInstance);

	//����·��
	static CString BuildPath( const CString& dir, const CString& fileName );
};
