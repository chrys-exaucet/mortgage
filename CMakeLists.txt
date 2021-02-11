# cmake_minimum_required(VERSION <specify CMake version here>)
project(mortgage C)

set(CMAKE_C_STANDARD 99)

add_executable(mortgage boot/src/main.c )
add_executable(mortgage core/address/address.h)
add_executable(mortgage core/client/client.c core/client/client.h)
add_executable(mortgage core/constants/constants.h utils/stringUtils.c core/good/good.h core/credit/credit.c core/credit/credit.h)