/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohouafi <ohouafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:54:11 by ohouafi           #+#    #+#             */
/*   Updated: 2025/08/30 16:09:39 by ohouafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_fork_and_print(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	print_if_alive(philo, "has taken a fork");
}

int	all_philos_have_eaten(t_program *program)
{
	int	target;
	int	i;
	int	eaten;

	if (program->number_of_times_each_philosopher_must_eat <= 0)
		return (0);
	target = program->number_of_times_each_philosopher_must_eat;
	i = 0;
	while (i < program->num_of_philos)
	{
		pthread_mutex_lock(&program->dead_lock);
		eaten = program->philos[i].meals_eaten;
		pthread_mutex_unlock(&program->dead_lock);
		if (eaten < target)
			return (0);
		i++;
	}
	return (1);
}

int	check_philos_death(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		if (checking_death(&program->philos[i]))
			return (1);
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_program	*program;
	int			dead;

	program = (t_program *)arg;
	while (1)
	{
		pthread_mutex_lock(&program->dead_lock);
		dead = program->dead_flag;
		pthread_mutex_unlock(&program->dead_lock);
		if (dead)
			return (NULL);
		if (all_philos_have_eaten(program))
		{
			pthread_mutex_lock(&program->dead_lock);
			program->dead_flag = 1;
			pthread_mutex_unlock(&program->dead_lock);
			return (NULL);
		}
		if (check_philos_death(program))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
