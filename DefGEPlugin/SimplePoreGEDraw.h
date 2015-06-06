#pragma once

#include "../MineGEDraw/MineGEDraw.h"

//����׻���Ч��
class SimplePoreGEDraw : public MineGEDraw {

public:
	ACRX_DECLARE_MEMBERS(SimplePoreGEDraw) ;

public:
	SimplePoreGEDraw () ;
	virtual ~SimplePoreGEDraw () ;

	virtual void setAllExtraParamsToDefault();
	virtual void configExtraParams();
	virtual void updateExtraParams();

	virtual void readKeyParam(DrawParamReader& reader);
	virtual void writeKeyParam(DrawParamWriter& writer);

	virtual void regPropertyDataNames(AcStringArray& names) const;
	virtual void readPropertyDataFromGE(const AcStringArray& values);

	virtual void readExtraParam(DrawParamReader& reader);
	virtual void writeExtraParam(DrawParamWriter& writer);

protected:
	virtual Adesk::Boolean subWorldDraw (AcGiWorldDraw *mode) ;
	virtual Acad::ErrorStatus subGetGripPoints (AcGePoint3dArray &gripPoints, AcDbIntArray &osnapModes, AcDbIntArray &geomIds) const ;
	virtual Acad::ErrorStatus subMoveGripPointsAt (const AcDbIntArray &indices, const AcGeVector3d &offset) ;
	virtual Acad::ErrorStatus subTransformBy( const AcGeMatrix3d & xform );
	virtual Acad::ErrorStatus subGetOsnapPoints (
		AcDb::OsnapMode osnapMode,
		Adesk::GsMarker gsSelectionMark,
		const AcGePoint3d &pickPoint,
		const AcGePoint3d &lastPoint,
		const AcGeMatrix3d &viewXform,
		AcGePoint3dArray &snapPoints,
		AcDbIntArray &geomIds) const ;

public:
	AcGePoint3d m_insertPt;   // ���������
	double m_radius;   // �׾�
	CString id;        // ��ױ��
} ;

#ifdef DEFGEPLUGIN_MODULE
ACDB_REGISTER_OBJECT_ENTRY_AUTO(SimplePoreGEDraw)
#endif
