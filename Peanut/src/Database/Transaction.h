//
// Created by wbq813 on 2018/3/27.
//

#ifndef PEANUT_TRANSACTION_H
#define PEANUT_TRANSACTION_H

#include <mysql.h>
#include "../Conf/Defination.h"

class Transaction
{
private:
    bool _isContinue;

    MYSQL * _conn;

public:
    Transaction()
    {
        _isContinue = true;
        _conn = _dbPool->getOneConnect();
        mysql_query(_conn,"START TRANSACTION");
    }

    /**
     * @Desc Use transaction to query;
     * */
    QueryResult execQuery(std::string sql)
    {
        Peanut::logInfo(sql.c_str());
        QueryResult queryResult;

        if (mysql_query(_conn, sql.c_str()) == 0)
        {
            MYSQL_RES *res = mysql_store_result(_conn);
            // Store result;
            while (true)
            {
                MYSQL_ROW row;
                if (!(row = mysql_fetch_row(res)))
                {
                    break;
                }
                std::vector<std::string> string_row;
                for (int i = 0; i < mysql_num_fields(res); i++)
                {
                    string_row.push_back(row[i]);
                }
                queryResult.addRow(string_row);
            }
            mysql_free_result(res);
            Peanut::logSuccess("Query OK! ");
        }
        else
        {
            _isContinue = false;
            Peanut::logError(mysql_error(_conn));
        }
        return queryResult;
    }

    /**
 * @Desc Use transaction to query;
 * */
    bool execUpdate(std::string sql)
    {
        Peanut::logInfo(sql.c_str());

        if (mysql_query(_conn, sql.c_str()) == 0)
        {
            Peanut::logSuccess("Query OK! ");
            return true;
        }
        else
        {
            _isContinue = false;
            Peanut::logError(mysql_error(_conn));
            return false;
        }
    }

    /**
     * @Desc commit transaction;
     * */
    bool commit()
    {
        bool result = true;
        if (!_isContinue)
        {
            mysql_query(_conn,"ROLLBACK");
            result = false;
        }
        else
        {
            if (!(mysql_query(_conn,"COMMIT")))
            {
                mysql_query(_conn,"ROLLBACK");
                result = true;
            }
        }
        _dbPool->close(_conn);
        return result;
    }
};

#endif //PEANUT_TRANSACTION_H
