/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohouafi <ohouafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:12:19 by ohouafi           #+#    #+#             */
/*   Updated: 2025/10/21 16:05:49 by ohouafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_program(t_program *program)
{
	int	i;

	i = -1;
	while (++i < program->num_of_philos)
		pthread_mutex_destroy(&program->fork_mutex_array[i]);
	pthread_mutex_destroy(&program->dead_lock);
	free(program->fork_mutex_array);
	free(program->philos);
}

int	parse_args(int ac, char **av, t_program *program)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (write(2, "invalid parameters\n", 19), 1);
	i = 1;
	while (i < ac)
	{
		if (!is_valid_digit(av[i]) || ft_atoi(av[i]) <= 0)
			return (write(2, "invalid parameters\n", 19), 1);
		i++;
	}
	program->num_of_philos = ft_atoi(av[1]);
	program->time_to_die = ft_atoi(av[2]);
	program->time_to_eat = ft_atoi(av[3]);
	program->time_to_sleep = ft_atoi(av[4]);
	program->number_of_times_each_philosopher_must_eat = -1;
	program->dead_flag = 0;
	if (ac == 6)
		program->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	return (0);
}

int	one_philo_case(t_philo *philo)
{
	if (philo->program->num_of_philos == 1)
	{
		print_if_alive(philo, "has taken a fork");
		ft_usleep(philo->program->time_to_die, philo);
		pthread_mutex_lock(&philo->program->dead_lock);
		if (!philo->program->dead_flag)
		{
			philo->program->dead_flag = 1;
			printf("%lu %d died\n",
				get_time() - philo->program->start_time, philo->id + 1);
		}
		pthread_mutex_unlock(&philo->program->dead_lock);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_program	program;
	int			i;

	program.fork_mutex_array = NULL;
	program.philos = NULL;
	if (parse_args(ac, av, &program))
		return (1);
	if (init_mutexes(&program))
		return (1);
	if (init_philosophers(&program))
	{
		i = -1;
		while (++i < program.num_of_philos)
			pthread_mutex_destroy(&program.fork_mutex_array[i]);
		free(program.fork_mutex_array);
		return (1);
	}
	i = -1;
	while (++i < program.num_of_philos)
		init_philo(&program, i);
	create_threads(&program);
	cleanup_program(&program);
	return (0);
}
