#pragma once

#include "../MineGE/DataLink.h"

//typedef AcArray<TWS_DataLink> TWS_DataLinkArray;

class TVNSDataLink : public DataLink
{
protected:
	virtual void regDatas();

public:
	CString name;                 // ����
};

// ���������ģ��
class TWS_DataLink : public TVNSDataLink
{
protected:
	virtual void regDatas();

public:
	double area;                  // �������
	double lenth;                 // ������ĳ���
	double q;

};

// �������
class Tunnel_DataLink : public TVNSDataLink
{
public:
	Tunnel_DataLink();
	~Tunnel_DataLink();

protected:
	virtual void regDatas();

public:
	double area;                  // �������
	double lenth;
};


//���ڶ�ȡ���ݵķ�Ͳ��������
class Chimney_DataLink : public TVNSDataLink
{
protected:
	virtual void regDatas();

public:
	double lenth;
	CString bends;
	double diameter;      // ֱ��
	CString tm;          // ��������
	double leakage;		//����©����
	int joints;			//��ͷ����
	double friction;	//Ħ������ϵ��
	double leakageFactor; //©��ϵ��
	double windage;			//����
	double hmWindage;		//���׷���
};

//������������
class BaseparamDataLink : public DataLink
{
protected:
	virtual void regDatas();

public:
	//CString name;                 // ����
	//CString district;              // ��������
	CString method;						//ͨ�緽��
	CString way;						//ͨ�緽ʽ
};

//�������
class Vent_InitDataLink : public DataLink
{
protected:
	virtual void regDatas();
public:
	double T;
	double ro;
	//double speed;
	double q0;
	double Cp;
};

class Vent_DataLink : public DataLink
{
protected:
	virtual void regDatas();
public:
	double m_time;			//ͨ��ʱ��
	double m_speed;			//�ų�����
	double m_A;				//ըҩ��
	double m_N;				//��������
	CString m_dynamiteWay;	//������ʽ
	double m_g;				//ƽ������
	double m_q0;			//����ָ��
	double m_PN;			//������
	double m_C1;			//����Ũ��
	double m_inT;			//���������
	double m_outT;			//�ŷ������
	double m_allPower;		//��ɢ����
	double m_Cp;			//�������ȱ�
	double m_ro;			//�����ܶ�
};

//�������
class LeakageCacul_DataLink : public DataLink
{
protected:
	virtual void regDatas();
public:
	CString hmLeakage;
	CString leakageFactor;
};
