/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 22:03:43 by mbelouar          #+#    #+#             */
/*   Updated: 2023/06/02 01:10:13 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	ft_time()
{
	struct timeval	tv;
	long	time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_in_ms);
}

void	ft_usleep(long start, int time_to_sleep)
{
	while (1)
	{
		if (ft_time() - start >= time_to_sleep)
			break ;
		usleep(200);
	}
}

void	ft_eating(t_philo *philo)
{
	static int count;

	pthread_mutex_lock(philo->eat_time);
	philo->time = ft_time();
	pthread_mutex_unlock(philo->eat_time);
	ft_print(philo, "is eating");
	ft_usleep(philo->time, philo->time_to_eat);
	pthread_mutex_lock(philo->eat_time);
	count++;
	philo->meal = count;
	pthread_mutex_unlock(philo->eat_time);
}

int	ft_print(t_philo *philo, char *act)
{
	pthread_mutex_lock(philo->eat_time);
	if (philo->die == 1)
	{
		pthread_mutex_unlock(philo->eat_time);
		return (1);
	}
	printf("%ld %d %s\n", ft_time() - philo->start_time, philo->philo_id, act);
	pthread_mutex_unlock(philo->eat_time);
	return (0);
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
