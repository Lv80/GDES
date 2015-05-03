#pragma once

#include "dlimexp.h"

typedef AcArray<CMFCPropertyGridProperty*> AcPropertyArray;
typedef double (*SyncFunc)(AcPropertyArray& properties);

//����ͬ��������
//ͨ����������ʵ���麯��caculate()�����㲻ͬ������ֵ
class MINEGE_DLLIMPEXP SyncFunctor
{
public:
	SyncFunctor(AcPropertyArray& pProps);
	//���麯��
	virtual double caculate() = 0;

protected:
	//Ҫͬ��������й��������Զ���
	//�û���Ҫ�Լ�����������飬�����������Զ�����˳����ӽ���
	AcPropertyArray& m_pProps;
};

//�����Զ������ԵĻ���
class MINEGE_DLLIMPEXP CustomGridProperty : public CMFCPropertyGridProperty
{
public:
	CustomGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL);
	~CustomGridProperty();
	//������ʾ�л�
	void highlight(bool bHighlight = true);
	//����ͬ������
	void setSyncFun(SyncFunctor* fn);

protected:
	//������������ֵ
	virtual void OnDrawValue(CDC* pDC, CRect rect);
	//����������������(δʵ��)
	virtual void OnDrawName(CDC* pDC, CRect rect);
	//˫��ͬ����������ֵ
	virtual BOOL OnDblClk(CPoint point);

protected:
	//�Ƿ����
	bool m_bHighlight;
	//�������ֺ�����ֵ�ľ��ο��С
	CRect m_valueRect, m_nameRect;
	//ͬ������ָ��(���û�ָ��)
	SyncFunctor* m_fn;
};

// ��������
class MINEGE_DLLIMPEXP CIntProp : public CustomGridProperty
{
public:
	CIntProp(const CString& strName, const COleVariant& varValue, int nMinValue, int nMaxValue, LPCTSTR lpszDescr = NULL);

	virtual BOOL OnUpdateValue();
private:
	int m_nMinValue;
	int m_nMaxValue;
};

// ����������
class MINEGE_DLLIMPEXP CNumericProp : public CustomGridProperty
{
public:
	CNumericProp(const CString& strName, const COleVariant& varValue, double dMinValue, double dMaxValue, unsigned short precise, LPCTSTR lpszDescr = NULL);

	virtual BOOL OnUpdateValue();
	virtual CString FormatProperty();

private:
	double m_dMinValue;
	double m_dMaxValue;
	unsigned short m_precise; // С���㾫��
};

class MINEGE_DLLIMPEXP IntStrProp : public CustomGridProperty
{
public:
	IntStrProp(const CString& name, int value, const AcDbIntArray& intValues, const AcStringArray& strValues, LPCTSTR lpszDescr = NULL);
	virtual BOOL OnUpdateValue();
	virtual CString FormatProperty();

private:
	CString Int2Str(int intValue);
	int Str2Int(const CString& strValue);

	//int m_value;
	AcDbIntArray m_intValues;
	AcStringArray m_strValues;
};

class MINEGE_DLLIMPEXP DateTimeProperty : public CustomGridProperty
{
public:
	DateTimeProperty(const CString& strName, const COleDateTime& timeSrc, LPCTSTR lpszDescr = NULL);

	virtual CString FormatProperty();
	virtual BOOL OnUpdateValue();

protected:
	virtual CWnd* CreateInPlaceEdit(CRect rectEdit, BOOL& bDefaultFormat);
	virtual void OnDrawDescription(CDC* pDC, CRect rect);
};

class MINEGE_DLLIMPEXP MyDateTimeCtrl : public CDateTimeCtrl
{
public:
	MyDateTimeCtrl(	DateTimeProperty* pProp) : m_pProp(pProp) {}

	DECLARE_MESSAGE_MAP()
	afx_msg void OnDtnDatetimechange(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnNMKillfocus(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnDtnCloseup(NMHDR *pNMHDR, LRESULT *pResult);
	// ʹ��NM_KILLFOCUS��DTN_CLOSEUP��2����ϢҲ�ܹ����Ŀ��

protected:
	DateTimeProperty* m_pProp;
};


class MINEGE_DLLIMPEXP DataObjectProperty : public CustomGridProperty
{
public:
	DataObjectProperty(const CString& name, const CString& value, const AcStringArray& strValues, LPCTSTR lpszDescr = NULL);

//protected:
//	virtual BOOL HasButton() const { return TRUE; } // ����list֮���������Ч����û����ʾһ��...��ť
//	virtual void OnClickButton(CPoint point) { AfxMessageBox(_T("helllo")); }
};
// ����һ��ClickProp���μ�MFCPropertyGridCtrlHelper.cppĩβ����