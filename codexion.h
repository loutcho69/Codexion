/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 19:50:20 by lobroue           #+#    #+#             */
/*   Updated: 2026/08/04 01:13:03 by lobroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
// HEAP ---------------------
typedef struct s_request
{
    int     coder_id;
    long    key;
}   t_request;

typedef struct s_heap
{
    t_request   *data;
    int         size;
    int         capacity;
}   t_heap;

int heap_init(t_heap *heap, int capacity);
void heap_free(t_heap *heap);
void	heap_push(t_heap *heap, t_request req);
t_request	heap_pop(t_heap *heap);
t_request	heap_peek(t_heap *heap);
void	heap_swap(t_request *a, t_request *b);
int	heap_parent(int i);
int	heap_left(int i);
int	heap_right(int i);

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
    t_heap  queue;
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
    long            seq_counter;
    pthread_mutex_t seq_mutex;
}   t_table;
// -- INIT ---------------------------------------
int init_dongles(t_table *table);
void init_coders(t_table *table);
int  init_table(t_table *table);
long	compute_key(t_coder *coder);

// --TIME-----------------------------------------
long get_time_ms(void);
int  simulation_stopped(t_table *table);
void log_state(t_table *table, int id, char *msg);
void precise_usleep(long duration_ms, t_table *table);
void	set_timeout(struct timespec *ts, long ms);
// CODER-----------------------
void	take_dongle(t_dongle *dongle, t_coder *coder);
void	release_dongle(t_dongle *dongle);
void	set_last_compil(t_coder *coder, long time);
void	*coder_routine(void *arg);
int		start_simulation(t_table *table);
void	take_both_dongles(t_coder *coder);
int	join_coders(t_table *table, int count);

// MONITOR -----------------------------
long	get_last_compil(t_coder *coder);
void	set_stop(t_table *table);
void	*monitor_routine(void *arg);
void	increment_compil(t_coder *coder);
int		get_compil_count(t_coder *coder);
int		all_compiled_enough(t_table *table);
// -- Parsing ------------------------------
int is_valid_number(char *str);
int ft_atoi_safe(char *str, int *result);   
int parse_one_int(char *str, int *dest);
int parse_scheduler(char *str, t_params *params);
int error_print(char *str);
int parse_args(int argc, char **argv, t_params *params);

// CLEANUP -------------------------------
void	cleanup(t_table *table);
void	destroy_dongles(t_table *table, int count);

#endif