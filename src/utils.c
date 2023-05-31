/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 22:03:43 by mbelouar          #+#    #+#             */
/*   Updated: 2023/05/31 15:44:35 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

unsigned long	ft_time()
{
	struct timeval	tv;
	unsigned long	time_in_ms;

	gettimeofday(&tv, NULL); // Get the current time
	time_in_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_in_ms);
}

// void	ft_usleep(size_t time_in_ms)
// {
// 	size_t time;

// 	time = ft_time() + time_in_ms;
// }

void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->eat_time);
	philo->time = ft_time();
	pthread_mutex_unlock(philo->eat_time);
	ft_print(philo, "is eating");
	usleep(philo->time_to_eat * 1000);
	philo->nb_meals++;
}

int	ft_print(t_philo *philo, char *act)
{
	pthread_mutex_lock(philo->eat_time);
	pthread_mutex_lock(philo->print_mutex);
	if (philo->die)
	{
		// pthread_mutex_unlock(philo->print_mutex);
		// pthread_mutex_unlock(philo->eat_time);
		return (1);
	}
	printf("%ld %d %s\n", ft_time() - philo->start_time, philo->philo_id, act);
	pthread_mutex_unlock(philo->print_mutex);
	pthread_mutex_unlock(philo->eat_time);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
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
