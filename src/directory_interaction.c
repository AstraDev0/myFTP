/*
** EPITECH PROJECT, 2023
** B-NWP-400-BER-4-1-myftp-matthis.brocheton
** File description:
** directory_interaction
*/

#include "../include/ftp.h"

int cwd(char **table, clients_s *clients)
{
    char cwd[1024];

    if (!table[1])
        return send_msg(clients->control_fd,
        "CWD <path> is required.", 503);
    if (check_dir(table[1]) == 0) {
        chdir(clients->path);
        chdir(table[1]);
        getcwd(cwd, sizeof(cwd));
        free(clients->path);
        clients->path = create_path(cwd);
        return send_msg(clients->control_fd,
        "Requested file action okay, completed.", 250);
    } else {
        return send_msg(clients->control_fd,
        "Failed to change directory", 550);
    }
    return 0;
}

int ls_list(char **table, clients_s *clients)
{
    char *cmd;
    int oldfd;

    send_msg(clients->control_fd, "Directory listing.", 150);
    cmd = malloc(sizeof(char) * (strlen(clients->path) + 27));
    sprintf(cmd, "/bin/ls -l \"%s\" | tail -n +2", clients->path);
    if (mode_passive_or_active(clients) == 84)
        return 84;
    if ((oldfd = dup(1)) == -1 || dup2(clients->pasv_socket.data_fd, 1) == -1
    || system(cmd) == -1 || dup2(oldfd, 1) == -1)
        return 84;
    send_msg(clients->control_fd, "Directory send.", 226);
    close(clients->pasv_socket.data_fd);
    free(cmd);
    return 0;
}

int show_pwd(clients_s *clients)
{
    char *path;

    path = malloc(sizeof(char) * (strlen(clients->path) + 29));
    sprintf(path, "\"%s\" is the current directory", clients->path);
    send_msg(clients->control_fd, path, 257);
    free(path);
    return 0;
}

int check_dir(char *path)
{
    DIR *dir = opendir(path);
    struct stat sb;

    if (dir == NULL || stat(path, &sb) == -1
    || !S_ISDIR(sb.st_mode) || chdir(path) == -1) {
        closedir(dir);
        return 84;
    }
    closedir(dir);
    return 0;
}

int cdup(clients_s *clients)
{
    char cwd[1024];

    if (check_dir("../") == 0) {
        chdir(clients->path);
        chdir("../");
        getcwd(cwd, sizeof(cwd));
        free(clients->path);
        clients->path = create_path(cwd);
        return send_msg(clients->control_fd,
        "Change directory successfully", 250);
    } else {
        return send_msg(clients->control_fd,
        "Failed to change directory", 550);
    }
    return 0;
}
