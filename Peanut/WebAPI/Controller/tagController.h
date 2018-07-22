/**
 * Created by wbq813 on 2018/4/14.
 * Gcc 5.4.0, Ubuntu1604
 * cn.codeyourlife
 * */

#ifndef PEANUT_TAGCONTROLLER_H
#define PEANUT_TAGCONTROLLER_H

#include <iostream>
#include "../../src/Http/IO/ReqInfo.h"

/**
 * @Desc Get all the tags;
 * */
static std::string tags(ReqInfo mnRequest)
{
    // Get connection node;
    std::string query = "SELECT * FROM tags ;";
    // Execute query;
    QueryResult queryResult = _dbPool->executeSql(query);
    _json j_vec(queryResult.getResult());
    return j_vec.dump();
}


#endif //PEANUT_TAGCONTROLLER_H
