#pragma once
#include "Resource.h"
#include "../ARX_ReportHelper/GasBaseAcesDlg.h"
#include "CGridListCtrlEx/CGridListCtrlGroups.h"
#include "CListCtrl_DataModel.h"

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
	// ��ɱø���ϵ��
	CString m_surplus;
	// ���ϵͳ����ϵ��
	CString m_workCondiction;
	// ��˹��ɱ�̨��
	CString m_numPump;
	// ������
	CString m_ret;

	CGridListCtrlGroups m_pumpListCtrl;
	CListCtrl_DataModel m_dataModel;
	vector<CListCtrl_DataRecord> m_records;

public:
	afx_msg void OnBnClickedOk();

private:
	void OnInitList();
	bool Caculate(const AcStringArray& baseData,const AcStringArray& pumpData,CString& strRet);
public:
	afx_msg void OnEnKillfocusPumpNumEdit();
};
