#pragma once
#include "afxcmn.h"
#include "ResultDlg.h"
#include "afxwin.h"
#include "CGridListCtrlGroups.h"
#include "CListCtrl_DataModel.h"
//#include "CListCtrl_DataModel.h"

class GasSysDlg : public GasBaseAcesDlg
{
	DECLARE_DYNAMIC(GasSysDlg)

public:
	GasSysDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~GasSysDlg();

	// �Ի�������
	enum { IDD = IDD_GAS_SYS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	// ����������˹���ϵͳ��
	CString m_numPermSys;
	// ������ʱ��˹���ϵͳ����
	CString m_numTempSys;
	//HICON m_hIcon;
	CGridListCtrlGroups m_permCListCtrl;
	CGridListCtrlGroups m_tempCListCtrl;

	CListCtrl_DataModel m_permDataModel;
	vector<CListCtrl_DataRecord> m_permRecords;

	CListCtrl_DataModel m_tempDataModel;
	vector<CListCtrl_DataRecord> m_tempRecords;

public:
	afx_msg void OnEnKillfocusPermsysNumEdit();
	// ����������˹���ϵͳ�б�
	//CEditListCtrl m_permSysListCtrl;
	afx_msg void OnBnClickedEnsure();
	afx_msg void OnEnKillfocusListEdit();
	afx_msg void OnEnSetfocusPermsysNumEdit();
	afx_msg void OnBnClickedPermClearButton();
	afx_msg void OnNMRClickPermsysInputList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeleteItem();

	afx_msg void OnBnClickedTempClearButton();
	afx_msg void OnBnClickedExitButton();

	afx_msg void OnNMRClickTempsysInputList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusTempesysNumEdit();
	afx_msg void OnEnSetfocusTempesysNumEdit();

private:
	void OnInitList();
	void SetPermItems(int num);
	void SetTempItems(int num);
	BOOL RecordRunningSysName(const AcStringArray& gasSysNams,const AcStringArray& gasSysRunning);
};
