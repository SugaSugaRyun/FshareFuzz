#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "client.h"
#include <stdio.h>
#define BUF_SIZE 512


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

//TEST(ClientUnit__Test, print_usage){}

#define PARSE_IPPORT (hostip && port_num) 
#define LIST_CASE (ch.command == list)
#define PUTGET_CASE (((ch.command == put) || (ch.command == get)) && ((file_path != NULL) && (dest_dir != NULL)))
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
	EXPECT_TRUE(PARSE_IPPORT && 
	1		
	
	);

}


//TEST(ClientUnit__Test, parse_directory){}


TEST(ClientUnit__Test, reuest){
/*
	size_t len = 10;
	MockSocket mock;

	EXPECT_CALL(mock, send(_, _, _, _)).WillOnce(Return(0));
	request(1);
*/
	EXPECT_EQ(0, 0);


}

TEST(ClientUnit__Test, receive_list_response){


}


TEST(ClientUnit__Test, make_directory){


}



TEST(ClientUnit__Test, receive_get_response){

}



TEST(ClientUnit__Test, receive_put_response){


}


TEST(ClientUnit__Test, receive_response){

}




int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
