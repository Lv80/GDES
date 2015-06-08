#pragma once

#include "RcuGE.h"

//ú��
class DEFGE_EXPORT_API CoalSurface : public RcuTagGE
{
public:
	ACRX_DECLARE_MEMBERS(CoalSurface) ;

protected:
	static Adesk::UInt32 kCurrentVersionNumber ;

public:
	//���캯��
	CoalSurface();

	// ��ȡ���������
	AcGePoint3d getInsertPt() const;

	// ���ò��������
	void setInsertPt(const AcGePoint3d& pt);

	double getWidth() const;
	void setWidth(double w);

	double getHeight() const;
	void setHeight(double h);

public:
	virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler *pFiler) const;
	virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler);

protected:
	virtual void writeKeyParam(DrawParamWriter& writer) const;
	virtual void readKeyParam(DrawParamReader& reader);

private:
	// key param
	AcGePoint3d m_insertPt;  // ���������
	double m_width, m_height; // ��Ⱥ͸߶�
};

#ifdef DEFGE_MODULE
ACDB_REGISTER_OBJECT_ENTRY_AUTO(CoalSurface)
#endif
