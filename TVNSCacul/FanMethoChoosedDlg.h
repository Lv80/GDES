#pragma once
#include "PropertyData_DockBarChildDlg.h"
#include "afxwin.h"

// FanMethoChoosedDlg �Ի���

class FanMethoChoosedDlg : public PropertyData_DockBarChildDlg
{
	DECLARE_DYNAMIC(FanMethoChoosedDlg)

public:
	FanMethoChoosedDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FanMethoChoosedDlg();

// �Ի�������
	enum { IDD = IDD_FAN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CComboBox m_method;

protected:
	void readPropertyData();
	void writePropertyData();

public:
	virtual BOOL OnInitDialog();

	CString m_fanRank;
private:
	CString m_ventMethod;
public:
	CString m_ventWay;
};
