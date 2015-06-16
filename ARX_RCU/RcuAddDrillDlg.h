#pragma once
#include "RcuAcUiBaseDlg.h"
#include "RcuDataLink.h"
#include "afxwin.h"

//�����곡�Ի���
class RcuAddDrillDlg : public RcuAcUiBaseDlg
{
	DECLARE_DYNAMIC(RcuAddDrillDlg)

public:
	RcuAddDrillDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RcuAddDrillDlg();

// �Ի�������
	enum { IDD = IDD_RCU_DRILL_NEW_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	// �곡����
	CString m_name;
	// �곡λ��
	int m_leftOrRight;
	// �곡λ��������
	CComboBox m_locaCombBox;
	// �곡���
	double m_width;
	// �곡�߶�
	double m_height;
	// �곡��ӭͷ�ľ���
	double m_dist;
	// ��ʼ���
	int m_index;

public:
	//�ӶԻ����ж�ȡ����
	void writeToDataLink(DrillSiteLink& ds_link);

public:
	afx_msg void OnBnClickedOk();
};
