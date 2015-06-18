#pragma once
#include "RcuAcUiBaseDlg.h"
#include "RcuDataLink.h"

// �곡��ƶԻ���
class RcuEditDrillDlg : public RcuAcUiBaseDlg
{
	DECLARE_DYNAMIC(RcuEditDrillDlg)

public:
	RcuEditDrillDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RcuEditDrillDlg();

// �Ի�������
	enum { IDD = IDD_RCU_DRILL_EDIT_DIALOG };

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
	//��ȡ���ݵ��Ի���
	void readFromDataLink(DrillSiteLink& ds_link);

	//ʯ��ͼԪid
	AcDbObjectId m_rock_gate;

	afx_msg void OnBnClickedOk();

};
