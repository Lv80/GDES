#pragma once

#include "RcuDataLink.h"

class RcuHelper
{
public:
	//�������е��곡
	static void FindAllRockGates(AcDbObjectIdArray& rock_gates);
	//�������곡������ú��
	static void GetRelatedCoalSurface(const AcDbObjectId& rock_gate, AcDbObjectId& coal_surf);
	//�������곡�������곡
	static void GetRelatedDrillSites(const AcDbObjectId& rock_gate, AcDbObjectIdArray& drill_sites);
	//������ú��������տ�
	static void GetRelatedClosePores(const AcDbObjectId& coal_surf, AcDbObjectIdArray& pores);
	//�������곡�����Ŀ���
	static void GetRelatedOpenPores(const AcDbObjectId& drill_site, AcDbObjectIdArray& pores);
	//ɾ�����곡�������������
	static void ClearRelatedOpenPores(const AcDbObjectId& drill_site);
	//ɾ����ú��������������
	static void ClearRelatedClosePores(const AcDbObjectId& coal_surf);

	//��ú������ȡ����
	static bool ReadCoalSurfaceData(const AcDbObjectId& coal_surf, CoalSurfaceLink& cs_link);
	//���곡��ȡ����
	static bool ReadDrillSiteData(const AcDbObjectId& drill_site, DrillSiteLink& ds_link);
	//�������ȡ����
	static bool ReadPoreData(const AcDbObjectId& pore, PoreLink& po_link);

	//�õ��곡�Լ�����ú�������
	static bool GetRockGateAndCoalSurfDatas(const AcDbObjectId& rock_gate, DrillSiteLink& ds_link, CoalSurfaceLink& cs_link);
	//�õ��곡������
	static bool GetDrillSiteData(const AcDbObjectId& drill_site, DrillSiteLink& ds_link);

	//������ˮƽ��ķ���Ǻ�����
	static void VectorToAngle(const AcGeVector3d& v, double& ang1, double& ang2);
	//����VectorToAngle����
	static void VectorToAngleTest();

	//����ú�������
	static bool CaculCoalSurfParam(DrillSiteLink& ds_link, CoalSurfaceLink& cs_link);
	//�����곡��2������
	//static bool CaculDrillSitePt(DrillSiteLink& ds_link,  const AcGePoint3d& rgInsertPt,AcGePoint3d& insertPt,AcGePoint3d& linkPt);
	//�����곡������������(�������곡�װ��)
	static bool CaculRelativeOpenPorePts(DrillSiteLink& ds_link, AcGePoint3dArray& pts);
	//����ú�������������(������ú��������ĵ�)
	static bool CaculRelativeClosePorePts(CoalSurfaceLink& cs_link, AcGePoint3dArray& pts);

	//�����곡��ú��ͼԪ(rg_link��cs_link�����ݻ���������ͼԪ�������������µ�ͼԪ)
	static bool CreateDrillSite(const AcGePoint3d& pt, DrillSiteLink& ds_link, CoalSurfaceLink& cs_link);
	//�������곡���������ͼԪ(����)
	static bool CreateOpenPores(const AcDbObjectId& drill_site, DrillSiteLink& ds_link);
	//������ú����������ͼԪ(�տ�)
	static bool CreateClosePores(const AcDbObjectId& coal_surf, CoalSurfaceLink& cs_link);

	//�����곡�����޸Ĺ�����ͼԪ(����)
	static bool ModifyDrillSiteRelatedGEs(const AcDbObjectId& drill_site, DrillSiteLink& ds_link);
	//�����곡�����޸Ĺ�����ͼԪ(ú�㡢�곡)
	static bool ModifyRockGateRelatedGEs(const AcDbObjectId& rock_gate, DrillSiteLink& ds_link, CoalSurfaceLink& cs_link);
	//����ú�������޸Ĺ�����ͼԪ(�տ�)
	static bool ModifyCoalSurfRelatedGEs(const AcDbObjectId& coal_surf, CoalSurfaceLink& cs_link);

	//�޸��곡����
	static bool ModifyDrillSitePt(const AcDbObjectId& drill_site, DrillSiteLink& ds_link);
	//��ȡ�곡�Ĳ��������
	static bool GetRockGateInsertPt(const AcDbObjectId& rock_gate, AcGePoint3d& insertPt);
	//��ȡú��Ĳ��������
	static bool GetCoalSurfInsertPt(const AcDbObjectId& coal_surf, AcGePoint3d& insertPt);
	//�����곡ͼԪ��2������
	static bool SetDrillSitePt(const AcDbObjectId& drill_site, const AcGePoint3d& insertPt);
	//��ȡ�곡��2������
	static bool GetDrillSitePt(const AcDbObjectId& drill_site, AcGePoint3d& insertPt);
};