#pragma once
#include "afxcmn.h"
#include "Resource.h"

// MineMainDescipDlg �Ի���

class  MineMainDescipDlg : public CDialog
{
	DECLARE_DYNAMIC(MineMainDescipDlg)

public:
	MineMainDescipDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MineMainDescipDlg();

	// �Ի�������
	enum { IDD = IDD_MINEDESC_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

public:
	CRichEditCtrl m_EditCtrl;
	CRichEditCtrl m_numEditCtrl;
};
