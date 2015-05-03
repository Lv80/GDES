#pragma once

#include "../MineGE/HelperClass.h"
#include "../ArxHelper/ArxUtilHelper.h"


#define SINGLE_FAN_CHIM		_T("��������Ͳ")

#define AXILIARY_RAM		_T("������Ͳ")

#define DISCONTI_RAM		_T("��Ϸ�Ͳ")

#define SINGLE_DOUBLE_ROW	_T("����˫��")

#define FAN_IN_SERRIER		_T("��������")

#define HYBIRD_VENT			_T("���ͨ��")

#define CABINET_VENT		_T("���ͨ��")

#define LIBRARY_VENT		_T("���ͨ��")

#define DRILLING_VENT		_T("���ͨ��")

static AcDbObjectId GetLinkedTTunelId(AcDbObjectId fanObjId)
{
	AcDbObjectId TTunelId;
	//��ȡ������ڵ����
	AcDbObjectId tunelId;
	DrawHelper::GetHostGE(fanObjId,tunelId);

	if (ArxUtilHelper::IsEqualType(_T("TTunnel"),tunelId))
	{
		TTunelId = tunelId;
	}

	else
	{
		//��ȡ���������������ӵĹ�����
		TTunelId = DrawHelper::GetRelatedTW(tunelId);
	}

return TTunelId;
}

static AcDbObjectIdArray GetLinkedFans(AcDbObjectId ttunnelId)
{
	AcDbObjectIdArray tunnelIds = DrawHelper::GetRelatedTunnel(ttunnelId);
	
	//tunnelIds.append(ttunnelId);
	//acutPrintf(_T("\n���ӵ��������:%d"),tunnelIds.length());

	AcDbObjectIdArray fanIds;
	int len = tunnelIds.length();
	for (int i = 0; i < len; i++)
	{
		AcDbObjectIdArray releatFanIds;
		DrawHelper::GetTagGEById2(tunnelIds[i],_T("LocalFan"),releatFanIds);
		int fanNum = releatFanIds.length();
		if(0 == fanNum) continue;
		for(int j = 0; j < fanNum; j++)
		{
			fanIds.append(releatFanIds[j]);
		}
	}

	//acutPrintf(_T("\n�ҵ�������ķ��������:%d"),fanIds.length());
	return fanIds;
}