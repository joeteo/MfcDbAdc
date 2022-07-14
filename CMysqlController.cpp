#include "pch.h"
#include "CMysqlController.h"

CMysqlController::CMysqlController()
{
	
}
CMysqlController::~CMysqlController()
{
	
}

bool CMysqlController::SelectQuery(char* sql, vector<DataRow*>& row)
{
	MYSQL* connection = NULL, conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	int query_stat;
	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS,
		DB_NAME, 3306, (char*) NULL, 0);

	mysql_query(connection, "set session character_set_connection=euckr;");
	mysql_query(connection, "set session character_set_results=euckr;");
	mysql_query(connection, "set session character_set_client=euckr;");

	if(connect == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return false;
	}
	query_stat = mysql_query(connection, sql);

	if(query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return false;
	}
		

	sql_result = mysql_store_result(connection);
	while((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{
		row.push_back(new DataRow(sql_row[0], sql_row[1],	sql_row[2]));

	}
	mysql_free_result(sql_result);

	mysql_close(connection);

	return true;

}

bool CMysqlController::SelectCountQuery(char* sql, unsigned long long& count)
{
	MYSQL* connection = NULL, conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	int query_stat;
	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS,
		DB_NAME, 3306, (char*)NULL, 0);

	mysql_query(connection, "set session character_set_connection=euckr;");
	mysql_query(connection, "set session character_set_results=euckr;");
	mysql_query(connection, "set session character_set_client=euckr;");

	if (connect == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return false;
	}
	query_stat = mysql_query(connection, sql);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return false;
	}


	sql_result = mysql_store_result(connection);
	sql_row = mysql_fetch_row(sql_result);

	count = atoi(sql_row[0]);

	mysql_free_result(sql_result);

	mysql_close(connection);

	return true;

}


bool CMysqlController::InsertQuery(char* sql)
{
	MYSQL* connection = NULL, conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	int query_stat;
	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS,
		DB_NAME, 3306, (char*)NULL, 0);
	mysql_query(connection, "set session character_set_connection=euckr;");
	mysql_query(connection, "set session character_set_results=euckr;");
	mysql_query(connection, "set session character_set_client=euckr;");

	if(connect == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return false;
			}

	query_stat = mysql_query(connection, sql);

	if(query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return false;
	}

	return true;

}

bool CMysqlController::InsertQuerys(vector<CString>& querys)
{
	MYSQL* connection = NULL, conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	int query_stat;
	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS,
		DB_NAME, 3306, (char*)NULL, 0);
	mysql_query(connection, "set session character_set_connection=euckr;");
	mysql_query(connection, "set session character_set_results=euckr;");
	mysql_query(connection, "set session character_set_client=euckr;");

	if (connect == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return false;
	}


	for(int i=0; i< querys.size();i++)
	{
		query_stat = mysql_query(connection, querys.at(i));

		if (query_stat != 0)
		{
			fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
			return false;
		}
	}
	querys.clear();

	return true;
}