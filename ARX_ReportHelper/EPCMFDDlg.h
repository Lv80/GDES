#pragma once
#include "ResultDlg.h"

// EPCMFDDlg �Ի���

class EPCMFDDlg : public GasBaseAcesDlg
{
	DECLARE_DYNAMIC(EPCMFDDlg)

public:
	EPCMFDDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~EPCMFDDlg();

// �Ի�������
	enum { IDD = IDD_EPCMFD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	//��ɴ�깤�շ������
	BOOL m_DDSP;
	// Ϊ��ɴ�����ĸ���̲��֡�������
	BOOL m_DCSEL;
	// ���ȡ��ʽ�ƻ���������ϵ
	BOOL m_SFCR;
	// ʩ���豸����Ҫ����
	BOOL m_CEME;
	// �ɾ�����ʩ�����
	BOOL m_MFCD;
	// ��ײ�����ʩ��Ҫ����׹�����
	BOOL m_DPCRD;
	// ʩ���豸����ȼƻ�
	BOOL m_CES;
	// Ԥ��Ч������֯����
	BOOL m_EROM;
	// ��Ч����˹ʱ��
	BOOL m_ETPG;
	// ��ȫ������ʩ
	BOOL m_SM;
	// �����ײ���ͼ
	BOOL m_BL;

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedDdspCheck();
	afx_msg void OnBnClickedMfcdCheck();
private:
	void SetEnableDDSP(BOOL isTrue);
	void SetEnableMFCD(BOOL isTrue);
};
