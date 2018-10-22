#pragma once

#include "DbModels.h"

class DbContext;


class ProductManager
{
public:
	ProductManager(DbContext& db);

private:
	DbContext& m_db;
	std::vector<db::product> m_products;
};
