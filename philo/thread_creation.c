/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohouafi <ohouafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:45:28 by ohouafi           #+#    #+#             */
/*   Updated: 2025/08/30 22:12:20 by ohouafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philo_threads(t_program *program, pthread_t *threads)
{
	int	i;

	i = 0;
	program->start_time = get_time();
	while (i < program->num_of_philos)
	{
		if (pthread_create(&threads[i], NULL, philo_routine,
				(void *)&program->philos[i]) != 0)
		{
			pthread_mutex_lock(&program->dead_lock);
			program->dead_flag = 1;
			pthread_mutex_unlock(&program->dead_lock);
			return (0);
		}
		i++;
	}
	return (1);
}

void	join_threads(pthread_t *threads, pthread_t monitor, t_program *program)
{
	int	i;

	(void)program;
	i = 0;
	while (i < program->num_of_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}

void	create_threads(t_program *program)
{
	pthread_t	*threads;
	pthread_t	monitor;

	threads = malloc(sizeof(pthread_t) * program->num_of_philos);
	if (!threads)
		return ;
	if (!create_philo_threads(program, threads))
	{
		free(threads);
		return ;
	}
	usleep(100);
	if (pthread_create(&monitor, NULL, monitor_routine, program) != 0)
	{
		pthread_mutex_lock(&program->dead_lock);
		program->dead_flag = 1;
		pthread_mutex_unlock(&program->dead_lock);
	}
	join_threads(threads, monitor, program);
	free(threads);
}
