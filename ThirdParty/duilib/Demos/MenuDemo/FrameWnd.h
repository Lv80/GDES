#pragma once

class CFrameWnd: public WindowImplBase
{
public:
	explicit CFrameWnd(LPCTSTR pszXMLPath);

	LPCTSTR GetWindowClassName() const;
	CDuiString GetSkinFile();
	CDuiString GetSkinFolder();
	//UILIB_RESOURCETYPE GetResourceType() const;
	//LPCTSTR GetResourceID() const;

     void InitWindow();
     void Notify(TNotifyUI& msg);
	 LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	 // CControlUI* CreateControl(LPCTSTR pstrClassName);
private:
	CDuiString		m_strXMLPath;

	map<CDuiString,bool> m_MenuCheckInfo; //����˵��ĵ�ѡ��ѡ��Ϣ
};