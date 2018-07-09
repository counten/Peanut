/*
* Author: micle 2018/3/6
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn 
*/

#include <iostream>

// Inner Project
#include "../../src/Util/StrUtil.h"
#include "../../src/Conf/Defination.h"

using namespace std;


/**
 * @Desc Get all the blog;
 * */
static string login(ReqInfo mnRequest)
{

    QueryResult queryResult;
    if(mnRequest.getContent().length() >0)
    {
        map<string, string> content;
        mnRequest.str2Map(mnRequest.getContent(), content);

        string email = Peanut::getValueMapKey(content, "user_email");
        string password = Peanut::getValueMapKey(content, "user_password");

        string query = "SELECT name,email,git FROM authors WHERE email="
                       + addQuo(email) +" AND passwd=" + addQuo(password) + " LIMIT 1;";
        queryResult = _dbPool->executeSql(query);
    }

    _json j_vec(queryResult.getResult());
    return j_vec.dump();
}
