#include "stdafx.h"
#include "DrawCmd.h"

#include "../MineGE/MineGE.h"
#include "../MineGE/LinkedGE.h"
#include "../MineGE/TagGE.h"
#include "../DefGE/ArcTunnel.h"
#include "../DefGE/Chimney.h"
#include "../DefGE/QTagGE.h"

#include "../MineGE/HelperClass.h"
#include "../ArxHelper/HelperClass.h"

/* ȫ�ֺ���(ʵ����PromptTool.cpp) */
extern bool GetClosePtAndAngle( const AcDbObjectId& objId, AcGePoint3d& pt, double& angle );
extern bool GetSEPt( const AcDbObjectId& objId, AcGePoint3d& spt, AcGePoint3d& ept );

static bool GetInsertPt( const AcDbObjectId& objId, AcGePoint3d& pt )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return false;

    AcDbObject* pObj;
    if( Acad::eOk != pTrans->getObject( pObj, objId, AcDb::kForRead ) )
    {
        actrTransactionManager->abortTransaction();
        return false;
    }
    DirectionTagGE* pDir = DirectionTagGE::cast( pObj );
    if( pDir == 0 )
    {
        actrTransactionManager->abortTransaction();
        return false;
    }

    pt = pDir->getInsertPt();

    actrTransactionManager->endTransaction();

    return true;
}

static void CacLineClosePt( const AcGePoint3d& spt, const AcGePoint3d& ept,
                            AcGePoint3d& pt, double& angle )
{
    // ����һ�������߶�
    AcGeLineSeg3d line( spt, ept );
    pt = line.closestPointTo( pt ); // ���������������ĵ�

    AcGeVector3d v = ept - spt;
    angle = v.angleTo( AcGeVector3d::kXAxis, -AcGeVector3d::kZAxis );
}

//static double getArcAngle(const AcGePoint3d& spt, const AcGePoint3d& ept, const AcGePoint3d& thirdPt,AcGePoint3d insertPt)
//{
//	AcGeCircArc3d arc(spt,thirdPt,ept);
//	AcGePoint3d cnt = arc.center();
//
//	AcGeVector3d cntToPtVec = insertPt - cnt;
//	cntToPtVec.rotateBy(PI*0.5,AcGeVector3d::kZAxis);
//	cntToPtVec.normalize();
//
//	AcGeVector3d sptToInsertPtVec = insertPt - spt;
//	double sptInsertPtLenth = sptToInsertPtVec.lengthSqrd();
//
//	AcGeVector3d eptToInsertPtVec = insertPt - ept;
//	double eptInsertPtLenth = eptToInsertPtVec.lengthSqrd();
//
//	if (sptInsertPtLenth > eptInsertPtLenth)
//	{
//		AcGeVector3d thirdPtToEptVec = ept - thirdPt;
//		thirdPtToEptVec.normalize();
//		double angleTE = cntToPtVec.angleTo(thirdPtToEptVec,-AcGeVector3d::kZAxis);
//		if (angleTE > 0.5 * PI)
//		{
//			cntToPtVec = - cntToPtVec;
//		}
//
//	}
//
//	else
//	{
//		AcGeVector3d sptToThirdPtVec = thirdPt - spt;
//		sptToThirdPtVec.normalize();
//		double angleST = cntToPtVec.angleTo(sptToThirdPtVec,-AcGeVector3d::kZAxis);
//		if (angleST > 0.5 * PI)
//		{
//			cntToPtVec = - cntToPtVec;
//		}
//
//	}
//
//	return cntToPtVec.angleTo(AcGeVector3d::kXAxis,-AcGeVector3d::kZAxis);
//
//}

//static void CacArcClosePt( const AcGePoint3d& spt, const AcGePoint3d& ept, const AcGePoint3d& thirdPt,
//                           AcGePoint3d& pt, double& angle )
//{
//    AcGeCircArc3d arc( spt, thirdPt, ept );
//    AcGePoint3d cnt = arc.center();
//    double radius = arc.radius();
//
//    AcGeVector3d v = ept - cnt;
//    AcGeVector3d v2 = ept - spt;
//    AcGeVector3d v3 = v.crossProduct( v2 );
//    int c = ( v3.z > 0 ? 1 : -1 );
//
//    // ����Բ�������
//    pt = arc.closestPointTo( pt );
//
//    // ����Ƕ�
//    v = pt - cnt;
//    v.rotateBy( c * PI / 2, AcGeVector3d::kZAxis );
//
//    //angle = v.angleTo( AcGeVector3d::kXAxis, -AcGeVector3d::kZAxis );
//	angle = getArcAngle(spt,ept,thirdPt,pt);
//}

static void ResetDirectionGE( const AcDbObjectId& objId, const AcDbObjectId& host, const AcGePoint3d& pt, double angle )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return;

    AcDbObject* pObj;
    if( Acad::eOk != pTrans->getObject( pObj, objId, AcDb::kForWrite ) )
    {
        actrTransactionManager->abortTransaction();
        return;
    }
    DirectionTagGE* pDirTag = DirectionTagGE::cast( pObj );
    if( pDirTag == 0 )
    {
        actrTransactionManager->abortTransaction();
        return;
    }
    pDirTag->setInsertPt( pt );
    pDirTag->setDirectionAngle( angle );
    pDirTag->setRelatedGE( host ); // ����ͼԪ

    actrTransactionManager->endTransaction();
}

void DrawCmd::JunctionEnclose( void )
{
    acutPrintf( _T( "\n����պ����...\n" ) );

    AcGePoint3d pt;
    if( !ArxUtilHelper::PromptPt( _T( "\nѡ����Ҫ�պϴ�������꣺" ), pt ) ) return;

    // ����պ�
    DrawHelper::LinkedGEJunctionClosure( pt );
}

static void ResetArcDirection(AcDbObjectId objId)
{

	AcTransaction* pTrans = actrTransactionManager->startTransaction();
	if( pTrans == 0 ) return;

	AcDbObject* pObj;
	if( Acad::eOk != pTrans->getObject( pObj, objId, AcDb::kForWrite ) )
	{
		actrTransactionManager->abortTransaction();
		return;
	}

	ArcTunnel* pArcTunnel = ArcTunnel::cast( pObj );
	if( pArcTunnel == 0 )
	{
		actrTransactionManager->abortTransaction();
		return;
	}

	pArcTunnel->reverse();  // ����ʼĩ������

	double angle; // �����ĽǶ�

	AcDbObjectIdArray objIds;
	DrawHelper::GetTagGEById2( objId, _T( "DirectionTagGE" ), objIds );
	int len = objIds.length();
	for( int i = 0; i < len; i++ )
	{
		if( Acad::eOk != pTrans->getObject( pObj, objIds[i], AcDb::kForWrite ) ) continue;

		DirectionTagGE* pDir = DirectionTagGE::cast( pObj );
		AcGePoint3d insertPt = pDir->getInsertPt();
		angle = pArcTunnel->getArcAngle(insertPt);
		//2014/8/22�޸�����������䣬Ϊ��ʹѹ��Ϊ����ʱ�����෴
		angle = DrawCmd::ControlDirByMethods(objId,angle);

		pDir->setDirectionAngle( angle );
	}

	actrTransactionManager->endTransaction();
}

static void ReverseTunnelDirection( const AcDbObjectId& objId )
{
	AcTransaction* pTrans = actrTransactionManager->startTransaction();
	if( pTrans == 0 ) return;

	AcDbObject* pObj;
	if( Acad::eOk != pTrans->getObject( pObj, objId, AcDb::kForWrite ) )
	{
		actrTransactionManager->abortTransaction();
		return;
	}

	LinkedGE* pEdge = LinkedGE::cast( pObj );
	if( pEdge == 0 )
	{
		actrTransactionManager->abortTransaction();
		return;
	}

	pEdge->reverse();  // ����ʼĩ������

	double angle = pEdge->getAngle(); // �����ĽǶ�


	// �������з�����ͼԪ���򣬰�����������
	AcDbObjectIdArray objIds;
	DrawHelper::GetTagGEById2( objId, _T( "DirectionTagGE" ), objIds );
	int len = objIds.length();
	for( int i = 0; i < len; i++ )
	{
		if( Acad::eOk != pTrans->getObject( pObj, objIds[i], AcDb::kForWrite ) ) continue;

		DirectionTagGE* pDir = DirectionTagGE::cast( pObj );

		//2014/8/22�޸�����������䣬Ϊ��ʹѹ��Ϊ����ʱ�����෴
		angle = DrawCmd::ControlDirByMethods(objId,angle);

		pDir->setDirectionAngle( angle );
	}

	actrTransactionManager->endTransaction();
}

void DrawCmd::ReverseDirection()
{
    AcDbObjectId objId = ArxUtilHelper::SelectObject( _T( "\n��ѡ��һ����֧��ͼԪ [�������˹��·��]��" ) );
    if( !ArxUtilHelper::IsEqualType( _T( "LinkedGE" ), objId ) ) return;

	if( ArxUtilHelper::IsEqualType( _T( "ArcTunnel" ), objId ) )
	{
		ResetArcDirection(objId);
	}

	else
	{
		//DrawHelper::ReverseDirection( objId );
		ReverseTunnelDirection( objId );
	}

}

void DrawCmd::ReBindEdge()
{
    CString msg = _T( "��ѡ��һ����ǩͼԪ[����/���ڷ細/����ǽ/���/���վ/��������/����]:" );
    AcDbObjectId objId = ArxUtilHelper::SelectObject( msg );
    if( objId.isNull() ) return;
    if( !ArxUtilHelper::IsEqualType( _T( "DirectionTagGE" ), objId ) ) return;

    CString msg2 = _T( "��ѡ��һ����֧ͼԪ[���/�ɾ�����/����]:" );
    AcDbObjectId host = ArxUtilHelper::SelectObject( msg2 );
    if( !ArxUtilHelper::IsEqualType( _T( "LinkedGE" ), host ) ) return;

    // ��ȡ��ǩͼԪ�Ĳ��������
    AcGePoint3d insertPt;
    if( !GetInsertPt( objId, insertPt ) ) return;

    AcGePoint3d pt;
    if( !ArxUtilHelper::PromptPt2( _T( "\n���ڷ�֧ͼԪ����ѡ��һ�������: " ), insertPt, pt ) ) return;

    double angle;
    GetClosePtAndAngle( host, pt, angle );

    // ���¹���tag
    ResetDirectionGE( objId, host, pt, angle );
}

void DrawCmd::ZoomMineGE()
{
    AcDbObjectId objId = ArxUtilHelper::SelectObject( _T( "��ѡ��һ��ͼԪʵ��:" ) );
    if( objId.isNull() ) return;

    ArxEntityHelper::ZoomToEntity( objId );
}

static bool GetEntStyle( const AcDbObjectId& objId, int& colorIndx, AcDbObjectId& layerId, AcDbObjectId& lineTypeId )
{

	AcTransaction* pTrans = actrTransactionManager->startTransaction();
	if( pTrans == 0 ) return false;

	AcDbObject* pObj;
	if( Acad::eOk != pTrans->getObject( pObj, objId, AcDb::kForWrite ) )
	{
		actrTransactionManager->abortTransaction();
		return false;
	}
	LinkedGE* pEdge = LinkedGE::cast( pObj );
	if( pEdge == 0 )
	{
		actrTransactionManager->abortTransaction();
		return false;
	}
	//if( !ArxUtilHelper::IsEqualType( _T( "ArcTunnel" ), objId ) )
	colorIndx = pEdge->colorIndex();
	layerId = pEdge->layerId();
	lineTypeId = pEdge->linetypeId();
	actrTransactionManager->endTransaction();
	return true;
}


static bool SetSEPt( const AcDbObjectId& objId, const AcGePoint3d& spt, const AcGePoint3d& ept )
{
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return false;

    AcDbObject* pObj;
    if( Acad::eOk != pTrans->getObject( pObj, objId, AcDb::kForWrite ) )
    {
        actrTransactionManager->abortTransaction();
        return false;
    }
    LinkedGE* pEdge = LinkedGE::cast( pObj );
    if( pEdge == 0 )
    {
        actrTransactionManager->abortTransaction();
        return false;
    }
	//if( !ArxUtilHelper::IsEqualType( _T( "ArcTunnel" ), objId ) )
    pEdge->setSEPoint( spt, ept );
    actrTransactionManager->endTransaction();

    return true;
}

static bool SetArcSEPt( const AcDbObjectId& objId, const AcGePoint3d& spt, const AcGePoint3d& ept,const AcGePoint3d& thirdPt )
{
	AcTransaction* pTrans = actrTransactionManager->startTransaction();
	if( pTrans == 0 ) return false;

	AcDbObject* pObj;
	if( Acad::eOk != pTrans->getObject( pObj, objId, AcDb::kForWrite ) )
	{
		actrTransactionManager->abortTransaction();
		return false;
	}
	ArcTunnel* pArcTunnel = ArcTunnel::cast( pObj );
	if( pArcTunnel == 0 )
	{
		actrTransactionManager->abortTransaction();
		return false;
	}
	//if( !ArxUtilHelper::IsEqualType( _T( "ArcTunnel" ), objId ) )
	pArcTunnel->setSEPoint( spt, ept );
	pArcTunnel->setThirdPt(thirdPt);
	actrTransactionManager->endTransaction();

	return true;
}

static bool GetSplitPoint( const AcGePoint3d& spt, const AcGePoint3d& ept, AcGePoint3d& pt )
{
    acedInitGet( RSG_NONULL, _T( "Dist" ) );

    ads_point _pt;
    int rt = acedGetPoint( asDblArray( spt ), _T( "��ָ���ָ������: [����(D)]" ), _pt );

    if( rt == RTKWORD )
    {
        acedInitGet( RSG_NONULL | RSG_NOZERO | RSG_NONEG, NULL );
        double d = 0;
        if( RTNORM != acedGetDist( asDblArray( spt ), _T( "���������: " ), &d ) ) return false;

        AcGeVector3d v = ept - spt;
        v.normalize();
        pt = spt + v * d;
    }
    else if( rt == RTNORM )
    {
        pt = asPnt3d( _pt );
    }
    else
    {
        return false;
    }

    return true;
}

static AcGePoint3d getOnePtOnArc(AcGePoint3d startPt,AcGePoint3d endPt,AcGeCircArc3d arc)
{
	//����һ���㣬�������ڴ������ߣ���������
	AcGePoint3d thirdPt;

	//ʼĩ�ڵ���е�
	AcGePoint3d cntArcPt = AcGePoint3d((startPt.x+endPt.x)/2,(startPt.y+endPt.y)/2,0);

	//��þ���Բ�ĺ����е�ĵ�λ���������ڹ����ཻ��
	AcGeVector3d v = endPt - startPt;
	v.rotateBy(PI*0.5,AcGeVector3d::kZAxis);
	v.normalize();

	//�뻡���ཻ��ֱ��
	AcGeLine3d line(cntArcPt,v);

	//nΪ����ĸ���,getPt1,getPt2�ֱ�Ϊ��һ������͵ڶ�������,���nΪ1����getPt2��Ч
	int n;
	AcGePoint3d getPt1,getPt2;

	while (Adesk::kTrue == arc.intersectWith(line,n,getPt1,getPt2))
	{
		//ֱ��ÿ����ת0.05*180/PI�ȣ�Ȼ�������������Ѱ
		v.rotateBy(0.05,AcGeVector3d::kZAxis);
		line.set(cntArcPt,v);

		if( 1 == n)
		{
			thirdPt = getPt1;
			break;
		}
	}

	return thirdPt;
}

static void splitArcTunnel(AcDbObjectId objId,AcGePoint3d spt,AcGePoint3d ept,AcGePoint3d pt)
{
	AcDbObject* pObj;
	if(Acad::eOk != acdbOpenObject( pObj, objId, AcDb::kForWrite ))return;
	ArcTunnel *pArcTunenl = ArcTunnel::cast(pObj);
	pObj->close();
	AcDbObjectId layerId,lineTypeId;
	int colorIndx;
	GetEntStyle(objId,colorIndx,layerId,lineTypeId);

	AcGeCircArc3d arc( spt, pArcTunenl->getArcCntPt(), ept);
	AcGePoint3d cnt = arc.center();	//Բ��ԭ��
	double radius = arc.radius();	//Բ���뾶

	AcGePoint3d thirdPt = getOnePtOnArc(pt,ept,arc);

	CString type;
	DataHelper::GetTypeName( objId, type );

	//��������㵽ĩ���һ�λ���
	ArcTunnel* pat = ArcTunnel::cast( ArxClassHelper::CreateObjectByType( type ) );
	pat->setSEPoint(pt,ept);
	pat->setThirdPt(thirdPt);
	pat->setLinetype(lineTypeId);
	pat->setColorIndex(colorIndx);
	pat->setLayer(layerId);
	if( !ArxUtilHelper::PostToModelSpace( pat ) )
	{
		// ��ӵ����ݿ�ʧ��
		delete pat;
	}

	else
	{
		//SetArcSEPt(objId,spt,pt,thirdPt2);
		//SetSEPt( objId, spt, pt );
		
		//ɾ��ԭ���Ļ���
		ArxEntityHelper::EraseObject( objId, true );

		thirdPt = getOnePtOnArc(spt,pt,arc);

		//����ʼ�㵽������һ�λ�
		ArcTunnel* pat0 = ArcTunnel::cast( ArxClassHelper::CreateObjectByType( type ) );
		pat0->setSEPoint(spt,pt);
		pat0->setThirdPt(thirdPt);
		pat0->setLinetype(lineTypeId);
		pat0->setColorIndex(colorIndx);
		pat0->setLayer(layerId);

		if( !ArxUtilHelper::PostToModelSpace( pat0 ) )
		{
			// ��ӵ����ݿ�ʧ��
			delete pat0;
		}
	}
}

void DrawCmd::SplitDeal()
{
	AcDbObjectId objId = ArxUtilHelper::SelectObject( _T( "��ѡ����Ҫ�ָ��ͼԪ:" ) );
	if( !ArxUtilHelper::IsEqualType( _T( "LinkedGE" ), objId ) ) return;

	AcGePoint3d spt, ept;
	if( !GetSEPt( objId, spt, ept ) )
	{
		acutPrintf( _T( "\n�޷���ȡʼĩ������" ) );
		return;
	}

	AcGePoint3d pt;
	if( !GetSplitPoint( spt, ept, pt ) ) return;
	//ArxUtilHelper::PromptPt(_T("��ָ���ָ�λ��: "), pt);

	if( pt == spt || pt == ept )
	{
		acutPrintf( _T( "\nʼĩ�㲻����Ϊ�ָ��!!!" ) );
		return;
	}

	SplitByPoint(objId,spt,ept,pt);
}

void DrawCmd::SplitByPoint(AcDbObjectId objId,AcGePoint3d spt,AcGePoint3d ept,AcGePoint3d pt)
{


    double angle;
    GetClosePtAndAngle( objId, pt, angle );
    /*AcGeLine3d L(spt, ept);
    if(!L.isOn(pt))
    {
    	acutPrintf(_T("���/������֮��ĵ㲻����Ϊ�ָ��!!!..."));
    	return;
    }*/

	//LinkedGE* oldEdge = LinkedGE::cast()
	AcDbObjectId layerId,lineTypeId;
	int colorIndx;
	GetEntStyle(objId,colorIndx,layerId,lineTypeId);
    // �½����
    CString type;
    DataHelper::GetTypeName( objId, type );
    LinkedGE* pEdge = LinkedGE::cast( ArxClassHelper::CreateObjectByType( type ) );
    if( pEdge == 0 ) return; // �������ʧ��
	
	pEdge->setColorIndex(colorIndx);
	pEdge->setLayer(layerId);
	pEdge->setLinetype(lineTypeId);

	//����ǻ������
	if( ArxUtilHelper::IsEqualType( _T( "ArcTunnel" ), objId ) )
	{
		splitArcTunnel(objId,spt,ept,pt);
	}
	else
	{
		pEdge->setSEPoint( pt, ept );
		if( !ArxUtilHelper::PostToModelSpace( pEdge ) )
		{
			// ��ӵ����ݿ�ʧ��
			delete pEdge;
		}
		else
		{
			// �ɹ���ӵ����ݿ�
			// ͬʱ�޸�ԭ���������
			SetSEPt( objId, spt, pt );
			DrawHelper::LinkedGEJunctionClosure( pt );
		}
	}
}

static Chimney* getChimObj(AcDbObjectId objId)
{
	AcTransaction* pTrans = actrTransactionManager->startTransaction();
	if( pTrans == 0 ) return NULL;

	AcDbObject* pObj;
	if( Acad::eOk != pTrans->getObject( pObj, objId, AcDb::kForWrite ) )
	{
		actrTransactionManager->abortTransaction();
		return NULL;
	}

	Chimney* pChim = Chimney::cast( pObj );
	if( pChim == 0 )
	{
		actrTransactionManager->abortTransaction();
		return NULL;
	}
	actrTransactionManager->endTransaction();
	
	return pChim;
}

static void UpdateChimney(AcDbObjectId objId)
{
	AcTransaction* pTrans = actrTransactionManager->startTransaction();
	if( pTrans == 0 ) return;

	AcDbObject* pObj;
	if( Acad::eOk != pTrans->getObject( pObj, objId, AcDb::kForWrite ) )
	{
		actrTransactionManager->abortTransaction();
		return;
	}

	Chimney* pChim = Chimney::cast( pObj );
	if( pChim == 0 )
	{
		actrTransactionManager->abortTransaction();
		return;
	}
	pChim->recordGraphicsModified(true);
	actrTransactionManager->endTransaction();

}

void DrawCmd::Merging(AcDbObjectId sourceId,AcDbObjectId mergeId)
{

	Chimney *sourceChim = getChimObj(sourceId);
	Chimney *mergeChim = getChimObj(mergeId);

	AcGePoint3dArray sourcePts = sourceChim->getControlPoint();
	AcGePoint3dArray mergePts = mergeChim->getControlPoint();

	int sourcePtsNum = sourcePts.length();
	int mergePtsNum = mergePts.length();

	AcGePoint3dArray findedPts;

	//��������
	if (sourcePts[0] == mergePts[0])
	{
		AcGePoint3dArray newPts;
		for (int i = sourcePtsNum-1; i >=0 ; i--)
		{
			newPts.append(sourcePts[i]);
		}
		for (int i = 0; i < mergePtsNum; i++)
		{
			newPts.append(mergePts[i]);
		}
		sourceChim->setControlPoint(newPts);
		ArxEntityHelper::EraseObject(mergeId,true);
		UpdateChimney(sourceId);
	}

	//��һ�ε��׽ڵ�͵ڶ��ε�ĩ�ڵ�
	else if (sourcePts[0] == mergePts[mergePtsNum-1])
	{
		for (int i = 0; i < sourcePtsNum; i++)
		{
			mergePts.append(sourcePts[i]);
		}
		mergeChim->setControlPoint(mergePts);
		ArxEntityHelper::EraseObject(sourceId,true);
		UpdateChimney(mergeId);

	}
	//�ڶ��ε�ĩ�ڵ�͵�һ�ε��׽ڵ�
	else if(sourcePts[sourcePtsNum-1] == mergePts[0])
	{
		for (int i = 0; i < mergePtsNum; i++)
		{
			sourcePts.append(mergePts[i]);
		}

		sourceChim->setControlPoint(sourcePts);
		ArxEntityHelper::EraseObject(mergeId,true);
		UpdateChimney(sourceId);

	}

	//ββ����
	else if (sourcePts[sourcePtsNum-1] == mergePts[mergePtsNum-1])
	{
		for (int i = mergePtsNum-1; i >=0 ; i--)
		{
			sourcePts.append(mergePts[i]);
		}
		sourceChim->setControlPoint(sourcePts);
		ArxEntityHelper::EraseObject(mergeId,true);
		UpdateChimney(sourceId);
	}

	else
	{
		//AfxMessageBox(_T("������β������������ܺϲ�!"));
		return;
	}

}

void DrawCmd::MergeChimney()
{
	AcDbObjectId sourceObjId = ArxUtilHelper::SelectObject( _T( "��ѡ����Ҫ�ϲ��ĵ�һ�η�Ͳ:" ) );
	if( !ArxUtilHelper::IsEqualType( _T( "Chimney" ), sourceObjId ) ) return;

	AcDbObjectId mergeObjId = ArxUtilHelper::SelectObject( _T( "��ѡ����Ҫ�ϲ��ĵڶ��η�Ͳ:" ) );
	if( !ArxUtilHelper::IsEqualType( _T( "Chimney" ), mergeObjId ) ) return;

	if (sourceObjId == mergeObjId)
	{
		AfxMessageBox(_T("����ѡ����ͬ�ķ�Ͳ�ϲ�!"),MB_OK | MB_ICONSTOP );
		return;
	}
	Merging(sourceObjId,mergeObjId);
}

double DrawCmd::ControlDirByMethods(AcDbObjectId objId, double angle)
{
	CString name;
	CString method;

	 bool isOppositeDir = false;
	DataHelper::GetPropertyData( objId, _T( "����" ), name );
	if (ArxUtilHelper::IsEqualType( _T( "TTunnel" ), objId ))
	{
		DataHelper::GetPropertyData( objId, _T( "ͨ�緽��" ), method );
	}
	else
	{
		AcDbObjectId tWorkId = DrawHelper::GetRelatedTW(objId);		
		DataHelper::GetPropertyData( tWorkId, _T( "ͨ�緽��" ), method );
	}

	if ( _T("������") != name && _T("�ط���") != name)
	{
		if (_T("ѹ��ʽ") == method || _T("��ѹ�̳�") == method)
		{
			isOppositeDir = true;
		}
	}

	if (true == isOppositeDir)
	{
		angle = PI + angle;
	}

	return angle;
}

void DrawCmd::DeleteDirection()
{
	AcDbObjectIdArray objIds;
	DrawHelper::FindMineGEs(_T("WindDirection"),objIds);
	for(int i = 0; i < objIds.length(); i++)
	{
		ArxEntityHelper::EraseObject( objIds[i], true );
	}
}

void DrawCmd::DeleteAllGasFlow()
{
	AcDbObjectIdArray objIds;
	DrawHelper::FindMineGEs(_T("GasFlowTagGE"),objIds);
	for(int i = 0; i < objIds.length(); i++)
	{
		ArxEntityHelper::EraseObject( objIds[i], true );
	}
}

void DrawCmd::DeleteFanTag()
{
	AcDbObjectIdArray objIds;
	DrawHelper::FindMineGEs(_T("FanTagGE"),objIds);
	for(int i = 0; i < objIds.length(); i++)
	{
		ArxEntityHelper::EraseObject( objIds[i], true );
	}

}

void DrawCmd::DeleteQTag()
{
	AcDbObjectIdArray objIds;
	DrawHelper::FindMineGEs(_T("QTagGE"),objIds);
	for(int i = 0; i < objIds.length(); i++)
	{
		ArxEntityHelper::EraseObject( objIds[i], true );
	}

}

void DrawCmd::DeleteEDTag()
{
	AcDbObjectIdArray objIds;
	DrawHelper::FindMineGEs(_T("EffectRanTagGE"),objIds);
	for(int i = 0; i < objIds.length(); i++)
	{
		ArxEntityHelper::EraseObject( objIds[i], true );
	}

}

#include "../DefGE/Joint.h"
void DrawCmd::testHD()
{
	AcDbObjectIdArray objIds;
	ArxUtilHelper::GetPickSetEntity( objIds );
	if( objIds.length() != 1 ) return;
	for(int i = 0; i < objIds.length();i++)
	{
		AcTransaction *pTran = actrTransactionManager->startTransaction();
		if(0 == pTran) return;
		AcDbObject *pObjt;
		if(Acad::eOk != pTran->getObject(pObjt,objIds[i],AcDb::kForWrite)) return;
		Test *test = Test::cast(pObjt);
		actrTransactionManager->endTransaction();

		if( !ArxUtilHelper::PostToModelSpace( test ) )
		{
			// ��ӵ����ݿ�ʧ��
			delete test;
		}

	}
	//Tunnel *pTunnel = Tunnel::cast()

}