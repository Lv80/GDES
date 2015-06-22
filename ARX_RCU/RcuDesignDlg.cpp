#include "stdafx.h"
#include "RcuDesignDlg.h"
#include "RcuEditRockGateDlg.h"
#include "RcuEditDrillSiteDlg.h"

#include "Rcu.h"
#include "RcuHelper.h"
#include "RcuDataLink.h"
#include "ListCtrlHelper.h"
#include "SwitchHelper.h"

#include "../ArxHelper/HelperClass.h"
#include "../MineGE/HelperClass.h"

#include "../DefGE/RcuGE.h"
#include "../DefGE/Pore.h"
#include "../DefGE/DrillSite.h"
#include "../DefGE/RockGate.h"
#include "../DefGE/CoalSurface.h"

//΢��list1�ı�ͷ�п��
static void CrackHeadColumnWidth(CListCtrl& m_list)
{
	m_list.SetColumnWidth(1, int(m_list.GetColumnWidth(1)*1.2));
	for(int i=5;i<m_list.GetHeaderCtrl()->GetItemCount()+1;i++)
	{
		m_list.SetColumnWidth(i, int(m_list.GetColumnWidth(i)*1.5));
	}
	m_list.SetColumnWidth(7, int(m_list.GetColumnWidth(7)*1.5));
}

//�޸��곡�б��n�е�����
static void ModifyDrillSiteToListCtrl(CListCtrl& m_list2, int n, const DrillSiteLink& ds_link)
{
	{
		m_list2.SetItemText( n, 1, ds_link.m_name );
	}
	{
		CString value;
		ArxUtilHelper::IntToString(ds_link.m_leftOrRight, value);
		m_list2.SetItemText( n, 2, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(ds_link.m_dist, value);
		m_list2.SetItemText( n, 3, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(ds_link.m_width, value);
		m_list2.SetItemText( n, 4, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(ds_link.m_height, value);
		m_list2.SetItemText( n, 5, value);
	}
	{
		CString value;
		ArxUtilHelper::IntToString(ds_link.m_start, value);
		m_list2.SetItemText( n, 6, value);
	}
}

//�޸�ʯ���б��n�е�����
static void ModifyRockGateToListCtrl(CListCtrl& m_list, int n, RockGateLink& rg_link)
{
	{
		m_list.SetItemText( n, 1, rg_link.m_name );
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(rg_link.m_length, value);
		m_list.SetItemText( n, 2, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(rg_link.m_width, value);
		m_list.SetItemText( n, 3, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(rg_link.m_height, value);
		m_list.SetItemText( n, 4, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(rg_link.m_dist, value);
		m_list.SetItemText( n, 5, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(rg_link.m_radius, value);
		m_list.SetItemText( n, 6, value);
	}
	{
		m_list.SetItemText( n, 7, rg_link.m_pt);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(rg_link.m_left, value);
		m_list.SetItemText( n, 8, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(rg_link.m_right, value);
		m_list.SetItemText( n, 9, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(rg_link.m_top, value);
		m_list.SetItemText( n, 10, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(rg_link.m_bottom, value);
		m_list.SetItemText( n, 11, value);
	}
}

//��ʯ���б�������һ��
static void InsertRockGateToListCtrl(CListCtrl& m_list, const AcDbObjectId& objId, RockGateLink& rg_link)
{
	//����һ��
	int row = ListCtrlHelper::InsertRowToListCtrl(m_list, objId);
	//����ʯ���б�ĸ�������
	ModifyRockGateToListCtrl(m_list, row, rg_link);
}

//���곡�б�������һ��
static void InsertDrillSiteToListCtrl(CListCtrl& m_list, const AcDbObjectId& objId,const DrillSiteLink& ds_link)
{
	//����һ��
	int row = ListCtrlHelper::InsertRowToListCtrl(m_list, objId);
	//�����곡�б�ĸ�������
	ModifyDrillSiteToListCtrl(m_list, row, ds_link);
}

static bool UpdateRockGateDataFromDlg(const AcDbObjectId& rock_gate, RockGateLink& rg_link, CoalSurfaceLink& cs_link)
{
	CAcModuleResourceOverride resourceOverride;

	//��ʼ��ʯ�ŶԻ���
	RcuEditRockGateDlg dlg;
	dlg.m_rock_gate = rock_gate;
	//���ʯ��id��Ϊ��,���ȡ���ݲ����µ��Ի���
	dlg.readFromDataLink(rg_link, cs_link);

	if(IDOK != dlg.DoModal()) return false;

	//�ӶԻ�������ȡ����
	dlg.writeToDataLink(rg_link, cs_link);

	//�����ݸ��µ�ͼԪ��
	rg_link.updateData(true);
	cs_link.updateData(true);

	return true;
}

static bool UpdateDrillSiteDataFromDlg(const AcDbObjectId& drill_site, DrillSiteLink& ds_link)
{
	CAcModuleResourceOverride resourceOverride;

	//��ʼ���곡�Ի���
	RcuEditDrillSiteDlg dlg;
	dlg.m_drill_site = drill_site;
	dlg.readFromDataLink(ds_link);

	if(IDOK != dlg.DoModal()) return false;

	//�ӶԻ�������ȡ����
	dlg.writeToDataLink(ds_link);

	if(!drill_site.isNull())
	{
		//�޸��곡�ļ��β���
		RcuHelper::ModifyDrillSiteParam(drill_site, ds_link);
	}

	//�����ݸ��µ�ͼԪ��
	ds_link.updateData(true);
	
	return true;
}

// RcuDesignDlg �Ի���

IMPLEMENT_DYNAMIC(RcuDesignDlg, DockBarChildDlg)

RcuDesignDlg::RcuDesignDlg(CWnd* pParent /*=NULL*/)
	: DockBarChildDlg(RcuDesignDlg::IDD, pParent)
{

}

RcuDesignDlg::~RcuDesignDlg()
{
	//ClearListCtrlItemDatas(m_list);
}

void RcuDesignDlg::DoDataExchange(CDataExchange* pDX)
{
	DockBarChildDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_LIST3, m_list2);
}

BEGIN_MESSAGE_MAP(RcuDesignDlg, DockBarChildDlg)
	ON_BN_CLICKED(IDC_BUTTON4, &RcuDesignDlg::OnBnClickedExport)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &RcuDesignDlg::OnLvnItemchangedList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &RcuDesignDlg::OnNMDblclkList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &RcuDesignDlg::OnNMRclickList1)
	ON_COMMAND(ID_RCU_LIST_HILIGHT, &RcuDesignDlg::OnHilightRockGateCommand)
	ON_COMMAND(ID_RCU_LIST_MODIFY, &RcuDesignDlg::OnModifyRockGateCommand)
	ON_COMMAND(ID_RCU_LIST_DELETE, &RcuDesignDlg::OnDeleteRockGateCommand)
	ON_COMMAND(ID_RCU_LIST_ADD, &RcuDesignDlg::OnAddRockGateCommand)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST3, &RcuDesignDlg::OnNMDblclkList2)
	ON_NOTIFY(NM_RCLICK, IDC_LIST3, &RcuDesignDlg::OnNMRclickList2)
	ON_COMMAND(IDR_DRILL_SITE_ADD, &RcuDesignDlg::OnAddDrillSiteCommand)
	ON_COMMAND(IDR_DRILL_SITE_DELETE, &RcuDesignDlg::OnDeleteDrillSiteCommand)
	ON_COMMAND(IDR_DRILL_SITE_MODIFY, &RcuDesignDlg::OnModifyDrillSiteCommand)
	ON_COMMAND(IDR_DRILL_SITE_HILIGHT, &RcuDesignDlg::OnHilightDrillSiteCommand)
END_MESSAGE_MAP()

BOOL RcuDesignDlg::OnInitDialog()
{
	DockBarChildDlg::OnInitDialog();

	m_list.SetExtendedStyle( m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	AcStringArray rock_fields;
	FieldHelper::GetAllFields(_T("RockGate"), rock_fields);
	// ����Column
	ListCtrlHelper::BuildListCtrlHeadColumns( m_list, rock_fields );
	CrackHeadColumnWidth(m_list);

	m_list2.SetExtendedStyle( m_list2.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	AcStringArray drill_fields;
	FieldHelper::GetAllFields(_T("DrillSite"), drill_fields);
	// ����Column
	ListCtrlHelper::BuildListCtrlHeadColumns( m_list2, drill_fields );

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void RcuDesignDlg::OnClosing()
{
	//ɾ���б���ÿһ�и���������(��Щ���ݶ���new������)
	//ClearListCtrlItemDatas(m_list);
	// �������
	//ClearList(m_list);
}

// RcuDesignDlg ��Ϣ�������

void RcuDesignDlg::OnBnClickedExport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

/**
http://blog.csdn.net/carl2380/article/details/4816392
http://blog.csdn.net/sjls2659/article/details/7580660
http://blog.csdn.net/oldmtn/article/details/9298577
����ListCtrlʱ��LVN_ITEMCHANGED��Ӧ3�ε���Ī������ı���
�������:
	�������´���
		if(LVIF_STATE == pNMLV->uChanged && (pNMLV->uNewState & LVIS_SELECTED))
		{
			int row = pNMLV->iItem;
		}
*/
void RcuDesignDlg::OnLvnItemchangedList1( NMHDR* pNMHDR, LRESULT* pResult )
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>( pNMHDR );

	if(LVIF_STATE == pNMLV->uChanged && (pNMLV->uNewState & LVIS_SELECTED))
	{
		int row1 = pNMLV->iItem;
		if( row1 != LB_ERR )
		{
			//��ǰѡ���ʯ��
			ItemData* pData1 = (ItemData*)m_list.GetItemData(row1);

			//�ĵ����л�
			DocumentLockSwitch lock_switch;

			//�����곡�������ֶ�
			AcStringArray fields;
			FieldHelper::GetAllFields(_T("DrillSite"), fields);

			//����ʯ�Ź������곡
			AcDbObjectIdArray drill_sites;
			RcuHelper::GetRelatedDrillSites(pData1->objId, drill_sites);

			//����곡�б�
			ListCtrlHelper::ClearListCtrl(m_list2);
			//��ӵ��곡�б�
			ListCtrlHelper::InsertDatasToListCtrl(m_list2, fields, drill_sites);
		}
	}

	*pResult = 1;
}

void RcuDesignDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//�ڼ���
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int row1 = pNMItemActivate->iItem;
	if( row1 != LB_ERR )
	{
		ItemData* pData1 = (ItemData*)m_list.GetItemData(row1);

		//�ĵ����л�
		DocumentLockSwitch lock_switch;
		//����ѡ��ͼԪ
		ArxEntityHelper::SelectEntity(pData1->objId);
		//��λ��ͼԪ
		ArxEntityHelper::ZoomToEntityForModeless(pData1->objId);
	}
	//����pResultΪ1,���θ�������Ӧ����Ϣ
	*pResult = 1;
}

void RcuDesignDlg::OnNMRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//�ڼ���
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int row = pNMItemActivate->iItem;
	//��ֹ�ڿհ�����������˵�
	//if (m_list.GetSelectedCount() > 0)
	{
		//�������δ���, ��������Ӧ��ListCtrl
		CMenu menu, *pPopup;
		menu.LoadMenu(IDR_RCU_LIST_MENU);
		pPopup = menu.GetSubMenu(0);
		CPoint myPoint;
		ClientToScreen(&myPoint);
		GetCursorPos(&myPoint); //���λ��
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y,this);  
	}
	//����pResultΪ1,���θ�������Ӧ����Ϣ
	*pResult = 1;
}

void RcuDesignDlg::OnAddRockGateCommand()
{
	//�л�controlbar����ʾ
	ControlBarShowSwitch cb_switch(this);

	//��ģ̬�Ի���AutoCAD��ý���
	//acedGetAcadDwgView()->SetFocus();

	//�л��ĵ���
	DocumentLockSwitch lock_switch;

	//ѡ��ʯ�ŵĲ��������
	AcGePoint3d pt;
	if(!ArxUtilHelper::PromptPt(_T("\n��ѡ��ʯ�ŵĲ�������꣺"), pt)) return;

	//���öԻ����ȡʯ�ź�ú������
	RockGateLink rg_link;
	CoalSurfaceLink cs_link;
	if(!UpdateRockGateDataFromDlg(AcDbObjectId::kNull, rg_link, cs_link)) return;

	//����ʯ�ź�ú��ͼԪ
	if(RcuHelper::CreateRockGate(pt, rg_link, cs_link))
	{
		//��list1�в���һ��ʯ������
		InsertRockGateToListCtrl(m_list, rg_link.getDataSource(), rg_link);
	}
}

void RcuDesignDlg::OnDeleteRockGateCommand()
{
	//MessageBox(_T("RcuDesignDlg::OnDeleteRockGateCommand"));
	int row1 = ListCtrlHelper::GetCurSelOfList(m_list);
	if(row1 != LB_ERR)
	{
		ItemData* pData1 = ( ItemData* )m_list.GetItemData( row1 );

		//�ĵ����л�
		DocumentLockSwitch lock_switch;

		//ɾ��ͼԪ
		ArxEntityHelper::EraseObject(pData1->objId, true);

		//ɾ��ѡ�����
		ListCtrlHelper::DeleteListCtrlItem(m_list, row1);

		//cad���ڻ�ȡ����
		acedGetAcadFrame()->SetFocus();
	}
}

void RcuDesignDlg::OnModifyRockGateCommand()
{
	//MessageBox(_T("RcuDesignDlg::OnLocateCommand"));
	int row1 = ListCtrlHelper::GetCurSelOfList(m_list);
	if(row1 == LB_ERR)
	{
		MessageBox( _T( "��ȷ����ǰ��һ�б�ѡ��!" ) );
		return;
	}
	ItemData* pData1 = ( ItemData* )m_list.GetItemData( row1 );

	//�ĵ��л���
	DocumentLockSwitch lock_switch;
	
	//��ȡʯ�ź�ú������
	RockGateLink rg_link;
	CoalSurfaceLink cs_link;
	if(!RcuHelper::GetRockGateAndCoalSurfDatas(pData1->objId, rg_link, cs_link))
	{
		MessageBox(_T("��ȡʯ�Ż�ú��ʧ��!!!"));
		return;
	}

	//�л�controlbar����ʾ
	ControlBarShowSwitch cb_switch(this);

	//�ӶԻ����и�������
	if(UpdateRockGateDataFromDlg(pData1->objId, rg_link, cs_link))
	{
		//�޸ĵ�ǰѡ��ʯ�ŵ�����
		ModifyRockGateToListCtrl(m_list, row1, rg_link);
		//acutPrintf(_T("\n����֮ǰ->���:%.4lf\t�߶�:%.4lf\n"),cs_link.m_width,cs_link.m_height);
	}
}

void RcuDesignDlg::OnHilightRockGateCommand()
{
	//MessageBox(_T("RcuDesignDlg::OnHilightRockGateCommand"));
	int row1 = ListCtrlHelper::GetCurSelOfList(m_list);
	if(row1 != LB_ERR)
	{
		ItemData* pData1 = ( ItemData* )m_list.GetItemData( row1 );

		//�ĵ����л�
		DocumentLockSwitch lock_switch;
		//����ѡ��ʯ��ͼԪ
		ArxEntityHelper::SelectEntity(pData1->objId);

		//cad���ڻ�ȡ����
		acedGetAcadFrame()->SetFocus();
	}
}

void RcuDesignDlg::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	//�ڼ���
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int row = pNMItemActivate->iItem;
	if( row != LB_ERR )
	{
		ItemData* pData = ( ItemData* )m_list2.GetItemData( row );

		//�ĵ����л�
		DocumentLockSwitch lock_switch;

		//����ѡ��ͼԪ
		ArxEntityHelper::SelectEntity(pData->objId);
		//��λ��ͼԪ
		ArxEntityHelper::ZoomToEntityForModeless(pData->objId);
	}
	//����pResultΪ1,���θ�������Ӧ����Ϣ
	*pResult = 1;
}

void RcuDesignDlg::OnNMRclickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	//�ڼ���
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int row = pNMItemActivate->iItem;
	//��ֹ�ڿհ�����������˵�
	//if (m_list2.GetSelectedCount() > 0)
	{
		//�������δ���, ��������Ӧ��ListCtrl
		CMenu menu, *pPopup;
		menu.LoadMenu(IDR_DRILL_SITE_MENU);
		pPopup = menu.GetSubMenu(0);
		CPoint myPoint;
		ClientToScreen(&myPoint);
		GetCursorPos(&myPoint); //���λ��
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
	}
	//����pResultΪ1,���θ�������Ӧ����Ϣ
	*pResult = 1;
}

void RcuDesignDlg::OnAddDrillSiteCommand()
{
	int row1 = ListCtrlHelper::GetCurSelOfList(m_list);
	if(row1 == LB_ERR)
	{
		MessageBox(_T("��ָ�������ʯ�ź��ٽ����곡���!"));
		return;
	}

	ItemData* pData1 = (ItemData*)m_list.GetItemData(row1);

	//�л�controlbar����ʾ
	ControlBarShowSwitch cb_switch(this);

	//��ģ̬�Ի���AutoCAD��ý���
	//acedGetAcadDwgView()->SetFocus();

	//�л��ĵ���
	DocumentLockSwitch lock_switch;

	//���öԻ����ȡ�곡����
	DrillSiteLink ds_link;
	if(!UpdateDrillSiteDataFromDlg(AcDbObjectId::kNull, ds_link)) return;

	//����ʯ�ź�ú��ͼԪ
	if(RcuHelper::CreateDrillSite(pData1->objId, ds_link))
	{
		//��list1�в���һ��ʯ������
		InsertDrillSiteToListCtrl(m_list2, ds_link.getDataSource(), ds_link);
	}

	//cad���ڻ�ȡ����
	acedGetAcadFrame()->SetFocus();
}

void RcuDesignDlg::OnDeleteDrillSiteCommand()
{
	int row2 = ListCtrlHelper::GetCurSelOfList(m_list2);
	if(row2 != LB_ERR)
	{
		ItemData* pData2 = ( ItemData* )m_list2.GetItemData(row2);

		//�ĵ����л�
		DocumentLockSwitch lock_switch;
		//ɾ���곡ͼԪ
		ArxEntityHelper::EraseObject(pData2->objId, true);

		//ɾ��ѡ�����
		ListCtrlHelper::DeleteListCtrlItem(m_list2, row2);

		//cad���ڻ�ȡ����
		acedGetAcadFrame()->SetFocus();
	}
}

void RcuDesignDlg::OnModifyDrillSiteCommand()
{
	int row1 = ListCtrlHelper::GetCurSelOfList(m_list);
	if(row1 == LB_ERR)
	{
		MessageBox(_T("�����ʯ�ź��ٽ����곡���!"));
		return;
	}

	int row2 = ListCtrlHelper::GetCurSelOfList(m_list2);
	if(row2 == LB_ERR)
	{
		MessageBox( _T( "��ѡ��һ���곡����ѡ��!" ) );
		return;
	}

	ItemData* pData1 = (ItemData*)m_list.GetItemData(row1);
	ItemData* pData2 = (ItemData*)m_list2.GetItemData(row2);

	//�л��ĵ���
	DocumentLockSwitch lock_switch;

	//���öԻ����ȡʯ�ź�ú������
	DrillSiteLink ds_link;
	if(!RcuHelper::GetDrillSiteData(pData2->objId, ds_link))
	{
		MessageBox(_T("��ȡ�곡����ʧ��!!!"));
		return;
	}

	//�л�controlbar����ʾ
	ControlBarShowSwitch cb_switch(this);

	if(UpdateDrillSiteDataFromDlg(pData2->objId, ds_link))
	{
		//��list1�в���һ��ʯ������
		ModifyDrillSiteToListCtrl(m_list2, row2, ds_link);
	}

	//cad���ڻ�ȡ����
	acedGetAcadFrame()->SetFocus();
}

void RcuDesignDlg::OnHilightDrillSiteCommand()
{
	//ShowOrHideWindow show_hide(this);
	int row2 = ListCtrlHelper::GetCurSelOfList(m_list2);
	if(row2 != LB_ERR)
	{
		ItemData* pData2 = (ItemData*)m_list2.GetItemData(row2);

		//�ĵ����л�
		DocumentLockSwitch lock_switch;

		//����ѡ���곡ͼԪ
		ArxEntityHelper::SelectEntity(pData2->objId);

		//cad���ڻ�ȡ����
		acedGetAcadFrame()->SetFocus();
	}
}

void RcuDesignDlg::initRockGateListCtrl()
{
	//�ĵ����л�
	DocumentLockSwitch lock_switch;

	AcStringArray fields;
	FieldHelper::GetAllFields(_T("RockGate"), fields);

	AcDbObjectIdArray objIds;
	RcuHelper::FindAllRockGates(objIds);

	ListCtrlHelper::InsertDatasToListCtrl(m_list, fields, objIds);
}
