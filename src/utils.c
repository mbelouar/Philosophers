/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 22:03:43 by mbelouar          #+#    #+#             */
/*   Updated: 2023/05/21 23:56:10 by mbelouar         ###   ########.fr       */
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
	pthread_mutex_lock(philo->eat_time);
	philo->time = ft_time();
	pthread_mutex_unlock(philo->eat_time);
	pthread_mutex_lock(philo->print_mutex);
	printf("%ld %d is eating\n", philo->time - philo->start_time, philo->philo_id);
	pthread_mutex_unlock(philo->print_mutex);
	usleep(philo->time_to_eat * 1000);
}

// void	ft_free(t_philo **arr)
// {
// 	int	i;

// 	i = -1;
// 	while (arr[++i])
// 		free(arr[i]);
// 	free(arr);
// }

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
