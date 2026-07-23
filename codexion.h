#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

// ── Forward declarations ──────────────────
typedef struct s_table  t_table;
typedef struct s_coder  t_coder;
typedef struct s_dongle t_dongle;

// ── Params ────────────────────────────────
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

// ── Dongle ────────────────────────────────
struct s_dongle
{
    int             id;
    pthread_mutex_t mutex;
    long last_release;
    int taken;
    pthread_cond_t available_cond;
};

// ── Coder ─────────────────────────────────
struct s_coder
{
    int             id;
    pthread_t       thread;
    long last_compil_start;
    int compil_count;
    int left_dongle;
    int right_dongle;
    t_table *table;
    pthread_mutex_t state_mutex;
};

// ── Table ─────────────────────────────────
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
// --TIME-----------------------------------------
struct timeval
{
    time_t      tv_sec;    // secondes depuis le 1er janvier 1970
    suseconds_t tv_usec;   // microsecondes écoulées DANS la seconde courante
};

long get_time_ms(void);
int  simulation_stopped(t_table *table);
void log_state(t_table *table, int id, char *msg);
void precise_usleep(long duration_ms, t_table *table);

// -- Parsing ------------------------------
int is_valid_number(char *str);
int ft_atoi_safe(char *str, int *result);
int parse_one_int(char *str, int *dest);
int parse_scheduler(char *str, t_params *params);
int error_print(char *str);
int parse_args(int argc, char **argv, t_params *params);
#endif