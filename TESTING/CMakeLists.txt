#초기 설정, cmake버전, 프로잭트 이름, 언어 스탠다드 버전
cmake_minimum_required(VERSION 3.18.2)
project(FshareFuzz)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

# coverage 측정
# add_compile_options(-g -O0 --coverage)
set(CMAKE_C_FLAGS "-g -O0 --coverage")
link_libraries(gcov)

# 라이브러리 파일들 static빌드
set(LIB_DIR LIBS)
include_directories(${LIB_DIR})
add_library(server STATIC ${LIB_DIR}/server.c ${LIB_DIR}/server.h)
add_library(client STATIC ${LIB_DIR}/client.c ${LIB_DIR}/client.h)

# 원본 프로그램들 빌드
set(s_target server-test.out)
add_executable(${s_target} fshared_main.c)
target_link_libraries(${s_target} PRIVATE server pthread)
set(c_target client-test.out)
add_executable(${c_target} fshare_main.c)
target_link_libraries(${c_target} PRIVATE client)

# googletest build
set(gtest_SRC_DIR googletest)
add_subdirectory(${gtest_SRC_DIR})
# add_subdirectory(googletest/googlemock)

# UNIT TARGET
include_directories(${gtest_SRC_DIR}/googletest/include)
include_directories(${gtest_SRC_DIR}/googlemock/include)

set(UNIT_TEST_ELF_S unit_test_s.out)
add_executable(${UNIT_TEST_ELF_S} gtest_server.cc)
target_link_libraries(${UNIT_TEST_ELF_S} gtest gtest_main gmock)
# target_include_directories(${UNIT_TEST_ELF_S} PUBLIC ${gtest_SRC_DIR}/googlemock/include)
target_link_libraries(${UNIT_TEST_ELF_S} server)

set(UNIT_TEST_ELF_C unit_test_c.out)
add_executable(${UNIT_TEST_ELF_C} gtest_client.cc)
target_link_libraries(${UNIT_TEST_ELF_C} gtest gtest_main gmock)
target_link_libraries(${UNIT_TEST_ELF_C} gtest gtest_main)
target_link_libraries(${UNIT_TEST_ELF_C} client)




