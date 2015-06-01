#pragma once
#include "GasBaseAcesDlg.h"
#include "afxwin.h"
#include "Resource.h"

// MEREDlg �Ի���

class MEREDlg : public GasBaseAcesDlg
{
	DECLARE_DYNAMIC(MEREDlg)

public:
	MEREDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MEREDlg();

// �Ի�������
	enum { IDD = IDD_MERE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	CComboBox m_methodCombBox;
	BOOL m_yesOrNo;
	CString m_objName;
	AcStringArray m_bookMks;

public:
	afx_msg void OnBnClickedOk();
	void setObjectName(const CString& txtSaveName);
	void setBookMarks(const AcStringArray& bookMks);
	void setDesText(const CString& des);

private:
	void writeDatasToFile(BOOL yesOrNo,const CString& strMethod);
public:
	CString m_des;
};
