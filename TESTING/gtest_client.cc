#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#define BUF_SIZE 512
using namespace std;
using namespace testing;

//override
/*
ssize_t send (int __fd, const void *__buf, size_t __n, int __flags){
	return (ssize_t)__n;	
}
ssize_t recv (int __fd, void *__buf, size_t __n, int __flags){
	return (ssize_t)__n;	
}
*/

TEST(ClientUnit__Test, get_cmd_code){

	cmd rst;
	char buf[BUF_SIZE];

	strcpy(buf, "list");
	rst = get_cmd_code(buf);
	EXPECT_EQ(rst, 0);

	strcpy(buf, "get");
	rst = get_cmd_code(buf);
	EXPECT_EQ(rst, 1);

	strcpy(buf, "put");
	rst = get_cmd_code(buf);
	EXPECT_EQ(rst, 2);

	strcpy(buf, "others");
	rst = get_cmd_code(buf);
	EXPECT_EQ(rst, N_cmd);

}

//TEST(ClientUnit__Test, print_usage){	print_usage();	}


#define PARSE_IPPORT (hostip && port_num) 
#define LIST_CASE (ch.command == list)
#define PUTGET_CASE (((ch.command == 1) || (ch.command == 2)) && ((file_path != NULL) && (dest_dir != NULL)))
TEST(ClientUnit__Test, get_option){
	int argc;
	char** argv = new char*[5];
	for(int i = 0; i < 5; i++) argv[i] = new char[20];

	argc = 3;
	strcpy(argv[0], "./fshare");
	strcpy(argv[1], "127.0.0.1:8080");
	strcpy(argv[2], "list");
	get_option(argc, argv); 
	EXPECT_TRUE(PARSE_IPPORT && LIST_CASE);

	argc = 5;
	strcpy(argv[1], "127.0.0.1:8080");
	strcpy(argv[2], "get");
	strcpy(argv[3], "filepath");
	strcpy(argv[4], "dest_dir");
	get_option(argc, argv); 
	EXPECT_TRUE(PARSE_IPPORT && PUTGET_CASE);

	strcpy(argv[1], "127.0.0.1:8080");
	strcpy(argv[2], "put");
	strcpy(argv[3], "filepath");
	strcpy(argv[4], "dest_dir");
	get_option(argc, argv); 
	EXPECT_TRUE(PARSE_IPPORT && PUTGET_CASE);


}

TEST(ClientUnit__Test, parse_directory){
	char toparse[BUF_SIZE];
	strcpy(toparse, "dir/dir/file");
	char* parsed = parse_directory(toparse);
	EXPECT_STREQ(parsed, "dir/dir");
}

/*
//wrapping origin c function mock
class Vclass{
public:
    virtual ~Vclass() {}
	virtual ssize_t send (int __fd, const void *__buf, size_t __n, int __flags){	return send(__fd, __buf, __n, __flags);}
	virtual ssize_t recv (int __fd, void *__buf, size_t __n, int __flags){	return send(__fd, __buf, __n, __flags);}
};

//for mocking
class Mclass : public Vclass  {
public:
	using Vclass::send;
	using Vclass::recv;
	MOCK_METHOD4(send, ssize_t(int __fd, const void *__buf, size_t __n, int __flags));
	MOCK_METHOD4(recv, ssize_t(int __fd, void *__buf, size_t __n, int __flags));
};

//TODO
TEST(ClientUnit__Test, request){

//Mclass mock;

//	EXPECT_CALL(mock, send)
//		.WillOnce(Return(100));
	


}
*/



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
    //  int result = mockB.B(1);
	//recv(1, NULL, 1, 1);
//    go_thread((void *)&hihi);
    delete(mockB);
}


/*
TEST(ClientUnit__Test, receive_list_response){


}


TEST(ClientUnit__Test, make_directory){

	EXPECT_EQ(0, 1);

}



TEST(ClientUnit__Test, receive_get_response){

	EXPECT_EQ(0, 1);

}



TEST(ClientUnit__Test, receive_put_response){

	EXPECT_EQ(0, 1);

}


TEST(ClientUnit__Test, receive_response){

	EXPECT_EQ(0, 1);

}
*/



int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
