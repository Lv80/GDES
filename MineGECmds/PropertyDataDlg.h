#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "../MineGE/FieldInfo.h"
#include "../MineGE/FieldInfoHelper.h"

//Ϊ�˱����PropertyArray���ͳ�ͻ��ʹ��AcArray����һ���µ���������
//�������Ե�ͬ������
typedef AcArray<CMFCPropertyGridProperty*> AcPropertyArray;

// �������ݶԻ���
class PropertyDataDlg : public CDialog
{
	DECLARE_DYNAMIC(PropertyDataDlg)

public:
	PropertyDataDlg(CWnd* pParent = NULL,CString func = _T(""));   // ��׼���캯��
	virtual ~PropertyDataDlg();

	afx_msg LRESULT OnPropertyChanged(WPARAM wparam, LPARAM lparam );
// �Ի�������
	enum { IDD = IDD_PROPERTY_DLG };

	// ����ͼԪ
	void setMineGE(const AcDbObjectId& objId);

	// ����ֶ�
	void addField(const CString& field);

	// �Ƿ���ʾȫ������
	void showAllData(bool bFlag);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	CMFCPropertyGridCtrl m_propertyDataList;
	AcDbObjectId m_objId;          // ͼԪid
	AcStringArray m_fields;        // Ҫ��ʾ���ֶ�
	bool m_showAll;                // �Ƿ���ʾȫ������(Ĭ��true)
	CString m_func;
	AcPropertyArray m_gasProps;           //����ʵ����˹����ص�ͬ������
	AcPropertyArray m_pressureProps;      //����ʵ��ѹ����ص�ͬ������
	AcPropertyArray m_flowProps;          //����ʵ����˹ӿ������ص�ͬ������
	bool caculate();
	void CtrlProperty(COleVariant& changedValue);
	void SyncPropertyDatas(const CString& filedName, COleVariant& changedValue,CMFCPropertyGridProperty*pProp );
};
