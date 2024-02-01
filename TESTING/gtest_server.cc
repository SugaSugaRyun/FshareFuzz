#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "server.h"
#include <iostream>
#include <string>

using namespace std;
using namespace testing;


class goat{
public:
    virtual void * go_threadWrapper(void * arg) {
        return go_thread(arg);
    }

    virtual ssize_t recvWrapper(int __fd, void *__buf, size_t __n, int __flags) {
        return recv(__fd, __buf, __n, __flags);
    }
};

class MockGoat : public goat {
public:
    MOCK_METHOD(void *, go_threadWrapper, (void * arg), (override));
    MOCK_METHOD(ssize_t, recvWrapper, (int, void *, size_t, int), (override));
};

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

// #include "gmock/gmock.h"


// class SimpleClass {

// public:
//     virtual int simpleFirstFunction(int a, int b) { return (a + simpleSecondFunction(b)); }
//     virtual int simpleSecondFunction(int b) { return (2 * b); }
//     // virtual ~SimpleClass();
// };


// class MockSimpleClass : public SimpleClass {
// public:
//     // MOCK_METHOD1(int, simpleSecondFunction, (int b), (override));
//     MOCK_METHOD2(simpleFirstFunction, int(int a, int b));
// };

// TEST(ServerUnit__TEST, ServerUnit__directory_check){
//     MockSimpleClass mymock;
//     // EXPECT_CALL(mymock, simpleFirstFunction(_,_)).WillOnce(Return(100));
//     // int result = mymock.simpleFirstFunction(2,1);
//     SimpleClass a;
//     int result = a.simpleFirstFunction(2,1);
//     EXPECT_EQ(result, 4);
// }

// int main(int argc, char *argv[]){
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }