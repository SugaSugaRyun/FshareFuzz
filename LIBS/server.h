#ifndef FSHARED
#define FSHARED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <libgen.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    list,
    get,
    put,
    N_cmd
} cmd;

typedef struct {
    cmd command;
    int src_path_len;
    int des_path_len;
    int payload_size;
} client_header;

typedef struct {
    int is_error; // on success 0, on error 1
    int payload_size;
} server_header;

extern char *recv_payload;
extern char *send_payload;
extern client_header ch ;
extern server_header sh ;

extern int port_num;
extern char * server_dir;

extern const int buf_size;
int send_bytes(int fd, char *buf, size_t len);
int directory_check(char *filepath);
void print_usage();
void get_option(int argc, char *argv[]);
void list_response(char *filepath, const int conn);
void get_response(int conn);
void make_directory(char *towrite);
void put_response(int conn);
void *go_thread(void *arg);

#ifdef __cplusplus
}
#endif

#endif // FSHARED
