#pragma once

#include "RcuDataLink.h"

class RcuHelper
{
public:
	//�������е�ʯ��
	static void FindAllRockGates(AcDbObjectIdArray& rock_gates);
	//������ʯ�Ź�����ú��
	static void GetCoalSurface(const AcDbObjectId& rock_gate, AcDbObjectId& coal_surf);
	//������ʯ�Ź������곡
	static void GetDrillSites(const AcDbObjectId& rock_gate, AcDbObjectIdArray& drill_sites);
	//������ú��������տ�
	static void GetAllClosePores(const AcDbObjectId& coal_surf, AcDbObjectIdArray& pores);
	//�������곡�����Ŀ���
	static void GetAllOpenPores(const AcDbObjectId& drill_site, AcDbObjectIdArray& pores);

	//��ʯ������ȡ����
	static bool GetRockGateData(const AcDbObjectId& rock_gate, RockGateLink& rg_link);
	//��ú������ȡ����
	static bool GetCoalSurfaceData(const AcDbObjectId& coal_surf, CoalSurfaceLink& cs_link);
	//���곡��ȡ����
	static bool GetDrillSiteData(const AcDbObjectId& drill_site, DrillSiteLink& ds_link);
	//�������ȡ����
	static bool GetPoreData(const AcDbObjectId& pore, PoreLink& po_link);
};
