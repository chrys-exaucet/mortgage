cmake_minimum_required(VERSION 3.13)
project(mortgage C)
set(CMAKE_C_STANDARD 99)

add_executable(mortgage boot/src/main.c )
add_executable(mortgage core/address/address.h)
add_executable(mortgage core/client/client.c core/client/client.h)
add_executable(mortgage core/constants/constants.h utils/strings/stringUtils.c core/good/good.h core/credit/credit.c core/credit/credit.h)
add_executable(mortgage infra/io/parser.csv/csv.c infra/io/parser.csv/csv.h infra/io/crud/client_crud.c infra/io/crud/client_crud.h infra/io/crud/credit_crud.c infra/io/crud/credit_crud.h utils/file/file_utils.c utils/file/file_utils.h utils/strings/stringUtils.h cli/menu/menu.c cli/menu/menu.h utils/time/time_utils.c utils/time/time_utils.h)