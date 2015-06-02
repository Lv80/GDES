#pragma once
#include "Resource.h"
#include "../ARX_ReportHelper/GasBaseAcesDlg.h"
#include "CGridListCtrlEx/CGridListCtrlGroups.h"
#include "GasCapacity_DataModel.h"

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

private:
	// �������˹ӿ����
	CString m_absGas;
	// �ܻط�����˹Ũ��
	CString m_gasConcentration;
	// ������ܻط����
	CString m_maxQ;
	// ���ش���ѹ
	CString m_localP;
	// ���ϵͳ����ϵ��
	CString m_workCondiction;
	// ��˹��ɱ�̨��
	CString m_numPump;
	// ������
	CString m_pumpRet;
	CString m_sysRet;

	CGridListCtrlGroups m_pumpListCtrl;
	GasCapacity_DataModel m_dataModel;
	vector<GasCapacity_DataRecord> m_records;

public:
	afx_msg void OnBnClickedOk();

private:
	void OnInitList();
public:
	afx_msg void OnEnKillfocusPumpNumEdit();
};
