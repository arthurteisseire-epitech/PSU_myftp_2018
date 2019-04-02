/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** myftp.h
*/

#ifndef PSU_MYFTP_2018_MYFTP_H
#define PSU_MYFTP_2018_MYFTP_H

#include <stdarg.h>
#include <stdbool.h>

enum fd_type {
    SERVER,
    CLIENT,
    FREE
};

typedef struct event_s {
    int fd;
    enum fd_type type;
    bool is_event;
} event_t;

typedef struct set_s {
    event_t *readfds;
    size_t size;
} set_t;

set_t *set_init(void);
void set_add_fd(set_t *set, event_t fd);
void set_reload_fd_set(set_t *set, fd_set *fd_s);
int set_find_max_fd(set_t *set);
void set_set_events(set_t *set, fd_set *fd_s);
event_t *set_poll_event(set_t *set);
void exit_with(const char *msg, ...);

#endif
