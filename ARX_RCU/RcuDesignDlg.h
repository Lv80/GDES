#pragma once

#include "acui.h"
#include "resource.h"

// RcuDesignDlg �Ի���

class RcuDesignDlg : public CAcUiDialog
{
	DECLARE_DYNAMIC(RcuDesignDlg)

public:
	RcuDesignDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RcuDesignDlg();

// �Ի�������
	enum { IDD = IDD_RCU_DESIGN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_rcuList;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnHdnItemdblclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
};
