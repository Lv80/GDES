#pragma once
//#include "Resource.h"
//#include "CListCtrl_DataModel.h"
//#include "config.h"
#include "ReportDataHelper.h"
#include "dlimexp.h"

#include <iostream>
#include <fstream>
using namespace std;
#include "AcFStream.h"

//����������۶Ի������
//ʵ�ֵ���ͼ�����ʾ�Ͷ�ȡ�ļ�����
class ARX_REPORTHELPER_DLLIMPEXP GasBaseAcesDlg : public CDialog
{
	DECLARE_DYNAMIC(GasBaseAcesDlg)

public:
	GasBaseAcesDlg(UINT nIDTemplate,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~GasBaseAcesDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	//virtual BOOL readDataFromFile(const CString& txtName, AcStringArray& datasArray);
	//virtual BOOL WriteDataToFile(const CString& txtName,const AcStringArray& nameArray,const AcStringArray& datasArray);
	
	CString GetAppPathDir();
	CString BuildPath( const CString& dir, const CString& fileName );

	DECLARE_MESSAGE_MAP()

protected:
	HICON m_hIcon;
};
