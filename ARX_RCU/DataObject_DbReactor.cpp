#include "StdAfx.h"
#include "DataObject_DbReactor.h"

#include "../MineGE/MineGE.h"
#include "../MineGE/TagGE.h"
#include "../MineGE/DataObject.h"
#include "../ArxHelper/HelperClass.h"

#include "../DefGE/RcuGE.h"
#include "../DefGE/Pore.h"
#include "../DefGE/DrillSite.h"
#include "../DefGE/RockGate.h"
#include "../DefGE/CoalSurface.h"

DataObject_DbReactor::DataObject_DbReactor ( AcDbDatabase* pDb ) : AcDbDatabaseReactor(), mpDatabase( pDb )
{
    if ( pDb )
    {
        //acutPrintf(_T("\nMineGEErase_DbReactor : %ld"), (long)pDb);
        pDb->addReactor ( this ) ;
    }
}

DataObject_DbReactor::~DataObject_DbReactor ()
{
    Detach () ;
}

void DataObject_DbReactor::Attach ( AcDbDatabase* pDb )
{
    Detach () ;
    if ( mpDatabase == NULL )
    {
        if ( ( mpDatabase = pDb ) != NULL )
            pDb->addReactor ( this ) ;
    }
}

void DataObject_DbReactor::Detach ()
{
    if ( mpDatabase )
    {
        mpDatabase->removeReactor ( this ) ;
        mpDatabase = NULL ;
    }
}

AcDbDatabase* DataObject_DbReactor::Subject () const
{
    return ( mpDatabase ) ;
}

bool DataObject_DbReactor::IsAttached () const
{
    return ( mpDatabase != NULL ) ;
}

static void FilterTagGE( const AcDbObjectId& objId,
                         const AcDbObjectIdArray& allObjIds,
                         Adesk::Boolean pErased,
                         AcDbObjectIdArray& objIds )
{
    if( allObjIds.isEmpty() ) return;

    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return;

    int len = allObjIds.length();
    for( int i = 0; i < len; i++ )
    {
        AcDbObject* pObj;
        if( Acad::eOk != pTrans->getObject( pObj, allObjIds[i], AcDb::kForRead, !pErased ) ) continue;

        TagGE* pTag = TagGE::cast( pObj );
        if( pTag == 0 ) continue;

        if( pTag->getRelatedGE() == objId )
        {
            objIds.append( allObjIds[i] );
        }
    }
    actrTransactionManager->endTransaction();
}

static void GetEntsByType_Helper( const CString& type, Adesk::Boolean pErased, AcDbObjectIdArray& allObjIds )
{
    if( pErased )
    {
        ArxDataTool::GetEntsByType( type, allObjIds, true );
    }
    else
    {
        ArxDataTool::GetErasedEntsByType( type, allObjIds, true );
    }
}

static void GetAllTagGEById( const AcDbObjectId& objId, Adesk::Boolean pErased, AcDbObjectIdArray& objIds )
{
    //acutPrintf(_T("\n��ʼ��ȡid..."));
    if( objId.isNull() ) return;

    AcDbObjectIdArray allObjIds;
    GetEntsByType_Helper( _T( "TagGE" ), pErased, allObjIds );

    // ����ɸѡ����objId������TagGE
    FilterTagGE( objId, allObjIds, pErased, objIds );

    //acutPrintf(_T("\n������ȡid..."));
}

// ��objectModified���޷���������
void DataObject_DbReactor::objectModified( const AcDbDatabase* dwg, const AcDbObject* dbObj )
{
    AcDbDatabaseReactor::objectModified ( dwg, dbObj );
    if( dbObj->isKindOf( DataObject::desc() ) )
    {
        DataObject* pDO = DataObject::cast( dbObj );
        AcDbObjectId objId = pDO->getGE();
		//ʯ�����ݷ����仯
		if(ArxUtilHelper::IsEqualType(_T("RockGate"), objId))
		{
			//���¼����곡�ĵװ�����

			//���¼���ú����Ĳ���
		}
		//�곡���ݷ����仯
		else if(ArxUtilHelper::IsEqualType(_T("DrillSite"), objId))
		{
			
		}
		//ú�������ݷ����仯
		else if(ArxUtilHelper::IsEqualType(_T("CoalSurface"), objId))
		{
			//���¼���ú�����
		}
    }
}