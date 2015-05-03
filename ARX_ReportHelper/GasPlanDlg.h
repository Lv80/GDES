#pragma once

#include "ResultDlg.h"

class GasPlanDlg : public GasBaseAcesDlg
{
	DECLARE_DYNAMIC(GasPlanDlg)

public:
	GasPlanDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~GasPlanDlg();

// �Ի�������
	enum { IDD = IDD_YEARPLAN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();


private:
	HICON m_hIcon;
	//��ɴ�귶Χ�ڹ滮����
	BOOL m_range;
	// ��ɴ�깤��
	BOOL m_SEE;
	// �����ʩ�豸
	BOOL m_EEF;
	// �ʽ�ƻ�
	BOOL m_CP;
	// ���滮���潻��
	BOOL m_CMFA;
	// ���滮������
	BOOL m_CRE;
	// �����
	BOOL m_DEQ;
	// �����˹��ɴ���ú�㷶Χ����Ӧ����Ȳ�������
	BOOL m_APS;
	// ʩ�����顢���ʱ�䡢�����
	BOOL m_TTV;
	// ���ָ�ꡢ�ʽ�ƻ�
	BOOL m_DFP;
	// ��ȳ�ɹ���
	BOOL m_AEP;
	// ��ȳ���豸��ʩ
	BOOL m_YEEF;
	// ��Ȳ��潻��
	BOOL m_YMFA;
	// ���������
	BOOL m_YRE;
};
