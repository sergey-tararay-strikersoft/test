#include "stdafx.h"
#include "ProductManager.h"
#include "DbContext.h"

ProductManager::ProductManager(DbContext& db)
	: m_db(db)
{

}
