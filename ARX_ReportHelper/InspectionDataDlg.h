#pragma once
#include "ResultDlg.h"

class InspectionDataDlg : public GasBaseAcesDlg
{
	DECLARE_DYNAMIC(InspectionDataDlg)

public:
	InspectionDataDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~InspectionDataDlg();

// �Ի�������
	enum { IDD = IDD_INSPECTION_DATA_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDwbCheck();
	afx_msg void OnBnClickedOk();

private:
	// ��ɹ��̿���ͼ
	BOOL m_DWB;
	// ���̿���ʱ��
	BOOL m_PST;
	// ����ʱ��
	BOOL m_CT;
	// �쳣�����¼
	BOOL m_AR;
	// ������������
	BOOL m_OID;

private:
	void SetEnableDWB(BOOL isTrue);

};
