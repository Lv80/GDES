#pragma once

#include "MyMsg.h"

class UIHelper
{
public:
	//��ʾʯ����Ʒ�ģ̬�Ի���
	static void ShowRcuDesignDockBar();
	//����ʯ����ƶԻ���
	static void DestroyRcuDesignDockBar();
	//��ʯ����ƶԻ�������Ϣ
	static void SendMessage(unsigned int msgCode, ArxMsg* msgParam);
};
