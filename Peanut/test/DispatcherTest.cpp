/*
* Author: wbq813 2018/01/12
* Env: ubuntu 1604, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#include "gtest/gtest.h"

// Inner Project
#include "../cn.codeyourlife.peanut/Database/Pool.h"
#include "../cn.codeyourlife.peanut/Conf/Conf.h"
#include "../cn.codeyourlife.peanut/Http/IO/ReqInfo.h"
#include "../WebAPI/RootersMap.h"


GTEST_API_ int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
    registerController();
    return RUN_ALL_TESTS();
}

Pool *_dbPool;


/**
 * @Desc Test if the class works;
 *
 * */
TEST(mnRequsetTest, c2)
{
    std::string demoUrl = "https://hm.baidu.com/hm.gif?cc=0&ck=1&cl=24-bit&ds=1600x900&vl=285"
            "&et=0&ja=0&ln=en-us&lo=0&lt=1516265317&rnd=1674414728&si=213eace820840c41fc55daed82e834e6"
            "&v=1.2.27&lv=3&ct=!!&tt=CodeYourLife(IT技术博客)&sn=47557";
    Request mnRequest("172.18.5.102", demoUrl);
    std::map <std::string, std::string> resutlMap = mnRequest.getUrlParams();
    EXPECT_EQ(17, resutlMap.size());
}