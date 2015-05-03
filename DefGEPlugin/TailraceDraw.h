#pragma once

#include "../MineGEDraw/MineGEDraw.h"

class TailraceGEDraw : public MineGEDraw
{
public:
	ACRX_DECLARE_MEMBERS(TailraceGEDraw);

public:
	TailraceGEDraw();
	~TailraceGEDraw(void);

	virtual void setAllExtraParamsToDefault();
	virtual void configExtraParams();
	virtual void updateExtraParams();

	virtual void readKeyParam(DrawParamReader& reader);
	virtual void writeKeyParam(DrawParamWriter& writer);

	virtual void regPropertyDataNames(AcStringArray& names) const;
	virtual void readPropertyDataFromGE(const AcStringArray& values);

	virtual void readExtraParam(DrawParamReader& reader);
	virtual void writeExtraParam(DrawParamWriter& writer);

	virtual void caclBackGroundMinPolygon(AcGePoint3dArray& pts);

private:
	void caculPts();

protected:
	virtual Adesk::Boolean subWorldDraw (AcGiWorldDraw *mode);

	virtual Acad::ErrorStatus subTransformBy(const AcGeMatrix3d & xform);

	virtual Acad::ErrorStatus subGetOsnapPoints (
		AcDb::OsnapMode osnapMode,
		Adesk::GsMarker gsSelectionMark,
		const AcGePoint3d &pickPoint,
		const AcGePoint3d &lastPoint,
		const AcGeMatrix3d &viewXform,
		AcGePoint3dArray &snapPoints,
		AcDbIntArray &geomIds) const ;

	virtual Acad::ErrorStatus subGetGripPoints( AcGePoint3dArray &gripPoints, AcDbIntArray &osnapModes, AcDbIntArray &geomIds ) const;

	virtual Acad::ErrorStatus subMoveGripPointsAt( const AcDbIntArray &indices, const AcGeVector3d &offset );

private:
	// key param
	AcGePoint3d m_insertPt;   // ���������
	double m_angle;           // ����Ƕȣ���ʱ�룬��λ���ȣ�

	// extra param
	double m_lenth;

	AcGePoint3d m_pt0;
	AcGePoint3d m_pt1;
	AcGePoint3d m_pt2;
	AcGePoint3d m_pt3;
	AcGePoint3d m_pt4;
	AcGePoint3d m_pt5;
	AcGePoint3d m_pt6;
	AcGePoint3d m_pt7;
	AcGePoint3d m_pt8;
	AcGePoint3d m_pt9;
	AcGePoint3d m_pt10;
	AcGePoint3d m_pt11;
	AcGePoint3d m_pt12;
	AcGePoint3d m_pt13;
	AcGePoint3d m_pt14;
	AcGePoint3d m_pt15;
};

#ifdef DEFGEPLUGIN_MODULE
ACDB_REGISTER_OBJECT_ENTRY_AUTO(TailraceGEDraw)
#endif