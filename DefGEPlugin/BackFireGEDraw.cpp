#include "StdAfx.h"
#include "BackFireGEDraw.h"

#include "DrawTool.h"
#include "DrawSpecial.h"

ACRX_CONS_DEFINE_MEMBERS ( BackFireGEDraw, MineGEDraw, 1 )

BackFireGEDraw::BackFireGEDraw()
{
}

BackFireGEDraw::~BackFireGEDraw( void )
{
}

void BackFireGEDraw::setAllExtraParamsToDefault()
{
	m_radius = 3;
}

void BackFireGEDraw::configExtraParams()
{

}

void BackFireGEDraw::updateExtraParams()
{

}

void BackFireGEDraw::writeKeyParam( DrawParamWriter& writer )
{
	writer.writePoint( m_insertPt );
	writer.writeDouble( m_angle );
}

void BackFireGEDraw::readKeyParam( DrawParamReader& reader )
{
	reader.readPoint( m_insertPt );
	reader.readDouble( m_angle );
}

void BackFireGEDraw::readExtraParam( DrawParamReader& reader )
{
	reader.readDouble( m_radius );
}

void BackFireGEDraw::writeExtraParam( DrawParamWriter& writer )
{
	writer.writeDouble( m_radius );
}

Adesk::Boolean BackFireGEDraw::subWorldDraw( AcGiWorldDraw* mode )
{
	assertReadEnabled () ;

	DrawCircle(mode,m_insertPt,m_radius,false);
	double pi = 3.1415926;
	AcGePoint3d spt,ept;
	AcGeVector3d v( AcGeVector3d::kXAxis );
	v.rotateBy( m_angle, AcGeVector3d::kZAxis );
	v.rotateBy(-pi / 4,AcGeVector3d::kZAxis);

	spt = m_insertPt + v * m_radius;
	ept = m_insertPt - v * m_radius;

	DrawLine(mode,spt,ept);

	return Adesk::kTrue;
}

Acad::ErrorStatus BackFireGEDraw::subTransformBy( const AcGeMatrix3d& xform )
{
	AcGeVector3d v( AcGeVector3d::kXAxis );
	v.rotateBy( m_angle, AcGeVector3d::kZAxis );
	v.transformBy( xform );

	// 1) ����һ��Բ
	AcDbCircle circle(m_insertPt, AcGeVector3d::kZAxis, m_radius);
	// 2) Բ����transformBy()�������б任
	circle.transformBy(xform);
	//3) ��ȡ���º�Ĳ���
	m_insertPt = circle.center();     // ��ȡ�任���Բ������
	m_radius = circle.radius(); // ��ȡ�任���Բ�뾶
	m_angle = v.angleTo( AcGeVector3d::kXAxis, -AcGeVector3d::kZAxis ); // �任�����ת�Ƕ�

	return Acad::eOk;
}

Acad::ErrorStatus BackFireGEDraw::subGetOsnapPoints (
	AcDb::OsnapMode osnapMode,
	Adesk::GsMarker gsSelectionMark,
	const AcGePoint3d& pickPoint,
	const AcGePoint3d& lastPoint,
	const AcGeMatrix3d& viewXform,
	AcGePoint3dArray& snapPoints,
	AcDbIntArray& geomIds ) const
{
	assertReadEnabled () ;
	if( osnapMode != AcDb::kOsModeCen )
		return Acad::eOk;

	Acad::ErrorStatus es = Acad::eOk;

	if( osnapMode == AcDb::kOsModeCen )
	{
		snapPoints.append( m_insertPt );
	}

	return es;
}

Acad::ErrorStatus BackFireGEDraw::subGetGripPoints( AcGePoint3dArray& gripPoints, AcDbIntArray& osnapModes, AcDbIntArray& geomIds ) const
{
	assertReadEnabled () ;

	gripPoints.append( m_insertPt );

	//AcGeVector3d v(AcGeVector3d::kXAxis);
	//v.rotateBy(m_angle,AcGeVector3d::kZAxis);
	//v *= m_radius;

	//gripPoints.append(m_insertPt + v);             // ������˵���Ϊ�е�

	return Acad::eOk;
}

Acad::ErrorStatus BackFireGEDraw::subMoveGripPointsAt( const AcDbIntArray& indices, const AcGeVector3d& offset )
{
	assertWriteEnabled () ;

	for( int i = 0; i < indices.length(); i++ )
	{
		int idx = indices.at( i );
		if ( idx == 0 )
		{
			m_insertPt += offset; 			// �����ƫ��
		}
		//if(idx == 1)
		//{
		//	// ����Բ
		//	// 1) ����x��Ķ˵�����
		//	AcGeVector3d v(AcGeVector3d::kXAxis);
		//	v.rotateBy(m_angle,AcGeVector3d::kZAxis);
		//	AcGePoint3d pt = m_insertPt + v*m_radius;

		//	// 2) ��������ƫ�Ƽ���
		//	pt += offset;

		//	// 3) ������������Բ��֮��ĳ��ȣ�����ΪԲ�뾶
		//	// ����������õ�һ��������Ȼ��õ���������
		//	m_radius = (pt - m_insertPt).length();
		//}
	}
	return Acad::eOk;
}

static void DividArc( const AcGePoint3d& spt, const AcGePoint3d& ept, const AcGePoint3d& thirdPt,
					 int count, AcGePoint3dArray& pts )
{
	pts.append( spt );

	AcGeCircArc3d arc( spt, thirdPt, ept );
	AcGePoint3d cnt = arc.center();
	//	double radius = arc.radius();
	AcGeVector3d v1 = spt - cnt;
	AcGeVector3d v2 = ept - cnt;
	int c = ( arc.normal().z > 0 ? 1 : -1 ); // ���߷���

	double a1 = v1.angleTo( AcGeVector3d::kXAxis, -AcGeVector3d::kZAxis );
	double a2 = v2.angleTo( AcGeVector3d::kXAxis, -AcGeVector3d::kZAxis );

	double dq = abs( a2 - a1 ) / count;
	//acutPrintf(_T("\na1:%.3f, a2:%.3f dq:%.3f c:%d"), a1, a2, dq, c);
	for( int i = 1; i < count; i++ )
	{
		v1.rotateBy( c * dq, AcGeVector3d::kZAxis );
		pts.append( cnt + v1 );
		//acutPrintf(_T("\n��%d:(%d,%d)"),i,pts[i].x,pts[i].y);
	}
	pts.append( ept );
}

void BackFireGEDraw::caclBackGroundMinPolygon( AcGePoint3dArray& pts )
{
	AcGeVector3d v0( AcGeVector3d::kXAxis );
	//AcGeCircArc3d arc( m_insertPt, v,m_radius );
	v0.rotateBy( m_angle, AcGeVector3d::kZAxis );
	//AcGePoint3d cnt = arc.center();
	AcGePoint3d spt = m_insertPt + v0*m_radius;
	AcGePoint3d ept = m_insertPt - v0*m_radius;
	v0.rotateBy(3.1415926/4,AcGeVector3d::kZAxis);
	AcGePoint3d pt = m_insertPt + v0*m_radius;

	AcGeCircArc3d arc( spt, pt, ept );
	AcGePoint3d cnt = arc.center();
	double radius = arc.radius();

	AcGeVector3d v = pt - cnt;
	v.normalize();

	DividArc( spt, ept, cnt + v * ( radius ), 90, pts );
	DividArc( ept, spt, cnt - v * ( radius ), 90, pts );

}

void BackFireGEDraw::regPropertyDataNames( AcStringArray& names ) const
{
	names.append(_T("��С"));
}

void BackFireGEDraw::readPropertyDataFromGE( const AcStringArray& values )
{
	CString strLenth;
	strLenth.Format(_T("%s"),values[0].kACharPtr());

	m_radius = _tstof(strLenth);
	if( 0 >= m_radius ) m_radius = 5;
}