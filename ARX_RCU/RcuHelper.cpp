#include "StdAfx.h"
#include "Rcu.h"
#include "RcuDataLink.h"
#include "SwitchHelper.h"
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

void RcuHelper::GetRelatedCoalSurface(const AcDbObjectId& rock_gate, AcDbObjectId& coal_surf)
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

void RcuHelper::GetRelatedDrillSites(const AcDbObjectId& rock_gate, AcDbObjectIdArray& drill_sites)
{
	//�������е��곡ͼԪ
	AcDbObjectIdArray tags;
	ArxDataTool::GetEntsByType(_T("DrillSite"), tags, true);
	if(tags.isEmpty()) return;

	//�����곡ͼԪ����������
	AcDbObjectIdArray hosts;
	DrawHelper::GetHosts(tags, hosts);
	if(hosts.length() != tags.length()) return;

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

void RcuHelper::GetRelatedClosePores(const AcDbObjectId& coal_surf, AcDbObjectIdArray& pores)
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

void RcuHelper::GetRelatedOpenPores(const AcDbObjectId& drill_site, AcDbObjectIdArray& pores)
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

bool RcuHelper::ReadRockGateData(const AcDbObjectId& rock_gate, RockGateLink& rg_link)
{
	if(rock_gate.isNull()) return false;

	rg_link.setDataSource(rock_gate);
	return rg_link.updateData(false);
}

bool RcuHelper::GetRockGateAndCoalSurfDatas(const AcDbObjectId& rock_gate, RockGateLink& rg_link, CoalSurfaceLink& cs_link)
{
	//��ȡʯ�Ź������������ݲ���䵽�Ի�����
	if(!RcuHelper::ReadRockGateData(rock_gate, rg_link)) return false;

	//����ʯ�Ź�����ú��
	AcDbObjectId coal_surf;
	RcuHelper::GetRelatedCoalSurface(rock_gate, coal_surf);
	if(coal_surf.isNull()) return false;

	//��ȡú�������
	if(!RcuHelper::ReadCoalSurfaceData(coal_surf, cs_link))	return false;
	
	return true;
}

bool RcuHelper::GetDrillSiteData(const AcDbObjectId& drill_site, DrillSiteLink& ds_link)
{
	//��ȡ�곡����
	return RcuHelper::ReadDrillSiteData(drill_site, ds_link);
}

bool RcuHelper::ReadCoalSurfaceData(const AcDbObjectId& coal_surf, CoalSurfaceLink& cs_link)
{
	if(coal_surf.isNull()) return false;

	cs_link.setDataSource(coal_surf);
	return cs_link.updateData(false);
}

bool RcuHelper::ReadDrillSiteData(const AcDbObjectId& drill_site, DrillSiteLink& ds_link)
{
	if(drill_site.isNull()) return false;

	ds_link.setDataSource(drill_site);
	return ds_link.updateData(false);
}

bool RcuHelper::ReadPoreData(const AcDbObjectId& pore, PoreLink& po_link)
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

void RcuHelper::VectorToAngleTest()
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

bool RcuHelper::CaculCoalSurfParam(const RockGateLink& rg_link,CoalSurfaceLink& cs_link)
{
	AcGePoint3d orign;
	ArxUtilHelper::StringToPoint3d(rg_link.m_pt,orign);
	Rcu rcu;
	rcu.setOrigin(orign);
	rcu.setRockGateParams(rg_link.m_dist,rg_link.m_top,rg_link.m_bottom,rg_link.m_left,rg_link.m_right);
	rcu.setTunnelParams(rg_link.m_height,rg_link.m_width,rg_link.m_width);
	//�ڶ���������ʯ��������ú������ļн�
	//���ǽ�������ʱû�У����Կ���90�ȵ�
	double angle = DegToRad(cs_link.m_angle);
	rcu.setCoalParams(angle,PI*0.5,cs_link.m_thick);
	double w,h;
	rcu.drillExtent(w,h);
	cs_link.m_width = w;
	cs_link.m_height = h;
	acutPrintf(_T("\n����ʱ->���:%.4lf\t�߶�:%.4lf\n"),cs_link.m_width,cs_link.m_height);
	return true;
}

bool RcuHelper::GetRockGateInsertPt( const AcDbObjectId& rock_gate, AcGePoint3d& insertPt )
{
	AcTransaction* pTrans = actrTransactionManager->startTransaction();
	if( pTrans == 0 ) return false;

	AcDbObject* pObj;
	if( Acad::eOk != pTrans->getObject( pObj, rock_gate, AcDb::kForWrite ) )
	{
		actrTransactionManager->abortTransaction();
		return false;
	}

	RockGate* pRG = RockGate::cast( pObj );
	if(pRG == 0)
	{
		actrTransactionManager->abortTransaction();
		return false;
	}

	insertPt = pRG->getInsertPt();

	actrTransactionManager->endTransaction();
	return true;
}

bool RcuHelper::CaculDrillSitePt(const DrillSiteLink& ds_link,const RockGateLink& rg_link, const AcGePoint3d& rgInsertPt, AcGePoint3d& insertPt, AcGePoint3d& linkPt)
{
	//���
	if(0 == ds_link.m_leftOrRight)
	{
		insertPt.x = rgInsertPt.x - rg_link.m_width / 2;
		linkPt.x = rgInsertPt.x - rg_link.m_width / 2 - 2 * ds_link.m_dist;
	}

	//�Ұ�
	else if(1 == ds_link.m_leftOrRight)
	{
		insertPt.x = rgInsertPt.x + rg_link.m_width / 2;
		linkPt.x = rgInsertPt.x + rg_link.m_width / 2 + 2 * ds_link.m_dist;
	}

	else return false;

	insertPt.y = rgInsertPt.y - ds_link.m_dist;
	insertPt.z = rgInsertPt.z;
	linkPt.y = rgInsertPt.y - ds_link.m_dist;
	linkPt.z = rgInsertPt.z;
	return true;
}

bool RcuHelper::SetDrillSitePt(const AcDbObjectId& drill_site, const AcGePoint3d& insertPt, const AcGePoint3d& linkPt)
{
	AcTransaction* pTrans = actrTransactionManager->startTransaction();
	if( pTrans == 0 ) return false;

	AcDbObject* pObj;
	if( Acad::eOk != pTrans->getObject( pObj, drill_site, AcDb::kForWrite ) )
	{
		actrTransactionManager->abortTransaction();
		return false;
	}

	DrillSite* pDS = DrillSite::cast( pObj );
	if(pDS == 0)
	{
		actrTransactionManager->abortTransaction();
		return false;
	}

	pDS->setInsertPt(insertPt);
	pDS->setLinkPt(linkPt);

	actrTransactionManager->endTransaction();
	return true;
}

bool RcuHelper::CreateRockGate(const AcGePoint3d& pt, RockGateLink& rg_link, CoalSurfaceLink& cs_link)
{
	DocumentLockSwitch lock_switch;

	//�½�ʯ�Ų����ò��������
	RockGate* pRG = new RockGate();
	pRG->setInsertPt(pt);

	CoalSurface* pCS = new CoalSurface();
	pCS->setInsertPt(AcGePoint3d(pt.x, pt.y+500, pt.z));

	//���ʯ�ŵ�cadͼ�����ݿ�
	if(!ArxUtilHelper::PostToModelSpace(pRG))
	{
		delete pRG; pRG = 0;
		return  false;
	}
	
	//����ú�����
	RcuHelper::CaculCoalSurfParam(rg_link,cs_link);
	//acutPrintf(_T("\n����֮��->���:%.4lf\t�߶�:%.4lf\n"),cs_link.m_width,cs_link.m_height);

	//ú�������ʯ��
	pCS->setRelatedGE(pRG->objectId());
	//���ú�㵽cadͼ�����ݿ�
	if(!ArxUtilHelper::PostToModelSpace(pCS))
	{
		delete pCS; pCS = 0;
		//ú���ύʧ��,��ɾ������ӵ�ʯ��
		ArxEntityHelper::EraseObject(pRG->objectId(), true);
		return false;
	}

	//ͨ��DataLink�޸�ʯ�ź�ú�������
	rg_link.setDataSource(pRG->objectId());
	rg_link.updateData(true);
	cs_link.setDataSource(pCS->objectId());
	cs_link.updateData(true);

	return true;
}

bool RcuHelper::CreateDrillSite(const AcDbObjectId& rock_gate, DrillSiteLink& ds_link)
{
	RockGateLink rg_link;
	if(!RcuHelper::ReadRockGateData(rock_gate, rg_link))
	{
		AfxMessageBox(_T("��ȡʯ�����ݷ�������!"));
		return false;
	}

	//�����곡�����������������
	AcGePoint3d insertPt,linkPt,rgInsertPt;
	RcuHelper::GetRockGateInsertPt(rock_gate,rgInsertPt);
	if(!RcuHelper::CaculDrillSitePt(ds_link,rg_link,rgInsertPt,insertPt,linkPt)) 
	{
		AfxMessageBox(_T("�곡λ�����ݴ���!"));
		return false;
	}

	//�½��곡�����ò��������
	DrillSite* pDS = new DrillSite();
	pDS->setInsertPt(insertPt);
	pDS->setLinkPt(linkPt);
	pDS->setRelatedGE(rock_gate);

	//����곡��cadͼ�����ݿ�
	if(!ArxUtilHelper::PostToModelSpace(pDS))
	{
		delete pDS; pDS = 0;
		return false;
	}

	//����ͼԪ������
	ds_link.setDataSource(pDS->objectId());
	ds_link.updateData(true);

	return true;
}

bool RcuHelper::ModifyDrillSiteParam(const AcDbObjectId& drill_site, DrillSiteLink& ds_link)
{
	if(drill_site.isNull()) return false;

	AcDbObjectId rock_gate;
	if(!DrawHelper::GetHostGE(drill_site, rock_gate)) return false;

	//��ȡʯ�ŵ�����
	RockGateLink rg_link;
	if(!RcuHelper::ReadRockGateData(rock_gate, rg_link)) return false;

	//��ȡʯ�ŵĲ��������
	AcGePoint3d pt;
	if(!RcuHelper::GetRockGateInsertPt(rock_gate, pt)) return false;

	AcGePoint3d insertPt, linkPt;
	if(!RcuHelper::CaculDrillSitePt(ds_link, rg_link, pt, insertPt, linkPt)) return false;

	//�޸��곡ͼԪ�ļ��ε�����
	return RcuHelper::SetDrillSitePt(drill_site, insertPt, linkPt);
}
