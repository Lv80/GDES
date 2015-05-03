#pragma once
#include "../MineGE/LinkedGE.h"

//��������ö��
enum CACUL_BASIS
{
	AFTER_DAMP	= 0,	//���ų�����
	DUST_SPEED	= 1,	//���ų�����
	UNIT_POWER	= 2,	//����λ����
	HEAT_ADJT	= 3,	//��������
	WORKER_NUM	= 4		//������Ա��
};

class VentCaculate
{
public:
		VentCaculate(AcDbObjectId objId);
		~VentCaculate();
		/*static */void ensureAir();
private:
	void initDatas(AcDbObjectId objId);
	/*static */double afterDampAirCacul();
	double speedAirCacul();
	double powerAirCacul();
	double tempAirCacul();
	double workerAirCacul();

	double getVentLenth(AcDbObjectId objId);
	
	LinkedGE* getLinkedGE(AcDbObjectId objId);

	void cheakQ();
public:
	//������
	double m_rqAirflow;		//���������
	//double m_airLeakage;	//©�籸��ϵ��
	//double m_windage;		//����
	int m_basis;	//���������ļ�������
	
	CString m_dynamiteWay;	//������ʽ

private:
	//��������Ҫ�ı���
	double m_lenth;			//�������
	double m_area;			//����������
	
	//�����������
	double m_time;			//ͨ��ʱ��
	double m_speed;			//�ų�����
	double m_A;				//ըҩ��
	double m_N;				//��������
	double m_g;				//ƽ������
	double m_q0;			//����ָ��
	double m_PN;			//������
	double m_C1;			//����Ũ��
	double m_inT;			//���������
	double m_outT;			//�ŷ������
	double m_allPower;		//��ɢ����
	double m_Cp;			//�������ȱ�
	double m_ro;			//�����ܶ�
	
	//��������
	CString m_method;				//ͨ�緽��
	CString m_way;				//ͨ�緽ʽ

};

