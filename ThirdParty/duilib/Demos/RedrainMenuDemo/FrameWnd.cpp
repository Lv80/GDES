#include "duilib.h"

CFrameWnd::CFrameWnd()
{
}

LPCTSTR CFrameWnd::GetWindowClassName() const
{
	return _T("MainWnd");
}

CDuiString CFrameWnd::GetSkinFile()
{
	return _T("Main_dlg.xml");
}

CDuiString CFrameWnd::GetSkinFolder()
{
	return _T("../skin/RedrainMenuRes");
}

// 	UILIB_RESOURCETYPE CFrameWnd::GetResourceType() const
// 	{
// 		return UILIB_ZIPRESOURCE;
// 	}
// 
// 
// 	LPCTSTR CFrameWnd::GetResourceID() const
// 	{
// 		return MAKEINTRESOURCE(IDR_ZIPRES1);
// 	}

void CFrameWnd::InitWindow()
{
	CenterWindow();
}

void CFrameWnd::OnFinalMessage( HWND hWnd )
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}

void CFrameWnd::Notify( TNotifyUI& msg )
{
	if( msg.sType == _T("click") ) 
	{	
		if( msg.pSender->GetName() == _T("btnMenu") ) 
		{
			CMenuWnd* pMenu = new CMenuWnd();
			CPoint point = msg.ptMouse;
			ClientToScreen(m_hWnd, &point);
			pMenu->Init(NULL, _T("menutest.xml"), point, &m_PaintManager, &m_MenuCheckInfo);
			//���򿪲˵�
			//pMenu->Init(NULL, _T("menutest.xml"), point, &m_PaintManager, &m_MenuCheckInfo, eMenuAlignment_Right );
			//���ϲ�򿪲˵�
			//pMenu->Init(NULL, _T("menutest.xml"), point, &m_PaintManager, &m_MenuCheckInfo, eMenuAlignment_Right | eMenuAlignment_Bottom);
		}
		else if (msg.pSender->GetName() == _T("Menu_btn") )
		{
			DUI__Trace(_T("�㵥���˰�ť"));
		}
	}
	WindowImplBase::Notify(msg);
}

 LRESULT CFrameWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
 {
	 if (uMsg == WM_MENUCLICK)
	 {
		 CDuiString *strMenuName = (CDuiString*)wParam;
		 bool bChecked = (bool)lParam;		 

		 if ( *strMenuName == _T("Menu_Test1")) 
		 {
			 if (bChecked)
			 {
				 MessageBox(m_hWnd, _T("��ѡ��Menu_Test1"), _T(""), MB_OK);
			 } 
			 else
			 {
				 MessageBox(m_hWnd, _T("��ȡ��Menu_Test1"), _T(""), MB_OK);
			 }			 
		 }
		 else if ( *strMenuName == _T("Menu_Test2")) 
		 {
				MessageBox(m_hWnd, _T("�㵥����Menu_Test2"), _T(""), MB_OK);		 
		 }
		 else if ( *strMenuName == _T("Menu_Test3")) 
		 {
			 if (bChecked)
			 {
				 MessageBox(m_hWnd, _T("��ѡ��Menu_Test3"), _T(""), MB_OK);
			 } 
			 else
			 {
				 MessageBox(m_hWnd, _T("��ȡ��Menu_Test3"), _T(""), MB_OK);
			 }			 
		 }

		 delete strMenuName;
	 }
	 bHandled = FALSE;
	 return 0;
 }