#pragma once

#include "MineGEDraw.h"

// ��֧��ͼԪ�Ļ���Ч���������
class MINEGE_DRAW_DLLIMPEXP JointDraw : public MineGEDraw {

public:
	ACRX_DECLARE_MEMBERS(JointDraw) ;

public:
	virtual void readKeyParam(DrawParamReader& reader);
	virtual void writeKeyParam(DrawParamWriter& writer);

public:
	virtual void extendByLength(double length);                              // �����������⣬����length(Ĭ�ϲ�����)

protected:
	JointDraw();

public:
	AcGePoint3d m_inserPt;   // �����
} ;

#ifdef MINEGEDRAW_MODULE
ACDB_REGISTER_OBJECT_ENTRY_AUTO(JointDraw)
#endif
