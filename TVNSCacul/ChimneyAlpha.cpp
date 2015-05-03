#include "StdAfx.h"
#include "ChimneyAlpha.h"

#include "../MineGE/HelperClass.h"
#include "../ArxHelper/ArxUtilHelper.h"

void SetAlpha( int chimType )
{
	AcDbObjectId objId;

	bool r;
	if(1 == chimType)//������Ͳ
	{
		r = SingleDataObjectHelper::GetObjectId( _T( "������Ͳֱ��" ), objId );
	}
	else
	{
		r = SingleDataObjectHelper::GetObjectId( _T( "������Ͳֱ��" ), objId );

	}
	//acutPrintf(_T("\nId:%s"),r?_T("�ɹ�"):_T("ʧ��"));
	AcTransaction* pTrans = actrTransactionManager->startTransaction();

	AcDbObject* pObj;
	if( Acad::eOk != pTrans->getObject( pObj, objId,  AcDb::kForWrite ) )
	{
		actrTransactionManager->abortTransaction();
		//acutPrintf(_T("\nxxxxxxx"));
	}
	
	if(1 == chimType)//������Ͳ
	{
		setMetalAlpha(objId);
	}
	else
	{
		setBlanketAlpha(objId);
	}


	actrTransactionManager->endTransaction();

}

CString GetAlpha( int chimType,CString diameter )
{
	AcDbObjectId objId;
	if(1 == chimType)//������Ͳ
	{
		SingleDataObjectHelper::GetObjectId( _T( "������Ͳֱ��" ), objId );
	}
	else
	{
		SingleDataObjectHelper::GetObjectId( _T( "������Ͳֱ��" ), objId );

	}

	AcTransaction* pTrans = actrTransactionManager->startTransaction();

	AcDbObject* pObj;
	if( Acad::eOk != pTrans->getObject( pObj, objId,  AcDb::kForRead ) )
	{
		actrTransactionManager->abortTransaction();
	}

	CString ss = getingAlpha(objId,diameter);

	//double ret;
	//ArxUtilHelper::StringToDouble(ss,ret);
	//ret = _ttol(ss);
	acutPrintf(_T("\nss:%s"),ss);
	actrTransactionManager->endTransaction();
	return ss;
}

void setMetalAlpha( AcDbObjectId objId )
{
	DataHelper::SetPropertyData( objId, _T( "200" ), _T("0.0049") );
	DataHelper::SetPropertyData( objId, _T( "300" ), _T("0.00441") );
	DataHelper::SetPropertyData( objId, _T( "400" ), _T("0.00392") );
	DataHelper::SetPropertyData( objId, _T( "500" ), _T("0.00343") );
	DataHelper::SetPropertyData( objId, _T( "600" ), _T("0.00294") );
	DataHelper::SetPropertyData( objId, _T( "800" ), _T("0.00245") );

}

void setBlanketAlpha( AcDbObjectId objId )
{
	DataHelper::SetPropertyData( objId, _T( "300" ), _T("0.0053") );
	DataHelper::SetPropertyData( objId, _T( "400" ), _T("0.0049") );
	DataHelper::SetPropertyData( objId, _T( "500" ), _T("0.0045") );
	DataHelper::SetPropertyData( objId, _T( "600" ), _T("0.0041") );
	DataHelper::SetPropertyData( objId, _T( "700" ), _T("0.0038") );
	DataHelper::SetPropertyData( objId, _T( "800" ), _T("0.0032") );
	DataHelper::SetPropertyData( objId, _T( "900" ), _T("0.0030") );
	DataHelper::SetPropertyData( objId, _T( "1000" ), _T("0.0029") );
}

CString getingAlpha( AcDbObjectId objId, CString diameter )
{
	CString ss;
	DataHelper::GetPropertyData( objId, diameter,ss );
	return ss;
}
