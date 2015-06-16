#pragma once

#include "acui.h"
#include "resource.h"

class RcuAcUiBaseDlg : public CAcUiDialog
{
	DECLARE_DYNAMIC(RcuAcUiBaseDlg)

public:
	RcuAcUiBaseDlg(UINT idd,CWnd* pParent = NULL,HINSTANCE hDialogResource=NULL);   // ��׼���캯��
	virtual ~RcuAcUiBaseDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

protected:
	HICON m_hIcon;
};

class ShowOrHideWindow
{
public:
	//���캯������
	ShowOrHideWindow(RcuAcUiBaseDlg* _dlg) : dlg(_dlg)
	{
		dlg->ShowWindow(SW_HIDE);
		////������֮������CAD����ʧȥ����
		//dlg->SetFocus();
	}
	//����������ʾ
	~ShowOrHideWindow()
	{
		dlg->ShowWindow(SW_SHOW);
	}
	RcuAcUiBaseDlg* dlg;
};
