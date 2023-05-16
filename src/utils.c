/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 22:03:43 by mbelouar          #+#    #+#             */
/*   Updated: 2023/05/15 04:06:40 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

unsigned long	ft_time()
{
	struct timeval	tv;
	unsigned long	time_in_ms;

	gettimeofday(&tv, NULL); // Get the current time
	time_in_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000; // Convert to milliseconds
	return (time_in_ms);
}

void	ft_eating(t_philo *philo)
{
	long	end_time;
	long	start_time;

	pthread_mutex_lock(philo->eat_time);
	start_time = philo->time;
	pthread_mutex_unlock(philo->eat_time);
	pthread_mutex_lock(philo->print_mutex);
	printf("\n\035[1;32m%ld %lu is eating\035[0m\n", philo->time, (unsigned long)philo->thread_id[philo->thread_index]);
	pthread_mutex_lock(philo->eat_time);
	end_time = ft_time();
	philo->time += end_time - start_time; // update the current time for the next philo
	pthread_mutex_unlock(philo->eat_time);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;
	int	i;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res = res + str[i] - 48;
		i++;
	}
	return (res * sign);
}
