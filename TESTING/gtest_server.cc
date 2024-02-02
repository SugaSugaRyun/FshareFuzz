#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "server.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using namespace testing;


class SockInterface {
public:
    ~SockInterface() {}
    // virtual ssize_t recv(int __fd, void *__buf, size_t __n, int __flags){
    //     return 0;
    // }
    virtual ssize_t recv(int __fd, void *__buf, size_t __n, int __flags) = 0;
    virtual int accept(int __fd, struct sockaddr *__restrict__ __addr, socklen_t *__restrict__ __addr_len) = 0;
    virtual ssize_t send(int __fd, const void *__buf, size_t __n, int __flags) = 0;
};

class SockMock : public SockInterface{
public:
    MOCK_METHOD(ssize_t, recv,  (int,void*,size_t,int),(override));
    MOCK_METHOD(ssize_t, send,  (int,const void*,size_t,int),(override));
    MOCK_METHOD(int,     accept,(int, struct sockaddr*, socklen_t *), (override));
};

SockMock *sockmock;  // B 함수의 mock 객체 생성
ssize_t recv(int __fd, void *__buf, size_t __n, int __flags){
    return sockmock->recv(__fd, __buf, __n, __flags);
}
int accept(int __fd, struct sockaddr *__restrict__ __addr, socklen_t *__restrict__ __addr_len){
    return sockmock->accept(__fd, __addr, __addr_len);
}
ssize_t send(int __fd, const void *__buf, size_t __n, int __flags){
    return sockmock->send(__fd, __buf, __n, __flags);
}

TEST(ServerUnit__TEST, ServerUnit__directory_check){
    string s_path = "./googletest/CMakeFiles";
    char * path = (char*)(s_path.c_str());
    EXPECT_EQ(directory_check(path),EXIT_SUCCESS);
    s_path = "./NOTaPATH";
    path = (char*)(s_path.c_str()); 
    EXPECT_EQ(directory_check(path),EXIT_FAILURE);
}

TEST(ServerUnit__TEST, ServerUnit__getoption){

    int gc = 5;
    char *gv[5];
    gv[0] = (char*)"test";
    gv[1] = (char*)"-p";
    gv[2] = (char*)"9999"; 
    gv[3] = (char*)"-d";
    gv[4] = (char*)"serverCloud";
    FILE* originalStderr = stderr;

    FILE* file = fopen("stderr_output.txt", "w");  
    stderr = file;

    get_option(gc,gv);

    stderr = originalStderr;
    fclose(file);
    ifstream readFile("stderr_output.txt");
    std::string stderrContent((std::istreambuf_iterator<char>(readFile)), std::istreambuf_iterator<char>());
    EXPECT_TRUE(stderrContent.find("\n") == string::npos); // stderr(\n)가 안 나오면 ture
}

TEST(ServerUnit__TEST, ServerUnit__makedirectory){
    FILE* originalStderr = stderr;

    FILE* file = fopen("stderr_output.txt", "w");  
    stderr = file;
    string temp;
    cin >> temp;
    char *path = strdup(temp.c_str());
    make_directory(path);

    char * parse = (char*)"";
    while(strcmp(parse, ".") != 0 && strcmp(parse, "/") != 0){
        parse = dirname(path);
    }
    
    char *command = (char*)malloc(sizeof(char)* (8 + strlen(path)) );
    memset(command, 0, sizeof(char)* (8 + strlen(path)));
    strcat(command, (char*)"rm -rf ");
    strcat(command, path);
    int result = -1;
    if(path[0] != '/'){
        result = std::system(command);
    }
    free(path);
    if (result == 0) {
        std::cout << "Directory removed successfully.\n";
    } else {
        std::cerr << "Error removing directory.\n";
    }

    stderr = originalStderr;
    fclose(file);
    ifstream readFile("stderr_output.txt");
    std::string stderrContent((std::istreambuf_iterator<char>(readFile)), std::istreambuf_iterator<char>());
    EXPECT_TRUE(stderrContent.find("\n") == string::npos); // stderr(\n)가 안 나오면 ture 
}

TEST(ServerUnit__TEST, ServerUnit__listresponse){
    sockmock = new SockMock();
    EXPECT_CALL(*sockmock, send(_, _, _, _))
        .WillRepeatedly(ReturnArg<2>());
    FILE* originalStderr = stderr;

    FILE* file = fopen("stderr_output.txt", "w");  
    stderr = file;
    string temp = "serverCloud";
    char* path = strdup(temp.c_str());
    list_response(path, 0);
    free(path);
    stderr = originalStderr;
    fclose(file);
    ifstream readFile("stderr_output.txt");
    std::string stderrContent((std::istreambuf_iterator<char>(readFile)), std::istreambuf_iterator<char>());
    EXPECT_TRUE(stderrContent.find("\n") == string::npos); // stderr(\n)가 안 나오면 ture    
    delete(sockmock);
}

TEST(ServerUnit__TEST, ServerUnit__getresponse){
    sockmock = new SockMock();
    EXPECT_CALL(*sockmock, send(_, _, _, _))
        .WillRepeatedly(ReturnArg<2>());
    EXPECT_CALL(*sockmock, recv(_,_,_,_))
        .WillOnce(Invoke([](int sockfd, const void *buf, size_t len, int flags) {
      string path = "serverCloud/meow1.txt";
      strncpy((char*)buf, path.c_str(), path.length());
      return path.length();
    }));
    FILE* originalStderr = stderr;

    FILE* file = fopen("stderr_output.txt", "w");  
    stderr = file;
    string temp = "serverCloud";
    char* path = strdup(temp.c_str());

    get_response(0);

    free(path);
    stderr = originalStderr;
    fclose(file);
    ifstream readFile("stderr_output.txt");
    std::string stderrContent((std::istreambuf_iterator<char>(readFile)), std::istreambuf_iterator<char>());
    EXPECT_TRUE(stderrContent.find("\n") == string::npos); // stderr(\n)가 안 나오면 ture    
    delete(sockmock);   
}

// TEST(ServerUnit__TEST, ServerUnit__goThread){
//     sockmock = new SockMock();
//     EXPECT_CALL(*sockmock,recv).WillOnce(Return(sizeof(ch)));
//     int hihi = 0;
//     // int result = mockB.B(1);
//     // go_thread((void *)&hihi);
//     delete(sockmock);
// }


int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}