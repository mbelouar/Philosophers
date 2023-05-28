/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:53:27 by mbelouar          #+#    #+#             */
/*   Updated: 2023/05/22 01:23:22 by mbelouar         ###   ########.fr       */
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
