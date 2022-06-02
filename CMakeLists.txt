project(enterdawn_nat_server)
cmake_minimum_required(VERSION 3.16)


set(CMAKE_CXX_STANDARD 17)
LINK_DIRECTORIES(/usr/local/lib)
add_executable(enterdawn_nat_server main.cpp logs/log.cpp logs/log.h tools/currenttime.h conf_reader/confreader.h getconn/getconn.cpp getconn/getconn.h conn/conn.cpp conn/conn.h)
target_link_libraries(${PROJECT_NAME} -lpthread)