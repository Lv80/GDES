#pragma once

/*
 * ���ӻ����渨����
 * ����һ�����б��ڹ���
 * Ҳ��ʹ�ô��뿴�������һЩ
 */
class UIHelper
{
public:
	static void ShowDrawManagerDlg();    // ��ʾͼԪ���ӻ�Ч������/�л��Ի���
	static void ShowFieldManagerDlg();   // ��ʾ�ֶι���Ի���
	static void ShowVarListDlg();        // ��ʾ�����б����Ի���
	static void ShowDataObjectStateDlg();// ��ʾ���ݶ������Ի���

	static void DisplayData();            // ��ʾ���ԶԻ���
	static void DisplayGasTubeDataByFunc(const CString& funcName);
	static void DisplayDataByDoubleClick(); // ˫����ʾ���ԶԻ���(pickset)
	static void DisplayDataByFuncName(const CString& funcName); //ͨ����������������ʾ�ֶΣ���������
	static void DisplayDrillDataByFunc(const CString& funcName); 
	static void DisplayGasPumpDataByFunc(const CString& funcName); 

};
