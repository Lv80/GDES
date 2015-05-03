#pragma once
#include "Resource.h"

// CheakFanDlg �Ի���

class CheakFanDlg : public CDialog
{
	DECLARE_DYNAMIC(CheakFanDlg)

public:
	CheakFanDlg(CWnd* pParent = NULL,AcDbObjectId fanId = NULL);   // ��׼���캯��
	virtual ~CheakFanDlg();

// �Ի�������
	enum { IDD = IDD_FAN_ENSUR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CString m_fantype;
	CString m_minQ;
	CString m_maxQ;
	CString m_minH;
	CString m_maxH;

	CString m_thearyQ;
	CString m_thearyH;
	
	AcDbObjectId m_fanId;
public:
	void readPropertyData();
	void writePropertyData();

	BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
