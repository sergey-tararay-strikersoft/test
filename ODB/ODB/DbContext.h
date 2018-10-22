#pragma once

#include <odb/database.hxx>
#include <odb/pgsql/database.hxx>

class DbContext
{
public:
	DbContext(const std::string& connectionString);
private:
	odb::pgsql::database m_db;
};