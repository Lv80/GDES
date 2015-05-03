#include "StdAfx.h"
#include "UIHelper.h"

#include "DrawManagerDlg.h"
#include "FieldManagerDlg.h"
#include "DataObjectStateDlg.h"
#include "VarListDlg.h"

#include "PropertyDataDlgHelper.h"

#include "../ArxHelper/HelperClass.h"
#include "../MineGE/DataListHelper.h"

void UIHelper::ShowDrawManagerDlg()
{
    // �л���Դ
    CAcModuleResourceOverride myResources;

    DrawManagerDlg dmd;
    dmd.DoModal(); // ���ӻ�Ч���л�������
}

void UIHelper::ShowFieldManagerDlg()
{
    // �л���Դ
    CAcModuleResourceOverride myResources;

    FieldManagerDlg fmd;
    fmd.DoModal(); // ���������ֶι���
}

//void UIHelper::ShowPropertyDataDlg()
//{
//
//}

void UIHelper::ShowVarListDlg()
{
    CAcModuleResourceOverride myResources;

    VarListDlg vld;
    vld.DoModal();
}

void UIHelper::ShowDataObjectStateDlg()
{
    CAcModuleResourceOverride myResources;

    DataObjectStateDlg dosd;
    dosd.DoModal();
}

void UIHelper::DisplayData()
{
    // ��ʾͼԪ����������
    AcDbObjectId objId = ArxUtilHelper::SelectObject( _T( "��ѡ��һ��ͼԪ:" ) );
    if( objId.isNull() ) return;
	//if( ArxUtilHelper::IsEqualType( _T( "GasFlowTagGE" ), objId ) ) return;
	if( ArxUtilHelper::IsEqualType( _T( "TagGE" ), objId ) && !ArxUtilHelper::IsEqualType( _T( "GasPumpGE" ), objId )) return;

	PropertyDataDlgHelper::DisplayPropertyDataDlg( objId );
}

void UIHelper::DisplayDrillDataByFunc(const CString& funcName)
{
	// ��ʾͼԪ����������
	AcDbObjectId objId = ArxUtilHelper::SelectObject( _T( "��ѡ��һ�����:" ) );
	if( objId.isNull() ) return;
	if( !ArxUtilHelper::IsEqualType( _T( "DrillGE" ), objId )) return;

	PropertyDataDlgHelper::DisplayPropertyByFunName(objId,funcName);
}

void UIHelper::DisplayGasTubeDataByFunc(const CString& funcName)
{
	// ��ʾͼԪ����������
	AcDbObjectId objId = ArxUtilHelper::SelectObject( _T( "��ѡ��һ����·:" ) );
	if( objId.isNull() ) return;
	if( !ArxUtilHelper::IsEqualType( _T( "GasTube" ), objId )) return;

	PropertyDataDlgHelper::DisplayPropertyByFunName( objId,funcName );
}

void UIHelper::DisplayGasPumpDataByFunc(const CString& funcName)
{
	// ��ʾͼԪ����������
	AcDbObjectId objId = ArxUtilHelper::SelectObject( _T( "��ѡ��һ����˹��:" ) );
	if( objId.isNull() ) return;
	if( !ArxUtilHelper::IsEqualType( _T( "GasPumpGE" ), objId )) return;

	PropertyDataDlgHelper::DisplayPropertyByFunName( objId,funcName );
}

void UIHelper::DisplayDataByDoubleClick()
{
    //acutPrintf(_T("\n˫���Զ���..."));
    AcDbObjectIdArray objIds;
    ArxUtilHelper::GetPickSetEntity( objIds );
    if( objIds.length() != 1 ) return;

	//if( ArxUtilHelper::IsEqualType( _T( "DrillGE" ), objIds[0] ))
	//{
	//	PropertyDataDlgHelper::DisplayPropertyByFunName(objIds[0],_T("��λ��ײ�������"));
	//}

	//else if( ArxUtilHelper::IsEqualType( _T( "GasTube" ), objIds[0] ))
	//{
	//	PropertyDataDlgHelper::DisplayPropertyByFunName(objIds[0],_T("��·����"));
	//}

	//else if( ArxUtilHelper::IsEqualType( _T( "GasPumpGE" ), objIds[0] ))
	//{
	//	PropertyDataDlgHelper::DisplayPropertyByFunName(objIds[0],_T("��˹�ü���"));
	//}

	//else
	//{
		// ��ʾ���ԶԻ���
		PropertyDataDlgHelper::DisplayPropertyDataDlg( objIds[0] );
	//}
}

void UIHelper::DisplayDataByFuncName(const CString& funcName)
{
	//acutPrintf(_T("\n˫���Զ���..."));
	//AcDbObjectIdArray objIds;
	//ArxUtilHelper::GetPickSetEntity( objIds );
	//if( objIds.length() != 1 ) return;
	AcDbObjectId objId;
	SingleDataObjectHelper::GetObjectId(_T("�������"),objId);
	//AcStringArray funcs;
	//CString funcName = _T("������Ϣ");
	//funcs.append(funcName);
	// ��ʾ���ԶԻ���
	PropertyDataDlgHelper::DisplayPropertyByFunName( objId, funcName );
}