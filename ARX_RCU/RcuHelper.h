#pragma once

#include "RcuDataLink.h"

class RcuHelper
{
public:
	//�������е�ʯ��
	static void FindAllRockGates(AcDbObjectIdArray& rock_gates);
	//������ʯ�Ź�����ú��
	static void GetRelatedCoalSurface(const AcDbObjectId& rock_gate, AcDbObjectId& coal_surf);
	//������ʯ�Ź������곡
	static void GetRelatedDrillSites(const AcDbObjectId& rock_gate, AcDbObjectIdArray& drill_sites);
	//������ú��������տ�
	static void GetRelatedClosePores(const AcDbObjectId& coal_surf, AcDbObjectIdArray& pores);
	//�������곡�����Ŀ���
	static void GetRelatedOpenPores(const AcDbObjectId& drill_site, AcDbObjectIdArray& pores);

	//��ʯ������ȡ����
	static bool ReadRockGateData(const AcDbObjectId& rock_gate, RockGateLink& rg_link);
	//��ú������ȡ����
	static bool ReadCoalSurfaceData(const AcDbObjectId& coal_surf, CoalSurfaceLink& cs_link);
	//���곡��ȡ����
	static bool ReadDrillSiteData(const AcDbObjectId& drill_site, DrillSiteLink& ds_link);
	//�������ȡ����
	static bool ReadPoreData(const AcDbObjectId& pore, PoreLink& po_link);

	//�õ�ʯ���Լ�����ú�������
	static bool GetRockGateAndCoalSurfDatas(const AcDbObjectId& rock_gate, RockGateLink& rg_link, CoalSurfaceLink& cs_link);
	//�õ��곡������
	static bool GetDrillSiteData(const AcDbObjectId& drill_site, DrillSiteLink& ds_link);

	//������ˮƽ��ķ���Ǻ�����
	static void VectorToAngle(const AcGeVector3d& v, double& ang1, double& ang2);
	//����VectorToAngle����
	static void VectorToAngleTest();

	//����ú�������
	static bool CaculCoalSurfParam(const RockGateLink& rg_link,CoalSurfaceLink& cs_link);
	//��ȡʯ�ŵļ��β��������
	static bool GetRockGateInsertPt(const AcDbObjectId& rock_gate, AcGePoint3d& insertPt);
	//�����곡��2������
	static bool CaculDrillSitePt(const DrillSiteLink& ds_link,const RockGateLink& rg_link,const AcGePoint3d& rgInsertPt,AcGePoint3d& insertPt,AcGePoint3d& linkPt);
	//�����곡ͼԪ��2������
	static bool SetDrillSitePt(const AcDbObjectId& drill_site, const AcGePoint3d& insertPt, const AcGePoint3d& linkPt);

	//����ʯ�ź�ú��ͼԪ(rg_link��cs_link�����ݻ���������ͼԪ�������������µ�ͼԪ)
	static bool CreateRockGate(const AcGePoint3d& pt, RockGateLink& rg_link, CoalSurfaceLink& cs_link);
	//�����곡ͼԪ(��ʯ�Ź���)
	static bool CreateDrillSite(const AcDbObjectId& rock_gate, DrillSiteLink& ds_link);
	//�޸��곡����
	static bool ModifyDrillSiteParam(const AcDbObjectId& drill_site, DrillSiteLink& ds_link);
};