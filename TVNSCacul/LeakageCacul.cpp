#include "StdAfx.h"
#include "LeakageCacul.h"
//#include "LeakageStandByDlg.h"
#include "NetWorkData.h"

#include "../DefGE/Chimney.h"
#include "../MineGE/HelperClass.h"

extern LeakageCacul_DataLink* LeakageCaculDatas(AcDbObjectId objId);
extern Chimney_DataLink* ChimneyDatas(AcDbObjectId objId );

LeakageCaculate::LeakageCaculate( AcDbObjectId objId ):m_leakage(0)
{
	m_objId = objId;
	initDatas();
}

LeakageCaculate::~LeakageCaculate()
{

}

void LeakageCaculate::initDatas()
{
	LeakageCacul_DataLink *lcdl = LeakageCaculDatas(m_objId);
	Chimney_DataLink *cdl = ChimneyDatas(m_objId);
	m_meterial = cdl->tm;
	m_chimLenth = cdl->lenth;
	m_joints = cdl->joints;
	m_diam = cdl->diameter * 0.001; //��λת����m
	m_windage = cdl->windage;

	if (_T("��ʹ�ø÷�������") ==  lcdl->hmLeakage )
	{
		m_hmLeakage = -1;
		//acutPrintf(_T("��ʹ�÷���һ"));
	}
	else
	{
		m_hmLeakage = _tstof(lcdl->hmLeakage) * 0.01;//��λ��%ת��ʵ�ʵ�λ 
	}

	if (_T("��ʹ�ø÷�������") ==  lcdl->leakageFactor )
	{
		m_leakageFactor = -1;
		//acutPrintf(_T("��ʹ�÷�����"));
	}
	else
	{
		m_leakageFactor = _tstof(lcdl->leakageFactor);
	}

}

double LeakageCaculate::LeakageCaculRet()
{
	if ( 0 == m_windage )
	{
		AfxMessageBox(_T("��Ͳ�ķ���û�м���!"),MB_OK | MB_ICONSTOP);
		return -1;
	}

	if ( 0 == m_chimLenth)
	{
		AfxMessageBox(_T("��Ͳ�Ĳ���û�и���!"),MB_OK | MB_ICONSTOP);
		return -1;
	}

	if (true == isLinkedNext())
	{
		m_joints += 1;
	}

	if (-1 != m_hmLeakage)
	{
		if (0 == m_hmLeakage)
		{
			AfxMessageBox(_T("©��ϵ���������û������"),MB_OK | MB_ICONSTOP);
			return -1;
		}

		if((100 - m_hmLeakage * m_chimLenth) <= 0)
		{
			AfxMessageBox(_T("����©���ʹ���"),MB_OK | MB_ICONSTOP);
			return -1;
		}
		m_leakage = 100 / (100 - m_hmLeakage * m_chimLenth);
	}
	if (-1 != m_leakageFactor)
	{
		if (0 == m_hmLeakage)
		{
			AfxMessageBox(_T("©��ϵ���������û������"),MB_OK | MB_ICONSTOP);
			return -1;
		}

		if (_T("������Ͳ") == m_meterial)
		{
			metalCacul();
		}

		else if (_T("������Ͳ") == m_meterial)
		{
			blanketCacul();
		}
	}

	return m_leakage;
}

void LeakageCaculate::metalCacul()
{
	double lenth = m_chimLenth / (1 + m_joints); //��Ͳ�ϳ�
	double windage = m_windage / m_chimLenth;	//ÿ�׷�Ͳ�ķ���
	
	double leakage = 1 + (m_leakageFactor * m_diam * m_joints * pow(windage * lenth,0.5))/3;
	m_leakage = pow(leakage,2);
}

void LeakageCaculate::blanketCacul()
{
	if (1 - m_joints * m_leakageFactor <= 0)
	{
		AfxMessageBox(_T("��ͷ��������\n����©��ϵ������"),MB_OK | MB_ICONSTOP);
		return;
	}
	m_leakage = 1 /( 1 - m_joints * m_leakageFactor);
}

bool LeakageCaculate::isLinkedNext()
{
	bool isLinked = false;
	AcDbEntity *pEnt;
	acdbOpenAcDbEntity(pEnt,m_objId,AcDb::kForRead);
	Chimney *pChim = Chimney::cast(pEnt);
	pEnt->close();

	AcGePoint3dArray pts = pChim->getControlPoint();
	//int ptsNum = pts.length();

	AcDbObjectIdArray chimsIds;
	DrawHelper::FindMineGEs(_T("Chimney"),chimsIds);

	int len = chimsIds.length();
	for (int i = 0; i < len; i++)
	{
		acdbOpenAcDbEntity(pEnt,chimsIds[i],AcDb::kForRead);
		pChim = Chimney::cast(pEnt);
		pEnt->close();

		AcGePoint3dArray ChimPts = pChim->getControlPoint();

		int ChimPtsNum = ChimPts.length();
		if ((pts.contains(ChimPts[0]) || pts.contains(ChimPts[ChimPtsNum-1])) && m_objId != chimsIds[i])
		{
			isLinked = true;
		}
	}

	return isLinked;
}