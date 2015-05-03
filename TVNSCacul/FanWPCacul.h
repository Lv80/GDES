#pragma once
#include "resource.h"
#include "enumDefine.h"

class FanWPCaculHelper
{
public:
	static AcDbObjectIdArray getLinkedChim( const AcDbObjectId& objId );
	static void fanWPWrite( const AcDbObjectId& objId,
		CString name,double Q,double H ,double theoryQ,
		double theoryH,double spaceH ,
		const CString& minQStr,const CString& maxQStr,const CString& minHStr,const CString& maxHStr);
	static ddoubleArray getMultiLinkedChim( const AcDbObjectId& objId);
	static void FanWPCacul(const AcDbObjectIdArray& fanIds,CString ttunelWay,CString method,CString rqQStr,const chooseType& chFanType);
	static void ReadData(CString way,double Q,double H,cstringArray &names,cstringArray &minQs,cstringArray &maxQs,
		cstringArray &minHs,cstringArray &maxHs,cstringArray &ratedPowers);
	//�������Ƚ�
	static void RealParamCaculQ( CString &name, 
		const cstringArray& names,const cstringArray& minQs,const cstringArray& maxQs,const cstringArray& minHs,const cstringArray& maxHs,
		double theoryQ,double r,double p,double& workQ,double& workH,double& spaceH,CString& minQStr,CString& maxQStr,CString& minHStr,
		CString& maxHStr,const cstringArray& ratedPowers,CString& ratedPower);
	//������ʱȽ�
	static void RealParamCaculP( CString &name, 
		const cstringArray& names,const cstringArray& minQs,const cstringArray& maxQs,const cstringArray& minHs,const cstringArray& maxHs,
		double theoryQ,double r,double p,double& workQ,double& workH,double& spaceH,CString& minQStr,CString& maxQStr,CString& minHStr,
		CString& maxHStr,const cstringArray& ratedPowers,CString& ratedPower);

	static void classifyFanByWay( AcDbObjectIdArray& fanIds, AcDbObjectIdArray& pushInIds, AcDbObjectIdArray& pullOutIds);
	static int getMaxClassify(const AcDbObjectIdArray& objIds,CString ranField);

private:
	static void singleQHCacul(const AcDbObjectIdArray& fanIds,CString ttunelWay,CString rqQStr,const chooseType& chFanType);
	static void axilQHCacul(const AcDbObjectIdArray& fanIds,CString ttunelWay,CString rqQStr,const chooseType& chFanType);
	static void seriesQHCacul(const AcDbObjectIdArray& fanIds,CString ttunelWay,CString rqQStr,const chooseType& chFanType);
	static void mutiserQHCacul(const AcDbObjectIdArray& fanIds,CString ttunelWay,CString rqQStr,const chooseType& chFanType);
	static bool randIsReasonable(const AcDbObjectIdArray& objIds,CString randField, int classifyIntMax);
	static void cheakMethod(const AcDbObjectIdArray& objIds,CString rqQStr);
	static void libVentQHCacul( const AcDbObjectIdArray& fanIds,CString ttunelWay,CString rqQStr,const chooseType& chFanType);
	
	static int PorQ;//������ѡ���ǹ���ѡ��,Ĭ���ǹ���ѡ��
};

//��������Ͳ
class SingleQHCacul
{
public:
	SingleQHCacul(AcDbObjectId fanObjId,double reqQ,const chooseType& chFanType);
	~SingleQHCacul();
	void caculateQH();

private:
	AcDbObjectId m_fanObjId;
	double m_reqQ;

	double m_workQ;	//������۷���
	double m_workH;	//������۷�ѹ

	chooseType m_chFanType;
};

//������Ͳ�����������
class AxilQHCacul
{
public:
	AxilQHCacul(AcDbObjectIdArray fanObjIds,double reqQ,const chooseType& chFanType);
	~AxilQHCacul();
	void caculateQH(CString way);

protected:
	bool choseFansFromDB(AcDbObjectIdArray fanObjIds,int flag);//flagΪͨ�緽ʽ�ı�ǩ
	bool choseFansByRand(AcDbObjectIdArray objIds, int classifyIntMax,int flag);
private:
	AcDbObjectIdArray m_fanObjIds;
	double m_reqQ;

	double m_workQ;
	double m_workH;

	chooseType m_chFanType;
};

//��Ϸ�Ͳ���������ȣ����ͨ��
class SeriesQHCacul:public AxilQHCacul
{
public:
	SeriesQHCacul(AcDbObjectIdArray fanObjIds,double reqQ,const chooseType& chFanType);
	~SeriesQHCacul();
	//virtual void caculateQH(CString way);

private:
	AcDbObjectIdArray m_fanObjIds;
	double m_reqQ;

	double m_workQ;
	double m_workH;

	chooseType m_chFanType;
};

//��������
class MutiserQHCacul : public AxilQHCacul
{
public:
	MutiserQHCacul(AcDbObjectIdArray fanObjIds,double reqQ,const chooseType& chFanType);
	~MutiserQHCacul();
	virtual void caculateQH(CString way);

private:
	virtual bool choseFansFromDB(AcDbObjectIdArray fanObjIds,int flag);
	virtual bool choseFansByRand(AcDbObjectIdArray objIds, int classifyIntMax,int flag);

//private:
//	void caculated(AcDbObjectId fanObjId,CString way);

private:
	AcDbObjectIdArray m_fanObjIds;
	double m_reqQ;

	double m_workQ;
	double m_workH;

	chooseType m_chFanType;
};

//���ͨ��
class LibVentQHCacul : public AxilQHCacul
{
public:
	LibVentQHCacul(AcDbObjectIdArray fanObjIds,double reqQ,const chooseType& chFanType);
	~LibVentQHCacul();
	void caculateQH(CString way);

private:
	virtual bool choseFansFromDB(AcDbObjectIdArray fanObjtIds,int flag);
	virtual bool choseFansByRand(AcDbObjectIdArray objIds, int classifyIntMax,int flag);
	void setFanNumsInLibs();
	AcDbObjectId getrelatedLib(AcDbObjectId fanId);

private:
	AcDbObjectIdArray m_fanObjIds;
	double m_reqQ;

	double m_workQ;
	double m_workH;

	chooseType m_chFanType;
};
