#pragma once

/**
��ģ̬�Ի�����cad����ͬ��ˢ�µ�ʵ�ַ���
��ARX_RCU��Ŀ��Ҫʵ�����µĹ��ܣ�
(1)�ڷ�ģ̬�Ի��������ӡ�ɾ�����޸�ͼԪ��cad��������ͬ�����£����ʵ�ֱȽϼ򵥣�
(2)��cad���������ӡ�ɾ�����޸ġ�undo/redo����ģ̬�Ի�����ͬ������

��2�����ܵ�ʵ���漰�����µ�һЩ����Ҫ�㣺
1���������ݿⷴӦ������ͼԪɾ�����޸ġ�undo/redo�ĺ�����������
   ��Щ���������÷�ģ̬�Ի���ĸ����ڣ�dockbar����ǿ��ˢ�º���
   �μ�Rcu_DbReactor::updateRcuDesignDlg()����
2��Rcu_DbReator::updateRcuDesignDlg()������ʵ�ֱȽϼ򵥣����ǵ��÷�ģ̬�Ի����ForceUpdate()����ǿ��ˢ��
3��RcuDesiginDockBarDlg::ForceUpdate()�����ڲ����Ǽ򵥵�����Invalidate()�����ػ����
   Ϊ�˱��������Ƶ�ˢ�£�����ʵ��ʹ��һ���򵥵ġ���������������ͨ��Global_GotoPaintFlag����OnPaint()ֻ������һ��
4��RcuDesiginDockBarDlg::OnPaint()�ڲ�������ӶԻ���ĸ��º�����ʵʱ���½���
*/

#include "RcuDesignDlg.h"

//��ģ̬ͣ���Ի���
class RcuDesiginDockBarDlg : public CAcUiDockControlBar {
	DECLARE_DYNAMIC (RcuDesiginDockBarDlg)

public:
	//----- Child dialog which will use the resource id supplied
	RcuDesignDlg mChildDlg;
	//ǿ��ˢ�½���
	void ForceUpdate();

public:
	RcuDesiginDockBarDlg ();
	virtual ~RcuDesiginDockBarDlg ();

public:
	virtual BOOL Create (CWnd *pParent, LPCTSTR lpszTitle) ;
	virtual void SizeChanged (CRect *lpRect, BOOL bFloating, int flags) ;

	afx_msg int OnCreate (LPCREATESTRUCT lpCreateStruct) ;
	afx_msg void OnSysCommand (UINT nID, LPARAM lParam) ;
	afx_msg void OnSize (UINT nType, int cx, int cy) ;
	afx_msg void OnPaint();
	virtual bool OnClosing ();

	DECLARE_MESSAGE_MAP()
} ;
