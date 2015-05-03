#pragma once

// Ԥ����һЩͼԪ���������ݳ���(ö��)

/*******************************/
/****** ���(Tunnel)���*******/
/*******************************/

// ��������
enum MATERIAL_TYPE
{
	MT_RIGID     = 0,   // ���Է�Ͳ(Ĭ��)
	MT_FLEXIBLE  = 1,   // ���Է�Ͳ
};

// ͨ������
// ���û��ָ����Ĭ��Ϊ����
enum VENT_TYPE
{
	VT_IN       = 0,   // ����
	VT_OUT      = 1,   // �ط�
};

//ͨ�緽��
enum VENT_METHOD
{
	VP_PUSH    = 0,        // ѹ��ʽ(Ĭ��)
	VP_PULL    = 1		  // ���ʽ
};

// ͨ�緽ʽ
enum VENT_WAY
{
	VENT_AUXI_RAM		= 0,	//������Ͳ
	VENT_DIST_RAM		= 1,	//��Ϸ�Ͳ
	VENT_SIG_DOUB		= 2,	//����˫��
	VENT_LOCAL_SERIER	= 3,	//������Ͳ
	VENT_HYBRID_VNT		= 4,	//���ͨ��
	VENT_WIND_CABT		= 5,	//���ͨ��
	VENT_WIND_LIB		= 6,	//���ͨ��
	VENT_DRILL_VENT		= 7		//���ͨ��
};
