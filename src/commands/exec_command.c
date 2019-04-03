/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** exec_command.c
*/

#include <unistd.h>
#include <string.h>
#include "utils.h"
#include "myftp.h"
#include "command.h"

static bool is_admin(struct user_s *user)
{
    return (strcmp(user->name, USERNAME) == 0
    && strcmp(user->password, PASSWORD) == 0);
}

static int exec_guest_command(poll_t *poll, connection_t *conn,
    const char *input)
{
    for (int i = 0; guest_commands[i].name; ++i)
        if (begin_with(guest_commands[i].name, input))
            return (guest_commands[i].f(poll, conn, input));
    return (COMMAND_NOT_FOUND);
}

static int exec_admin_command(poll_t *poll, connection_t *conn,
    const char *input)
{
    for (int i = 0; admin_commands[i].name; ++i)
        if (begin_with(admin_commands[i].name, input))
            return (admin_commands[i].f(poll, conn, input));
    return (COMMAND_NOT_FOUND);
}

void exec_command(poll_t *poll, connection_t *conn)
{
    char input[64] = {0};
    int rd_bytes = read(conn->sock.fd, input, sizeof(input));
    int status;

    input[rd_bytes] = '\0';
    status = exec_guest_command(poll, conn, input);
    if (is_admin(&conn->user) && status == COMMAND_NOT_FOUND)
        exec_admin_command(poll, conn, input);
}
