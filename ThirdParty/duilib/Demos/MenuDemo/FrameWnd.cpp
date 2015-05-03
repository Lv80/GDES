#include "duilib.h"

CFrameWnd::CFrameWnd( LPCTSTR pszXMLPath )
	:  m_strXMLPath(pszXMLPath)
{
}

LPCTSTR CFrameWnd::GetWindowClassName() const
{
	return _T("MainWnd");
}

CDuiString CFrameWnd::GetSkinFile()
{
	return m_strXMLPath;
}

CDuiString CFrameWnd::GetSkinFolder()
{
	return _T("Skin");
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

	__super::Notify(msg);
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
				 MessageBox(m_hWnd, L"��ѡ��Menu_Test1", L"", 0);
			 } 
			 else
			 {
				 MessageBox(m_hWnd, L"��ȡ��Menu_Test1", L"", 0);
			 }			 
		 }
		 else if ( *strMenuName == _T("Menu_Test2")) 
		 {
				MessageBox(m_hWnd, L"�㵥����Menu_Test2", L"", 0);		 
		 }
		 else if ( *strMenuName == _T("Menu_Test3")) 
		 {
			 if (bChecked)
			 {
				 MessageBox(m_hWnd, L"��ѡ��Menu_Test3", L"", 0);
			 } 
			 else
			 {
				 MessageBox(m_hWnd, L"��ȡ��Menu_Test3", L"", 0);
			 }			 
		 }

		 delete strMenuName;
	 }
	 bHandled = false;
	 return 0;
 }