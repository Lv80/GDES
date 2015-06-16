#include "StdAfx.h"
#include "RcuHelper.h"

#include "../ArxHelper/HelperClass.h"
#include "../MineGE/HelperClass.h"

#include "../DefGE/RcuGE.h"
#include "../DefGE/Pore.h"
#include "../DefGE/DrillSite.h"
#include "../DefGE/RockGate.h"
#include "../DefGE/CoalSurface.h"

void RcuHelper::FindAllRockGates(AcDbObjectIdArray& rock_gates)
{
	ArxDataTool::GetEntsByType(_T("RockGate"), rock_gates, true);
}

void RcuHelper::GetCoalSurface(const AcDbObjectId& rock_gate, AcDbObjectId& coal_surf)
{
	//�������е�ú��ͼԪ
	AcDbObjectIdArray tags;
	ArxDataTool::GetEntsByType(_T("CoalSurface"), tags, true);

	//����ú��ͼԪ����������
	AcDbObjectIdArray hosts;
	DrawHelper::GetHosts(tags, hosts);

	//ƥ��
	int n = hosts.length();
	for(int i=0;i<n;i++)
	{
		if(hosts[i] == rock_gate)
		{
			coal_surf = tags[i];
			break;
		}
	}
}

void RcuHelper::GetDrillSites(const AcDbObjectId& rock_gate, AcDbObjectIdArray& drill_sites)
{
	//�������е��곡ͼԪ
	AcDbObjectIdArray tags;
	ArxDataTool::GetEntsByType(_T("DrillSite"), tags, true);

	//�����곡ͼԪ����������
	AcDbObjectIdArray hosts;
	DrawHelper::GetHosts(tags, hosts);

	//ƥ��
	int n = hosts.length();
	for(int i=0;i<n;i++)
	{
		if(hosts[i] == rock_gate)
		{
			drill_sites.append(tags[i]);
		}
	}
}

void RcuHelper::GetAllClosePores(const AcDbObjectId& coal_surf, AcDbObjectIdArray& pores)
{
	//�������е����ͼԪ
	AcDbObjectIdArray tags;
	ArxDataTool::GetEntsByType(_T("Pore"), tags, true);

	//�������ͼԪ����������
	AcDbObjectIdArray hosts;
	DrawHelper::GetHosts(tags, hosts);

	//ƥ��
	int n = hosts.length();
	for(int i=0;i<n;i++)
	{
		if(hosts[i] == coal_surf)
		{
			pores.append(tags[i]);
		}
	}
}

void RcuHelper::GetAllOpenPores(const AcDbObjectId& drill_site, AcDbObjectIdArray& pores)
{
	//�������е����ͼԪ
	AcDbObjectIdArray tags;
	ArxDataTool::GetEntsByType(_T("Pore"), tags, true);

	//�������ͼԪ����������
	AcDbObjectIdArray hosts;
	DrawHelper::GetHosts(tags, hosts);

	//ƥ��
	int n = hosts.length();
	for(int i=0;i<n;i++)
	{
		if(hosts[i] == drill_site)
		{
			pores.append(tags[i]);
		}
	}
}

bool RcuHelper::GetRockGateData(const AcDbObjectId& rock_gate, RockGateLink& rg_link)
{
	if(rock_gate.isNull()) return false;

	rg_link.setDataSource(rock_gate);
	rg_link.updateData(false);
	return true;
}

bool RcuHelper::GetCoalSurfaceData(const AcDbObjectId& coal_surf, CoalSurfaceLink& cs_link)
{
	if(coal_surf.isNull()) return false;

	cs_link.setDataSource(coal_surf);
	cs_link.updateData(false);
	return true;
}

bool RcuHelper::GetDrillSiteData(const AcDbObjectId& drill_site, DrillSiteLink& ds_link)
{
	if(drill_site.isNull()) return false;

	ds_link.setDataSource(drill_site);
	ds_link.updateData(false);
	return true;
}

bool RcuHelper::GetPoreData(const AcDbObjectId& pore, PoreLink& po_link)
{
	if(pore.isNull()) return false;

	po_link.setDataSource(pore);
	po_link.updateData(false);
	return true;
}

void RcuHelper::VectorToAngle(const AcGeVector3d& v, double& ang1, double& ang2)
{
	//������xoyƽ���ϵ�ͶӰ
	AcGeVector3d u = v.orthoProject(AcGeVector3d::kZAxis);
	acutPrintf(_T("\nͶӰֵ:x=%.3f, y=%.3f z=%.3f"), u.x, u.y, u.z);
	ang1 = u.angleTo(AcGeVector3d::kXAxis/*, AcGeVector3d::kZAxis*/);
	ang2 = u.angleTo(v);
}

void RcuHelper::VectorToAngle()
{
	AcGeVector3d v(1,1,1);
	double ang1, ang2;
	RcuHelper::VectorToAngle(v, ang1, ang2);
	acutPrintf(_T("\n����:(%.3f, %.3f, %.3f)"), v.x, v.y, v.z);
	acutPrintf(_T("\n����-->�����1:%f  ���ǣ�%f"), ang1, ang2);
	acutPrintf(_T("\n�Ƕ�-->�����1:%f  ���ǣ�%f"), ang1*57.295, ang2*57.295);

	AcGeVector3d v1(1,0,0);
	RcuHelper::VectorToAngle(v1, ang1, ang2);
	acutPrintf(_T("\n����:(%.3f, %.3f, %.3f)"), v1.x, v1.y, v1.z);
	acutPrintf(_T("\n����-->�����1:%f  ���ǣ�%f"), ang1, ang2);
	acutPrintf(_T("\n�Ƕ�-->�����1:%f  ���ǣ�%f"), ang1*57.295, ang2*57.295);

	AcGeVector3d v2(-1,-1,1);
	RcuHelper::VectorToAngle(v2, ang1, ang2);
	acutPrintf(_T("\n����:(%.3f, %.3f, %.3f)"), v2.x, v2.y, v2.z);
	acutPrintf(_T("\n����-->�����1:%f  ���ǣ�%f"), ang1, ang2);
	acutPrintf(_T("\n�Ƕ�-->�����1:%f  ���ǣ�%f"), ang1*57.295, ang2*57.295);
}