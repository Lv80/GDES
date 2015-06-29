#include "StdAfx.h"
#include "Rcu2.h"
#include "RcuDataLink.h"
#include "SwitchHelper.h"
#include "RcuHelper.h"
#include <algorithm>

#include "../ArxHelper/HelperClass.h"
#include "../MineGE/HelperClass.h"

#include "../DefGE/RcuGE.h"
#include "../DefGE/Pore.h"
#include "../DefGE/DrillSite.h"
#include "../DefGE/RockGate.h"
#include "../DefGE/CoalSurface.h"

void RcuHelper::FindAllDrillSite(AcDbObjectIdArray& rock_gates)
{
	ArxDataTool::GetEntsByType(_T("DrillSite"), rock_gates, true);
}

void RcuHelper::GetRelatedCoalSurface(const AcDbObjectId& drill_site, AcDbObjectId& coal_surf)
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
		if(hosts[i] == drill_site)
		{
			coal_surf = tags[i];
			break;
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

void RcuHelper::ClearRelatedOpenPores(const AcDbObjectId& drill_site)
{
	//�����������곡���������
	AcDbObjectIdArray pores;
	RcuHelper::GetRelatedOpenPores(drill_site, pores);
	if(pores.isEmpty()) return;

	//ɾ�����
	ArxEntityHelper::EraseObjects(pores, Adesk::kTrue);
}

void RcuHelper::ClearRelatedClosePores(const AcDbObjectId& coal_surf)
{
	//�����������곡���������
	AcDbObjectIdArray pores;
	RcuHelper::GetRelatedOpenPores(coal_surf, pores);
	if(pores.isEmpty()) return;

	//ɾ�����
	ArxEntityHelper::EraseObjects(pores, Adesk::kTrue);
}

bool RcuHelper::GetDrillSiteAndCoalSurfDatas(const AcDbObjectId& drill_site, DrillSiteLink& ds_link, CoalSurfaceLink& cs_link)
{
	//��ȡ�곡�������������ݲ���䵽�Ի�����
	if(!RcuHelper::ReadDrillSiteData(drill_site, ds_link)) return false;

	//�����곡������ú��
	AcDbObjectId coal_surf;
	RcuHelper::GetRelatedCoalSurface(drill_site, coal_surf);
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

bool RcuHelper::CaculCoalSurfParam( DrillSiteLink& ds_link, CoalSurfaceLink& cs_link)
{
	AcGePoint3d orign = ds_link.m_pt;

	//����rcu����м���
	Rcu2 rcu;
	//����ú�����(��Ǻͺ��)
	rcu.setCoalSurf(DegToRad(cs_link.m_angle), cs_link.m_thick);
	//�����곡����������
	rcu.setDrillSite1(ds_link.m_height, ds_link.m_width);
	//�����곡���������ұ������
	rcu.setDrillSite2(ds_link.m_top, ds_link.m_bottom, ds_link.m_left, ds_link.m_right);
	//�����곡����ú�����С����
	rcu.setDrillSite3(ds_link.m_dist);

	//����ú����ĳ�ɷ�Χ��Ⱥ͸߶�
	rcu.drillExtent(cs_link.m_width, cs_link.m_height);
	//����ú����(���ĵ����ꡢ��������������������������)
	AcGePoint3d cnt;
	AcGeVector3d normV, headV, dipV;
	if(!rcu.drillSurface(cnt, normV, headV, dipV)) return false;
	cs_link.m_pt = cnt + orign.asVector();
	cs_link.m_normV = normV;
	cs_link.m_headV = headV;
	cs_link.m_dipV = dipV;

	return true;
}

bool RcuHelper::CaculRelativeOpenPorePts(DrillSiteLink& ds_link, AcGePoint3dArray& pts)
{
	//������׵�����
	//�곡�Ŀ���ϲ��ö��ٸ����
	int n1 = int(ds_link.m_width/ds_link.m_pore_gap);
	//�곡�ĸ߶��ϲ��ö��ٸ����
	int n2 = int(ds_link.m_height/ds_link.m_pore_gap);

	AcGePoint3d pt = AcGePoint3d::kOrigin;
	//ӭͷ,�����㴦�����½�
	pt += AcGeVector3d(-0.5*ds_link.m_width, 0, 0);
	for(int i=0;i<n1;i++)
	{
		pt.x += ds_link.m_pore_gap;
		pt.y = 0;
		for(int j=0;j<n2;j++)
		{
			pt.y += ds_link.m_pore_gap;
			pts.append(pt);
		}
	}
	return true;
}

bool RcuHelper::CaculRelativeClosePorePts(CoalSurfaceLink& cs_link, AcGePoint3dArray& pts)
{
	//��ɷ�Χ�Ŀ���ϲ�����׸���
	int n1 = int(cs_link.m_width/cs_link.m_gas_radius);
	//��ɷ�Χ�ĸ߶��ϲ�����׸���
	int n2 = int(cs_link.m_height/cs_link.m_gas_radius);

	//�������½ǵĵ�����,������㿪ʼ����
	AcGePoint3d origin = AcGePoint3d::kOrigin + cs_link.m_headV*cs_link.m_width*-0.5 + cs_link.m_dipV*cs_link.m_height*-0.5;
	for(int i=0;i<n1;i++)
	{
		//����������
		AcGePoint3d pt = origin + cs_link.m_headV*cs_link.m_gas_radius*(i+1);
		for(int j=0;j<n2;j++)
		{
			//����������
			pt += cs_link.m_dipV*cs_link.m_gas_radius;
			pts.append(pt);
		}
	}
	return true;
}

bool RcuHelper::GetDrillSiteInsertPt( const AcDbObjectId& drill_site, AcGePoint3d& insertPt )
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

	insertPt = pDS->getInsertPt();

	actrTransactionManager->endTransaction();
	return true;
}

bool RcuHelper::GetCoalSurfInsertPt( const AcDbObjectId& coal_surf, AcGePoint3d& insertPt )
{
	AcTransaction* pTrans = actrTransactionManager->startTransaction();
	if( pTrans == 0 ) return false;

	AcDbObject* pObj;
	if( Acad::eOk != pTrans->getObject( pObj, coal_surf, AcDb::kForWrite ) )
	{
		actrTransactionManager->abortTransaction();
		return false;
	}

	CoalSurface* pCS = CoalSurface::cast( pObj );
	if(pCS == 0)
	{
		actrTransactionManager->abortTransaction();
		return false;
	}

	insertPt = pCS->getInsertPt();

	actrTransactionManager->endTransaction();
	return true;
}

bool RcuHelper::SetDrillSitePt(const AcDbObjectId& drill_site, const AcGePoint3d& insertPt)
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

	actrTransactionManager->endTransaction();
	return true;
}

bool RcuHelper::GetDrillSitePt(const AcDbObjectId& drill_site, AcGePoint3d& insertPt)
{
	AcTransaction* pTrans = actrTransactionManager->startTransaction();
	if( pTrans == 0 ) return false;

	AcDbObject* pObj;
	if( Acad::eOk != pTrans->getObject( pObj, drill_site, AcDb::kForRead ) )
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

	insertPt = pDS->getInsertPt();

	actrTransactionManager->endTransaction();
	return true;
}

bool RcuHelper::CreateDrillSite(const AcGePoint3d& pt, DrillSiteLink& ds_link, CoalSurfaceLink& cs_link)
{
	//����ú�����
	if(!RcuHelper::CaculCoalSurfParam(ds_link, cs_link)) return false;

	AcGePoint3d origin = ds_link.m_pt;
	AcGePoint3d cnt = cs_link.m_pt;

	//�ĵ����л�
	DocumentLockSwitch lock_switch;

	//�½��곡�����ò��������
	DrillSite* pDS = new DrillSite();
	pDS->setInsertPt(pt);
	//pDS->enableFollow(true); // ��������Ч��

	CoalSurface* pCS = new CoalSurface();
	pCS->setInsertPt(pt + (cnt - origin));
	//pCS->enableFollow(true); // ��������Ч��

	//����곡��cadͼ�����ݿ�
	if(!ArxUtilHelper::PostToModelSpace(pDS))
	{
		delete pDS; pDS = 0;
		return  false;
	}

	//ú��������곡
	pCS->setRelatedGE(pDS->objectId());
	//���ú�㵽cadͼ�����ݿ�
	if(!ArxUtilHelper::PostToModelSpace(pCS))
	{
		delete pCS; pCS = 0;
		//ú���ύʧ��,��ɾ������ӵ��곡
		ArxEntityHelper::EraseObject(pDS->objectId(), true);
		return false;
	}

	//ͨ��DataLink�޸��곡��ú�������
	ds_link.setDataSource(pDS->objectId());
	ds_link.updateData(true);
	cs_link.setDataSource(pCS->objectId());
	cs_link.updateData(true);

	//���ú�����(�տ�)
	if(!RcuHelper::CreateClosePores(pCS->objectId(), cs_link)) return false;

	//����ú������׵�
	return true;
}


bool RcuHelper::ModifyDrillSitePt(const AcDbObjectId& drill_site, DrillSiteLink& ds_link)
{
	if(drill_site.isNull()) return false;

	//AcDbObjectId drill_site;
	//if(!DrawHelper::GetHostGE(drill_site, drill_site)) return false;

	if(!RcuHelper::ReadDrillSiteData(drill_site, ds_link)) return false;

	//��ȡ�곡�Ĳ��������
	AcGePoint3d pt;
	if(!RcuHelper::GetDrillSiteInsertPt(drill_site, pt)) return false;

	AcGePoint3d insertPt;
	// 	if(!RcuHelper::CaculDrillSitePt(ds_link, ds_link, pt, insertPt, linkPt)) return false;

	//�޸��곡ͼԪ�ļ��ε�����
	return RcuHelper::SetDrillSitePt(drill_site, insertPt);
}

bool RcuHelper::CreateOpenPores(const AcDbObjectId& drill_site, DrillSiteLink& ds_link)
{
	//��ȡ�곡�ļ�������
	AcGePoint3d insertPt;
	if(!RcuHelper::GetDrillSitePt(drill_site, insertPt)) return false;

	//�����������
	AcGePoint3dArray pts;
	if(!RcuHelper::CaculRelativeOpenPorePts(ds_link, pts)) return false;

	//����װ�Ļ���(���ӵ�����ƫ��һ��ĸ߶Ⱦ���)
	AcGePoint3d xoy_origin = insertPt;
	//�½��곡�����ò��������
	for(int i=0;i<pts.length();i++)
	{
		//���µ�������
		AcGePoint3d pt = pts[i];

		Pore* pPore = new Pore();
		//����xoyƽ��
		pPore->setInsertPt(xoy_origin + pt.asVector());
		pPore->setRelatedGE(drill_site);

		//����곡��cadͼ�����ݿ�
		if(!ArxUtilHelper::PostToModelSpace(pPore))
		{
			delete pPore; pPore = 0;
			continue;
		}
		else
		{
			//�����漰��2������:
			//ƽ��ͶӰ�������xoyƽ�棬���곡���������ǽ����xozƽ��
			AcGePoint3d xoz_origin = ds_link.m_pt;

			PoreLink pore_link;
			pore_link.setDataSource(pPore->objectId());
			pore_link.m_pore_num = i + ds_link.m_start;
			pore_link.m_pore_size = ds_link.m_pore_size;
			//����xozƽ��,����Ҫ�ѵ�pt��y��z����
			std::swap(pt.y, pt.z);
			pore_link.m_pt = xoz_origin + pt.asVector();
			pore_link.updateData(true);
		}
	}

	return true;
}

bool RcuHelper::CreateClosePores(const AcDbObjectId& coal_surf, CoalSurfaceLink& cs_link)
{
	//����ú������������
	AcGePoint3dArray pts;
	if(!RcuHelper::CaculRelativeClosePorePts(cs_link, pts)) return false;

	//��ȡú��Ĳ��������
	AcGePoint3d insertPt;
	if(!RcuHelper::GetCoalSurfInsertPt(coal_surf, insertPt)) return false;

	//�½��곡�����ò��������
	for(int i=0;i<pts.length();i++)
	{
		//���µ�������
		AcGePoint3d pt = pts[i];

		Pore* pPore = new Pore();
		//����xoyƽ��
		pPore->setInsertPt(insertPt + pt.asVector());
		pPore->setRelatedGE(coal_surf);

		//����곡��cadͼ�����ݿ�
		if(!ArxUtilHelper::PostToModelSpace(pPore))
		{
			delete pPore; pPore = 0;
			continue;
		}
		else
		{
			PoreLink pore_link;
			pore_link.setDataSource(pPore->objectId());
			pore_link.m_pore_num = i + 1;
			pore_link.m_pore_size = cs_link.m_gas_radius;
			pore_link.m_pt = cs_link.m_pt + pt.asVector();
			pore_link.updateData(true);
		}
	}

	return true;
}

bool RcuHelper::ModifyDrillSiteRelatedGEs(const AcDbObjectId& drill_site, DrillSiteLink& ds_link)
{
	return CreateOpenPores(drill_site, ds_link);
}

bool RcuHelper::ModifyCoalSurfRelatedGEs(const AcDbObjectId& coal_surf, CoalSurfaceLink& cs_link)
{
	return CreateClosePores(coal_surf, cs_link);
}

bool RcuHelper::ModifyDrillSiteRelatedGEs(const AcDbObjectId& drill_site, DrillSiteLink& ds_link, CoalSurfaceLink& cs_link)
{
	//�����곡������ú��
	AcDbObjectId coal_surf;
	RcuHelper::GetRelatedCoalSurface(drill_site, coal_surf);
	if(coal_surf.isNull()) return false;

	if(!drill_site.isNull()) 
	{
		ClearRelatedOpenPores(drill_site);
		ClearRelatedClosePores(coal_surf);
	}

	//���¼���ú�����
	if(!RcuHelper::CaculCoalSurfParam(ds_link, cs_link)) return false;

	//�������ݵ�ú��ͼԪ��
	if(!cs_link.updateData(true)) return false;

	//�޸�ú�������ͼԪ
	if(!ModifyCoalSurfRelatedGEs(coal_surf, cs_link)) return false;

	ds_link.setDataSource(drill_site);
	ds_link.updateData(false);

	//�������ݵ��곡ͼԪ��
	if(ds_link.updateData(true))
	{
		//�޸��곡������ͼԪ
		ModifyDrillSiteRelatedGEs(drill_site, ds_link);
	}

	return true;
}
