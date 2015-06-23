#pragma once

#include "../MineGE/DataLink.h"

//4��ʯ�Ž�úͼԪ���ݹ���,���ٲ���Ҫ���ַ����������������͵�ת������

class RockGateLink : public DataLink
{
protected:
	virtual void regDatas()
	{
		linkStringData( _T( "����" ), &m_name );
		linkDoubleData( _T( "����" ), &m_length );
		linkDoubleData( _T( "���" ), &m_width );
		linkDoubleData( _T( "�߶�" ), &m_height );
		linkDoubleData( _T( "��С����" ), &m_dist );
		linkDoubleData( _T( "��װ뾶" ), &m_radius );
		linkStringData( _T( "ӭͷ�װ����ĵ�����" ), &m_pt );
		linkDoubleData( _T( "��ﱣ��" ), &m_left );
		linkDoubleData( _T( "�Ұﱣ��" ), &m_right );
		linkDoubleData( _T( "�ϰﱣ��" ), &m_top );
		linkDoubleData( _T( "�°ﱣ��" ), &m_bottom );
	}

public:
	CString m_pt;
	double m_length;
	double m_width;
	double m_height;
	double m_left;
	double m_right;
	double m_top;
	double m_bottom;
	double m_dist;
	double m_radius;
	CString m_name;
};

class CoalSurfaceLink : public DataLink
{
protected:
	virtual void regDatas()
	{
		linkDoubleData( _T( "���" ), &m_thick );
		linkDoubleData( _T( "���" ), &m_angle );
		//��$�ŵ��ֶα�ʾ���ֶν������ڲ�����,��Ӧ��Ҳ����Ҫ��ʾ�ڶԻ��������
		linkDoubleData( _T( "$ͶӰ���" ), &m_width );
		linkDoubleData( _T( "$ͶӰ�߶�" ), &m_height );
	}

public:
	double m_thick;
	double m_angle;
	double m_width;
	double m_height;
};

class DrillSiteLink : public DataLink
{
protected:
	virtual void regDatas()
	{
		linkStringData( _T( "����" ), &m_name );
		linkIntData( _T( "λ��" ), &m_leftOrRight );
		linkDoubleData( _T( "��ӭͷ�ľ���" ), &m_dist );
		linkDoubleData( _T( "���" ), &m_width );
		linkDoubleData( _T( "�߶�" ), &m_height );
		linkIntData( _T( "��ʼ���" ), &m_start );
		//��$�ŵ��ֶα�ʾ���ֶν������ڲ�����,��Ӧ��Ҳ����Ҫ��ʾ�ڶԻ��������
		linkStringData( _T( "$�װ�����" ), &m_name );
	}

public:
	CString m_name;
	int m_leftOrRight;
	double m_dist;
	double m_width;
	double m_height;
	int m_start;
	//���������ַ�����ʾ��,xyz֮��ͨ�����ŷָ�
	//��ͨ��ArxUtilHelper::StringToPoint3d��̬��������ת��
	CString m_pt;
};

class PoreLink : public DataLink
{
protected:
	virtual void regDatas()
	{
		linkIntData( _T( "���" ), &m_num );
		linkDoubleData( _T( "�뾶" ), &m_radius );
		//��$�ŵ��ֶα�ʾ���ֶν������ڲ�����,��Ӧ��Ҳ����Ҫ��ʾ�ڶԻ��������
		linkStringData( _T( "$����" ), &m_pt );
	}

public:
	int m_num;
	double m_radius;
	//���������ַ�����ʾ��,xyz֮��ͨ�����ŷָ�
	//��ͨ��ArxUtilHelper::StringToPoint3d��̬��������ת��
	CString m_pt;
};