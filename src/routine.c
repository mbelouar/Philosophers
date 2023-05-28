/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 01:23:13 by mbelouar          #+#    #+#             */
/*   Updated: 2023/05/22 01:40:10 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*routine(void	*arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2)
		usleep(500);
	while (1)
	{
		printf("%ld %d is thinking ...\n", ft_time() - philo->start_time, philo->philo_id);
		pthread_mutex_lock(philo->left_chopstick);
		printf("%ld %d has taken a fork\n", ft_time() - philo->start_time, philo->philo_id);
		pthread_mutex_lock(philo->right_chopstick);
		printf("%ld %d has taken a fork\n", ft_time() - philo->start_time, philo->philo_id);
		ft_eating(philo);
		pthread_mutex_unlock(philo->left_chopstick);
		pthread_mutex_unlock(philo->right_chopstick);
		printf("%ld %d is sleeping\n", ft_time() - philo->start_time, philo->philo_id);
		usleep(philo->time_to_sleep * 1000);
	}
	return (NULL);
}
