#pragma once

class LeakageCaculate
{
public:
	LeakageCaculate(AcDbObjectId objId);
	~LeakageCaculate();
	double LeakageCaculRet();

private:
	void initDatas();
	void metalCacul();
	void blanketCacul();
	//�жϸ÷�Ͳ�Ƿ������һ����Ͳ������ǽ�ͷ����1
	bool isLinkedNext();

public:
	double m_leakage;

private:
	double m_hmLeakage;
	double m_leakageFactor;
	CString m_meterial;
	double m_chimLenth;
	int m_joints;
	double m_diam;
	double m_windage;

	AcDbObjectId m_objId;
};