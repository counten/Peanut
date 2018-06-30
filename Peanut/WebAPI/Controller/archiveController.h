/**
 * Created by micle on 2018/4/17.
 * Gcc 5.4.0, Ubuntu1604
 * cn.codeyourlife
 * */

#ifndef PEANUT_ARCHIVECONTROLLER_H
#define PEANUT_ARCHIVECONTROLLER_H

#include <iostream>
#include "../../cn.codeyourlife.peanut/Http/IO/ReqInfo.h"
#include "../../cn.codeyourlife.peanut/Database/QueryResult.h"
#include "../../cn.codeyourlife.peanut/Conf/Defination.h"

static std::string archive(ReqInfo mnRequest)
{
    std::string query = "SELECT title, create_time, detail_id FROM blogs ORDER BY create_time DESC;";
    QueryResult queryResult = _dbPool->executeSql(query);
    _json j_vec(queryResult.getResult());
    return j_vec.dump();
}

#endif //PEANUT_ARCHIVECONTROLLER_H
