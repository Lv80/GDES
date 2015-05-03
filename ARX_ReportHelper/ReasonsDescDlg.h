#pragma once

#include "Resource.h"

class ReasonsDescDlg : public CDialog
{
	DECLARE_DYNAMIC(ReasonsDescDlg)

public:
	ReasonsDescDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ReasonsDescDlg();

// �Ի�������
	enum { IDD = IDD_REASONS_DESC_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	// ��������
	CString m_reasonsDesc;
	BOOL m_yesOrNo;
	afx_msg void OnBnClickedOk();
private:
	HICON m_hIcon;
};
