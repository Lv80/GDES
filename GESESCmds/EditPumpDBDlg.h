#pragma once

#include "Resource.h"
#include "afxcmn.h"
#include <SqliteHelper/SqliteHelper.h>
#include "afxwin.h"
#include "BtnST.h"

struct DBDatas 
{
	CString type;
	CString weight;
	CString speed;
	CString maxp;
	CString factory;
	CString length;
	CString height;
	CString weidth;
	CString absp;
	CString power;
	CString maxq;
	CString minabsp;

	void CopyFromType(const TypeTable& tt)
	{
		type = tt.type;
		minabsp.Format(_T("%d"), tt.absP);
		weight.Format(_T("%d"), tt.weight);
		length.Format(_T("%d"), tt.length);
		weidth.Format(_T("%d"), tt.weidth);
		height.Format(_T("%d"), tt.heigth);
		factory = tt.factName;
	}

	void CopyFromProperty(const PropertyTable& pt)
	{
		speed.Format(_T("%d"), pt.speed);
		power.Format(_T("%.1f"), pt.power);
		maxq.Format(_T("%.2f"), pt.maxQ);
		maxp.Format(_T("%d"), pt.maxP);
		absp.Format(_T("%d"), pt.absP);
	}

	void Print()
	{
		acutPrintf(_T("\n����:%s,��������ѹ:%s,����:%s,��:%s,��:%s,��:%s,����:%s,ת��:%s,�������:%s,�������:%s,����ѹ��:%s,�����ѹ:%s"),
			type,minabsp,weight,length,weidth,height,factory,speed,power,maxq,maxp,absp);
	}
};

typedef std::vector<DBDatas> DBDatasVector;

class EditPumpDBDlg : public CDialog
{
	DECLARE_DYNAMIC(EditPumpDBDlg)

public:
	EditPumpDBDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~EditPumpDBDlg();

// �Ի�������
	enum { IDD = IDD_FIND_PUMP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_btype;
	BOOL m_bweight;
	BOOL m_bspeed;
	BOOL m_bmaxp;
	BOOL m_bfactory;
	BOOL m_blength;
	BOOL m_bheight;
	BOOL m_bweidth;
	BOOL m_bminabsp;
	BOOL m_babsp;
	BOOL m_bpower;
	BOOL m_bmaxq;
	BOOL m_ball;
	CString m_type;
	CString m_weight;
	CString m_speed;
	CString m_maxp;
	CString m_factory;
	CString m_length;
	CString m_height;
	CString m_weidth;
	CString m_absp;
	CString m_power;
	CString m_maxq;
	CString m_minabsp;
	CString m_itemsNum;
	CListCtrl m_listCtrl;

	CButtonST m_powerBtn;
	CButtonST m_abspBtn;
	CButtonST m_maxqBtn;
	CButtonST m_typeBtn;
	CButtonST m_weightBtn;
	CButtonST m_speedBtn;
	CButtonST m_factoryBtn;
	CButtonST m_lengthBtn;
	CButtonST m_heightBtn;
	CButtonST m_weidthBtn;
	CButtonST m_minabspBtn;
	CButtonST m_maxpBtn;
	CButtonST m_allBtn;
	//CListCtrlEx m_listCtrl;

protected:
	HICON m_hIcon;

private:
	void SetAllCheckBox();
	void OnInitListCtrl();
	void UpdateList( const DBDatasVector& datasV );
	void setCountFans();
	//�����������
	//1--ֻ�����ͱ������
	//2--ֻ�����Ա������
	//3--�������ͱ��������Ա�����
	int CheckBoxTable();
	bool FindPumpsByCondition( DBDatasVector& datasV );
	bool DeletePump( const DBDatas& datas );
	void OnlyTypesql(CString& ttsql,CString& msg);
	void OnlyPropertysql(CString& ptsql,CString& msg);
	int GetCheckBoxNum();
	bool EditsHasEmpty();
	bool GetEditContents(TypeTable& tt,PropertyTable& pt);
	void SetCheckBoxIcon();

public:
	afx_msg void OnBnClickedAllPumpCheck();
	afx_msg void OnBnClickedPumpNameCheck();
	afx_msg void OnBnClickedPumpLengthCheck();
	afx_msg void OnBnClickedPumpAbspCheck();
	afx_msg void OnBnClickedPumpWeightCheck();
	afx_msg void OnBnClickedPumpHeightCheck();
	afx_msg void OnBnClickedPumpPowerCheck();
	afx_msg void OnBnClickedPumpSpeedCheck();
	afx_msg void OnBnClickedPumpWeidthCheck();
	afx_msg void OnBnClickedPumpMaxqCheck();
	afx_msg void OnBnClickedPumpMaxpCheck();
	afx_msg void OnBnClickedPumpMinabspCheck();
	afx_msg void OnBnClickedPumpFactoryCheck();
	afx_msg void OnBnClickedExitButton();
	afx_msg void OnBnClickedUpdatePumpdbButton();
	afx_msg void OnBnClickedFindPump();
	afx_msg void OnNMRClickFindPumpRetList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeleteItem();
	afx_msg void OnNMDblclkFindPumpRetList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickFindPumpRetList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC *pDC,CWnd *pWnd,UINT nCtlColor);
};
