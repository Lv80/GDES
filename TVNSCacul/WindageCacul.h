#pragma once

class WindageCacul
{
public:
	WindageCacul(AcDbObjectId objId);
	~WindageCacul();
	double windageCaculRet();
	double windageCaculByHM();

private:
	void setMethodByFan(AcDbObjectId objId);
	void setKsaiBEByBend();

	void initDatas(AcDbObjectId objId);

private:
	//��Ͳ�Ĳ���
	double m_alpha;	//��ͲĦ������ϵ��
	double m_lenth;	//��Ͳ���ȣ�ȫ����
	double m_diam;	//��Ͳֱ��
	int	   m_joint;	//��Ͳ��ͷ��
	double m_hmWindage;	//���׷���
	CString m_bends;	//����Ƕ�
	CString m_method;	//ͨ�緽��
	CString m_meter;	//��Ͳ����

	//�����������
	double m_ksaiJO;	//��Ͳ��ͷ�ֲ�����ϵ��,������ȡƫ��ֵ0.15(ȡ�˹̶�ֵ)
	double m_ksaiBE;	//��Ͳ����ֲ�����ϵ��
	double m_ksaiON;	//��Ͳ���ھֲ�����ϵ��(���ѹ��ʽ)->1
	double m_ksaiIN;	//��Ͳ��ھֲ�����ϵ��(��Գ��ʽ)->0.6

	double m_ro;	//�����ܶȣ�ȡ������Ŀ����ܶ�
};