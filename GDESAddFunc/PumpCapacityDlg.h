#pragma once
#include "Resource.h"
#include "../ARX_ReportHelper/GasBaseAcesDlg.h"
#include "afxcmn.h"

// PumpCapacityDlg �Ի���

class PumpCapacityDlg : public GasBaseAcesDlg
{
	DECLARE_DYNAMIC(PumpCapacityDlg)

public:
	PumpCapacityDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PumpCapacityDlg();

// �Ի�������
	enum { IDD = IDD_PUMP_ABILITY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	// �������˹ӿ����
	CString m_absGas;
	// �ܻط�����˹Ũ��
	CString m_gasConcentration;
	// ������ܻط����
	CString m_maxQ;
	// ���ش���ѹ
	CString m_localP;
	// ��ɱø���ϵ��
	CString m_surplus;
	// ���ϵͳ����ϵ��
	CString m_workCondiction;
	// ��˹��ɱ�̨��
	CString m_numPump;
	CListCtrl m_pumpListCtrl;
};
