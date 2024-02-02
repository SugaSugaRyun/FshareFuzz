#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
using namespace testing;
using ::testing::Return;
using ::testing::NiceMock;
using ::testing::SetArgReferee;
using ::testing::_;

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


NiceMock<Mclass>* mock;


//override
ssize_t send (int __fd, const void *__buf, size_t __n, int __flags){
	return mock->send(__fd, __buf, __n, __flags);
}
ssize_t recv (int __fd, void *__buf, size_t __n, int __flags){
	return mock->recv(__fd, __buf, __n, __flags);
}



TEST(ClientUnit__Test, get_cmd_code){

	cmd rst;
	char buf[buf_size];

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
	char toparse[buf_size];
	strcpy(toparse, "dir/dir/file");
	char* parsed = parse_directory(toparse);
	EXPECT_STREQ(parsed, "dir/dir");
}

TEST(ClientUnit__Test, request){
	mock = new NiceMock<Mclass>();
	char target[buf_size];
	FILE *fp;

	//list
	EXPECT_CALL(*mock, send)
		.WillOnce(Return(sizeof(ch)));

	fp = freopen("stdout_", "w", stdout);
	ch.command = (cmd)0; //list
	request(0);

	freopen("/dev/tty", "w", stdout);
    ifstream readFile("stdout_");
    std::string strList((std::istreambuf_iterator<char>(readFile)), std::istreambuf_iterator<char>());
	strcpy(target, ">> List request completed!\n");
	EXPECT_STREQ(strList.c_str(), target); 

	//get
	EXPECT_CALL(*mock, send)
		.WillOnce(Return(sizeof(ch)))
		.WillOnce(Return(ch.payload_size));

	fp = freopen("stdout_", "w", stdout);
	ch.command = (cmd)1; //get
	request(0);

	freopen("/dev/tty", "w", stdout);
    ifstream readFile2("stdout_");
    std::string strGet((std::istreambuf_iterator<char>(readFile2)), std::istreambuf_iterator<char>());
	strcpy(target, ">> Get request completed!\n");
	EXPECT_STREQ(strGet.c_str(), target); 

	//put
	strcpy(file_path, "clientCloud/hello");
	strcpy(dest_dir, "test");

	EXPECT_CALL(*mock, send)
		.WillOnce(Return(sizeof(ch)))
		.WillOnce(Return(strlen(file_path) + strlen(dest_dir)))
		.WillRepeatedly(Return(1));

	fp = freopen("stdout_", "w", stdout);
	ch.command = (cmd)2; //put
	request(0);

	freopen("/dev/tty", "w", stdout);
    ifstream readFile3("stdout_");
    std::string strPut((std::istreambuf_iterator<char>(readFile3)), std::istreambuf_iterator<char>());
	strcpy(target, ">> Put request completed!\n");
	EXPECT_STREQ(strPut.c_str(), target); 


	delete(mock);
	system("rm stdout_");
}

TEST(ClientUnit__Test, receive_list_response){
	mock = new NiceMock<Mclass>();
	FILE *fp, *tmp;

	//receive error case
	EXPECT_CALL(*mock, recv)
		.WillOnce(Return(1));
	tmp = stderr;
	fp = fopen("stderr_", "w");
	stderr = fp;
	receive_list_response(0);

	stderr = tmp;
	fclose(fp);

    ifstream readFile("stderr_");
    std::string strErr((std::istreambuf_iterator<char>(readFile)), std::istreambuf_iterator<char>());
    EXPECT_TRUE(strErr.find("receive error :") != string::npos);


	//response error case
	sh.is_error = 1;
	EXPECT_CALL(*mock, recv)
		.WillOnce(Return(sizeof(sh)));
	tmp = stderr;
	fp = fopen("stderr_", "w");
	stderr = fp;
	receive_list_response(0);

	stderr = tmp;
	fclose(fp);

    ifstream readFile2("stderr_");
    std::string strErr2((std::istreambuf_iterator<char>(readFile2)), std::istreambuf_iterator<char>());
    EXPECT_TRUE(strErr2.find("response error :") != string::npos);
	sh.is_error = 0;	


	//normal case - recv once
	sh.payload_size = 10;
	EXPECT_CALL(*mock, recv)
		.WillOnce(Return(sizeof(sh)))
		.WillOnce(Return(sh.payload_size))
		.WillOnce(Return(0));

	fp = freopen("stdout_", "w", stdout);
	receive_list_response(0);

	freopen("/dev/tty", "w", stdout);
    ifstream readFile3("stdout_");
    std::string strOut((std::istreambuf_iterator<char>(readFile3)), std::istreambuf_iterator<char>());
    EXPECT_TRUE(strOut.find(">") != string::npos);

	
	//receive error 2 case
	sh.payload_size = 10;
	EXPECT_CALL(*mock, recv)
		.WillOnce(Return(sizeof(sh)))
		.WillOnce(Return(1));

	tmp = stderr;
	fp = fopen("stderr_", "w");
	stderr = fp;
	receive_list_response(0);

	stderr = tmp;
	fclose(fp);

    ifstream readFile4("stderr_");
    std::string strErr3((std::istreambuf_iterator<char>(readFile4)), std::istreambuf_iterator<char>());
    EXPECT_TRUE(strErr3.find("receive error 2 :") != string::npos);


	//normal case - recv multiple time
	sh.payload_size = buf_size + 10;
	EXPECT_CALL(*mock, recv)
		.WillOnce(Return(sizeof(sh)))
		.WillOnce(Return(buf_size))
		.WillOnce(Return(10))
		.WillOnce(Return(0));

	fp = freopen("stdout_", "w", stdout);
	receive_list_response(0);

	freopen("/dev/tty", "w", stdout);
    ifstream readFile5("stdout_");
    std::string strOut2((std::istreambuf_iterator<char>(readFile5)), std::istreambuf_iterator<char>());
    EXPECT_TRUE(strOut2.find(">") != string::npos);

	delete(mock);
	system("rm stdout_");
	system("rm stderr_");
}


TEST(ClientUnit__Test, make_directory){

	char towrite[buf_size];
	FILE* fp; 
	//already exist case
	fp = freopen("stdout_", "w", stdout);
	strcpy(towrite, "dir_exist/test");
	struct stat info;
    if(stat(towrite, &info) == 0 && S_ISDIR(info.st_mode)) system("mkdir dir_exist");
	make_directory(towrite);

	freopen("/dev/tty", "w", stdout);
	ifstream readFile("stdout_");
    std::string strOut((std::istreambuf_iterator<char>(readFile)), std::istreambuf_iterator<char>());
    EXPECT_TRUE(strOut.find("dir :") != string::npos);

	//mkdir case
	fp = freopen("stdout_", "w", stdout);
	system("rm -rf dir_not_exist");
	strcpy(towrite, "dir_not_exist/test");
	make_directory(towrite);

	freopen("/dev/tty", "w", stdout);
	ifstream readFile2("stdout_");
    std::string strOut2((std::istreambuf_iterator<char>(readFile2)), std::istreambuf_iterator<char>());
    EXPECT_TRUE(strOut2.find("dir :") != string::npos);

	system("rm stdout_");

}



TEST(ClientUnit__Test, receive_get_response){
	printf("TODO\n");
	EXPECT_EQ(0, 1);

}


TEST(ClientUnit__Test, receive_put_response){
	mock = new NiceMock<Mclass>();
	FILE *fp, *tmp;
	char target[buf_size];

	//normal case
	sh.is_error = 0;
	EXPECT_CALL(*mock, recv)
		.WillOnce(Return(sizeof(sh)));
	sprintf(target, ">> Writing %s on server succesfully completed!\n", basename(file_path));
	fp = freopen("stdout_", "w", stdout);
	receive_put_response(0);
	
	freopen("/dev/tty", "w", stdout);
    ifstream readFile("stdout_");
    std::string strList((std::istreambuf_iterator<char>(readFile)), std::istreambuf_iterator<char>());
	EXPECT_STREQ(strList.c_str(), target); 


	//receive error case
	EXPECT_CALL(*mock, recv)
		.WillOnce(Return(0));
	tmp = stderr;
	fp = fopen("stderr_", "w");
	stderr = fp;
	receive_put_response(0);

	stderr = tmp;
	fclose(fp);

    ifstream readFile2("stderr_");
    std::string strErr1((std::istreambuf_iterator<char>(readFile2)), std::istreambuf_iterator<char>());
    EXPECT_TRUE(strErr1.find("receive error :") != string::npos);
	

	//response error case
	EXPECT_CALL(*mock, recv)
		.WillOnce(Return(sizeof(sh)));
	sh.is_error = 1;
	tmp = stderr;
	fp = fopen("stderr_", "w");
	stderr = fp;
	receive_put_response(0);

	stderr = tmp;
	fclose(fp);

    ifstream readFile3("stderr_");
    std::string strErr2((std::istreambuf_iterator<char>(readFile3)), std::istreambuf_iterator<char>());
    EXPECT_TRUE(strErr2.find("response error :") != string::npos);

	delete(mock);
	system("rm stdout_");
	system("rm stderr_");

}


//TEST(ClientUnit__Test, receive_response){}



int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
