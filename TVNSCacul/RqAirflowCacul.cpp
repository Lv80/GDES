#include "StdAfx.h"
#include "RqAirflowCacul.h"
#include "NetWorkData.h"
#include <cmath>

//#include "../MineGE/LinkedGE.h"
#include "../MineGE/HelperClass.h"

extern double GetMaxValues(double a, double b);
extern TWS_DataLink* TWSDatas(AcDbObjectId objId);
extern BaseparamDataLink* BaseparamDatas(AcDbObjectId objId);
extern Vent_DataLink* CaculParamDatas(AcDbObjectId objId);


VentCaculate::VentCaculate(AcDbObjectId objId):m_basis(0),m_rqAirflow(0)
{
	initDatas(objId);
}

VentCaculate::~VentCaculate()
{

}

void VentCaculate::initDatas(AcDbObjectId objId)
{
	TWS_DataLink* ts = TWSDatas(objId);
	//m_lenth = getVentLenth(objId);
	m_lenth = 100;
	m_area = ts->area;

	Vent_DataLink* vtl = CaculParamDatas(objId);
	m_time = vtl->m_time;				//ͨ��ʱ��
	m_speed = vtl->m_speed;				//�ų�����
	m_A = vtl->m_A;						//ըҩ��
	m_N = vtl->m_N;						//��������
	m_dynamiteWay = vtl->m_dynamiteWay;	//������ʽ
	m_g = vtl->m_g;						//ƽ������
	m_q0 = vtl->m_q0;					//����ָ��
	m_PN = vtl->m_PN;					//������
	m_C1 = vtl->m_C1;					//����Ũ��
	m_inT = vtl->m_inT;					//���������
	m_outT = vtl->m_outT;				//�ŷ������
	m_allPower = vtl->m_allPower;		//��ɢ����
	m_Cp = vtl->m_Cp;					//�������ȱ�
	m_ro = vtl->m_ro;					//�����ܶ�

	BaseparamDataLink *bpl = BaseparamDatas(objId);
	m_method = bpl->method;
	m_way = bpl->way;
}

double VentCaculate::afterDampAirCacul()
{
	double dampQ = 0;

	if (0 == m_lenth)
	{
		//AfxMessageBox(_T("���⹤���泤��!"),MB_OK | MB_ICONSTOP);
		return 0;
	}
	if (0 == m_area)
	{
		AfxMessageBox(_T("���⹤����������!"),MB_OK | MB_ICONSTOP);
		return 0;
	}

	if (_T("���ʽ") == m_method)//���ʽ
	{
		double throwLenth;

		if (_T("���׹���") == m_dynamiteWay )//���׹���
		{
			throwLenth = 15 + m_A / 5;
			//acutPrintf(_T("\n���׹�"));
		}

		else //if (_T("���׹���") == m_dynamiteWay )//���׹���
		{
			throwLenth = 15 + m_A;
			//acutPrintf(_T("\n���׹�"));
		}

		double v1 = m_A * throwLenth * m_area;
		dampQ = 18 * pow(v1,0.5) / m_time;

		//acutPrintf(_T("\n���ʽ"));
	}

	else
	{
		double v1 = m_A * m_lenth * m_area;
		dampQ = 19 * pow(v1,0.5) / m_time;
		
		if (_T("ѹ��ʽ") == m_method)
		m_dynamiteWay = _T("ѹ��ʽ�����Ǹ���");
	}
	acutPrintf(_T("\n�����̼������:%lfm^3/s"),dampQ);

	return dampQ;
}

double VentCaculate::speedAirCacul()
{
	double speedQ = m_speed * m_area;
	acutPrintf(_T("\n���ų����ټ������:%lfm^3/s"),speedQ);
	return speedQ;
}

double VentCaculate::powerAirCacul()
{
	double powerQ1 = 0,powerQ2 = 0;
	if(0 != m_C1)
	{
		powerQ1 = 10 * m_g / 36 / m_C1;
	}
	else
	{
		//AfxMessageBox(_T("�к�����ɷֵ�����Ũ��û��ֵ"),MB_OK | MB_ICONSTOP);
		return 0;
	}
	powerQ2 = m_q0 * m_PN / 60;
	double powerQ = GetMaxValues(powerQ1,powerQ2);
	acutPrintf(_T("\n����λ���ʼ������:%lfm^3/s"),powerQ);
	return powerQ;
}

double VentCaculate::tempAirCacul()
{
	double tempQ = 0;
	double v = m_Cp * m_ro * (m_outT - m_inT);
	if (0 == v)
	{
		//AfxMessageBox(_T("�����ŷ�����²������"),MB_OK | MB_ICONSTOP);
		return 0;
	}
	else if(v < 0)
	{
		//AfxMessageBox(_T("��������²��ܴ����ŷ������"),MB_OK | MB_ICONSTOP);
		return 0;
	}
	else
	{
		tempQ = m_allPower / v;
	}
	acutPrintf(_T("\n���������ڼ������:%lfm^3/s"),tempQ);
	return tempQ;
}

double VentCaculate::workerAirCacul()
{
	double workers = 4 * m_N / 60;
	acutPrintf(_T("\n�������������������:%lfm^3/s"),workers);
	return workers;
}

void VentCaculate::ensureAir()
{
	double reqArray[5];
	//if(-1 == (reqArray[0] = afterDampAirCacul())) return;
	//if(-1 == (reqArray[1] = speedAirCacul()))		return;
	//if(-1 == (reqArray[2] = powerAirCacul()))		return;
	//if(-1 == (reqArray[3] = tempAirCacul()))		return;
	//if(-1 == (reqArray[4] = workerAirCacul()))	return;

	reqArray[0] = afterDampAirCacul();
	reqArray[1] = speedAirCacul();
	reqArray[2] = powerAirCacul();
	reqArray[3] = tempAirCacul();
	reqArray[4] = workerAirCacul();

	double reqQ = 0;
	//ȡ������
	for (int i = 0; i< 5;i++)
	{
		reqQ = GetMaxValues(reqArray[i],reqQ);
	}

	//�ж����������������
	for(int i = 0;i < 5; i++)
	{
		if (reqArray[i] == reqQ)
		{
			m_basis = i;
			break;
		}
	}

	m_rqAirflow = reqQ;
	cheakQ();
	if (m_rqAirflow <= 0)
	{
		return;
	}

	//acutPrintf(_T("\n�ܳ���:%f"),m_lenth);
}

void VentCaculate::cheakQ()
{
	double cheakq = 4 * m_area;
	CString msg;
	switch(m_basis)
	{
	case AFTER_DAMP:
		msg = _T("������Ϊ�����̼������÷���");
		break;
	case DUST_SPEED:
		msg = _T("������Ϊ���ų����ټ������÷���");
		break;
	case UNIT_POWER:
		msg = _T("������Ϊ����λ���ʷ���ָ��������÷���");
		break;
	case HEAT_ADJT:
		msg = _T("������Ϊ���������ڼ������÷���");
		break;
	case WORKER_NUM:
		msg = _T("������Ϊ�������������������÷���");
		break;
	default:
		break;
	}

	CString msgAll;
	if (cheakq < m_rqAirflow)
	{
		msgAll = _T("����ʧ��,���ٳ���!");
		m_rqAirflow = 0;
		msgAll.Append(_T("\n"));
		msgAll.Append(msg);
		AfxMessageBox(msgAll);
		return;
	}
	else if (m_rqAirflow <= 0 )
	{
		msgAll = _T("����ʧ��\n����������ȫ");
		AfxMessageBox(msgAll);
		return;
	}
	//else
	//{
	//	msgAll = _T("����ɹ�!");
	//}
}

double VentCaculate::getVentLenth(AcDbObjectId objId)
{
	AcDbObjectIdArray objIds;
	DrawHelper::FindMineGEs(_T("Tunnel"),objIds);
	int len = objIds.length();

	AcGePoint3d spt,ept;
	//��ȡѡ�������ʼĩ�ڵ�
	LinkedGE *pEdge = getLinkedGE(objId);
	pEdge->getSEPoint(spt,ept);

	AcGePoint3dArray findedPts;
	findedPts.append(spt);

	for(int i = 0; i < len; i++)
	{
		pEdge = getLinkedGE(objIds[i]);
		pEdge->getSEPoint(spt,ept);
		//acutPrintf(_T("\n%d->ʼ�ڵ�:(%f,%f),ĩ�ڵ�(%f,%f)"),i,spt.x,spt.y,ept.x,ept.y);
		if (findedPts.contains(spt) && !findedPts.contains(ept))
		{
			findedPts.append(ept);
			i = -1;
		}
		else if (findedPts.contains(ept) && !findedPts.contains(spt))
		{
			findedPts.append(spt);
			i = -1;
		}
	}

	CString ventLenthStr;
	DataHelper::GetPropertyData( objId, _T( "����" ), ventLenthStr);
	double ventLenth = _tstof(ventLenthStr);

	for (int i = 0;i < len; i++)
	{		
		//��Ҫ�ų�������ͻط���
		CString name;
		bool isVentTunel = false;
		DataHelper::GetPropertyData( objIds[i], _T( "����" ), name );

		if ( _T("������") != name && _T("�ط���") != name)
		{
			isVentTunel = true;
		}

		//��ȡ���������ʼĩ�ڵ�
		pEdge = getLinkedGE(objIds[i]);
		pEdge->getSEPoint(spt,ept);

		CString lenthStr;
		DataHelper::GetPropertyData( objIds[i], _T( "����" ), lenthStr);
		double lenth = _tstof(lenthStr);
		
		if ((findedPts.contains(spt)||findedPts.contains(ept))&& isVentTunel)
		{
			//acutPrintf(_T("\nʼ�ڵ�:(%f,%f),ĩ�ڵ�(%f,%f)"),spt.x,spt.y,ept.x,ept.y);
			ventLenth += lenth;
		}
	}
	return ventLenth;
}

LinkedGE* VentCaculate::getLinkedGE(AcDbObjectId objId)
{
	AcDbObject* pObj;
	acdbOpenObject( pObj, objId, AcDb::kForRead );

	LinkedGE* pEdge = LinkedGE::cast( pObj );
	pObj->close();

	return pEdge;
}