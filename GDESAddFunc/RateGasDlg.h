#pragma once
#include "Resource.h"
#include "../ARX_ReportHelper/GasBaseAcesDlg.h"

class RateGasDlg : public GasBaseAcesDlg
{
	DECLARE_DYNAMIC(RateGasDlg)

public:
	RateGasDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RateGasDlg();

// �Ի�������
	enum { IDD = IDD_GAS_RATE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
	// �������˹ӿ����
	CString m_relativeGas;
	// �󾮾�����˹ӿ����
	CString m_absGas;
	CString m_ret;
public:
	afx_msg void OnBnClickedOk();
};
