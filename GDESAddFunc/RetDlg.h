#pragma once
#include "Resource.h"
#include "../ARX_ReportHelper/GasBaseAcesDlg.h"

class RetDlg : public GasBaseAcesDlg
{
	DECLARE_DYNAMIC(RetDlg)

public:
	RetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RetDlg();

// �Ի�������
	enum { IDD = IDD_RET_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
	CString m_pumpRet;
	CString m_sysRet;
	CString m_yearRet;
	CString m_preRet;
	CString m_rateRet;
	CString m_ret;
private:
	void GetRet();
public:
	afx_msg void OnBnClickedOk();
};
