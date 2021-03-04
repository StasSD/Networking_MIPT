#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

/* for sockets */
#include <sys/socket.h>
#include <sys/un.h>

/* for ip addressing */
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

/* For multi-threaded server */
#include <pthread.h>

/* For communication between computers */
//#define COMM
//#define FRIENDIP "192.168.43.159"

/* For internet communication */
//#define INET

/* UDP server */
#define UDP


//#define LOCAL

/* TCP server */
//#define TCP

/* Debugging macros */
#define DEBUG 0
#define D(expr) if (DEBUG) { expr; }
#define ERROR(error) fprintf(stderr, "Error in line %d, function %s: "         \
                                    "%s\n", __LINE__, __func__, strerror(error)) \

/* Commands that a client can send to a server */
#define PRINT "--print"
#define EXIT "--exit"
#define LS "ls"
#define CD "cd"
#define BROAD "--broadcast"

/* Command and message size */
#define CMDSIZE 32
#define MSGSIZE 1024

/* Max path that can be sent via cd command */
#define MAXPATH 1024


/* Client_data field to send info back to client */
struct message {    
    int id;
    char cmd[CMDSIZE];
    char data[MSGSIZE];
    struct sockaddr_in client_data;
};

/* Types of commands that can be sent to our server */
enum cmds {
    PRINT_CMD = 0,
    EXIT_CMD,
    LS_CMD,
    CD_CMD,
    BRCAST_CMD,
    BAD_CMD
};

/* Lengths of commands */
enum cmd_len {
    PRINT_LEN = sizeof(PRINT) - 1,
    EXIT_LEN = sizeof(EXIT) - 1,
    LS_LEN = sizeof(LS) - 1,
    CD_LEN = sizeof(CD) - 1 ,
    BROAD_LEN = sizeof(BROAD) - 1,
};


/* Path for local communication with sockets */
#define PATH "/tmp/my_socket"

/* Port for communication */
#define PORT 23456

/* Maximum amount of clients */
#define MAXCLIENTS 100000

/* Maximum amount of pending requests */
#define MAX_QUEUE 20

/* Mutexes which are responsible for threads */
extern pthread_mutex_t mutexes[];

int check_input(int argc, char** argv, char** command, char** arg);

int send_message(int sk, struct message* msg, int msg_len, struct sockaddr_in* sk_addr);

void* handle_connection(void* client_pipe);

int lookup(int* id_map, int n_ids, pid_t id);

void print_info(struct message* msg);