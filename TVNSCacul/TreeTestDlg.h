#pragma once
#include "afxcmn.h"
#include "Resource.h"

// TreeTestDlg �Ի���

class TreeTestDlg : public CDialog
{
	DECLARE_DYNAMIC(TreeTestDlg)

public:
	TreeTestDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TreeTestDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_treeCtrl;
	BOOL m_result;
};
