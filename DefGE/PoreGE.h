#pragma once

#include "../MineGE/MineGE.h"
#include "dlimexp.h"

//���ͼԪ(���ף��տ�)
class DEFGE_EXPORT_API PoreGE : public MineGE
{
public:
	ACRX_DECLARE_MEMBERS(PoreGE) ;

protected:
	static Adesk::UInt32 kCurrentVersionNumber ;

public:
	// ��ȡ���������
	AcGePoint3d getInsertPt() const;

	// ���ò��������
	void setInsertPt(const AcGePoint3d& pt);

public:
	virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler *pFiler) const;
	virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler);

protected:
	PoreGE();
	PoreGE(const AcGePoint3d& insertPt);

	virtual void writeKeyParam(DrawParamWriter& writer) const;
	virtual void readKeyParam(DrawParamReader& reader);

private:
	// key param
	AcGePoint3d m_insertPt;  // ���������
};

#ifdef DEFGE_MODULE
ACDB_REGISTER_OBJECT_ENTRY_AUTO(PoreGE)
#endif
