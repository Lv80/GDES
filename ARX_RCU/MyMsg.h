#pragma once

/**
* �Զ�����Ϣ�ο�����:
	http://blog.csdn.net/code_robot/article/details/7724667
	http://blog.csdn.net/penpenandtongtong/article/details/18598907
*/

//����ͼԪ
#define WM_ADD_GE WM_USER+1000
//ɾ��ͼԪ
#define WM_DEL_GE WM_USER+1001
//�޸�ͼԪ
#define WM_CHANGE_GE WM_USER+1002

//�Զ�����Ϣ����
struct ArxMsg
{
	CString clsName;     // ��������
	AcDbObjectId objId;  // ͼԪID
};