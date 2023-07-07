/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:56 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/05 01:49:34 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define USEC_DIVISOR 1

typedef struct s_philo_philo {
	int	philosopher_id;
	int	is_holding_2_forks;
	int	time_since_last_meal;
	int	number_of_meals;
}	t_philo_philo;

typedef struct s_philo_args {
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	has_fifth;
	int	number_of_times_each_philosopher_must_eat;
}	t_philo_args;

typedef struct s_philo_info {
	t_philo_args	args;
	int				index;
	pthread_mutex_t	index_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	pthread_t		*tdata;
	struct timeval	start_tv;
}	t_philo_info;

#endif
