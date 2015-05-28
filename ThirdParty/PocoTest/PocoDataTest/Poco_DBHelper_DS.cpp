/**
* 参考链接：
* http://www.vimer.cn/2011/03/%E6%9B%B4%E7%AE%80%E6%B4%81%E7%9A%84c%E6%95%B0%E6%8D%AE%E5%BA%93%E8%AE%BF%E9%97%AE%E6%A1%86%E6%9E%B6-soci.html
* http://www.cyqdata.com/cnblogs/article-detail-25077
* poco提供了2种数据库操作方法
* (1) 使用原始的数据类型,一个字段对应一个变量(参见Poco_DBHelper_Atom.cpp的实现)
* (2) 使用数据结构来操作(比如结构体，类),要实现这种方式,poco要求特例化TypeHandler模板(参见Poco_DBHelper_DS.cpp)
* 第1种方法简单灵活,但比较繁琐(需要很多的中间赋值过程)
* 第2种方法直观,代码看起来更简洁
* poco的TypeHandler机制有一些问题,它要求与数据库中的字段的顺序位置一致,通过位置来绑定变量
* 另一个与poco类似的soci库就没有这种限制,soci可以通过名字来绑定变量(参见上面的第1个链接)
* 注:sql是数据的集合,顺序并不重要,所以poco的这种限制有点不合理
*/

#include "DBHelper.h"

#include <Poco/Data/Session.h>
#include <Poco/Data/SQLite/Connector.h>
#include <Poco/Data/DataException.h>

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;
using Poco::Data::DataException;

static void InitDbSystem()
{
	Poco::Data::SQLite::Connector::registerConnector();
}

static void ShutDownDbSystem()
{
	Poco::Data::SQLite::Connector::unregisterConnector();
}

/**
 * 参考: poco文档首页/POCO Data User Guide
 * 特化TypeHandler模板必须要放在Poco::Data命名空间里
 */
namespace Poco {
	namespace Data {

		//特化TypeHandler<PumpType>
		template <>
		class TypeHandler<PumpType>
		{
		public:
			//bind是在使用use到一个数据结构(不是基本的int、string)的时候被调用
			static void bind(std::size_t pos, const PumpType& obj, AbstractBinder::Ptr pBinder, AbstractBinder::Direction dir)
			{
				//std::cout<<"bind................."<<std::endl;
				poco_assert_dbg (!pBinder.isNull());

				// the table is defined as Person (FirstName VARCHAR(30), lastName VARCHAR, SocialSecNr INTEGER(3))
				// Note that we advance pos by the number of columns the datatype uses! For string/int this is one.
				pos++;
				//TypeHandler<int>::bind(pos++, obj.id, pBinder, dir);
				TypeHandler<std::string>::bind(pos++, obj.type, pBinder, dir);
				TypeHandler<int>::bind(pos++, obj.absP, pBinder, dir);
				TypeHandler<int>::bind(pos++, obj.weight, pBinder, dir);
				TypeHandler<int>::bind(pos++, obj.length, pBinder, dir);
				TypeHandler<int>::bind(pos++, obj.width, pBinder, dir);
				TypeHandler<int>::bind(pos++, obj.height, pBinder, dir);
				TypeHandler<std::string>::bind(pos++, obj.factName, pBinder, dir);
			}

			//字段的个数
			static std::size_t size()
			{
				return 8; // we handle three columns of the Table!
			}

			//prepare是在使用prepareStatement的时候被调用
			static void prepare(std::size_t pos, const PumpType& obj, AbstractPreparator::Ptr pPrepare)
			{
				//std::cout<<"prepare................."<<std::endl;
				poco_assert_dbg (!pPrepare.isNull());
				// the table is defined as Person (FirstName VARCHAR(30), lastName VARCHAR, SocialSecNr INTEGER(3))
				// Note that we advance pos by the number of columns the datatype uses! For string/int this is one.

				TypeHandler<int>::prepare(pos++, obj.id, pPrepare);
				TypeHandler<std::string>::prepare(pos++, obj.type, pPrepare);
				TypeHandler<int>::prepare(pos++, obj.absP, pPrepare);
				TypeHandler<int>::prepare(pos++, obj.weight, pPrepare);
				TypeHandler<int>::prepare(pos++, obj.length, pPrepare);
				TypeHandler<int>::prepare(pos++, obj.width, pPrepare);
				TypeHandler<int>::prepare(pos++, obj.height, pPrepare);
				TypeHandler<std::string>::prepare(pos++, obj.factName, pPrepare);
			}

			//extract是在使用into到一个数据结构(不是基本的int、string)的时候被调用
			static void extract(std::size_t pos, PumpType& obj, const PumpType& defVal, AbstractExtractor::Ptr pExt)
				/// obj will contain the result, defVal contains values we should use when one column is NULL
			{
				std::cout<<"extract................."<<std::endl;
				poco_assert_dbg (!pExt.isNull());

				TypeHandler<int>::extract(pos++, obj.id, defVal.id, pExt);
				TypeHandler<std::string>::extract(pos++, obj.type, defVal.type,pExt);
				TypeHandler<int>::extract(pos++, obj.absP, defVal.absP, pExt);
				TypeHandler<int>::extract(pos++, obj.weight, defVal.weight, pExt);
				TypeHandler<int>::extract(pos++, obj.length, defVal.length, pExt);
				TypeHandler<int>::extract(pos++, obj.width, defVal.width, pExt);
				TypeHandler<int>::extract(pos++, obj.height, defVal.height, pExt);
				TypeHandler<std::string>::extract(pos++, obj.factName, defVal.factName, pExt);
			}

		private:
			TypeHandler();
			~TypeHandler();
			TypeHandler(const TypeHandler&);
			TypeHandler& operator=(const TypeHandler&);
		};

		//特化TypeHandler<PumpProperty>
		template <>
		class TypeHandler<PumpProperty>
		{
		public:
			//bind是在使用use到一个数据结构(不是基本的int、string)的时候被调用
			static void bind(std::size_t pos, const PumpProperty& obj, AbstractBinder::Ptr pBinder, AbstractBinder::Direction dir)
			{
				//std::cout<<"bind................."<<std::endl;
				poco_assert_dbg (!pBinder.isNull());

				// the table is defined as Person (FirstName VARCHAR(30), lastName VARCHAR, SocialSecNr INTEGER(3))
				// Note that we advance pos by the number of columns the datatype uses! For string/int this is one.
				pos++;
				//TypeHandler<int>::bind(pos++, obj.id, pBinder, dir);
				TypeHandler<int>::bind(pos++, obj.catagory_id, pBinder, dir);
				TypeHandler<int>::bind(pos++, obj.speed, pBinder, dir);
				TypeHandler<double>::bind(pos++, obj.power, pBinder, dir);
				TypeHandler<double>::bind(pos++, obj.maxQ, pBinder, dir);
				TypeHandler<int>::bind(pos++, obj.maxP, pBinder, dir);
				TypeHandler<int>::bind(pos++, obj.absP, pBinder, dir);
			}

			//字段的个数
			static std::size_t size()
			{
				return 7; // we handle three columns of the Table!
			}

			//prepare是在使用prepareStatement的时候被调用
			static void prepare(std::size_t pos, const PumpProperty& obj, AbstractPreparator::Ptr pPrepare)
			{
				//std::cout<<"prepare................."<<std::endl;
				poco_assert_dbg (!pPrepare.isNull());
				// the table is defined as Person (FirstName VARCHAR(30), lastName VARCHAR, SocialSecNr INTEGER(3))
				// Note that we advance pos by the number of columns the datatype uses! For string/int this is one.

				TypeHandler<int>::prepare(pos++, obj.id, pPrepare);
				TypeHandler<int>::prepare(pos++, obj.catagory_id, pPrepare);
				TypeHandler<int>::prepare(pos++, obj.speed, pPrepare);
				TypeHandler<double>::prepare(pos++, obj.power, pPrepare);
				TypeHandler<double>::prepare(pos++, obj.maxQ, pPrepare);
				TypeHandler<int>::prepare(pos++, obj.maxP, pPrepare);
				TypeHandler<int>::prepare(pos++, obj.absP, pPrepare);
			}

			//extract是在使用into到一个数据结构(不是基本的int、string)的时候被调用
			static void extract(std::size_t pos, PumpProperty& obj, const PumpProperty& defVal, AbstractExtractor::Ptr pExt)
				/// obj will contain the result, defVal contains values we should use when one column is NULL
			{
				std::cout<<"extract................."<<std::endl;
				poco_assert_dbg (!pExt.isNull());

				TypeHandler<int>::extract(pos++, obj.id, defVal.id, pExt);
				TypeHandler<int>::extract(pos++, obj.catagory_id, defVal.catagory_id, pExt);
				TypeHandler<int>::extract(pos++, obj.speed, defVal.speed, pExt);
				TypeHandler<double>::extract(pos++, obj.power, defVal.power, pExt);
				TypeHandler<double>::extract(pos++, obj.maxQ, defVal.maxQ, pExt);
				TypeHandler<int>::extract(pos++, obj.maxP, defVal.maxP, pExt);
				TypeHandler<int>::extract(pos++, obj.absP, defVal.absP, pExt);
			}

		private:
			TypeHandler();
			~TypeHandler();
			TypeHandler(const TypeHandler&);
			TypeHandler& operator=(const TypeHandler&);
		};
	} 
} // namespace Poco::Data

struct DBHelperImpl
{
	DBHelperImpl(const std::string& connector, const std::string& connectionString) 
		: session(connector, connectionString) {}
	Session session;
};

//简化写法
#define SESSION d->session

DBHelper::DBHelper(const std::string& connector, const std::string& connectionString)
{
	InitDbSystem();
	d = new DBHelperImpl(connector, connectionString);
}

DBHelper::~DBHelper()
{
	delete d; d = 0;
	ShutDownDbSystem();
}

bool DBHelper::createPumpTypeTable()
{
	bool ret = true;
	try
	{
		// drop sample table, if it exists
		SESSION << "drop table if exists TypeTable", now;

		// (re)create table
		SESSION << "create table TypeTable ([id] INTEGER PRIMARY KEY AUTOINCREMENT, [type] NVARCHAR(20), [absP] INTEGER, [weight] INTEGER, [length] INTEGER,[weidth] INTEGER,[heigth] INTEGER,[factoryName] NVARCHAR(100))", now;
	}
	catch(DataException& e)
	{
		ret = false;
	}
	return ret;
}

bool DBHelper::insertPumpType(const PumpType& pump_)
{
	bool ret = true;
	try
	{
		//去掉const修饰，否则use会报错
		PumpType& pump = const_cast<PumpType&>(pump_);
		Statement insert(SESSION);
		insert << "insert info TypeTable values(?, ?, ?, ?, ?, ?, ?, ?)", use(pump), now;
	}
	catch(DataException& e)
	{
		ret = false;
	}
	return ret;
}

bool DBHelper::getPumpTypeTable(PumpTypeTable& tbls)
{
	bool ret = true;
	try
	{
		Statement select(SESSION);
		select << "select * from TypeTable", into(tbls), now;
	}
	catch(DataException& e)
	{
		ret = false;
	}
	return ret;
}

bool DBHelper::insertPumpTypeTable(const PumpTypeTable& tbls)
{
	if(tbls.empty()) return false;

	bool ret = true;
	try
	{
		//去掉const修饰，否则use会报错
		PumpTypeTable& pump_tables = const_cast<PumpTypeTable&>(tbls);

		Statement insert(SESSION);
		insert << "insert into TypeTable values(?, ?, ?, ?, ?, ?, ?, ?)", use(pump_tables), now;
	}
	catch(DataException& e)
	{
		ret = false;
	}
	return ret;
}

bool DBHelper::createPumpPropertyTable()
{
	bool ret = true;
	try
	{
		// drop sample table, if it exists
		SESSION << "drop table if exists PropertyTable", now;

		// (re)create table
		SESSION << "create table PropertyTable ([id] INTEGER PRIMARY KEY AUTOINCREMENT, [catagory_id] INTEGER REFERENCES [Category]([id]), [speed] INTEGER, [power] REAL, [maxQ] REAL,[maxP] INTEGER, [absP] INTEGER)", now;
	}
	catch(DataException& e)
	{
		ret = false;
	}
	return ret;
}

bool DBHelper::insertPumpProperty(const PumpProperty& pump_)
{
	bool ret = true;
	try
	{
		//去掉const修饰，否则use会报错
		PumpProperty& pump = const_cast<PumpProperty&>(pump_);
		Statement insert(SESSION);
		insert << "insert into PropertyTable values(?, ?, ?, ?, ?, ?, ?)", use(pump), now;
	}
	catch(DataException& e)
	{
		ret = false;
	}
	return ret;
}

bool DBHelper::insertPumpPropertyTable(const PumpPropertyTable& tbls)
{
	if(tbls.empty()) return false;

	bool ret = true;
	try
	{
		//去掉const修饰，否则use会报错
		PumpPropertyTable& pump_tables = const_cast<PumpPropertyTable&>(tbls);

		Statement insert(SESSION);
		insert << "insert into PropertyTable values(?, ?, ?, ?, ?, ?, ?)", use(pump_tables), now;
	}
	catch(DataException& e)
	{
		ret = false;
	}
	return ret;
}

bool DBHelper::getPumpPropertyTable(PumpPropertyTable& tbls)
{
	bool ret = true;
	try
	{
		Statement select(SESSION);
		select << "select * from PropertyTable", into(tbls), now;
	}
	catch(DataException& e)
	{
		ret = false;
	}
	return ret;
}
