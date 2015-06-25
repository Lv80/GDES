#pragma once
#include "RcuAcUiBaseDlg.h"
#include "RcuDataLink.h"

// �곡��ƶԻ���
class RcuEditDrillSiteDlg : public RcuAcUiBaseDlg
{
	DECLARE_DYNAMIC(RcuEditDrillSiteDlg)

public:
	RcuEditDrillSiteDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RcuEditDrillSiteDlg();

// �Ի�������
	enum { IDD = IDD_RCU_DRILL_SITE_EDIT_DIALOG };

public:
	//ʯ��ͼԪid
	AcDbObjectId m_drill_site;
	//��ȡ���ݵ��Ի���
	void readFromDataLink(DrillSiteLink& ds_link);
	//�ӶԻ����ж�ȡ����
	void writeToDataLink(DrillSiteLink& ds_link);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// �곡����
	CString m_name;
	// �곡λ��
	int m_pos;
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
	//�׾�
	double m_pore_size;

public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
