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
 *	|-4���ϵͳ����ϵ��
 *	|-5��˹��̨��
 * ����2����
 * ��̨��˹�ö��������˹���Ũ�ȡ���˹��ѹ������ɱø���ϵ����ÿ�׳�����ܵ�ʵ���ھ���ÿ�׹ܵ���Ͼ������١��ܵ�����ϵ��
 * ����3���������
*/
bool Calculate::MineGasCapacityCacul( const AcStringArray& baseDatas,const AcStringArray& pumpDatas,CString& strPumpRet,CString& strSysRet )
{
	if(baseDatas.isEmpty() || pumpDatas.isEmpty()) return false;
	doubleVector dBaseDatas,dPumpDatas;
	StringsToNum(baseDatas,dBaseDatas);
	StringsToNum(pumpDatas,dPumpDatas);
	if(dBaseDatas[0] <= 0) return false;
	int pumpNum = (int)dBaseDatas[5];
	double sumPump = 0;
	double sumTube = 0;
	for(int j = 0; j < pumpNum; j++)
	{
		double pumpQ = dPumpDatas[7*j];
		double pumpCon = dPumpDatas[7*j+1];
		double pumpP = dPumpDatas[7*j+2];
		double pumpKP = dPumpDatas[7*j + 3];
		double tubeD = dPumpDatas[7*j+4];
		double tubeV = dPumpDatas[7*j+5];
		double tubeKS = dPumpDatas[7*j+6];

		double tmp1 = pumpQ * pumpCon* 0.01 * dBaseDatas[4] * (dBaseDatas[2]-pumpP);
		double temp = tmp1 / pumpKP / 101.325;
		sumPump += temp;

		double tmp2 = (tubeD / 0.1457) * (tubeD / 0.1457) * tubeV * pumpCon * 0.01  * (dBaseDatas[2]-pumpP);
		double temp2 = tmp2 / tubeKS / 101.325;
		sumTube += temp2;

		//acutPrintf(_T("\n��%d̨��\t Q:%.2lf,C:%.2lf,P:%.2lf"),j+1,pumpQ,pumpCon,pumpP);
	}

	double ret = (dBaseDatas[1]*0.01*dBaseDatas[3] + sumPump) * 330 * 1440 * 0.0001 / dBaseDatas[0];
	strPumpRet.Format(_T("%.2lf"),ret);

	ret = (dBaseDatas[1]*0.01*dBaseDatas[3] + sumTube) * 330 * 1440 * 0.0001 / dBaseDatas[0];
	strSysRet.Format(_T("%.2lf"),ret);

	//for(int i = 0 ; i < dBaseDatas.size(); i++)
	//{
	//	acutPrintf(_T("\n��%d��ֵ:%.2lf"),i+1,dBaseDatas[i]);
	//}
	//acutPrintf(_T("\n��һ��ֵ:%.2lf\t�ڶ���ֵ:%.2lf\t������ֵ:%.2lf"),dBaseDatas[1]*0.01*dBaseDatas[3],sumPump,330 * 1440 * 0.0001 / dBaseDatas[0]);
	return true;
}

/*
 * ����1����
 *	|-0�������ʵ�ʳ����˹��
 *	|-1Ԥ����������˹�������ú��Ӧ����˹��ú����
 *	|-2���ܻط�����˹Ũ��
 *	|-3������ܻط����
 *	|-4�󾮳�ǰ���ϵ��
*/

bool Calculate::MineGasRealCacul( const AcStringArray& datas,CString& strYearRet )
{
	if(datas.isEmpty()) return false;
	doubleVector dDatas;
	StringsToNum(datas,dDatas);

	if(dDatas[4] <= 0) return false;
	double ret = (dDatas[2]*0.01*dDatas[3] + dDatas[0]/dDatas[4]/365/1440) * 330 * 1440 * 0.0001 / dDatas[1];
	//acutPrintf(_T("\nQs:%.2lf,k:%.2lf"),dDatas[0],dDatas[4]);
	//acutPrintf(_T("\n��һ��ֵ:%.2lf\t�ڶ���ֵ:%.2lf\t������ֵ:%.2lf"),dDatas[2]*0.01*dDatas[3], dDatas[0]/dDatas[4]/365/1440,330 * 1440 * 0.0001 / dDatas[1]);

	strYearRet.Format(_T("%.2lf"),ret);
	return true;
}