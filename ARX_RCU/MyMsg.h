#pragma once

/**
* �Զ�����Ϣ�ο�����:
	http://blog.csdn.net/code_robot/article/details/7724667
	http://blog.csdn.net/penpenandtongtong/article/details/18598907
	��PostMessage������
	http://blog.csdn.net/tian_jinping/article/details/23264649
*/

//����ͼԪ
#define WM_RCU_ADD WM_USER+1000
//ɾ��ͼԪ
#define WM_RCU_DEL WM_USER+1001
//�޸�ͼԪ
#define WM_RCU_MODIFY WM_USER+1002
//ˢ�¶Ի���
#define WM_RCU_UPDATE WM_USER+1003

//�Զ�����Ϣ����
struct ArxMsg
{
	CString clsName;     // ��������
	AcDbObjectId objId;  // ͼԪID
};