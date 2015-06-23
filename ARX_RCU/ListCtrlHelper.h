#pragma once

struct ItemData
{
	int iItem;            // �ڼ��е�����
	AcDbObjectId objId;   // ����id
};

class ListCtrlHelper
{
public:
	static int SearchRowOfList(CListCtrl& m_list, const AcDbObjectId& objId);
	//�б��еĵ�ǰѡ�е���
	static int GetCurSelOfList(CListCtrl& m_list);
	//�����б���б�ͷ
	static void BuildListCtrlHeadColumns(CListCtrl& m_list, const AcStringArray fields);
	//����һ��
	static int InsertRowToListCtrl(CListCtrl& m_list, const AcDbObjectId& objId);
	//�Ӷ��ͼԪ����ȡ���ݲ����ӵ��б���
	static void InsertDatasToListCtrl(CListCtrl& m_list, const AcStringArray fields, const AcDbObjectIdArray& objIds);
	//ɾ���б��е�ĳһ������
	static void DeleteListCtrlItem(CListCtrl& m_list, int row);
	//����б�
	static void ClearListCtrl(CListCtrl& m_list);
};