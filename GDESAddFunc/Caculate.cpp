#include "StdAfx.h"
#include "Caculate.h"
#include <vector>

typedef std::vector<double> doubleVector;

static void StringsToNum( const AcStringArray& strDatas, doubleVector& doubleDatas)
{
	for(int i = 0; i < strDatas.length(); i++)
	{
		double temp = _tstof(strDatas[i].kACharPtr());
		doubleDatas.push_back(temp);
	}
}

/*
 * ����1����
 *	|-0�������˹ӿ����
 *	|-1���ܻط�����˹Ũ��
 *	|-2���ش���ѹ
 *	|-3������ܻط����
 *	|-4��ɱø���ϵ��
 *	|-5���ϵͳ����ϵ��
 *	|-6��˹��̨��
 * ����2����̨��˹�ö��������˹���Ũ�ȡ���˹��ѹ��
 * ����3���������
*/
bool Calculate::PumpCapacityCacul( const AcStringArray& baseDatas,const AcStringArray& pumpDatas,CString& strRet )
{
	if(baseDatas.isEmpty() || pumpDatas.isEmpty()) return false;
	doubleVector dBaseDatas,dPumpDatas;
	StringsToNum(baseDatas,dBaseDatas);
	StringsToNum(pumpDatas,dPumpDatas);
	if(dBaseDatas[0] <= 0) return false;
	int pumpNum = (int)dBaseDatas[6];
	double sumPump = 0;
	for(int j = 0; j < pumpNum; j++)
	{
		double pumpQ = dPumpDatas[3*j];
		double pumpCon = dPumpDatas[3*j+1];
		double pumpP = dPumpDatas[3*j+2];

		double tmp1 = pumpQ * pumpCon* 0.01 * dBaseDatas[5] * (dBaseDatas[2]-pumpP);
		double temp = tmp1 / 2.0 / 101.325;
		sumPump += temp;
		//acutPrintf(_T("\n��%d̨��\t Q:%.2lf,C:%.2lf,P:%.2lf"),j+1,pumpQ,pumpCon,pumpP);
	}

	double ret = (dBaseDatas[1]*0.01*dBaseDatas[3] + sumPump) * 330 * 1440 * 0.0001 / dBaseDatas[0];
	strRet.Format(_T("%.2lf"),ret);
	//for(int i = 0 ; i < dBaseDatas.size(); i++)
	//{
	//	acutPrintf(_T("\n��%d��ֵ:%.2lf"),i+1,dBaseDatas[i]);
	//}
	//acutPrintf(_T("\n��һ��ֵ:%.2lf\t�ڶ���ֵ:%.2lf\t������ֵ:%.2lf"),dBaseDatas[1]*0.01*dBaseDatas[3],sumPump,330 * 1440 * 0.0001 / dBaseDatas[0]);
	return true;
}