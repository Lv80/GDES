#pragma once
#include "RcuAcUiBaseDlg.h"

//�����곡�Ի���
class RcuAddDrillDlg : public RcuAcUiBaseDlg
{
	DECLARE_DYNAMIC(RcuAddDrillDlg)

public:
	RcuAddDrillDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RcuAddDrillDlg();

// �Ի�������
	enum { IDD = IDD_DRILL_NEW_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
