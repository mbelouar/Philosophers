/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:53:27 by mbelouar          #+#    #+#             */
/*   Updated: 2023/05/15 04:30:47 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int ac, char **av)
{
	t_philo philo;

	if (check_args_and_stock(&philo, ac, av) || create_threads(&philo))
		return (1);
	return (0);
}

int	init_mutex(t_philo *philo)
{
	int	i;

	i = -1;
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
	philo->forks = malloc(sizeof(pthread_mutex_t *) * philo->nb_philo);
	if (!philo->forks)
		return (1);
	while (++i < philo->nb_meals)
	{
		if (pthread_mutex_init(philo->forks[i], NULL) != 0)
		{
			pthread_mutex_destroy(philo->eat_time);
			pthread_mutex_destroy(philo->print_mutex);
			return (free (philo->print_mutex), free (philo->eat_time), 1);
		}
	}
	return (0);
}

void	*routine(void	*arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->print_mutex);
	printf("\n\033[1;32m%ld %lu is thinking...\033[0m\n", philo->time, (unsigned long)philo->thread_id[philo->thread_index]);
	pthread_mutex_unlock(philo->print_mutex);
	pthread_mutex_lock(philo->left_chopstick);
	pthread_mutex_lock(philo->right_chopstick);
	printf("\n\034[1;32m%ld %lu has taken a fork\034[0m\n", philo->time, (unsigned long)philo->thread_id[philo->thread_index]);
	ft_eating(philo);
	pthread_mutex_unlock(philo->left_chopstick);
	pthread_mutex_unlock(philo->right_chopstick);

	return (NULL);
}

int	create_threads(t_philo *philo)
{
	t_philo	**all_philos;
	int		i;

	all_philos = (t_philo **)malloc(sizeof(t_philo *) * philo->nb_meals);
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
		all_philos[i]->thread_id[i] = pthread_self();
		all_philos[i]->nb_philo = philo->nb_philo;
		all_philos[i]->nb_meals = philo->nb_meals;
		all_philos[i]->time = ft_time();
		all_philos[i]->time_to_eat = philo->time_to_eat;
		all_philos[i]->time_to_sleep = philo->time_to_sleep;
		all_philos[i]->left_chopstick = philo->forks[i];
		all_philos[i]->right_chopstick = philo->forks[(i + 1) % (philo->nb_philo)];
		all_philos[i]->print_mutex = philo->print_mutex;
		all_philos[i]->eat_time = philo->eat_time;
		all_philos[i]->thread_index = i;
		if (pthread_create(&philo->thread_id[i], NULL, routine, (void *)all_philos[i]) != 0)
			return (free (all_philos), free (philo->thread_id), 1);
		sleep (200);
	}
	return (0);
}

int	check_args_and_stock(t_philo *philo, int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Invalid number of arguments\n");
		return (1);
	}
	philo->nb_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philo->nb_meals = ft_atoi(av[5]);
	else
		philo->nb_meals = 0;
	if (philo->nb_philo <= 0 || philo->nb_philo > 200 || philo->time_to_die < 0
						|| philo->time_to_eat < 0 || philo->time_to_sleep < 0)
	{
		printf("ERROR, Check the arguments\n");
		return (1);
	}
	return (0);
}
