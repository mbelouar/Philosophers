/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 01:23:13 by mbelouar          #+#    #+#             */
/*   Updated: 2023/06/04 23:12:29 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*routine(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 0)
		usleep(500);
	while (1)
	{
		if (ft_print(philo, "is thinking") == 1)
			return (NULL);
		pthread_mutex_lock(philo->left_chopstick);
		ft_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_chopstick);
		ft_print(philo, "has taken a fork");
		ft_eating(philo);
		pthread_mutex_unlock(philo->left_chopstick);
		pthread_mutex_unlock(philo->right_chopstick);
		if (ft_print(philo, "is sleeping") == 1)
			return (NULL);
		ft_usleep(ft_time(), philo->time_to_sleep);
	}
	return (NULL);
}
