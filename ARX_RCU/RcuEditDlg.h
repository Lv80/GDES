#pragma once

#include "acui.h"
#include "resource.h"

#include "RcuDataLink.h"

//ʯ�Ž�ú�༭�Ի���(��"ʯ�����"�Ҽ��˵��е��øöԻ���)
class RcuEditDlg : public CAcUiDialog
{
	DECLARE_DYNAMIC(RcuEditDlg)

public:
	RcuEditDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RcuEditDlg();

// �Ի�������
	enum { IDD = IDD_RCU_EDIT_DLG };

public:
	//ʯ��ͼԪid
	AcDbObjectId m_rock_gate;
	//��ʯ���ж�ȡ���ݸ��Ի���
	bool readDataFromRockGate(const AcDbObjectId& rock_gate);
	//�ӶԻ�������ȡ���ݲ����浽ʯ��ͼԪ��
	bool writeDataToRockGate(const AcDbObjectId& rock_gate);

protected:
	//�Ի�����ʯ��ͼԪ֮�佻������
	void exchangeRockGateData(RockGateLink& rg_link, bool save);
	//�Ի�����ú��ͼԪ֮�佻������
	void exchangeCoalSurfaceData(CoalSurfaceLink& cs_link, bool save);
	//�Ի������곡ͼԪ֮�佻������
	void exchangeDrillSiteData(DrillSiteLink& ds_link, bool save);
	//��listctrl�в���id����drill_site����
	int findDrillSiteRow(const AcDbObjectId& drill_site);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	double m_x;
	double m_y;
	double m_z;
	double m_length;
	double m_width;
	double m_height;
	double m_left;
	double m_right;
	double m_top;
	double m_bottom;
	double m_radius;
	double m_thick;
	double m_angle;
	double m_dist;
	CListCtrl m_list;

	//"ȷ��"��ť��Ϣ
	afx_msg void OnBnClickedOk();
	//listrctrl˫����Ϣ
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	//listrctrl�Ҽ���Ϣ
	afx_msg void OnNMRclickList2(NMHDR *pNMHDR, LRESULT *pResult);

	//�˵�����Ϣ��Ӧ
	afx_msg void OnAddCommand();
	afx_msg void OnDeleteCommand();
	afx_msg void OnModifyCommand();
	afx_msg void OnHilightCommand();

	//�麯������
	virtual BOOL OnInitDialog();
};
