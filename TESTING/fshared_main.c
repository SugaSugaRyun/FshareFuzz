#include "server.h"

int
main(int argc, char * argv[])
{
    get_option(argc, argv) ;

    /* Connect socket */

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0) ;
    if (listen_fd == 0) {
        perror("socket failed : ") ;
        exit(EXIT_FAILURE) ;
    }

    struct sockaddr_in address ;
    memset(&address, '0', sizeof(address)) ;
    address.sin_family = AF_INET ;
    address.sin_addr.s_addr = INADDR_ANY ; // localhost
    address.sin_port = htons(port_num) ;
    if (bind(listen_fd, (struct sockaddr *) &address, sizeof(address)) < 0) { 
        perror("bind failed : ") ;
        exit(EXIT_FAILURE) ;
    }

    while (1) {
        if (listen(listen_fd, 16) < 0) {
            perror("listen failed : ") ;
            exit(EXIT_FAILURE) ; 
        }

        int * new_socket = (int *) malloc(sizeof(int)) ;
        int address_len = sizeof(address) ;
        *new_socket = accept(listen_fd, (struct sockaddr *) &address, (socklen_t *) &address_len) ;
        if (*new_socket < 0) {
            perror("accept failed : ") ;
            exit(EXIT_FAILURE) ;
        }

        pthread_t working_thread ;
        if (pthread_create(&working_thread, NULL, go_thread, new_socket) == 0) {
            // data receiving is done in working thread
        } else {
            close(*new_socket) ;
        }
    }

    return 0 ;
}
