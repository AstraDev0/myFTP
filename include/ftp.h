/*
** EPITECH PROJECT, 2023
** B-NWP-400-BER-4-1-myftp-matthis.brocheton
** File description:
** ftp
*/

#ifndef FTP_H_
    #define FTP_H_
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <stdio.h>
    #include <string.h>
    #include <assert.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <pthread.h>
    #include <sys/types.h>
    #include <sys/time.h>
    #include <errno.h>
    #include <ctype.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #define MAXDATASIZE 6000
    #define FTP_MODE_NOTHING 0
    #define FTP_MODE_PASSIVE 1
    #define FTP_MODE_ACTIVE 2

typedef struct Pasv Pasv;
struct Pasv {
    int data_fd;
    int mode;
    struct sockaddr_in address;
};

typedef struct clients_s clients_s;
struct clients_s {
    char *ip_addr;
    int port;
    int control_fd;
    char *user;
    char *path;
    int connected;
    Pasv pasv_socket;
    clients_s *next;
    clients_s *prec;
};

typedef struct sock sock;
struct sock {
    int server_fd;
    int valread;
    struct sockaddr_in address;
    int opt;
    int addrlen;
    int activity;
    char *port_serv;
    char *path_serv_default;
    int sd;
    fd_set readfds;
    clients_s *clients;
};

    #include "proto.h"
#endif /* !FTP_H_ */
