#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#define BUF_SIZE 512
using namespace testing;
using ::testing::Return;
using ::testing::SetArgReferee;
using ::testing::_;

//override
ssize_t send (int __fd, const void *__buf, size_t __n, int __flags){
	return (ssize_t)__n;	
}
ssize_t recv (int __fd, void *__buf, size_t __n, int __flags){
	return (ssize_t)__n;	
}

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
class Vclass {
    public:
        virtual ~Vclass() {}
        virtual ssize_t send(int sockfd, const void* buf,  size_t len, int flags) = 0;
        virtual ssize_t recv(int sockfd, void* buf,  size_t len, int flags) = 0;
};

class Mclass: public Vclass{
    using Vclass::send;
    using Vclass::recv;
  public:
  	MOCK_METHOD(ssize_t, send ,(int sockfd, const void* buf,  size_t len, int flags),(override));
    MOCK_METHOD(ssize_t, recv,(int sockfd, void* buf,  size_t len, int flags),(override));
};
*/


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

Mclass mock;

//	EXPECT_CALL(mock, send)
//		.WillOnce(Return(100));
	
	send(1, NULL, 1, 1);

/*
	int rst = vc.send(1, NULL, 1, 1);
	printf("%d\n", rst);

	int fd[2];
	char buf[BUF_SIZE];
	if(pipe(fd) == -1) perror("pipe");


	ch.command = list;
	request(fd[1]);
	recv(fd[0], buf, 10, 0);
	printf("	#%s\n", buf);

	ch.command = get;
	request(fd[1]);
	ch.command = put;
	request(fd[1]);
*/

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
