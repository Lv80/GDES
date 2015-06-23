#pragma once

#include "DockBarChildDlg.h"
#include "BtnST.h"
/**
	CButtonSTʹ�ü��
	http://www.cnblogs.com/lidabo/archive/2012/12/17/2821122.html
*/

//ʯ�Ž�ú������Ի���
class RcuDesignDlg : public DockBarChildDlg
{
	DECLARE_DYNAMIC(RcuDesignDlg)

public:
	RcuDesignDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RcuDesignDlg();

// �Ի�������
	enum { IDD = IDD_RCU_DESIGN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//ʯ���б�
	CListCtrl m_list;
	//�곡�б�
	CListCtrl m_list2;
	CButtonST m_updBtn;

	//ˢ�°�ť������Ϣ
	afx_msg void OnBnClickedUpdate();
	//������ť������Ϣ
	afx_msg void OnBnClickedExport();
	//ʯ���б����л�ʱ��������Ϣ
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	//ʯ���б�˫����Ϣ
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	//ʯ���б��Ҽ���Ϣ
	afx_msg void OnNMRclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	//�곡�б�˫����Ϣ
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	//�곡�б��Ҽ���Ϣ
	afx_msg void OnNMRclickList2(NMHDR *pNMHDR, LRESULT *pResult);

	//ʯ���б��Ҽ��˵�����Ϣ��Ӧ
	afx_msg void OnHilightRockGateCommand();
	afx_msg void OnModifyRockGateCommand();
	afx_msg void OnDeleteRockGateCommand();
	afx_msg void OnAddRockGateCommand();

	//�곡�б��Ҽ��˵�����Ϣ��Ӧ
	afx_msg void OnAddDrillSiteCommand();
	afx_msg void OnDeleteDrillSiteCommand();
	afx_msg void OnModifyDrillSiteCommand();
	afx_msg void OnHilightDrillSiteCommand();

	//��ӦMyMsg.h���Զ�����Ϣ
	afx_msg LRESULT OnRcuAddMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRcuDelMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRcuModifyMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRcuUpdateMessage(WPARAM wParam, LPARAM lParam);

	//�Ի����麯������
	virtual BOOL OnInitDialog();
	virtual void OnClosing();

	//�������Щ�������ṩ���Զ�����Ϣӳ�亯��ʹ��
private:
	//�����û�ָ���Ĳ�������ʯ���б�
	void updateRockGateListCtrl(unsigned int op, const AcDbObjectId& rock_gate);
	//�����û�ָ���Ĳ��������곡�б�
	void updateDrillSiteListCtrl(unsigned int op, const AcDbObjectId& drill_site);
	
	//����ʯ��
	void addRockGate(const AcDbObjectId& rock_gate);
	//ɾ��ʯ��
	void delRockGate(int row1);
	//�޸�ʯ��
	void modifyRockGate(int row1);

	//�����곡
	void addDrillSite(const AcDbObjectId& drill_site);
	//ɾ���곡
	void delDrillSite(int row2);
	//�޸��곡
	void modifyDrillSite(int row2);

	//���¶Ի���
	void updateUI();
};
