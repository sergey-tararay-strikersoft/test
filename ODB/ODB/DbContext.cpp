#include "stdafx.h"
#include "DbContext.h"

DbContext::DbContext(const std::string& connectionString)
	: m_db(connectionString)
{
}
