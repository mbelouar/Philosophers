/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:53:47 by mbelouar          #+#    #+#             */
/*   Updated: 2023/05/21 23:56:14 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_philo {
	int				philo_id;
	int				nb_philo;
	int				nb_meals;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				thread_index;
	long			start_time;
	long			time;
	pthread_t		*thread_id;
	pthread_mutex_t **forks;
	pthread_mutex_t	*left_chopstick;
	pthread_mutex_t	*right_chopstick;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*eat_time;
}	t_philo;


int				check_args_and_stock(t_philo *philo, int ac, char **av);
int				ft_atoi(const char *str);
unsigned long	ft_time();
int				init_mutex(t_philo *philo);
// void			ft_free(char **arr);
int				create_threads(t_philo *philo);
void			ft_eating(t_philo *philo);

#endif
