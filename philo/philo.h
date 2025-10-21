/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohouafi <ohouafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 02:13:04 by ohouafi           #+#    #+#             */
/*   Updated: 2025/08/30 23:08:02 by ohouafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define INT_MIN -2147483648
# define INT_MAX 2147483647

typedef struct s_program	t_program;

typedef struct s_philo
{
	pthread_t				thread;
	int						id;
	int						meals_eaten;
	size_t					last_meal;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			*left_fork;
	t_program				*program;
}							t_philo;

typedef struct s_program
{
	size_t					time_to_die;
	size_t					time_to_eat;
	size_t					time_to_sleep;
	size_t					start_time;
	int						num_of_philos;
	int						number_of_times_each_philosopher_must_eat;
	int						dead_flag;
	pthread_mutex_t			dead_lock;
	pthread_mutex_t			*fork_mutex_array;
	t_philo					*philos;
}							t_program;

int							alive_and_unlock(pthread_mutex_t *dead_lock,
								int *dead_flag);
void						print_if_alive(t_philo *philo, const char *msg);
void						lock_fork_and_print(t_philo *philo,
								pthread_mutex_t *fork);
void						take_forks(t_philo *philo);
void						put_down_forks(t_philo *philo);
void						philo_is_eating(t_philo *philo);
void						sleeping(t_philo *philo);
void						thinking(t_philo *philo);
int							check_if_dead(t_philo *philo);
int							philo_cycle(t_philo *philo);
void						*philo_routine(void *arg);
int							all_philos_have_eaten(t_program *program);
void						*monitor_routine(void *arg);
int							checking_death(t_philo *p);
long						ft_atoi(const char *str);
int							is_valid_digit(char *str);
long						get_time(void);
void						create_threads(t_program *program);
void						join_threads(pthread_t *threads, pthread_t monitor,
								t_program *program);
int							create_philo_threads(t_program *program,
								pthread_t *threads);
int							parse_args(int ac, char **av, t_program *program);
int							one_philo_case(t_philo *philo);
void						cleanup_program(t_program *program);
void						cleanup_program(t_program *program);
int							init_mutexes(t_program *program);
int							init_philosophers(t_program *program);
int							init_philo(t_program *program, int i);
void						ft_usleep(long time_ms, t_philo *philo);

#endif
