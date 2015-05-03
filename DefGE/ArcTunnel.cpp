#include "StdAfx.h"
#include "ArcTunnel.h"

Adesk::UInt32 ArcTunnel::kCurrentVersionNumber = 1 ;

ACRX_DXF_DEFINE_MEMBERS (
    ArcTunnel, Tunnel,
    AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent,
    AcDbProxyEntity::kNoOperation,
    �������, DEFGEAPP
)

ArcTunnel::ArcTunnel () : Tunnel ()
{
}

ArcTunnel::ArcTunnel( const AcGePoint3d& startPt, const AcGePoint3d& endPt, const AcGePoint3d& thirdPt )
    : Tunnel( startPt, endPt ), m_thirdPt( thirdPt )
{

}

ArcTunnel::~ArcTunnel ()
{
}

AcGePoint3d ArcTunnel::getThirdPt() const
{
    assertReadEnabled();

    return m_thirdPt;
}

void ArcTunnel::setThirdPt( const AcGePoint3d& pt )
{
    assertWriteEnabled();

    m_thirdPt = pt;
}

AcGePoint3d ArcTunnel::getArcCntPt() const
{
	assertReadEnabled();
	AcGeCircArc3d arc( m_startPt, m_endPt, m_thirdPt );
	AcGePoint3d cnt = arc.center();//Բ��ԭ��
	double radius = arc.radius();//Բ���뾶

	AcGeVector3d v = m_startPt - m_endPt;

	AcGePoint3d sePt = m_startPt + v * 0.5;//Բ��ʼĩ�ڵ���е�
	AcGeVector3d vt = m_thirdPt - sePt;

	v.rotateBy(PI*0.5, AcGeVector3d::kZAxis);//��ʼĩ������ת90��

	double anglev = v.angleTo( AcGeVector3d::kXAxis, -AcGeVector3d::kZAxis );
	double anglevt = vt.angleTo( AcGeVector3d::kXAxis, -AcGeVector3d::kZAxis );
	double cp = abs(anglev-anglevt);
	if (cp > PI)//��֤�н�Ϊ���
	{
		cp = 2*PI - cp;
	}

	if (cp > PI * 0.5)//����нǴ���90�ȣ�˵��Ҫ��ȡ�ĵ���Բ������һ��
	{
		v = -v;
	}
	v.normalize();

	return cnt + v * radius;
}

Acad::ErrorStatus ArcTunnel::dwgOutFields ( AcDbDwgFiler* pFiler ) const
{
    assertReadEnabled () ;

    Acad::ErrorStatus es = Tunnel::dwgOutFields ( pFiler ) ;
    if ( es != Acad::eOk )
        return ( es ) ;

    if ( ( es = pFiler->writeUInt32 ( ArcTunnel::kCurrentVersionNumber ) ) != Acad::eOk )
        return ( es ) ;

    pFiler->writeItem( m_thirdPt );

    return ( pFiler->filerStatus () ) ;
}

Acad::ErrorStatus ArcTunnel::dwgInFields ( AcDbDwgFiler* pFiler )
{
    assertWriteEnabled () ;

    Acad::ErrorStatus es = Tunnel::dwgInFields ( pFiler ) ;
    if ( es != Acad::eOk )
        return ( es ) ;

    Adesk::UInt32 version = 0 ;
    if ( ( es = pFiler->readUInt32 ( &version ) ) != Acad::eOk )
        return ( es ) ;
    if ( version > ArcTunnel::kCurrentVersionNumber )
        return ( Acad::eMakeMeProxy ) ;

    pFiler->readItem( &m_thirdPt );

    return ( pFiler->filerStatus () ) ;
}

void ArcTunnel::writeKeyParam( DrawParamWriter& writer ) const
{
    assertReadEnabled();

    LinkedGE::writeKeyParam( writer );
    writer.writePoint( m_thirdPt );

}

void ArcTunnel::readKeyParam( DrawParamReader& reader )
{
    assertWriteEnabled();

    LinkedGE::readKeyParam( reader );
    reader.readPoint( m_thirdPt );

}

bool ArcTunnel::ptIsOnArc( AcGePoint3d pt ) const
{
	AcGePoint3d cntArcPt = getArcCntPt();
	AcGePoint3d cntSEPt = AcGePoint3d((m_startPt.x+m_endPt.x)/2,(m_startPt.y+m_endPt.y)/2,0);
	
	AcGeVector3d ptVec = pt - cntSEPt;
	AcGeVector3d cntArcVec = cntArcPt - cntSEPt;

	double anglePtV = ptVec.angleTo(AcGeVector3d::kXAxis,-AcGeVector3d::kZAxis);
	double angleCntArcPtV = cntArcVec.angleTo(AcGeVector3d::kXAxis,AcGeVector3d::kZAxis);

	double cp = abs(anglePtV-angleCntArcPtV);
	if (cp > PI)//��֤�н�Ϊ���
	{
		cp = 2*PI - cp;
	}

	bool ret = false;
	if (cp < PI * 0.5)//����нǴ���90�ȣ�˵���ĵ���Բ������һ��
	{
		ret = true;
	}

	return ret;
}

double ArcTunnel::getArcAngle(AcGePoint3d insertPt)
{
	AcGePoint3d arcCentPt = getArcCntPt();
	AcGeCircArc3d arc(m_startPt,arcCentPt,m_endPt);
	AcGePoint3d cnt = arc.center();

	AcGeVector3d sptToInsertPtVec = insertPt - m_startPt;
	double sptInsertPtLenth = sptToInsertPtVec.lengthSqrd();

	AcGeVector3d eptToInsertPtVec = insertPt - m_endPt;
	double eptInsertPtLenth = eptToInsertPtVec.lengthSqrd();

	AcGeVector3d cntToPtVec;
	//acutPrintf(_T("\n��ʼ��ľ�����:%f,��ĩ��ľ�����:%f"),sptInsertPtLenth,eptInsertPtLenth);

	if (sptInsertPtLenth > eptInsertPtLenth)
	{
		//acutPrintf(_T("\n����ĩ��ȽϽ�,������:%f"),eptInsertPtLenth);
		AcGeVector3d thirdPtToEptVec = m_endPt - arcCentPt;
		thirdPtToEptVec.normalize();
		cntToPtVec = insertPt - cnt;
		cntToPtVec.rotateBy(PI*0.5,AcGeVector3d::kZAxis);
		cntToPtVec.normalize();

		double angleTE = cntToPtVec.angleTo(thirdPtToEptVec/*,-AcGeVector3d::kZAxis*/);
		//acutPrintf(_T("\n��ԽǶ���:%f"),angleTE);

		//if (angleTE > PI)
		//{
		//	angleTE = 2*PI - angleTE;
		//}

		if (angleTE > 0.5 * PI)
		{
			cntToPtVec = - cntToPtVec;
		}

	}

	else
	{
		//acutPrintf(_T("\n����ʼ��ȽϽ�,������:%f"),sptInsertPtLenth);
		AcGeVector3d sptToThirdPtVec = arcCentPt - m_startPt;
		sptToThirdPtVec.normalize();
		cntToPtVec = insertPt - cnt;
		cntToPtVec.rotateBy(PI*0.5,AcGeVector3d::kZAxis);
		cntToPtVec.normalize();

		double angleST = cntToPtVec.angleTo(sptToThirdPtVec/*,-AcGeVector3d::kZAxis*/);
		//acutPrintf(_T("\n��ԽǶ���:%f"),angleST);

		//if (angleST > PI)
		//{
		//	angleST = 2*PI - angleST;
		//}

		if (angleST > 0.5 * PI)
		{
			cntToPtVec = - cntToPtVec;
		}

	}

	return cntToPtVec.angleTo(AcGeVector3d::kXAxis,-AcGeVector3d::kZAxis);

}
