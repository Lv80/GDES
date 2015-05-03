#pragma once

#include "afxpropertygridctrl.h"
#include "PropertyData_DockBarChildDlg.h"
#include "afxwin.h"

class PropertyDockBarChildDlg : public PropertyData_DockBarChildDlg
{
	DECLARE_DYNAMIC(PropertyDockBarChildDlg)

public:
	PropertyDockBarChildDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PropertyDockBarChildDlg();

	afx_msg LRESULT OnPropertyChanged(WPARAM,LPARAM);
// �Ի�������
	enum { IDD = IDD_PROPERTY_GRID_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	//// ����ͼԪ
	//void setMineGE(const AcDbObjectId& objId);

	//// ����ֶ�
	//void addField(const CString& field);

	void readPropertyData();
	void writePropertyData();

private:
	CMFCPropertyGridCtrl m_propertyDataList;
	//AcDbObjectId m_objId;          // ͼԪid
	//AcStringArray m_fields;        // Ҫ��ʾ���ֶ�
};
