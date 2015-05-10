#include "StdAfx.h"
#include "UIHelper.h"

#include "SoUILoader.h"
#include "realwnddlg.h"
//#include "SouiRealWndHandler.h"
//#include "MemFlash.h"
//#include "httpsvr/HTTPServer.h"
//#include "uianimation/UiAnimationWnd.h"

#include "../ArxHelper/HelperClass.h"
#include "../MineGE/HelperClass.h"

#include <controls.extend/propgrid/SPropertyGrid.h>
#include <controls.extend/SFlyWnd.h>
#include <controls.extend/SFadeFrame.h>
#include <controls.extend/sradiobox2.h>
#include <controls.extend/SVscrollbar.h>
#include <controls.extend/SChromeTabCtrl.h>
#include <controls.extend/siectrl.h>
#include <controls.extend/schatedit.h>
#include <controls.extend/SScrollText.h>
#include <controls.extend/SCalendar2.h>
#include <controls.extend/SListCtrlEx.h>

class MySoUiLoader : public SoUILoader
{
public:
	MySoUiLoader(HINSTANCE hInstance) : SoUILoader(hInstance)
	{

	}

	~MySoUiLoader() 
	{
		//ж�ز˵��߿����hook
		CMenuWndHook::UnInstallHook();  
	}

	virtual LPCTSTR getSkinDir() const
	{
		return _T("\\..\\..\\Skin\\ArxSoUI");
	}

	virtual bool initExtendControls()
	{
		//��SApplicationϵͳ��ע�����ⲿ��չ�Ŀؼ���SkinObj��
		//SWkeLoader wkeLoader;
		//if(wkeLoader.Init(_T("wke.dll")))        
		//{
		//	pSouiApp->RegisterWndFactory(TplSWindowFactory<SWkeWebkit>());//ע��WKE�����
		//}
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SGifPlayer>());//ע��GIFPlayer
		//pSouiApp->RegisterSkinFactory(TplSkinFactory<SSkinGif>());//ע��SkinGif
		//pSouiApp->RegisterSkinFactory(TplSkinFactory<SSkinAPNG>());//ע��SSkinAPNG
		//pSouiApp->RegisterSkinFactory(TplSkinFactory<SSkinVScrollbar>());//ע�����������Ƥ��

		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SIPAddressCtrl>());//ע��IP�ؼ�
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SPropertyGrid>());//ע�����Ա�ؼ�
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SChromeTabCtrl>());//ע��ChromeTabCtrl
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SIECtrl>());//ע��IECtrl
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SChatEdit>());//ע��ChatEdit
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SScrollText>());//ע��SScrollText
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SListCtrlEx>());//ע��SListCtrlEx

		//if(SUCCEEDED(CUiAnimation::Init()))
		//{
		//	pSouiApp->RegisterWndFactory(TplSWindowFactory<SUiAnimationWnd>());//ע�ᶯ���ؼ�
		//}
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SFlyWnd>());//ע����ж����ؼ�
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SFadeFrame>());//ע�ὥ���������ؼ�
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SRadioBox2>());//ע��RadioBox2
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SCalendar2>());//ע��SCalendar2

		//SSkinGif::Gdiplus_Startup();
		return true;
	}

	virtual bool initSysResource()
	{
		if(SoUILoader::initSysResource())
		{
			//����hook���Ʋ˵��ı߿�
			CMenuWndHook::InstallHook(hInstance,_T("_skin.sys.menu.border"));
		}
		return SoUILoader::initSysResource();
	}

	virtual bool initRealWnd()
	{
		//�����洰�ڴ���ӿ�
		//CSouiRealWndHandler * pRealWndHandler = new CSouiRealWndHandler();
		//pSouiApp->SetRealWndHandler(pRealWndHandler);
		//pRealWndHandler->Release();

		return SoUILoader::initRealWnd();
	}
};

void UIHelper::ShowSoUIDlg()
{
	// �л���Դ
	CAcModuleResourceOverride myResources;

	//����soui��ص��齨����Դ
	MySoUiLoader suLoader(_hdllInstance);
	if(!suLoader.init()) return;

	//��������ʾʹ��SOUI����Ӧ�ó��򴰿�
	CRealWndDlg dlg;
	dlg.DoModal();
}