/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohouafi <ohouafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:00:04 by ohouafi           #+#    #+#             */
/*   Updated: 2025/08/30 23:07:41 by ohouafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_if_alive(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&philo->program->dead_lock);
	if (!philo->program->dead_flag)
		printf("%lu %d %s\n",
			get_time() - philo->program->start_time, philo->id + 1, msg);
	pthread_mutex_unlock(&philo->program->dead_lock);
}

int	check_if_dead(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->program->dead_lock);
	dead = philo->program->dead_flag;
	pthread_mutex_unlock(&philo->program->dead_lock);
	return (dead);
}

int	philo_cycle(t_philo *philo)
{
	take_forks(philo);
	philo_is_eating(philo);
	put_down_forks(philo);
	sleeping(philo);
	thinking(philo);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->program->dead_lock);
	philo->last_meal = philo->program->start_time;
	pthread_mutex_unlock(&philo->program->dead_lock);
	if (one_philo_case(philo))
		return (NULL);
	if ((philo->id + 1) % 2 == 0)
		usleep(100);
	while (!check_if_dead(philo))
	{
		if (!philo_cycle(philo))
			break ;
	}
	return (NULL);
}
