#pragma once
#include "../MineGE/TagGE.h"
#include "dlimexp.h"

class DEFGE_EXPORT_API FanTagGE : public TagGE 
{
public:
	ACRX_DECLARE_MEMBERS(FanTagGE) ;
	FanTagGE();
	FanTagGE(AcGePoint3d& insertPt,CString name,CString way,double q,double h);
	virtual ~FanTagGE();

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

	double m_q;	//�����������
	double m_h;	//���������ѹ
	CString m_name;	//����ͺ�
	CString m_way;	//����Ĺ�����ʽ

};
#ifdef DEFGE_MODULE
ACDB_REGISTER_OBJECT_ENTRY_AUTO(FanTagGE)
#endif