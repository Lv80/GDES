#pragma once

struct CListCtrl_DataRecord
{
	CListCtrl_DataRecord()
	{}

	CListCtrl_DataRecord(const CString& strIndx, const CString& strQ, const CString& strCon,  const CString& strP)
		:m_strIndx(strIndx)
		,m_strQ(strQ)
		,m_strCon(strCon)
		,m_strP(strP)
	{}

	CString	m_strIndx;
	CString	m_strQ;
	CString	m_strCon;
	CString m_strP;

	CString GetCellText(int col, bool title) const
	{
		switch(col)
		{
		case 0: { static const CString title0(_T("���")); return title ? title0 : m_strIndx; }
		case 1: { static const CString title1(_T("��˹�õĶ����(m3/min)")); return title ? title1 : m_strQ; }
		case 2: { static const CString title2(_T("��˹���Ũ��(%)")); return title ? title2 : m_strCon; }
		case 3: { static const CString title3(_T("��˹��ѹ��(kPa)")); return title ? title3 : m_strP; }
		default:{ static const CString emptyStr; return emptyStr; }
		}
	}

	int  GetColCount() const { return 4; }
};

class CListCtrl_DataModel
{
	vector<CListCtrl_DataRecord> m_Records;
	int	m_LookupTime;
	int m_RowMultiplier;
	int m_RowCount;

public:
	CListCtrl_DataModel()
		:m_RowMultiplier(0)
		,m_LookupTime(0)
		,m_RowCount(0)
	{
		InitDataModel();
	}

	void InitDataModel()
	{
		int oldCount = m_Records.size();
		if(oldCount > m_RowCount)
		{
			int dif = oldCount - m_RowCount;
			for(int i = dif-1; i >= 0; i--)
			{
				m_Records.pop_back();
			}
			return;
		}
		//m_Records.clear();
		for(int i = 0; i < m_RowCount - oldCount; i++)
		{
			CString strIndx;
			strIndx.Format(_T("%d"),i+oldCount+1);
			m_Records.push_back( CListCtrl_DataRecord(strIndx,_T(""), _T(""), _T("") ));
		}

		//if (m_RowMultiplier > 1)
		//{
		//	vector<CListCtrl_DataRecord> rowset(m_Records);
		//	m_Records.reserve((m_RowMultiplier-1) * rowset.size());
		//	for(int i = 0 ; i < m_RowMultiplier ; ++i)
		//	{
		//		m_Records.insert(m_Records.end(), rowset.begin(), rowset.end());
		//	}
		//}
	}

	CString GetCellText(size_t lookupId, int col) const
	{
		if (lookupId >= m_Records.size())
		{
			static CString oob(_T("Out of Bound"));
			return oob;
		}
		// How many times should we search sequential for the row ?
		for(int i=0; i < m_LookupTime; ++i)
		{
			for(size_t rowId = 0; rowId < m_Records.size(); ++rowId)
			{
				if (rowId==lookupId)
					break;
			}
		}
		return m_Records.at(lookupId).GetCellText(col, false);
	}

	//vector<CString> GetRunning() const
	//{
	//	vector<CString> isRuning;
	//	for(size_t rowId = 0 ; rowId < m_Records.size(); ++rowId)
	//		isRuning.push_back( m_Records[rowId].m_strQ );
	//	sort(isRuning.begin(), isRuning.end());
	//	isRuning.erase(unique(isRuning.begin(), isRuning.end()), isRuning.end());
	//	return isRuning;
	//}

	size_t GetRowIds() const { return m_Records.size(); }
	int GetColCount() const { return CListCtrl_DataRecord().GetColCount(); }
	CString GetColTitle(int col) const { return CListCtrl_DataRecord().GetCellText(col, true); }

	vector<CListCtrl_DataRecord>& GetRecords() { return m_Records; }
	void SetRowMultiplier(int multiply) { if (m_RowMultiplier != multiply ) { m_RowMultiplier = multiply; InitDataModel(); } }
	void SetRowCount(int rowCount) { if (m_RowCount != rowCount ) { m_RowCount = rowCount;InitDataModel(); } }
	void SetRecords(vector<CListCtrl_DataRecord> records){ m_Records.clear();copy(records.begin(),records.end(),back_inserter(m_Records));}
	//vector<CListCtrl_DataRecord> GetRecords(){ return m_Records;}
};