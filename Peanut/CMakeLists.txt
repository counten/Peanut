cmake_minimum_required(VERSION 3.4)
set(PROJ_NAME Peanut)
project(${PROJ_NAME})
set(CMAKE_CXX_STANDARD 11)


# module source file ***********************************************
set(PEANUT src)

set(MODULE_CONF
        ${PEANUT}/Conf/Conf.h
        ${PEANUT}/Conf/Conf.cpp
        ${PEANUT}/Conf/Defination.h
        )

set(MODULE_UTIL
        ${PEANUT}/Util/StrUtil.h
        ${PEANUT}/Util/StrUtil.cpp
        ${PEANUT}/Util/TimeUtil.h

        ${PEANUT}/Util/EdCode.h
        ${PEANUT}/Util/EdCode.cpp
        ${PEANUT}/Util/Json.hpp
        ${PEANUT}/Util/Hash.h
        ${PEANUT}/Util/Hash.cpp
        ${PEANUT}/Util/Session.h)

set(MODULE_HTTP
        ${PEANUT}/Http/HttpHandle.h
        ${PEANUT}/Http/HttpHandle.cpp
        ${PEANUT}/Http/HttpReq.h
        ${PEANUT}/Http/HttpReq.cpp
        ${PEANUT}/Http/IO/Buffer.h
        ${PEANUT}/Http/IO/Buffer.cpp
        ${PEANUT}/Http/IO/Cache.h
        ${PEANUT}/Http/IO/ReqInfo.h
        ${PEANUT}/Http/IO/ReqInfo.cpp
        ${PEANUT}/Http/Tcp.h
        ${PEANUT}/Http/Tcp.cpp)

set(MODULE_DATABASE
        ${PEANUT}/Database/Pool.h
        ${PEANUT}/Database/Pool.cpp
        ${PEANUT}/Database/QueryResult.h
        ${PEANUT}/Database/QueryResult.cpp
        ${PEANUT}/Database/Transaction.h)

set(MODULE_lOG
        ${PEANUT}/Log/Log.h)

set(MODULE_WEBAPI
        WebAPI/RootersMap.h
        WebAPI/Controller/blogController.h
        WebAPI/Controller/userController.h
        WebAPI/Controller/tagController.h
        WebAPI/Controller/archiveController.h)

set(MODULE_BIN
        ${PEANUT}/Bin/EPollUtil.cpp
        ${PEANUT}/Bin/EPollUtil.h
        ${PEANUT}/Bin/ThreadPool.cpp
        ${PEANUT}/Bin/ThreadPool.h
        ${PEANUT}/Bin/Peanut.h
        ${PEANUT}/Bin/Peanut.cpp)

set(MODULE_TEST
        test/DatabaseTest.cpp
        test/DispatcherTest.cpp
        test/EdCodeTest.cpp
        test/UtilTest.cpp)


# **********************************************************************
set(mysqlclientDir Lib/mysql-connector)
include_directories(${mysqlclientDir}/include)
link_directories(${mysqlclientDir}/lib)
link_libraries(mysqlclient)

if (release)
    message("Release mode running")

    add_executable(
            ${PROJ_NAME}
            main.cpp
            ${MODULE_CONF}
            ${MODULE_HTTP}
            ${MODULE_UTIL}
            ${MODULE_DATABASE}
            ${MODULE_lOG}
            ${MODULE_BIN}
            ${MODULE_WEBAPI}
    )
else()
    message("Test mode running")

    #Add the google test subdirectory

#    set(googleTestDir Lib/googletest)
#    add_subdirectory(${googleTestDir})
#    include_directories(${googleTestDir}/googletest/include)
#    include_directories(${googleTestDir}/googlemock/include)

    add_executable(
            ${PROJ_NAME}
            ${MODULE_CONF}
            ${MODULE_HTTP}
            ${MODULE_UTIL}
            ${MODULE_DATABASE}
            ${MODULE_lOG}
            ${MODULE_BIN}
            ${MODULE_WEBAPI}
            main.cpp
#            ${MODULE_TEST}
    )

#    target_link_libraries(${PROJ_NAME} gtest gtest_main)
#    target_link_libraries(${PROJ_NAME} gmock gmock_main)

endif (release)

# Link liberary *********************************************************
target_link_libraries(${PROJ_NAME} pthread)
target_link_libraries(${PROJ_NAME} mysqlclient)
