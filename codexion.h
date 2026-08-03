/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 19:50:20 by lobroue           #+#    #+#             */
/*   Updated: 2026/08/04 01:37:10 by lobroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 19:50:20 by lobroue           #+#    #+#             */
/*   Updated: 2026/08/04 01:26:51 by lobroue          ###   ########.fr       */
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

/* ── Forward declarations ─────────────────────────────────────────────── */
typedef struct s_table		t_table;
typedef struct s_coder		t_coder;
typedef struct s_dongle		t_dongle;

/* ── Heap ─────────────────────────────────────────────────────────────── */
typedef struct s_request
{
	int		coder_id;
	long	key;
}	t_request;

typedef struct s_heap
{
	t_request	*data;
	int			size;
	int			capacity;
}	t_heap;

/* ── Params ───────────────────────────────────────────────────────────── */
typedef struct s_params
{
	int	nb_coders;
	int	time_to_burnout;
	int	time_to_compile;
	int	time_to_debug;
	int	time_to_refactor;
	int	compiles_required;
	int	dongle_cooldown;
	int	scheduler;
}	t_params;

/* ── Dongle ───────────────────────────────────────────────────────────── */
struct s_dongle
{
	int				id;
	int				taken;
	long			last_release;
	pthread_mutex_t	mutex;
	pthread_cond_t	available_cond;
	t_heap			queue;
};

/* ── Coder ────────────────────────────────────────────────────────────── */
struct s_coder
{
	int				id;
	int				compil_count;
	int				left_dongle;
	int				right_dongle;
	long			last_compil_start;
	pthread_t		thread;
	pthread_mutex_t	state_mutex;
	t_table			*table;
};

/* ── Table ────────────────────────────────────────────────────────────── */
typedef struct s_table
{
	t_params		params;
	long			start_time;
	long			seq_counter;
	int				stop;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	seq_mutex;
}	t_table;

/* ── Parsing ──────────────────────────────────────────────────────────── */
int			is_valid_number(char *str);
int			ft_atoi_safe(char *str, int *result);
int			parse_one_int(char *str, int *dest);
int			parse_scheduler(char *str, t_params *params);
int			parse_args(int argc, char **argv, t_params *params);
int			error_print(char *str);

/* ── Init ─────────────────────────────────────────────────────────────── */
int			init_table(t_table *table);
int			init_dongles(t_table *table);
void		init_coders(t_table *table);

/* ── Time ─────────────────────────────────────────────────────────────── */
long		get_time_ms(void);
void		set_timeout(struct timespec *ts, long ms);
void		precise_usleep(long duration_ms, t_table *table);
void		log_state(t_table *table, int id, char *msg);

/* ── Heap operations ──────────────────────────────────────────────────── */
int			heap_init(t_heap *heap, int capacity);
void		heap_free(t_heap *heap);
void		heap_push(t_heap *heap, t_request req);
t_request	heap_pop(t_heap *heap);
t_request	heap_peek(t_heap *heap);
void		heap_swap(t_request *a, t_request *b);
int			heap_parent(int i);
int			heap_left(int i);
int			heap_right(int i);
void		heap_sift_up(t_heap *heap, int i);
void		heap_sift_down(t_heap *heap, int i);
void		heap_remove_by_id(t_heap *heap, int coder_id);

/* ── Coder ────────────────────────────────────────────────────────────── */
void		*coder_routine(void *arg);
int			start_simulation(t_table *table);
int			join_coders(t_table *table, int count);
void		take_dongle(t_dongle *dongle, t_coder *coder);
void		take_both_dongles(t_coder *coder);
void		release_dongle(t_dongle *dongle);
void		set_last_compil(t_coder *coder, long time);
long		compute_key(t_coder *coder);
long		next_seq(t_table *table);

/* ── Monitor ──────────────────────────────────────────────────────────── */
void		*monitor_routine(void *arg);
int			simulation_stopped(t_table *table);
void		set_stop(t_table *table);
long		get_last_compil(t_coder *coder);
void		increment_compil(t_coder *coder);
int			get_compil_count(t_coder *coder);
int			all_compiled_enough(t_table *table);

/* ── Cleanup ──────────────────────────────────────────────────────────── */
void		cleanup(t_table *table);
void		destroy_dongles(t_table *table, int count);

#endif