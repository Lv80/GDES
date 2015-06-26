#pragma once

#include "RcuAcUiBaseDlg.h"

#include "RcuDataLink.h"

//ʯ�Ž�ú�༭�Ի���(��"ʯ�����"�Ҽ��˵��е��øöԻ���)
class RcuEditRockGateDlg : public RcuAcUiBaseDlg
{
	DECLARE_DYNAMIC(RcuEditRockGateDlg)

public:
	RcuEditRockGateDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RcuEditRockGateDlg();

// �Ի�������
	enum { IDD = IDD_RCU_ROCK_GATE_EDIT_DLG };

public:
	//ʯ��ͼԪid
	AcDbObjectId m_rock_gate;
	//��/д����
	void readFromDataLink( DrillSiteLink& ds_link, CoalSurfaceLink& cs_link);
	void writeToDataLink( DrillSiteLink& ds_link, CoalSurfaceLink& cs_link);

private:
	//�Ի�����ʯ��ͼԪ֮�佻������
	void exchangeRockGateData( DrillSiteLink& ds_link, bool save);
	//�Ի�����ú��ͼԪ֮�佻������
	void exchangeCoalSurfaceData(CoalSurfaceLink& cs_link, bool save);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	double m_x;
	double m_y;
	double m_z;
	double m_width;
	double m_height;
	double m_left;
	double m_right;
	double m_top;
	double m_bottom;
	double m_gas_radius;
	double m_thick;
	double m_angle;
	double m_dist;

	//"ȷ��"��ť��Ϣ
	afx_msg void OnBnClickedOk();

	//�麯������
	virtual BOOL OnInitDialog();
};
