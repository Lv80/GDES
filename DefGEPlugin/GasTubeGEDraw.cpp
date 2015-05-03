#include "StdAfx.h"
#include "GasTubeGEDraw.h"
#include "DrawTool.h"

ACRX_CONS_DEFINE_MEMBERS ( GasTubeGEDraw, LinkedGEDraw, 1 )

GasTubeGEDraw::GasTubeGEDraw()
{
}

GasTubeGEDraw::~GasTubeGEDraw( void )
{
}

void GasTubeGEDraw::setAllExtraParamsToDefault()
{

}

void GasTubeGEDraw::configExtraParams()
{

}

void GasTubeGEDraw::updateExtraParams()
{

}

void GasTubeGEDraw::readExtraParam( DrawParamReader& reader )
{
	// do nothing
}

void GasTubeGEDraw::writeExtraParam( DrawParamWriter& writer )
{
	// do nothing
}

void GasTubeGEDraw::extendByLength( double length )
{
	AcGeVector3d v = m_endPt - m_startPt;
	v.normalize();

	m_endPt = m_endPt + v * length; // �޸�ĩ������
}

Adesk::Boolean GasTubeGEDraw::subWorldDraw( AcGiWorldDraw* mode )
{
	assertReadEnabled () ;

	AcGePoint3dArray pts;
	pts.append( m_startPt );
	pts.append( m_endPt );
	mode->geometry().worldLine( pts.asArrayPtr() );
	//DrawPolyLine( mode, m_startPt, m_endPt, 10 );

	return Adesk::kTrue;
}

//----- AcDbEntity protocols
Acad::ErrorStatus GasTubeGEDraw::subTransformBy( const AcGeMatrix3d& xform )
{
	m_startPt.transformBy( xform );
	m_endPt.transformBy( xform );

	return Acad::eOk;
}

//- Osnap points protocol
Acad::ErrorStatus GasTubeGEDraw::subGetOsnapPoints (
	AcDb::OsnapMode osnapMode,
	Adesk::GsMarker gsSelectionMark,
	const AcGePoint3d& pickPoint,
	const AcGePoint3d& lastPoint,
	const AcGeMatrix3d& viewXform,
	AcGePoint3dArray& snapPoints,
	AcDbIntArray& geomIds ) const
{
	assertReadEnabled () ;

	// ֻ��׽1�����͵ĵ㣺�˵�
	if( osnapMode != AcDb::kOsModeEnd )
		return Acad::eOk;

	Acad::ErrorStatus es = Acad::eOk;

	if ( osnapMode == AcDb::kOsModeEnd )
	{
		snapPoints.append( m_startPt );
		snapPoints.append( m_endPt );
	}

	return es;
}

//- Grip points protocol
Acad::ErrorStatus GasTubeGEDraw::subGetGripPoints (
	AcGePoint3dArray& gripPoints, AcDbIntArray& osnapModes, AcDbIntArray& geomIds ) const
{
	assertReadEnabled () ;
	//----- This method is never called unless you return eNotImplemented
	//----- from the new getGripPoints() method below (which is the default implementation)

	gripPoints.append( m_startPt );
	gripPoints.append( m_endPt );
	return Acad::eOk;
}

Acad::ErrorStatus GasTubeGEDraw::subMoveGripPointsAt ( const AcDbIntArray& indices, const AcGeVector3d& offset )
{
	assertWriteEnabled () ;
	//----- This method is never called unless you return eNotImplemented
	//----- from the new moveGripPointsAt() method below (which is the default implementation)

	for( int i = 0; i < indices.length(); i++ )
	{
		int idx = indices.at( i );
		// ʼ�ڵ�
		if ( idx == 0 ) m_startPt += offset;

		if ( idx == 1 ) m_endPt += offset;
	}
	return Acad::eOk;
}

Acad::ErrorStatus GasTubeGEDraw::subGetGeomExtents( AcDbExtents& extents ) const
{
	assertReadEnabled();

	extents.addPoint( m_startPt );
	extents.addPoint( m_endPt );

	return Acad::eOk;
}
