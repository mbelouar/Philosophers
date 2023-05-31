/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 01:22:02 by mbelouar          #+#    #+#             */
/*   Updated: 2023/05/31 15:44:32 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	init_mutex(t_philo *philo)
{
	int	i;

	philo->print_mutex = malloc(sizeof(pthread_mutex_t));
	philo->eat_time = malloc(sizeof(pthread_mutex_t));
	if (!philo->print_mutex || !philo->eat_time)
		return (1);
	if (pthread_mutex_init(philo->print_mutex, NULL) != 0)
		return (free (philo->print_mutex), free (philo->eat_time), 1);
	if (pthread_mutex_init(philo->eat_time, NULL) != 0)
	{
		pthread_mutex_destroy(philo->print_mutex);
		return (free (philo->print_mutex), free (philo->eat_time), 1);
	}
	philo->forks = malloc(sizeof(pthread_mutex_t *));
	if (!philo->forks)
		return (1);
	i = -1;
	while (++i < philo->nb_philo)
	{
		philo->forks[i] = malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(philo->forks[i], NULL) != 0)
		{
			pthread_mutex_destroy(philo->eat_time);
			pthread_mutex_destroy(philo->print_mutex);
			return (free (philo->print_mutex), free (philo->eat_time), 1);
		}
	}
	return (0);
}

int	create_threads(t_philo *philo)
{
	t_philo	**all_philos;
	int		i;

	all_philos = malloc(sizeof(t_philo *) * philo->nb_meals);
	philo->thread_id = malloc(sizeof(pthread_t) * philo->nb_philo);
	if (!all_philos || !philo->thread_id)
		return (1);
	if (init_mutex(philo) != 0)
		return (free (all_philos), free (philo->thread_id), 1);
	i = -1;
	while (++i < philo->nb_philo)
	{
		all_philos[i] = malloc(sizeof(t_philo));
		if (!all_philos)
			return (1);
		all_philos[i]->philo_id = i + 1;
		all_philos[i]->die = 0;
		all_philos[i]->nb_philo = philo->nb_philo;
		all_philos[i]->nb_meals = philo->nb_meals;
		all_philos[i]->start_time = ft_time();
		all_philos[i]->time = ft_time();
		all_philos[i]->time_to_eat = philo->time_to_eat;
		all_philos[i]->time_to_sleep = philo->time_to_sleep;
		all_philos[i]->left_chopstick = philo->forks[i];
		all_philos[i]->right_chopstick = philo->forks[(i + 1) % (philo->nb_philo)];
		all_philos[i]->print_mutex = philo->print_mutex;
		all_philos[i]->eat_time = philo->eat_time;
		if (pthread_create(&philo->thread_id[i], NULL, routine, all_philos[i]) != 0)
			return (free (all_philos), free (philo->thread_id), 1);
	}
	while (1)
	{
		i = -1;
		while (++i < philo->nb_philo)
		{
			pthread_mutex_lock(all_philos[i]->eat_time);
			if (ft_time() - all_philos[i]->time >= philo->time_to_die)
			{
				philo->die = 1;
				ft_print(philo, "is died");
				pthread_mutex_unlock(all_philos[i]->eat_time);
				i = -1;
				while (++i < philo->nb_philo)
					pthread_join(all_philos[i]->thread_id[i], NULL);
				return (0);
			}
			usleep(200);
			pthread_mutex_unlock(all_philos[i]->eat_time);
		}
	}
	return (0);
}
