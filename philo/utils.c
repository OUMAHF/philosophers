/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohouafi <ohouafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:12:09 by ohouafi           #+#    #+#             */
/*   Updated: 2025/08/30 22:30:58 by ohouafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_digit(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

long	ft_atoi(const char *str)
{
	long	i;
	long	res;
	long	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		if (res > INT_MAX || res < INT_MIN)
			return (-1);
		i++;
	}
	return (res * sign);
}

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "timing_error\n", 13);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	checking_death(t_philo *p)
{
	size_t	start;

	pthread_mutex_lock(&p->program->dead_lock);
	start = get_time();
	if (start - p->last_meal > p->program->time_to_die
		&& !p->program->dead_flag)
	{
		p->program->dead_flag = 1;
		printf("%lu %d died\n", start - p->program->start_time,
			p->id + 1);
		pthread_mutex_unlock(&p->program->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&p->program->dead_lock);
	return (0);
}

void	ft_usleep(long time_ms, t_philo *philo)
{
	long	start;

	start = get_time();
	while (get_time() < start + time_ms)
	{
		if (check_if_dead(philo) || checking_death(philo))
			return ;
		usleep(500);
	}
}
