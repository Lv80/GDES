#pragma once
#include "AcUiBaseDlg.h"

//�����곡�Ի���
class AddDrillDlg : public AcUiBaseDlg
{
	DECLARE_DYNAMIC(AddDrillDlg)

public:
	AddDrillDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AddDrillDlg();

// �Ի�������
	enum { IDD = IDD_DRILL_NEW_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
