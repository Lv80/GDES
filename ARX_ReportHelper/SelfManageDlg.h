#pragma once
#include "ResultDlg.h"

// SelfManageDlg �Ի���

class SelfManageDlg : public GasBaseAcesDlg
{
	DECLARE_DYNAMIC(SelfManageDlg)

public:
	SelfManageDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SelfManageDlg();

// �Ի�������
	enum { IDD = IDD_SELFMANAGE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
private:
	// ��˹��ɴ�����۹�����ϵ
	BOOL m_GDES;
	// ��˹��ɴ������ϸ��
	BOOL m_GDJR;
	// ��˹��ɹ���Ϳ��˽����ƶ�
	BOOL m_GDMAR;
	// ��ɹ��̼�������ƶ�
	BOOL m_DPIA;
	// �ȳ��������ƶ�
	BOOL m_AFDRM;
	// �������������ƶ�
	BOOL m_TFMS;
};
