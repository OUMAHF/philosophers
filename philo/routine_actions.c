/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohouafi <ohouafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:27:24 by ohouafi           #+#    #+#             */
/*   Updated: 2025/08/30 20:13:23 by ohouafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if ((philo->id + 1) % 2 != 0)
	{
		lock_fork_and_print(philo, philo->right_fork);
		lock_fork_and_print(philo, philo->left_fork);
	}
	else
	{
		lock_fork_and_print(philo, philo->left_fork);
		lock_fork_and_print(philo, philo->right_fork);
	}
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_is_eating(t_philo *philo)
{
	int	is_alive;

	pthread_mutex_lock(&philo->program->dead_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	is_alive = !philo->program->dead_flag;
	pthread_mutex_unlock(&philo->program->dead_lock);
	if (is_alive)
		printf("%lu %d is eating\n",
			get_time() - philo->program->start_time, philo->id + 1);
	ft_usleep(philo->program->time_to_eat, philo);
}

void	sleeping(t_philo *philo)
{
	print_if_alive(philo, "is sleeping");
	ft_usleep(philo->program->time_to_sleep, philo);
}

void	thinking(t_philo *philo)
{
	print_if_alive(philo, "is thinking");
}
