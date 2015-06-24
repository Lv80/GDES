#pragma once

#include "../MineGE/DataLink.h"

//4��ʯ�Ž�úͼԪ���ݹ���,���ٲ���Ҫ���ַ����������������͵�ת������

class RockGateLink : public DataLink
{
public:
	RockGateLink() : m_length(0), m_width(0), m_height(0), 
		             m_left(0), m_right(0), m_top(0), m_bottom(0),
					 m_dist(0)
	{

	}
protected:
	virtual void regDatas()
	{
		linkStringData( _T( "����" ), &m_name );
		linkDoubleData( _T( "����" ), &m_length );
		linkDoubleData( _T( "���" ), &m_width );
		linkDoubleData( _T( "�߶�" ), &m_height );
		linkDoubleData( _T( "��С����" ), &m_dist );
		linkPointData( _T( "ӭͷ�װ����ĵ�����" ), &m_pt );
		linkDoubleData( _T( "��ﱣ��" ), &m_left );
		linkDoubleData( _T( "�Ұﱣ��" ), &m_right );
		linkDoubleData( _T( "�ϰﱣ��" ), &m_top );
		linkDoubleData( _T( "�°ﱣ��" ), &m_bottom );
	}

public:
	//�����ڲ��洢�����ַ�����ʾ��,xyz֮��ͨ�����ŷָ�
	AcGePoint3d m_pt;
	double m_length;
	double m_width;
	double m_height;
	double m_left;
	double m_right;
	double m_top;
	double m_bottom;
	double m_dist;
	CString m_name;
};

class CoalSurfaceLink : public DataLink
{
public:
	CoalSurfaceLink() : m_thick(0), m_angle(0), m_width(0), m_height(0), 
		                m_gas_radius(3)
	{

	}
protected:
	virtual void regDatas()
	{
		linkDoubleData( _T( "���" ), &m_thick );
		linkDoubleData( _T( "���" ), &m_angle );
		linkDoubleData( _T( "��׳�ɰ뾶" ), &m_gas_radius );
		//��$�ŵ��ֶα�ʾ���ֶν������ڲ�����,��Ӧ��Ҳ����Ҫ��ʾ�ڶԻ��������
		linkDoubleData( _T( "$ͶӰ���" ), &m_width );
		linkDoubleData( _T( "$ͶӰ�߶�" ), &m_height );
		linkPointData(_T("$���ĵ�����"), &m_pt);
		linkVectorData(_T("$ƽ�淨����"), &m_normal);
	}

public:
	double m_thick;
	double m_angle;
	double m_width;
	double m_height;
	//�����ڲ��洢�����ַ�����ʾ��,xyz֮��ͨ�����ŷָ�
	AcGePoint3d m_pt;
	AcGeVector3d m_normal;
	double m_gas_radius;
};

class DrillSiteLink : public DataLink
{
public:
	DrillSiteLink() : m_leftOrRight(0), m_dist(0), m_depth(0), m_height(0), 
		              m_start(1), m_gap(0), m_radius(0)
	{

	}
protected:
	virtual void regDatas()
	{
		linkStringData( _T( "����" ), &m_name );
		linkIntData( _T( "λ��" ), &m_leftOrRight );
		linkDoubleData( _T( "��ӭͷ�ľ���" ), &m_dist );
		linkDoubleData( _T( "���" ), &m_depth );
		linkDoubleData( _T( "�߶�" ), &m_height );
		linkIntData( _T( "��ʼ���" ), &m_start );
		linkDoubleData( _T( "�׾�" ), &m_radius );
		linkDoubleData( _T( "�׾�" ), &m_gap );
		//��$�ŵ��ֶα�ʾ���ֶν������ڲ�����,��Ӧ��Ҳ����Ҫ��ʾ�ڶԻ��������
		linkPointData( _T( "$�װ�����" ), &m_pt );
	}

public:
	CString m_name;
	int m_leftOrRight;
	double m_dist;
	double m_depth;
	double m_height;
	int m_start;
	//�����ڲ��洢�����ַ�����ʾ��,xyz֮��ͨ�����ŷָ�
	AcGePoint3d m_pt;
	double m_gap;
	double m_radius;
};

class PoreLink : public DataLink
{
public:
	PoreLink() : m_num(0), m_radius(0)
	{

	}
protected:
	virtual void regDatas()
	{
		linkIntData( _T( "���" ), &m_num );
		linkDoubleData( _T( "�뾶" ), &m_radius );
		//��$�ŵ��ֶα�ʾ���ֶν������ڲ�����,��Ӧ��Ҳ����Ҫ��ʾ�ڶԻ��������
		linkPointData( _T( "$����" ), &m_pt );
	}

public:
	int m_num;
	double m_radius;
	//���������ַ�����ʾ��,xyz֮��ͨ�����ŷָ�
	//��ͨ��ArxUtilHelper::StringToPoint3d��̬��������ת��
	AcGePoint3d m_pt;
};