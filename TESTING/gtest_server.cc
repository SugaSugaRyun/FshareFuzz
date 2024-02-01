#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "server.h"
#include <iostream>
#include <string>

using namespace std;
using namespace testing;


// class goat{
// public:
//     virtual void * go_threadWrapper(void * arg) {
//         return go_thread(arg);
//     }

//     virtual ssize_t recvWrapper(int __fd, void *__buf, size_t __n, int __flags) {
//         return recv(__fd, __buf, __n, __flags);
//     }
// };

// class MockGoat : public goat {
// public:
//     // MOCK_METHOD(void *, go_threadWrapper, (void * arg), (override));
//     MOCK_METHOD(ssize_t, recvWrapper, (int, void *, size_t, int), (override));
// };

// TEST(ServerUnit__TEST, ServerUnit__directory_check){
//     string s_path = "./googletest/CMakeFiles";
//     char * path = (char*)(s_path.c_str());
//     EXPECT_EQ(directory_check(path),EXIT_SUCCESS);
//     s_path = "./NOTaPATH";
//     path = (char*)(s_path.c_str()); 
//     EXPECT_EQ(directory_check(path),EXIT_FAILURE);
// }

// TEST(ServerUnit__TEST, ServerUnit__goThread){
//     MockGoat gtmock;
//     EXPECT_CALL(gtmock, recvWrapper(_,_,_,_)).WillOnce(Return(sizeof(ch)));
//     // ON_CALL(gtmock, recvWrapper(_,_,_,_));
//     // EXPECT_CALL(gtmock, go_threadWrapper(_));
//     char * a = (char*)malloc(10);
//     // go_thread(a);
//     // gtmock.go_threadWrapper();
//     // void *b = gtmock.go_threadWrapper(a);
//     goat gt;
//     gt.go_threadWrapper(a);
// }

// int main(int argc, char *argv[]){
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }

using ThreadFunctionPointer = void *(*)(void *);


class aaA {
public:
    ~aaA() {}
    virtual ssize_t recv(int __fd, void *__buf, size_t __n, int __flags){
        return 0;
    }
};

class MockB : public aaA{
public:
    MOCK_METHOD(ssize_t, recv, (int,void*,size_t,int));
};


MockB *mockB;  // B 함수의 mock 객체 생성
ssize_t recv(int __fd, void *__buf, size_t __n, int __flags){
    return mockB->recv(__fd, __buf, __n, __flags);
}

TEST(MyTest, TestAWithMockB) {
    mockB = new MockB();
    EXPECT_CALL(*mockB,recv).WillOnce(Return(sizeof(ch)));
    int hihi = 0;
    // int result = mockB.B(1);
    go_thread((void *)&hihi);
    delete(mockB);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
