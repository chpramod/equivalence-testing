#ifndef SOCKET_HEADER_FILE
#define SOCKET_HEADER_FILE

#define __SKIP __attribute__((crest_skip))

void socket_pair() __SKIP;
void client_wait() __SKIP;
void send_initial_values() __SKIP;
void recv_initial_values() __SKIP;

#endif