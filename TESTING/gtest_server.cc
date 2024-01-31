#include "gtest/gtest.h"
#include "gtest/gmock.h"
#include "server.h"
#include <iostream>
#include <string>

using namespace std;

TEST(ServerUnit__TEST, ServerUnit__directory_check){
    string s_path = "./googletest/CMakeFiles";
    char * path = (char*)(s_path.c_str());
    EXPECT_EQ(directory_check(path),EXIT_SUCCESS);
    s_path = "./NOTaPATH";
    path = (char*)(s_path.c_str()); 
    EXPECT_EQ(directory_check(path),EXIT_FAILURE);
}

int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}