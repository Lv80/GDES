#pragma once

//��ģ̬���ĵ������л�
class DocumentLockSwitch
{
public:
	DocumentLockSwitch()
	{
		acDocManager->lockDocument( curDoc() );
	}
	~DocumentLockSwitch()
	{
		acDocManager->unlockDocument( curDoc() );
	}
};

//�л�controlbar��ʾ
class ControlBarShowSwitch
{
public:
	//���캯������controlbar
	ControlBarShowSwitch(CWnd* _dlg) : dlg(_dlg)
	{
		ShowParentControlBar(dlg, FALSE);
	}
	//����������ʾcontrolbar
	~ControlBarShowSwitch()
	{
		ShowParentControlBar(dlg, TRUE);
	}

private:
	static void ShowParentControlBar(CWnd* pWnd, BOOL bShow)
	{
		CAcModuleResourceOverride myResources;
		CControlBar* pBar = reinterpret_cast<CControlBar*>(pWnd->GetParent());
		if(pBar == 0) return;

		CMDIFrameWnd* pAcadFrame = acedGetAcadFrame();
		if(pAcadFrame == 0) return;

		pAcadFrame->ShowControlBar( pBar, bShow, FALSE );
	}
	CWnd* dlg;
};

//�л�ģ̬������ʾ/����
class ShowOrHideWindow
{
public:
	//���캯������
	ShowOrHideWindow(CDialog* _dlg) : dlg(_dlg)
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
	CDialog* dlg;
};