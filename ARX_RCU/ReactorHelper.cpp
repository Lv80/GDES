#include "StdAfx.h"
#include "ReactorHelper.h"
#include "DataObject_DbReactor.h"

/*
 * ���ڼ�¼��Document��ص�reactor
 * ����AcDbDataBaseReactor��AcEdInputPointMonitor�ȶ������ĵ���ص�
 * һ���ĵ������Ӧһ��reactor�����Կ�����"�ֲ���"
 * ��AcEditorReactor����AcEditor�����Կ�����"ȫ�ֵ�"
 * ��arx����Ϣ���̿��Կ�������kLoadAppMsg()��AcEditor��Ч��
 * �������������ĵ�����(AcApDocument)�����ݿ����(AcDbDatabase)������Ч��
 * ֻ����kLoadDwgMsg()�е��ĵ������ݿ����ſ�ʼ��Ч
 */
#include <map>
struct DocumentReactor
{
    DocumentReactor() : pDOReactor( 0 ) {}
    DataObject_DbReactor* pDOReactor;

    // ...
    // ������һ����ڹ���Ҳ����˶��ĵ�������
    // 1) �½��ĵ�������kLoadDwgMsg��Ϣ
    // 2) �����ĵ�������arx����Ҳ�������е��ĵ�����kLoadDwgMsg��Ϣ
    // 3) �ر��ĵ��� ����kUnloadDwgMsg��Ϣ
    // 4) ж��arx����Ҳ�������е��ĵ�����kUnloadDwgMsg��Ϣ
};

/*
 * long���ͱ�ʾAcApDocument*��ָ���ַ
 */
typedef std::map<long, DocumentReactor> DocumentReactorMap;

DocumentReactorMap* pDocumentReactorMap_RCU = 0;

void ReactorHelper::CreateDocumentReactorMap()
{
    if( pDocumentReactorMap_RCU == 0 )
    {
        pDocumentReactorMap_RCU = new DocumentReactorMap();
    }
}

void ReactorHelper::RemoveDocumentReactorMap()
{
    delete pDocumentReactorMap_RCU;
    pDocumentReactorMap_RCU = 0;
}

void ReactorHelper::AddDocumentReactor( AcApDocument* pDoc )
{
    if( pDoc == 0 ) return;
    if( pDocumentReactorMap_RCU == 0 ) return;
    long id = ( long )pDoc;
    DocumentReactorMap::iterator itr = pDocumentReactorMap_RCU->find( id );
    if( itr != pDocumentReactorMap_RCU->end() ) return;

    DocumentReactor dr;
    //dr.pTooltipMonitor = new MineGETooltipMonitor(pDoc);
    dr.pDOReactor = new DataObject_DbReactor( pDoc->database() );

    pDocumentReactorMap_RCU->insert( DocumentReactorMap::value_type( id, dr ) );
}

void ReactorHelper::RemoveDocumentReactor( AcApDocument* pDoc )
{
    if( pDoc == 0 ) return;
    if( pDocumentReactorMap_RCU == 0 ) return;
    long id = ( long )pDoc;
    DocumentReactorMap::iterator itr = pDocumentReactorMap_RCU->find( id );
    if( itr == pDocumentReactorMap_RCU->end() ) return;

    // �����
    DocumentReactor dr = itr->second;
    delete dr.pDOReactor;
    //delete dr.pTooltipMonitor;

    pDocumentReactorMap_RCU->erase( id );
}