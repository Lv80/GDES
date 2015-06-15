#pragma once

#include "acui.h"
#include "Resource.h"

// ����ģ̬�Ի����3����Ϣ�����˻���DockBarChildDlg
// ����������Ϳ���ֻרע�Ի��������Ϣ����
// ͬʱ�����ظ�����
class DockBarChildDlg : public CAcUiDialog 
{
	DECLARE_DYNAMIC (DockBarChildDlg)

public:
	virtual ~DockBarChildDlg();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	DockBarChildDlg(UINT idd, CWnd *pParent =NULL, HINSTANCE hInstance = NULL) ;

public:
	//��ʾ/���ظ�����(dockbar)
	void ShowParentControlBar(BOOL bShow) const;
	virtual void OnClosing(); // Ĭ��ʵ��Ϊ��(�����Ҫ����رգ����ظú���)
	virtual BOOL OnCommand (WPARAM wParam, LPARAM lParam) ;
	afx_msg void OnSize (UINT nType, int cx, int cy) ;
	afx_msg LRESULT OnAcadKeepFocus (WPARAM wParam, LPARAM lParam) ;
} ;

//�л�controlbar��ʾ
class ControlBarShowSwitch
{
public:
	//���캯������controlbar
	ControlBarShowSwitch(DockBarChildDlg* _dlg) : dlg(_dlg)
	{
		dlg->ShowParentControlBar(FALSE);
	}
	//����������ʾcontrolbar
	~ControlBarShowSwitch()
	{
		dlg->ShowParentControlBar(TRUE);
	}
	DockBarChildDlg* dlg;
};
