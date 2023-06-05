/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:53:27 by mbelouar          #+#    #+#             */
/*   Updated: 2023/06/04 23:06:13 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int ac, char **av)
{
	t_philo			philo;
	pthread_mutex_t	forks[255];

	if (check_args_and_stock(&philo, ac, av) || create_threads(&philo, forks))
		return (1);
	clear_all(&philo, forks);
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
		printf("Error, Check the arguments\n");
		return (1);
	}
	return (0);
}

void	clear_all(t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < philo->nb_philo)
		pthread_mutex_destroy(&forks[i]);
	pthread_mutex_destroy(philo->eat_time);
	pthread_mutex_destroy(philo->print_mutex);
	free(philo->thread_id);
	free(philo->eat_time);
	free(philo->print_mutex);
}
