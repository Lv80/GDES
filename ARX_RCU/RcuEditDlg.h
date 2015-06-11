#pragma once

#include "acui.h"
#include "resource.h"

// RcuDesignDlg �Ի���

class RcuEditDlg : public CAcUiDialog
{
	DECLARE_DYNAMIC(RcuEditDlg)

public:
	RcuEditDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RcuEditDlg();

// �Ի�������
	enum { IDD = IDD_RCU_EDIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double m_x;
	double m_y;
	double m_z;
	double m_length;
	double m_width;
	double m_height;
	double m_left;
	double m_right;
	double m_top;
	double m_bottom;
	double m_radius;
	double m_thick;
	double m_angle;
	double m_dist;
	CListCtrl m_siteList;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnHdnItemdblclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
};
