#pragma once

#include <string>
#include <vector>

struct PumpType 
{
	int id;
	std::string type;
	std::string factName;
	int absP;
	int weight;
	int length;
	int width;
	int height;
};

struct PumpProperty 
{
	int id;
	int catagory_id;
	int speed;
	double power;
	double maxQ;
	int maxP;
	int absP;
};

typedef std::vector<PumpType> PumpTypeTable;
typedef std::vector<PumpProperty> PumpPropertyTable;
typedef std::vector<int> IDArray;

class DBHelper
{
public:
	DBHelper(const std::string& connector, const std::string& connectionString);
	~DBHelper();

	//����
	bool createPumpTypeTable();
	//����һ������
	bool insertPumpType(const PumpType& pump);
	//���Ӷ������
	bool insertPumpTypeTable(const PumpTypeTable& tbls);
	//��ѯ
	bool getPumpTypeTable(PumpTypeTable& tbls, const std::string& condition="");
	//�޸�(����pump��id������)
	bool updatePumpType(const PumpType& pump);
	//ɾ��
	bool delPumpType(int id);
	//ɾ����������
	bool delPumpTypes(const IDArray& ids);
	//��ȡTypeTable���һ�����ݵ�id
	bool getLastPumpTypeId(int& id);
	//����id��������
	bool getPumpType(int id, PumpType& pump);
	//����id����һϵ�е�����
	bool getPumpTypeTableByIDs(const IDArray& ids, PumpTypeTable& tbls);

	//����
	bool createPumpPropertyTable();
	//����һ������
	bool insertPumpProperty(const PumpProperty& pump);
	//���Ӷ������
	bool insertPumpPropertyTable(const PumpPropertyTable& tbls);
	//��ѯ
	bool getPumpPropertyTable(PumpPropertyTable& tbls, const std::string& condition="");
	//�޸�(����pump��id������)
	bool updatePumpProperty(const PumpProperty& pump);
	//ɾ��
	bool delPumpProperty(int& id);
	//ɾ���������
	bool delPumpProperties(const IDArray& ids);
	//��ȡPropertyTable�������һ�����ݵ�id
	bool getLastPumpPropertyId(int& id);
	//����id��������
	bool getPumpProperty(int id, PumpProperty& pump);
	//����id����һϵ�е�����
	bool getPumpPropertyTableByIDs(const IDArray& ids, PumpPropertyTable& tbls);

private:
	struct DBHelperImpl* d;
};
