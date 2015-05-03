#pragma once
#include "../MineGE/TagGE.h"
#include "dlimexp.h"

class DEFGE_EXPORT_API QTagGE : public TagGE 
{
public:
	ACRX_DECLARE_MEMBERS(QTagGE) ;
	QTagGE();
	QTagGE(AcGePoint3d& insertPt,double q);
	virtual ~QTagGE();

protected:
	static Adesk::UInt32 kCurrentVersionNumber;

public:

public:
	virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler *pFiler) const;
	virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler);

protected:
	virtual void writeKeyParam(DrawParamWriter& writer) const;
	virtual void readKeyParam(DrawParamReader& reader);


private:
	AcGePoint3d m_insertPt; //�����ǩ�ĵĲ���㣬Ҳ���Ƿ���Ĳ����

	double m_q;	//����
};
#ifdef DEFGE_MODULE
ACDB_REGISTER_OBJECT_ENTRY_AUTO(QTagGE)
#endif