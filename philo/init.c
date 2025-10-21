/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohouafi <ohouafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:42:20 by ohouafi           #+#    #+#             */
/*   Updated: 2025/08/28 02:23:32 by ohouafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philosophers(t_program *program)
{
	int	i;

	i = 0;
	program->philos = malloc(sizeof(t_philo) * program->num_of_philos);
	if (!program->philos)
		return (1);
	program->dead_flag = 0;
	if (pthread_mutex_init(&program->dead_lock, NULL))
	{
		free(program->philos);
		return (1);
	}
	return (0);
}

int	init_mutexes(t_program *program)
{
	int	i;

	program->fork_mutex_array = malloc(sizeof(pthread_mutex_t)
			* program->num_of_philos);
	if (!program->fork_mutex_array)
		return (1);
	i = 0;
	while (i < program->num_of_philos)
	{
		if (pthread_mutex_init(&program->fork_mutex_array[i], NULL))
		{
			free(program->fork_mutex_array);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_philo(t_program *program, int i)
{
	t_philo	*philo;

	philo = &program->philos[i];
	philo->id = i;
	philo->meals_eaten = 0;
	philo->last_meal = 0;
	philo->left_fork = &program->fork_mutex_array[i];
	philo->right_fork = &program->fork_mutex_array[(i + 1)
		% program->num_of_philos];
	philo->program = program;
	return (0);
}
