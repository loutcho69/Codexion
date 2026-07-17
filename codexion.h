#ifndef CODEXION_H
#define CODEXION_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct s_params
{
    int nb_coders;
    int time_to_burnout;
    int time_to_compile;
    int time_to_debug;
    int time_to_refactor;
    int compiles_required;
    int dongle_cooldown;
    int scheduler;
}   t_params;

typedef struct s_table
{
    t_params        params;
    long            start_time;
    t_coder         *coders;
    t_dongle        *dongles;
    int             stop;
    pthread_mutex_t print_mutex;
    pthread_mutex_t stop_mutex;
}   t_table;

#endif