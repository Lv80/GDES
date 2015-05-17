#include "StdAfx.h"
#include "PropertyDataUpdater.h"

#include "FieldInfoHelper.h"
#include "DataHelperImpl.h"

#include "FieldHelper.h"
#include "DataHelper.h"
#include "DataListHelper.h"

#include "../ArxHelper/ArxEntityHelper.h"
#include "DrawHelper.h"

#include "MFCPropertyGridCtrlHelper.h"
#include "FuncFieldHelper.h"
#include "../ArxHelper/ArxUtilHelper.h"

// ���ַ���ת����bool����
// ��COleVariant�У�bool����ʹ��short��ʾ(boolValue---VT_BOOL)
// -1��ʾtrue��0��ʾfalse
static bool StringToBool( const CString& str )
{
    if( str.GetLength() == 0 ) return false;
    return ( _ttoi( str ) != 0 );
}

static void StringToDataTime( const CString& str, COleDateTime& dt )
{
    if( ( str.GetLength() == 0 ) || !dt.ParseDateTime( str ) )
    {
        dt = COleDateTime::GetCurrentTime();
    }
}

/*
static void BuildPropList2(MFCPropertyGridCtrlHelper& pgch,
                           const CString& name, const CString& value,
						   ClickPropModifyCallBack cb,
						   const FieldInfo& info)
{
	if(cb == 0) return;

	// ��һЩ���ƣ�ֻ������DT_STRING, m_useList=false, bEnable=true��info
	DATA_TYPE dt = info.getDataType();
	bool m_useList = info.isDataListUse();
	bool bEnable = info.isEnable();
	if((dt == DT_STRING) && !m_useList && bEnable)
	{
		// ��ӵ��������
		pgch.addClickProperty(name, value, cb);
	}
}

// �ص���Ϣӳ���
// ��"���ԶԻ���"��ʾǰ����ӳ���
// Ȼ�󴫵ݸ�readDataFromGE()����
// ������������ֶ����Ʋ��Ҷ�Ӧ��ClickPropModifyCallBackInfo
// �����ݸ�BuildPropList2()����
std::map<CString, ClickPropModifyCallBack> cbInfoMaps;

bool ShaftPropertySet(const CString& oldValue, CString& newValue)
{
	ShaftExtraPropertyDlg sepd;
	if(sepd.DoModal() == IDOK)
	{
		// ʹ��oldValue��һЩ����
		// ......
		// �����µĽ��
		newValue = xxx;
		return true;
	}
	else
	{
		return false;
	}
}
// ����
// ����ShaftPropertySet�����ĵ�ַ(ȫ�ֺ�������̬�������ྲ̬��Ա����)
// "��Ͳ��������" --> {&ShaftPropertySet, "�Ի������þ�Ͳ��������"}
// "xxx"            --> {cb2, "xdddsf"}
*/

static void BuildPropList( MFCPropertyGridCtrlHelper& pgch, CMFCPropertyGridProperty *pGroup,const CString& name, const CString& value, const FieldInfo& info )
{
    DATA_TYPE dt       = info.m_dt;
    int nMinValue      = info.m_minValue2;
    int nMaxValue      = info.m_maxValue2;
    double dMinValue   = info.m_minValue;
    double dMaxValue   = info.m_maxValue;
    LIST_TYPE lt       = info.m_lt;
    CString varName    = info.m_varName;
	int tole	   = info.m_tolrance;
    bool bEnable       = info.m_enable;
    CString m_descr    = info.m_descr;
    LPCTSTR descr = NULL;
    if( m_descr.GetLength() != 0 ) descr = ( LPCTSTR )m_descr;
    switch( dt )
    {
    case DT_STRING:
        pgch.addStringProperty( pGroup, name, value, descr, bEnable );
        break;

    case DT_INT:
        pgch.addIntProperty( pGroup, name, _ttoi( value ), nMinValue, nMaxValue, descr, bEnable );
        break;

    case DT_NUMERIC:
        pgch.addDoubleProperty( pGroup, name, _tstof( value ), dMinValue, dMaxValue, tole, descr, bEnable );
        break;

    case DT_BOOL:
        pgch.addBoolProperty( pGroup, name, StringToBool( value ), descr, bEnable );
        break;

    case DT_DATE:
    {
        COleDateTime dt;
        StringToDataTime( value, dt );
        pgch.addDateTimeProperty( pGroup, name, dt, descr, bEnable );
    }
    break;

    case DT_LIST:
        if( lt == LT_STRING )
        {
            AcStringArray strList;
            if( StringListHelper::GetStringList( varName, strList ) )
            {
                pgch.addStringPropertyList( pGroup, name, value, strList, descr, bEnable );
            }
            else
            {
                pgch.addStringProperty( pGroup, name, value, descr, bEnable );
            }
        }
        else if( lt == LT_INT )
        {
            AcDbIntArray intList;
            AcStringArray strList;
            if( IntStrListHelper::GetIntStrList( varName, intList, strList ) )
            {
                pgch.addIntPropertList( pGroup, name, _ttoi( value ), intList, strList, descr, bEnable );
            }
            else
            {
                pgch.addStringProperty( pGroup, name, value, descr, bEnable );
            }
        }
        else if( lt == LT_OBJECT )
        {
            AcStringArray strList;
            if( DataObjectListHelper::GetObjectNameList( varName, strList ) )
            {
                pgch.addDataObjectPropertyList( pGroup, name, value, strList, descr, bEnable );
            }
            else
            {
                pgch.addStringProperty( pGroup, name, value, descr, bEnable );
            }
        }
        break;
    }
}

static void PrintPropList( CMFCPropertyGridCtrl* pPropDataList )
{
    int count = pPropDataList->GetPropertyCount();
    acutPrintf( _T( "\n�������ݿؼ����������ݸ���:%d" ), count );
    for( int i = 0; i < count; i++ )
    {
        CMFCPropertyGridProperty* pProp = pPropDataList->GetProperty( i );
        acutPrintf( _T( "\name=%s\tvalue=%s" ), pProp->GetName(), pProp->GetValue() );
    }
    acutPrintf( _T( "\n" ) );
}

static void ExcludeSpecial(int& funcCount,AcStringArray& funcNames,const CString& excludeName)
{
	if( funcCount > 1 ) 
	{
		int indx = funcNames.find( excludeName );
		if(indx != -1)
		{
			funcNames.removeAt(indx);
			funcCount = funcCount - 1;
		}
	}
}

bool PropertyDataUpdater::BuildPropGridCtrl( CMFCPropertyGridCtrl* pPropDataList, const CString& type, const AcStringArray& funcFieldsInfo )
{
    if( pPropDataList == NULL ) return false;
    if( type.GetLength() == 0 ) return false;

    // �������ӵ�����
    pPropDataList->RemoveAll();
    //acutPrintf(_T("\n�����������..."));

	int funcCount = 0;
	AcStringArray funcNames;
	for (int i = 0; i < funcFieldsInfo.length(); i++)
	{
		if ( _T("$") == funcFieldsInfo[i] )
		{
			funcCount += 1;
			funcNames.append(funcFieldsInfo[i+1]);
		}
	}

	ExcludeSpecial(funcCount,funcNames,_T("��·����"));
	ExcludeSpecial(funcCount,funcNames,_T("��λ��ײ�������"));
	ExcludeSpecial(funcCount,funcNames,_T("��˹�ü���"));
	ExcludeSpecial(funcCount,funcNames,_T("��˹��ѡ�Ͳο�"));
	ExcludeSpecial(funcCount,funcNames,_T("��С����"));

	for(int i = 0; i < funcCount; i++)
	{
		CString funcName = funcNames[i].kACharPtr();
		CMFCPropertyGridProperty *pGroup = new CMFCPropertyGridProperty(funcName);
		pPropDataList->AddProperty(pGroup);
	}

	MFCPropertyGridCtrlHelper pgch( pPropDataList );
	for(int i = 0; i < funcCount; i++)
	{
		CString funcName = funcNames[i].kACharPtr();
		int indx = funcFieldsInfo.find(funcName);
		CMFCPropertyGridProperty *pGroup = pPropDataList->GetProperty(i);
		for(int j = indx+1; j < funcFieldsInfo.length(); j++)
		{
			if( _T("$") == funcFieldsInfo[j] ) break;
			CString name = funcFieldsInfo[j].kACharPtr();
			FieldInfo info; // Ĭ������(DT_STRING, m_enable=true, m_descr =_T(""))
			FieldInfoHelper::ReadFieldInfo( type, name, info );
			// ����PropertyList
			BuildPropList( pgch, pGroup, name, _T( "" ), info ); // ������ַ���
		}
	}
    return true;
}

static void SetPropValue( CMFCPropertyGridProperty* pProp, const FieldInfo& info, const CString& value )
{
    switch( info.m_dt )
    {
    case DT_STRING:
        pProp->SetValue( ( COleVariant )value );
        break;

    case DT_INT:
		if ( _ttoi( value ) < info.m_minValue2 || _ttoi( value ) > info.m_maxValue2 )
		{ 
			 pProp->SetValue( ( long ) info.m_minValue2 );
		}
		else
		{
			pProp->SetValue( ( long )_ttoi( value ) );
		}
        break;

    case DT_NUMERIC:
		if ( _ttoi( value ) < info.m_minValue || _ttoi( value ) > info.m_maxValue )
		{ 
			pProp->SetValue( ( long ) info.m_minValue );
		}
		else
		{
			pProp->SetValue( _tstof( value ) );
		}
        break;

    case DT_BOOL:
        pProp->SetValue(( long )( StringToBool( value ) ? 1 : 0 ));
        break;

    case DT_DATE:
    {
        COleDateTime dt;
        StringToDataTime( value, dt );
        pProp->SetValue( ( COleVariant )dt );
    }
    break;

    case DT_LIST:
        if( info.m_lt == LT_STRING )
        {
            pProp->SetValue( ( COleVariant )value );
        }
        else if( info.m_lt == LT_INT )
        {
            pProp->SetValue( ( long )_ttoi( value ) );
        }
        else if( info.m_lt == LT_OBJECT )
        {
            pProp->SetValue( ( COleVariant )value );
        }
        break;

    default:
        pProp->SetValue( ( COleVariant )value ); // Ĭ��Ϊ�ַ�������
        break;
    }
}

bool PropertyDataUpdater::ReadDataFromGE( CMFCPropertyGridCtrl* pPropDataList, const AcDbObjectId& objId )
{
    if( pPropDataList == NULL ) return false;
    if( objId.isNull() ) return false;

    //PrintPropList(pPropDataList);

    // �������
    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return false;

    AcDbObject* pObj;
    if( Acad::eOk != pTrans->getObject( pObj, objId, AcDb::kForRead ) )
    {
		acutPrintf(_T("open data for read failed.....\n"));
        actrTransactionManager->abortTransaction();
        return false;
    }
    DataObject* pDO = DataObject::cast( pObj );
    if( pDO == 0 )
    {
		acutPrintf(_T("is not a dataobject....\n"));
        actrTransactionManager->abortTransaction();
        return false;
    }

    //acutPrintf(_T("\n��ȡ����..."));
    DataHelperImpl dh( pDO );
	//�������ԣ�����ط��ĵĸ�����Ⱥ��ĸ��������������ĸ���
    int nCount = pPropDataList->GetPropertyCount();
    for ( int i = 0; i < nCount; i++ )
    {
        CMFCPropertyGridProperty* pGroup = pPropDataList->GetProperty( i );
		//acutPrintf(_T("\n���Ը���:%d"),pGroup->GetSubItemsCount());
		for(int j = 0; j < pGroup->GetSubItemsCount(); j++)
		{
			CMFCPropertyGridProperty* pProp = pGroup->GetSubItem( j );

			CString value;
			dh.getPropertyData( pProp->GetName(), value ); // ������������
			//acutPrintf(_T("\n����:%s->�ֶ�:%s->ֵ:%s"),pGroup->GetName(),pProp->GetName(),value);
			FieldInfo info; // Ĭ������(DT_STRING, m_enable=true, m_descr =_T(""))
			FieldInfoHelper::ReadFieldInfo( pDO->getType(), pProp->GetName(), info );
			SetPropValue( pProp, info, value ); // ��������ֵ
		}

		//DATA_TYPE dt       = info.m_dt;
		//LIST_TYPE lt       = info.m_lt;
		//if (dt == DT_LIST && lt == LT_INT)
		//{
		//	
		//}

    }

    actrTransactionManager->endTransaction();
    return true;
}

static void Update( )
{
	AcDbObjectIdArray objIds;
	DrawHelper::FindMineGEs(_T("DifferPressSensorGE"),objIds);
	DrawHelper::FindMineGEs(_T("GasSensorGE"),objIds);
	DrawHelper::FindMineGEs(_T("FlowSensorGE"),objIds);
	DrawHelper::FindMineGEs(_T("TempeSensorGE"),objIds);
	DrawHelper::FindMineGEs(_T("GasFlowTagGE"),objIds);
	for(int i = 0; i < objIds.length(); i++ )
	{
		ArxEntityHelper::UpdateEntity( objIds[i] ); // ǿ�Ƹ�����ʾЧ��
	}

}

bool PropertyDataUpdater::WriteDataToGE( CMFCPropertyGridCtrl* pPropDataList, const AcDbObjectId& objId )
{
	if( pPropDataList == NULL ) return false;
	if( objId.isNull() ) return false;

	// û���������ݿɸ���
	if( pPropDataList->GetPropertyCount() == 0 ) return false;

	AcTransaction* pTrans = actrTransactionManager->startTransaction();
	if( pTrans == 0 ) return false;

	AcDbObject* pObj;
	if( Acad::eOk != pTrans->getObject( pObj, objId, AcDb::kForWrite ) )
	{
		actrTransactionManager->abortTransaction();
		return false;
	}
	DataObject* pDO = DataObject::cast( pObj );
	if( pDO == 0 )
	{
		actrTransactionManager->abortTransaction();
		return false;
	}

	//acutPrintf(_T("\nд������..."));
	DataHelperImpl dh( pDO );
	int nCount = pPropDataList->GetPropertyCount();
	for ( int i = 0; i < nCount; i++ )
	{
		CMFCPropertyGridProperty* pGroup = pPropDataList->GetProperty( i );
		//acutPrintf(_T("\n���Ը���:%d"),pGroup->GetSubItemsCount());
		for(int j = 0; j < pGroup->GetSubItemsCount(); j++)
		{
			CMFCPropertyGridProperty* pProp = pGroup->GetSubItem( j );
			CString value = pProp->GetValue();
			//acutPrintf(_T("\n�ֶ�:%s"),value);
			//acutPrintf(_T("\nд���ݹ���:%s->�ֶ�:%s->ֵ:%s"),pGroup->GetName(),pProp->GetName(),value);
			bool ret = dh.setPropertyData( pProp->GetName(), value ); // ������������
			//acutPrintf(_T("\n���ݸ���%s"),ret?_T("�ɹ�"):_T("ʧ��"));
		}
	}
	actrTransactionManager->endTransaction();

	//����ʲô����д�붼������˹����
	Update();
	return true;
}
