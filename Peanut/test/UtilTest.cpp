/*
* Author: wbq813 2018/3/20
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn 
*/

#include "gtest/gtest.h"
#include "../cn.codeyourlife.peanut/Util/Hash.h"

TEST(UtilTest, hash)
{
    StringHash stringHash;

    stringHash.Hash("micle", "miclewang@outlook.com");
    stringHash.Hash("nana", "2743587185@qq.com");

//    std::cout<<"\n"<< stringHash.Hashed("wbq813");
//    std::cout<< "\n"<< stringHash.Hashed("nana");
    ASSERT_TRUE(stringHash.Hashed("micle") != stringHash.Hashed("nana"));
}
