#include "StdAfx.h"
#include "GasSensorGE.h"
#include "../MineGE/DataHelper.h"
#include "../MineGE/DataListHelper.h"

Adesk::UInt32 GasSensorGE::kCurrentVersionNumber = 1 ;

ACRX_DXF_DEFINE_MEMBERS ( GasSensorGE, 
						 DirectionTagGE, AcDb::kDHL_CURRENT,
						 AcDb::kMReleaseCurrent,AcDbProxyEntity::kNoOperation,
						 ��˹������, DEFGEAPP )

						 GasSensorGE::GasSensorGE ()
{
}

GasSensorGE::GasSensorGE( const AcGePoint3d& insertPt, double angle )
: DirectionTagGE( insertPt, angle )
{
}

GasSensorGE::~GasSensorGE ()
{
}

static void ReadWriteData( const AcDbObjectId& sObjId, const CString& sField, const AcDbObjectId& tObjId, const CString& tField )
{
	CString v;
	DataHelper::GetPropertyData( sObjId, sField, v );
	
	DataHelper::SetPropertyData( tObjId, tField, v );
}

void GasSensorGE::writePropertyDataToGEDraw( MineGEDraw* pGEDraw ) const
{
	AcDbObjectId gID = getRelatedGE();
	AcDbObjectId objID = objectId();
	ReadWriteData(gID,_T("�ܵ��е���˹Ũ��"),objID,_T("��˹Ũ��"));
	MineGE::writePropertyDataToGEDraw(pGEDraw);
}