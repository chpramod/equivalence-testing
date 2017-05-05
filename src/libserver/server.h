#ifndef SOCKET_HEADER_FILE
#define SOCKET_HEADER_FILE

// #define __SKIP __attribute__((crest_skip))
#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN extern
#endif
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <time.h> 
//  q
#include <dirent.h>
#include <netinet/tcp.h>

// #include "../run_crest/concolic_search.h"
// using std::cout;
// using std::endl
// #include <fstream>



#define SEND_SIZE 1024
// using namespace crest;

#define TRUE   1
#define FALSE  0
typedef long long int value_t;

#include <string.h>

struct FDS{
	int fd[3];
	int available[3];
	fd_set readfds;
	int master_socket, max_clients;
};

struct INPUT{
	int num;
	value_t inputs[256];
};

EXTERN struct FDS socket_pair(int port) __attribute__((crest_skip));
EXTERN struct FDS client_wait(int port) __attribute__((crest_skip));
// EXTERN void send_initial_values(int sockid,char buf[], int len) __attribute__((crest_skip));
// EXTERN char *recv_initial_values();// __SKIP;
EXTERN int recv_ans(int sockid) __attribute__((crest_skip));
EXTERN int send_ans(char *a1, char *a2, int len1, int len2);
EXTERN int recv_constraints(int sockid, char* s); 
EXTERN void send_branch_cond(struct FDS*,char* s, int len);
EXTERN void send_branch_cond_first(struct FDS*,char* s, int len);
EXTERN int match_outputs(int sockid, char output_server[]);
EXTERN void send_output(struct FDS,char buf[],int len) __attribute__((crest_skip));
EXTERN void recv_output(int sockid, char output_server[]);
EXTERN void can_die(struct FDS);
EXTERN void store_input(struct INPUT*);

#endif