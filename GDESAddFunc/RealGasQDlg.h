#pragma once
#include "Resource.h"
#include "../ARX_ReportHelper/GasBaseAcesDlg.h"
#include "afxwin.h"

class RealGasQDlg : public GasBaseAcesDlg
{
	DECLARE_DYNAMIC(RealGasQDlg)

public:
	RealGasQDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RealGasQDlg();

// �Ի�������
	enum { IDD = IDD_YEAR_GASQ_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

private:
	// �������ʵ�ʳ����˹��
	CString m_lastGas;
	// Ԥ����������˹�������ú��Ӧ����˹��ú����
	CString m_maxGas;
	// ���ܻط�����˹Ũ��
	CString m_gasCon;
	// ������ܻط����
	CString m_maxQ;
	// �󾮳�ǰ���ϵ��
	CString m_k;
	// ������
	CString m_yearRet;
};
