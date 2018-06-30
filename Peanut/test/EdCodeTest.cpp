/*
* Author: micle 2018/3/7
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn 
*/


#include "gtest/gtest.h"

// Inner Project
#include "../cn.codeyourlife.peanut/Util/EdCode.h"

TEST(EdCodeTest, ed1)
{
    std::string in = "SELECT name,email,git FROM authors WHERE email='miclewang%40outlook.com' AND passwd='123456' LIMIT 1;";
    std::string res = "SELECT name,email,git FROM authors WHERE email='miclewang@outlook.com' AND passwd='123456' LIMIT 1;";
    std::string out = Peanut::UrlDecode(in);
//    std::cout << out;
    ASSERT_EQ(res, out);
}
