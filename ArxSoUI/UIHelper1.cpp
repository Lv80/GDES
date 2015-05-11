#include "StdAfx.h"
#include "UIHelper.h"

#include "SoUILoader.h"
#include "realwnddlg.h"
#include "SouiRealWndHandler.h"

#include "../ArxHelper/HelperClass.h"
#include "../MineGE/HelperClass.h"

using namespace SOUI;

class MySoUiLoader1 : public SoUILoader
{
public:
	MySoUiLoader1(HINSTANCE hInstance) : SoUILoader(hInstance)
	{

	}

	~MySoUiLoader1() 
	{
	}

	virtual LPCTSTR getSkinDir() const
	{
		return _T("\\..\\..\\Skin\\demo1");
	}

	virtual bool initRealWnd()
	{
		//�����洰�ڴ���ӿ�
		//CSouiRealWndHandler * pRealWndHandler = new CSouiRealWndHandler();
		//pSouiApp->SetRealWndHandler(pRealWndHandler);
		//pRealWndHandler->Release();

		return SoUILoader::initRealWnd();
	}

	virtual bool initGlobalStyle()
	{
		//����ȫ����Դ����XML
		//��ʼ��SOUIȫ����Դ
		return (TRUE == pSouiApp->Init(_T("uidef"), _T("xml"))); 
	}
};

void UIHelper::ShowSoUIDlg1()
{
	// �л���Դ
	CAcModuleResourceOverride myResources;

	//����soui��ص��齨����Դ
	MySoUiLoader1 suLoader(_hdllInstance);
	if(!suLoader.init()) return;

	CRealWndDlg dlg;
	dlg.DoModal();
}