#pragma once

#define RES_TYPE 0   //���ļ��м�����Դ
// #define RES_TYPE 1   //��PE��Դ�м���UI��Դ
// #define RES_TYPE 2   //��zip���м�����Դ

#ifdef _DEBUG
#define SYS_NAMED_RESOURCE _T("soui-sys-resourced.dll")
#else
#define SYS_NAMED_RESOURCE _T("soui-sys-resource.dll")
#endif

using namespace SOUI;

class SoUILoader
{
public:
	SoUILoader(HINSTANCE _hInstance) : hInstance(_hInstance), pSouiApp(0)
	{
		HRESULT hRes = CoInitialize(NULL);
		SASSERT(SUCCEEDED(hRes));
		//�͹ٷ���������Щ��ͬ
		//��SetCurrentDirectoryǰ����dll
		hSysResource=LoadLibrary(SYS_NAMED_RESOURCE);
	}

	virtual ~SoUILoader()
	{
		hInstance = 0; hSysResource = 0;
		delete pSouiApp; pSouiApp = 0;
		CoUninitialize();
	}

	SComMgr* getComMrg()
	{
		return &comMgrObj;
	}

	bool init()
	{
		if(!initRender()) return false;
		if(!initApp()) return false;
		if(!initSysResource()) return false;
		if(!initResource()) return false;
		if(!initScripts()) return false;
		if(!initExtendControls()) return false;
		if(!initRealWnd()) return false;
		if(!initGlobalStyle()) return false;
		return true;
	}

	virtual LPCTSTR getSkinDir() const
	{
		return _T(".");
	}

	virtual bool initRender()
	{
		//����render���(render_gdi��render_skia)
		//bLoaded = pComMgr->CreateRender_Skia((IObjRef**)&pRenderFactory)
		BOOL bLoaded = getComMrg()->CreateRender_GDI((IObjRef**)&pRenderFactory);
		SASSERT_FMT(bLoaded,_T("load interface [%s] failed!"),_T("render-gdi"));

		//����ͼƬ����ģ��(imggid��imgwic)
		bLoaded=getComMrg()->CreateImgDecoder((IObjRef**)&pImgDecoderFactory);
		SASSERT_FMT(bLoaded,_T("load interface [%s] failed!"), _T("imgdecoder"));

		//Ϊ��Ⱦģ����������Ҫ���õ�ͼƬ����ģ��
		if(bLoaded == TRUE)
		{
			pRenderFactory->SetImgDecoderFactory(pImgDecoderFactory);
		}
		return bLoaded == TRUE;
	}

	virtual bool initApp()
	{
		if(pSouiApp == 0)
		{
			pSouiApp=new SApplication(pRenderFactory, hInstance);
			SStringT strResDir = pSouiApp->GetAppDir();
			strResDir += getSkinDir();
			//�����������·���޸ĵ�demo���ڵ�Ŀ¼
			//ע��:������ڼ���soui-sys-resource.dll֮������,����souiϵͳ��Դ���ػ�ʧ��!!!
			SetCurrentDirectory(strResDir);
			//SOUIϵͳ���Ǵ�appdirȥ������Դ
			//ע:���˵���ǲ�׼ȷ��,soui��Դ�����в�û��ʹ��GetAppDir(),��Ҫ��������SetCurrentDirectory()���õ�ǰ·��
			pSouiApp->SetAppDir(strResDir);
		}
		return true;
	}

	virtual bool initResource()
	{
		//����һ����Դ�ṩ����,SOUIϵͳ��ʵ����3����Դ���ط�ʽ
		//�ֱ��Ǵ��ļ����أ���EXE����Դ���ؼ���ZIPѹ��������
		CAutoRefPtr<IResProvider>   pResProvider;
		BOOL bLoaded = FALSE;

#if (RES_TYPE == 0)//���ļ�����
		CreateResProvider(RES_FILE,(IObjRef**)&pResProvider);
		bLoaded = pResProvider->Init((LPARAM)_T("uires"),0);
#elif (RES_TYPE==1)//��EXE��Դ����
		CreateResProvider(RES_PE,(IObjRef**)&pResProvider);
		bLoaded = pResProvider->Init((WPARAM)hInstance,0);
#elif (RES_TYPE==2)//��ZIP������
		bLoaded=getComMrg()->CreateResProvider_ZIP((IObjRef**)&pResProvider);
		SASSERT_FMT(bLoaded,_T("load interface [%s] failed!"),_T("resprovider_zip"));

		ZIPRES_PARAM param;
		param.ZipFile(pRenderFactory, _T("uires.zip"),"souizip");
		bLoaded = pResProvider->Init((WPARAM)&param,0);
		SASSERT(bLoaded);
#endif

		if(bLoaded == TRUE)
		{
			//��������IResProvider����SApplication����
			//����Դ����Ƥ��
			pSouiApp->AddResProvider(pResProvider);
		}
		return (bLoaded == TRUE);
	}

	virtual bool initScripts()
	{
		BOOL bLoaded = FALSE;
#ifdef DLL_CORE
		//����LUA�ű�ģ�飬ע�⣬�ű�ģ��ֻ����SOUI�ں�����DLL��ʽ����ʱ����ʹ�á�
		bLoaded = getComMrg()->CreateScrpit_Lua((IObjRef**)&pScriptLua);
		SASSERT_FMT(bLoaded,_T("load interface [%s] failed!"),_T("scirpt_lua"));
		pSouiApp->SetScriptFactory(pScriptLua);
#endif//DLL_CORE

		return true;
	}

	virtual bool initExtendControls()
	{
		return true;
	}

	virtual bool initSysResource()
	{
		//����ϵͳ��Դ
		if(hSysResource == 0) return false;

		BOOL bLoaded = FALSE;
		CAutoRefPtr<IResProvider> sysSesProvider;
		CreateResProvider(RES_PE,(IObjRef**)&sysSesProvider);
		bLoaded = sysSesProvider->Init((WPARAM)hSysResource,0);

		if(bLoaded == TRUE)
		{
			pSouiApp->LoadSystemNamedResource(sysSesProvider);

			//����hook���Ʋ˵��ı߿�
			CMenuWndHook::InstallHook(hInstance,_T("_skin.sys.menu.border"));
		}

		return (bLoaded == TRUE);
	}

	virtual bool initRealWnd()
	{
		return true;
	}

	virtual bool initGlobalStyle()
	{
		//����ȫ����Դ����XML
		//��ʼ��SOUIȫ����Դ
		return (TRUE == pSouiApp->Init(_T("xml_init"), _T("xml"))); 
	}

protected:
	HINSTANCE hInstance;                                //��ǰģ��(exe��dll�ľ��)
	HMODULE hSysResource;                               //souiϵͳ��Դdll�ľ��
	SComMgr comMgrObj;                                  // ������ع�����
	CAutoRefPtr<IImgDecoderFactory> pImgDecoderFactory; //ͼƬ������
	CAutoRefPtr<IRenderFactory> pRenderFactory;         //UI��Ⱦģ��,��render-gdi.dll��render-skia.dll�ṩ
	//CAutoRefPtr<ITranslatorMgr> trans;                //�����Է���ģ��,��translator.dll�ṩ
	CAutoRefPtr<IScriptFactory> pScriptLua;             //lua�ű�ģ��,��scriptmodule-lua.dll�ṩ
	SApplication* pSouiApp;
};
