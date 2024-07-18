/*
** EPITECH PROJECT, 2021
** project name
** File description:
** simple description
*/

#ifndef PROTO_H_
    #define PROTO_H_

int main(int ac, char **av);
int start(int ac, char **av);
void clients_connection(sock *socket_var);
clients_s *event_client_disconnected(sock *socket_var, clients_s *clients);
void loop_check_disconnection(sock *socket_var);
void wait_client(sock *socket_var);
void handle_error(int ac, char **av);
void error_server(char *message, int server_fd);
void delete_clients(clients_s *clients);
void free_element(clients_s *client_delete);
clients_s *delete_client(sock *socket_var, clients_s *client_delete);
clients_s *add_client(sock *socket_var, int control_fd,
char *ip_addr, int port);
void clear(sock *socket_var, char *path);
int user(char **table, clients_s *clients);
int pass(char **table, clients_s *clients);
int cwd(char **table, clients_s *clients);
int ls_list(char **table, clients_s *clients);
int show_pwd(clients_s *clients);
int check_dir(char *path);
int cdup(clients_s *clients);
int check_match(char c, char *separator, int count);
int check_separator(char *str, char *separator, int v);
int count_sprt(char *str, char *separator, int col, char **result);
char **separate_table(char **result, char *str, char *separator, int count_st);
char **my_split(char *str, char *separator);
int mode_passive_or_active(clients_s *clients);
int init_pasv(clients_s *clients, int *port_data, Pasv *pasv);
int pasv(clients_s *clients);
void table_free(char **table);
char *create_path(char *path);
int count_int(int number, int i);
int count_table(char **table, int i);
int generate_random_number(int min, int max);
int server(char *port, char *path);
int port_send_info(clients_s *clients, char **ip_split);
int port(clients_s *clients, char **table);
int connect_to_port(clients_s *clients);
int delete_file(char **table, clients_s *clients);
int retr(clients_s *clients, char **table);
int stor(clients_s *clients, char **table);
int send_msg(int sd, char *msg, int type);
int get_order_next(char **table, clients_s *clients);
int get_order(char **table, clients_s *clients);
void child_sockets_wait_activity(sock *socket_var);
void init(sock *socket_var);
sock init_varaible(char *port, char *path);
char *init_path_default(void);
int usage(void);

#endif /* PROTO_H_ */
