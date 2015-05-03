#include "StdAfx.h"

#include "GraphAlgo.h"
//�������������ͷ�ļ�
#include "DfsNetWork.h"
#include "../ArxHelper/ArxUtilHelper.h"
#include "../ArxHelper/ArxEntityHelper.h"

static void SetGasTubeColor(AcDbObjectIdArray objIds)
{
	// ��¼ԭ������ɫ
	AcArray<Adesk::UInt16> colors;
	if( !ArxEntityHelper::GetEntitiesColor( objIds, colors ) ) return;

	// ������ʾ��ǩͼԪ
	ArxEntityHelper::SetEntitiesColor( objIds, 4 );

	// �ж�
	ArxUtilHelper::Pause();

	// �ָ�ԭ����ɫ
	ArxEntityHelper::SetEntitiesColor2( objIds, colors );

	//ArxEntityHelper::SetEntitiesColor( objIds, 4 ); // ��ɫ������ʾ·��

}

static void DealPaths(DfsNetWork& dn, IntArray& pathNums, EdgeArray& allPath)
{
	int st = 0;
	for(int i=0;i<pathNums.size();i++)
	{
		//��i��·���ķ�֧����
		int n = pathNums[i];
		//acutPrintf(_T("\n��%d��·���ķ�֧��:%d"),i+1,n);
		//��i��·��
		EdgeArray p;
		//��allPath�и��Ƶ�����p��
		std::copy(allPath.begin()+st, allPath.begin()+st+n, std::back_inserter(p));
		//��һ��·���Ŀ�ʼλ��
		st += n;
		//GetObjIdsByArc(dn,objIds,p);
		AcDbObjectIdArray objIds;
		int len = p.size();
		for( int i = 0; i < len; i++ )
		{
			objIds.append( dn.getIdByEdge( p[i] ) );
		}
		if(!objIds.isEmpty())
		{
			SetGasTubeColor(objIds);
		}
	}
}

void GraphAlgo::FindGasTubePaths(const AcDbObjectId& sObjId, const AcDbObjectId& tObjId, AcDbIntArray& pathNums, AcDbObjectIdArray& allPaths)
{
	DfsNetWork dn;
	//acutPrintf(_T("\n��ʼ����·��....ʼ��:%ld, ĩ��:%ld"), sObjId.asOldId(), tObjId.asOldId());
	
	Digraph::Arc se = dn.getEdgeById( sObjId );
	Digraph::Arc te = dn.getEdgeById( tObjId );

	//acutPrintf(_T("\n��ʼ����·��....ʼ���֧�ڲ����:%d"), se == INVALID ? -1 : Digraph::id(se));
	//acutPrintf(_T("\n��ʼ����·��....ĩ���֧�ڲ����:%d"), te == INVALID ? -1 : Digraph::id(te));

	IntArray g_pathNums;
	EdgeArray g_allPaths;
	dn.getAllPath(dn.getEdgeById( sObjId ), dn.getEdgeById( tObjId ), g_pathNums, g_allPaths);

	//��lemon��֧ת���ɶ�Ӧ��objectid
	//acutPrintf(_T("\n·������:%d\n"),g_pathNums.size());
	if(!g_pathNums.empty())
	{
		for(int i=0;i<g_pathNums.size();i++)
		{
			//acutPrintf(_T("%d "), g_pathNums[i]);
			pathNums.append(g_pathNums[i]);
		}
		//acutPrintf(_T("\n"));
		for(int i=0;i<g_allPaths.size();i++)
		{
			allPaths.append(dn.getIdByEdge(g_allPaths[i]));
		}
	}
}