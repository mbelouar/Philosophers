/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 01:22:02 by mbelouar          #+#    #+#             */
/*   Updated: 2023/06/04 01:10:18 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	init_mutex_and_forks(t_philo *philo, pthread_mutex_t *forks)
{
	pthread_mutex_t	*lock;
	pthread_mutex_t	*print;
	int				i;

	i = -1;
	lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(lock, NULL);
	print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(print, NULL);
	philo->eat_time = lock;
	philo->print_mutex = print;
	while (++i < philo->nb_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
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
	t_philo				all_philos[255];
	pthread_mutex_t		forks[255];
	int		i;

	philo->thread_id = malloc(sizeof(pthread_t) * philo->nb_philo);
	if (!philo->thread_id)
		return (1);
	if (init_mutex_and_forks(philo, forks) != 0)
		return (free (philo->thread_id), 1);
	i = -1;
	while (++i < philo->nb_philo)
	{
		all_philos[i].philo_id = i + 1;
		all_philos[i].die = 0;
		all_philos[i].nb_philo = philo->nb_philo;
		all_philos[i].start_time = ft_time();
		all_philos[i].meal = 0;
		all_philos[i].time = ft_time();
		all_philos[i].time_to_eat = philo->time_to_eat;
		all_philos[i].time_to_sleep = philo->time_to_sleep;
		all_philos[i].left_chopstick = &forks[i];
		all_philos[i].right_chopstick = &forks[(i + 1) % (philo->nb_philo)];
		all_philos[i].print_mutex = philo->print_mutex;
		all_philos[i].eat_time = philo->eat_time;
		if (pthread_create(&philo->thread_id[i], NULL, routine, &all_philos[i]) != 0)
			return (free (philo->thread_id), 1);
		pthread_detach(philo->thread_id[i]);
		usleep(10);
	}
	return (check_death(philo, all_philos));
}

int	check_death(t_philo *philo, t_philo *all_philos)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < philo->nb_philo)
		{
			pthread_mutex_lock(philo->eat_time);
			if (ft_time() - all_philos[i].time > philo->time_to_die)
			{
				// pthread_mutex_lock(philo->die_m);
				// philo->die = 1;
				// pthread_mutex_unlock(philo->die_m);
				pthread_mutex_lock(philo->print_mutex);
				printf("%ld %d is died\n", ft_time() - all_philos[i].start_time, all_philos[i].philo_id);
				// i = -1;
				// while (++i < philo->nb_philo)
				// 	pthread_detach(philo->thread_id[i]);
				return (1);
			}
			if (all_philos[i].meal > philo->nb_philo * philo->nb_meals && philo->nb_meals)
			{
				pthread_mutex_unlock(philo->eat_time);
						i = -1;
				while (++i < philo->nb_philo)
					pthread_detach(philo->thread_id[i]);
				return (1);
			}
			pthread_mutex_unlock(philo->eat_time);
			usleep(200);
		}
	}
}
