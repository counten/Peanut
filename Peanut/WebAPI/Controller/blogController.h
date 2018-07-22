/*
* Author: micle 2018/01/18
* Env: ubuntu 1604, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#include <iostream>
#include "../../src/Database/QueryResult.h"
#include "../../src/Database/Pool.h"
#include "../../src/Conf/Defination.h"
#include "../../src/Database/Transaction.h"
#include "../../src/Util/TimeUtil.h"
#include "../../src/Util/StrUtil.h"

using namespace Peanut;
using namespace std;
/**
 * @Desc Get all the blog;
 * */
static string queryBlogs(ReqInfo mnRequest)
{
    string query = "SELECT * FROM blogs";
    string tag_id = mnRequest.getUrlParam("tagId");
    string detail_id = mnRequest.getUrlParam("detail_id");
    if(tag_id!= "")
    { // query by tag_id
        query = query + " WHERE tag_id = " + addQuo(tag_id);
    }
    else if(detail_id!= "")
    { // query by id
        query = query + " WHERE detail_id = " + addQuo(detail_id);
    }
    query += +" ORDER BY update_time DESC;";
    QueryResult queryResult = _dbPool->executeSql(query.c_str());

    _json j_vec(queryResult.getResult());
    return j_vec.dump();
}


/**
 * @Desc Get all the blog belong to user;
 * */
static string blogsBelongUser(ReqInfo mnRequest)
{
    string query = "SELECT id, title, create_time, update_time, author_name, detail_id FROM blogs";
    string uName = mnRequest.getUrlParam("uName");
    if(uName!= "")
    {
        query = query + " WHERE author_name = " + addQuo(uName);
    }
    query += +" ORDER BY update_time DESC;";
    QueryResult queryResult = _dbPool->executeSql(query.c_str());

    _json j_vec(queryResult.getResult());
    return j_vec.dump();
}

/**
 * @Desc Get blog detail map to id;
 * */
static string blogDetail(ReqInfo mnRequest)
{
    // Get connection node;
    string query = "SELECT * FROM details WHERE id = "
                        + addQuo(mnRequest.getUrlParam("id")) + ";";
    // Execute query;
    QueryResult queryResult = _dbPool->executeSql(query.c_str());
    _json j_vec(queryResult.getResult());
    return j_vec.dump();
}

/**
 * @Desc Create new blog;
 * */
static string newBlog(ReqInfo mnRequest)
{
    /**
     * 1. 生成detial_id，插入detial；
     * 2. 查询是否有这个tag，
     * 3. 有则取得id，没有则生成tag_id;
     * 4. 查询用户；
     * 5. 插入blog；
     *
     * 实现transaction 维护事物的原子性。
     * */
    string contentStr = mnRequest.getContent();
//    logInfo(contentStr);
    unsigned long cLoc = contentStr.find("&content=");
    string detail = contentStr.substr(cLoc + 9);
    map<string, string> content;
    mnRequest.str2Map(contentStr.substr(0, cLoc), content);

    string email = getValueMapKey(content, "user_email");
    string title = getValueMapKey(content, "title");
    string desc = getValueMapKey(content, "desc");
    string tags = getValueMapKey(content, "tags");

    // db transaction；
    Transaction trans;
    // insert detail;
    string detail_id = "detial"+getTimestamps();
    trans.execUpdate("INSERT INTO details VALUES(" + addQuo(detail_id) + ", " + addQuo(detail)+");");

    // check if tag aready in db;
    QueryResult tagsDb = trans.execQuery(
            "SELECT * FROM tags WHERE UPPER(name) = " + addQuo(str2UpperCase(tags)) +" LIMIT 1;");
    string tag_id = "";
    if(tagsDb.getRowCount() > 0)
    {
        tag_id = tagsDb.getElement(0,0);
        trans.execUpdate("UPDATE tags SET blog_num = blog_num + 1 WHERE id = "+ addQuo(tag_id) +";");
    }
    else
    {
        tag_id = "tag"+getTimestamps();
        trans.execUpdate("INSERT INTO tags VALUES(" + addQuo(tag_id) + ", " + addQuo(tags)+", 1 );");
    }


    // getUserInfo
    QueryResult userInfo = trans.execQuery(
            "SELECT id, name FROM authors WHERE email= " + addQuo(email)+" limit 1;");

    string blog_id = "blog"+getTimestamps();

    trans.execUpdate("INSERT INTO blogs VALUES("
                     + addQuo(blog_id) +", "
                     + addQuo(title)+", "
                     + addQuo(desc) +", "
                     + addQuo(getTimestamps())+", "
                     + addQuo(getTimestamps())+", "
                     + addQuo(userInfo.getElement(0, 0))+", "
                     + addQuo(userInfo.getElement(0, 1))+", "
                     + addQuo(tag_id)+", "
                     + addQuo(tags)+", "
                     + addQuo(detail_id)+");");
    trans.commit();
    return "true";
}

/**
 * @Desc Update blog;
 * */
 static string updateBlog(ReqInfo mnRequest)
{
    string contentStr = mnRequest.getContent();
    unsigned long cLoc = contentStr.find("&content=");
    string detail = contentStr.substr(cLoc + 9);
    map<string, string> content;
    mnRequest.str2Map(contentStr.substr(0, cLoc), content);

    string title = getValueMapKey(content, "title");
    string desc = getValueMapKey(content, "desc");
    string tags = getValueMapKey(content, "tags");
    string detail_id = getValueMapKey(content, "detail_id");

    // db transaction；
    Transaction trans;
    // update detail;
    trans.execUpdate("UPDATE details SET detail=" + addQuo(detail) + " WHERE id=" + addQuo(detail_id));

    // check if tag aready in db;
    QueryResult tagsDb = trans.execQuery(
            "SELECT * FROM tags WHERE UPPER(name) = " + addQuo(str2UpperCase(tags)) +" LIMIT 1");
    string tag_id = "";
    if(tagsDb.getRowCount() > 0)
    {
        tag_id = tagsDb.getElement(0,0);
        trans.execUpdate("UPDATE tags SET blog_num = blog_num + 1 WHERE id = "+ addQuo(tag_id));
    }
    else
    {
        tag_id = "tag"+getTimestamps();
        trans.execUpdate("INSERT INTO tags VALUES(" + addQuo(tag_id) + ", " + addQuo(tags)+", 1 )");
    }

    trans.execUpdate("UPDATE blogs SET abstract=" + addQuo(desc)
                     + ", tag_id=" + addQuo(tag_id)
                     + ", tag_name=" + addQuo(tags)
                     + ", title=" +addQuo(title)
                     + " WHERE detail_id=" + addQuo(detail_id));
    trans.commit();
    return "true";
}