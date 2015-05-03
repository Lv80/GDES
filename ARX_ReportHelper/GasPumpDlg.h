#pragma once
#include "ResultDlg.h"
#include "afxcmn.h"
#include "CGridListCtrlGroups.h"
#include "GasPumpDataModel.h"

class GasPumpDlg : public GasBaseAcesDlg
{
	DECLARE_DYNAMIC(GasPumpDlg)

public:
	GasPumpDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~GasPumpDlg();

// �Ի�������
	enum { IDD = IDD_GAS_PUMP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CGridListCtrlGroups m_gasPumpCListPump;

private:
	void InitListCtrl();
	BOOL readDataFromFiles(vector<GasPumpDataRecord>& records,int& num);
	//BOOL WriteDataToFile(const CString& txtName,const ArrayVector& datas);
	BOOL readPumpDatas( ArrayVector& datavector);
	BOOL readDataFromSysDlg(AcStringArray& sysNames);
private:
	GasPumpDataModel m_dataModel;
	vector<GasPumpDataRecord> m_records;
};
