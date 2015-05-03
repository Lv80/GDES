#pragma once
#include "afxwin.h"
#include "Resource.h"

// WcyPropertyDlg �Ի���

class WcyPropertyDlg : public CDialog
{
	DECLARE_DYNAMIC(WcyPropertyDlg)

public:
	WcyPropertyDlg(CWnd* pParent = NULL,CString func = _T(""));   // ��׼���캯��
	virtual ~WcyPropertyDlg();

// �Ի�������
	enum { IDD = IDD_PROPERTY_DLG2 };

	// ����ͼԪ
	void setMineGE(const AcDbObjectId& objId);

	// ����ֶ�
	void addField(const CString& field);

	// �Ƿ���ʾȫ������
	void showAllData(bool bFlag);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	BOOL InitPropGridCtrl();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnCbnSelchangeCaculMathodCombo();

private:
	CComboBox m_method;
	CMFCPropertyGridCtrl m_propertyDataList;
	AcDbObjectId m_objId;          // ͼԪid
	AcStringArray m_fields;        // Ҫ��ʾ���ֶ�
	bool m_showAll;                // �Ƿ���ʾȫ������(Ĭ��true)
	CString m_func;

	bool caculate();
};
