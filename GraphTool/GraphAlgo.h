#pragma once

#include "dlimexp.h"

//ͼ�㷨������
class GRAPH_EXPORT_API GraphAlgo
{
public:
	//����������·֮���������˹��··��
	static void FindGasTubePaths(const AcDbObjectId& sObjId, const AcDbObjectId& tObjId, AcDbIntArray& pathNums, AcDbObjectIdArray& allPaths);
};