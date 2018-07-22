/*
* Author: micle 2018/01/12
* Env: ubuntu 1604, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/


#ifndef MNSERVER_MNBASE_H
#define MNSERVER_MNBASE_H

#include <iostream>
#include <map>

// Inner Project
#include "Controller/blogController.h"
#include "Controller/userController.h"
#include "Controller/tagController.h"
#include "Controller/archiveController.h"

std::map<std::string, pController> _controllerMap;

// Register URL here !
static const void registerController()
{
    // blog related API
    _controllerMap["/blogs"] = &queryBlogs;
    _controllerMap["/blogsBelongUser"] = &blogsBelongUser;
    _controllerMap["/detail"] = &blogDetail;
    _controllerMap["/newBlog"] = &newBlog;
    _controllerMap["/updateBlog"] = &updateBlog;

    // tags related API
    _controllerMap["/tags"] = &tags;

    // archive related API
    _controllerMap["/archive"] = &archive;

    // User related API
    _controllerMap["/login"] = &login;
}

#endif //MNSERVER_MNBASE_H
