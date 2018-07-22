/*
* Author: micle 2018/01/18
* Env: ubuntu 1604, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#include <iostream>
#include "../../src/Log/Log.h"
#include "../../src/Http/Dispatcher/MnRequest.h"
#include "../../src/Database/Pool.h"
#include "../../ThirdPar/json.hpp"
using json = nlohmann::json;

/**
 * @Desc Get all the blog;
 * */
static std::string blogsController(MnRequest mnRequest)
{

    std::string query = "select * from blogs;";
    QueryResult queryResult = mnPool->executeSql(query.c_str());

    json j_vec(queryResult.getString_table());
    return j_vec.dump();
}

/**
 * @Desc Get blog detail map to id;
 * */
static std::string detailController(MnRequest mnRequest)
{

    // Get connection node;
    std::string query = "select * from details where id = \"" + mnRequest.getUrlParam("id") + "\";";
    // Execute query;
    QueryResult queryResult = mnPool->executeSql(query.c_str());
    json j_vec(queryResult.getString_table());
    return j_vec.dump();
}