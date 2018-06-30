cmake_minimum_required(VERSION 3.4)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/Conf/Conf.h
        src/Conf/Conf.cpp

        src/Log/Log.h
        src/Log/Log.cpp

        src/Http/Tcp.cpp
        src/Http/Tcp.h
        src/Http/IO/HttpRes.cpp
        src/Http/IO/HttpRes.h
        src/Http/IO/HttpReq.cpp
        src/Http/IO/HttpReq.h
        src/Http/Dispatcher/MnRequest.cpp
        src/Http/Dispatcher/MnRequest.h
        src/Http/Dispatcher/Dispatcher.cpp
        src/Http/Dispatcher/Dispatcher.h

        src/Database/QueryResult.h
        src/Database/QueryResult.cpp
        src/Database/Pool.cpp
        src/Database/Pool.h

        src/Util/FileUtil.cpp
        src/Util/FileUtil.h
        src/Util/TimeUtil.cpp
        src/Util/TimeUtil.h
        src/Util/StrUtil.cpp
        src/Util/StrUtil.h
        src/Http/Frame.cpp
        src/Http/Frame.h
        src/Http/ThreadPool.h
        src/Util/EdCode.cpp
        src/Util/EdCode.h
        src/Util/CodeConverter.h

        ThirdPar/json.hpp
        )

set(LOGIC_FILES
        Logic/RootersMap.h
        Logic/RootersMap.cpp
        Logic/Controller/blogController.h
        )

set(mysqlclientDir ThirdPar/mysql-connector)
include_directories(${mysqlclientDir}/include)
link_directories(${mysqlclientDir}/lib)
link_libraries(mysqlclient)

set(MAIN_FILE src/main.cpp)
add_executable(Peanut_protype ${MAIN_FILE} ${SOURCE_FILES} ${LOGIC_FILES})


#target_link_libraries(Peanut mysqlclient)
target_link_libraries(Peanut_protype mysqlclient)
target_link_libraries(Peanut_protype pthread)
