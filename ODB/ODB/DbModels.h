#pragma once

#include <string>
#include <odb/core.hxx>
#include <odb/nullable.hxx>

namespace db
{
	PRAGMA_DB(object table("customers"))
	struct customer
	{
		customer() : id(0) { }
		customer(const std::string& name) : id(0), name(name) { }

		PRAGMA_DB(id auto)
		const __int64 id;

		std::string name;
	};

	PRAGMA_DB(object table("products"))
	struct product
	{
		product() : id(0) { }
		product(const std::string& name) : id(0), name(name) { }

		PRAGMA_DB(id auto)
		const __int64 id;

		std::string name;
	};

	PRAGMA_DB(object table("orders"))
	struct order
	{
		order(): id(0), product_id(0), customer_id(0), date() { }
		order(const customer& c, const product& p, double sum) : id(0), customer_id(c.id), product_id(p.id), sum(sum), date() {}

		PRAGMA_DB(id auto)
		const __int64 id;

		__int64 customer_id;
		__int64 product_id;
		double sum;

		PRAGMA_DB(type("timestamp") readonly default("CURRENT_TIMESTAMP"))
		const time_t date;
	};



	#pragma db view object(order) object(customer inner: order::customer_id == customer::id) object(product inner: order::product_id == product::id)
	struct customer_order
	{
		#pragma db column(order::id)
		__int64 id;

		#pragma db column(customer::name)
		std::string customer_name;

		#pragma db column(product::name)
		std::string product_name;

		double sum;
		time_t date;
	};

}
