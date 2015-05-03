#pragma once

#include "BuildVentNetwork.h"
#include "VentEdgeData.h"

typedef Digraph::ArcMap<VentEdgeData*> DFS_EdgeDataMap;

class DfsNetWork
{
public:
	DfsNetWork(void);
	~DfsNetWork(void);

	Digraph::Arc getEdgeById(const AcDbObjectId& objId);       // ����id���ҷ�֧
	AcDbObjectId getIdByEdge(Digraph::Arc e);                  // ���ݷ�֧����id

	void doDFS(Digraph::Arc se, Digraph::Arc te, EdgeArray& p);
	void getAllPath(Digraph::Arc se,Digraph::Arc te,IntArray& pathNums,EdgeArray& allPath);

private:
	bool initNetwok();	                 // �������粢��ȡͼԪ��������
	bool isInitNetworkOk() const;        // ��ʼ�������Ƿ�ɹ�
	void setInitNetwokState(bool bState);// ���������ʼ��״̬(�ɹ�/ʧ��)
	void initAirEdges();                 // ��ʼ���÷�ص��֧

private:
	Digraph dg;                       // ͨ������(����ͼ)
	ArcFilter ef;                     // ��Ϸ�֧����
	Digraph::Node sn, tn;             // ��������Դ��ͻ��
	//NodeGeoDataMap ngm;

	DFS_EdgeDataMap datas;         // ��֧������(��֧��ͨ�����ͣ����ֶ�)
	EdgeArray airEdges;                 // �÷�ص��֧����
	bool bInitNetwokState;            // �����ʼ���Ƿ�ɹ�(Ĭ�ϳɹ�)
};
