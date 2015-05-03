#include "StdAfx.h"
#include "NetWorkData.h"

void TVNSDataLink::regDatas()
{
	linkStringData( _T( "����" ), &name );
}


void TWS_DataLink::regDatas()
{
	TVNSDataLink::regDatas();

	linkDoubleData( _T( "�����" ), &q );
	linkDoubleData( _T( "����" ), &lenth );
	linkDoubleData( _T( "�������" ), &area );
}


Tunnel_DataLink::Tunnel_DataLink()
{

}

Tunnel_DataLink::~Tunnel_DataLink()
{

}

void Tunnel_DataLink::regDatas()
{
	TVNSDataLink::regDatas();
	linkDoubleData( _T( "�������" ), &area );
	linkDoubleData( _T( "����" ), &lenth );
}

void BaseparamDataLink::regDatas()
{
	//linkStringData(_T("������"),&name);
	//linkStringData(_T("��������"),&district);
	linkStringData(_T("ͨ�緽��"),&method);
	linkStringData(_T("ͨ�緽ʽ"),&way);
}

void Vent_InitDataLink::regDatas()
{
	linkDoubleData( _T( "ͨ��ʱ��" ), &T );
	linkDoubleData( _T( "�����ܶ�" ), &ro );
	//linkDoubleData( _T( "�ų�����" ), &speed );
	linkDoubleData( _T("��λ���ʵķ���ָ��"), &q0);
	linkDoubleData( _T( "�������ȱ�" ), &Cp);

}

void Chimney_DataLink::regDatas()
{
	TVNSDataLink::regDatas();
	linkDoubleData( _T( "����" ), &lenth);
	linkDoubleData( _T( "ֱ��" ), &diameter );
	linkStringData( _T( "����" ), &tm );
	linkStringData( _T( "���" ), &bends );
	linkDoubleData( _T( "����©����" ), &leakage );
	linkDoubleData( _T( "Ħ��ϵ��" ), &friction );
	linkIntData( _T( "��ͷ��" ), &joints );
	linkDoubleData( _T( "©��ϵ��" ), &leakageFactor );
	linkDoubleData( _T( "��Ͳ����" ), &windage );
	linkDoubleData( _T( "���׷���" ), &hmWindage );

}

void Vent_DataLink::regDatas()
{
	linkDoubleData( _T( "ͨ��ʱ��" ), &m_time );
	linkDoubleData( _T( "�����ܶ�" ), &m_ro );
	linkDoubleData( _T( "�ų�����" ), &m_speed );
	linkDoubleData( _T("��λ���ʵķ���ָ��"), &m_q0);
	linkDoubleData( _T( "�������ȱ�" ), &m_Cp);

	linkDoubleData( _T("һ�α���ըҩ������"), &m_A );
	linkStringData( _T( "������ʽ" ), &m_dynamiteWay );
	linkDoubleData( _T( "��������" ), &m_N );
	linkDoubleData( _T("�к��ɷֵ�ƽ������"), &m_g);
	linkDoubleData( _T("�к��ɷֵ�����Ũ��"), &m_C1);

	linkDoubleData( _T("�����豸������"), &m_PN );
	linkDoubleData( _T( "���������" ), &m_inT );
	linkDoubleData( _T( "�ŷ������" ), &m_outT );
	linkDoubleData( _T("��Դ��ɢ����"), &m_allPower );

}

void LeakageCacul_DataLink::regDatas()
{
	linkStringData(_T("����©����"),&hmLeakage);
	linkStringData(_T("©��ϵ��"),&leakageFactor);
}