#pragma once
#include "afxwin.h"
#include "resource.h"
#include "afxcmn.h"
#include "enumDefine.h"


// FanChooseDlg �Ի���
class FanChooseDlg : public CDialog
{
	DECLARE_DYNAMIC(FanChooseDlg)

public:
	FanChooseDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FanChooseDlg();

// �Ի�������
	enum { IDD = IDD_CHOOSE_FAN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedOk();

	chooseType m_chFanType;
};
