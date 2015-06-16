#pragma once

/*
 * ��ɾ��һ��ͼԪ��Ҫͬʱɾ��ͼԪ�ϵı�ǩͼԪTagGE
 * �Լ�������ģ��ͼԪModelGE
 */
class DataObject_DbReactor : public AcDbDatabaseReactor 
{
protected:
	AcDbDatabase *mpDatabase ;

public:
	DataObject_DbReactor (AcDbDatabase *pDb =NULL) ;
	virtual ~DataObject_DbReactor () ;

	virtual void Attach (AcDbDatabase *pDb) ;
	virtual void Detach () ;
	virtual AcDbDatabase *Subject () const ;
	virtual bool IsAttached () const ;

	/*
	 * �����ݶ����ں�̨���ı䣬ǿ�Ƹ�����֮������ͼ��Ч��
	 * ��ЩͼԪ�Ŀ��ӻ�Ч���������йأ�������վ(Joint)
	 */
	virtual void objectModified(const AcDbDatabase* dwg, const AcDbObject* dbObj);
} ;
