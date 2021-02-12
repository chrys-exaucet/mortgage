# cmake_minimum_required(VERSION <specify CMake version here>)
project(mortgage C)

set(CMAKE_C_STANDARD 99)

add_executable(mortgage boot/src/main.c )
add_executable(mortgage core/address/address.h)
add_executable(mortgage core/client/client.c core/client/client.h)
add_executable(mortgage core/constants/constants.h utils/stringUtils.c core/good/good.h core/credit/credit.c core/credit/credit.h)
add_executable(mortgage infra/io/parser.csv/csv.c infra/io/parser.csv/csv.h infra/io/crud/client_crud.c infra/io/crud/client_crud.h infra/io/crud/credit_crud.c infra/io/crud/credit_crud.h utils/file_utils.c utils/file_utils.h utils/stringUtils.h cli/menu.c cli/menu.h)