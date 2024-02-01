#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "server.h"
#include <iostream>
#include <string>

using namespace std;
using namespace testing;


class SockInterface {
public:
    ~SockInterface() {}
    virtual ssize_t recv(int __fd, void *__buf, size_t __n, int __flags){
        return 0;
    }
};

class SockMock : public SockInterface{
public:
    MOCK_METHOD(ssize_t, recv, (int,void*,size_t,int));
};


SockMock *sockmock;  // B 함수의 mock 객체 생성
ssize_t recv(int __fd, void *__buf, size_t __n, int __flags){
    return sockmock->recv(__fd, __buf, __n, __flags);
}

TEST(ServerUnit__TEST, ServerUnit__directory_check){
    string s_path = "./googletest/CMakeFiles";
    char * path = (char*)(s_path.c_str());
    EXPECT_EQ(directory_check(path),EXIT_SUCCESS);
    s_path = "./NOTaPATH";
    path = (char*)(s_path.c_str()); 
    EXPECT_EQ(directory_check(path),EXIT_FAILURE);
}

TEST(ServerUnit__TEST, ServerUnit__goThread){
    sockmock = new SockMock();
    EXPECT_CALL(*sockmock,recv).WillOnce(Return(sizeof(ch)));
    int hihi = 0;
    // int result = mockB.B(1);
    go_thread((void *)&hihi);
    delete(sockmock);
}

int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}