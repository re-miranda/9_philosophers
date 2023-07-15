/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:56 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/14 22:20:40 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define GLOBAL_USLEEP 100

typedef struct s_philo_health {
	struct timeval	start_tv;
	struct timeval	meal_tv;
	int	meal_count;
}	t_philo_health;

typedef struct s_philo_args {
	int	nb_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	has_fifth;
	int	number_of_times_each_philosopher_must_eat;
}	t_philo_args;

typedef struct s_philo_info {
	int				index;
	int				print_allowed;
	int				simulation_continue;
	pthread_mutex_t	index_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	simulation_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*health_data_mutex;
	pthread_t		*tdata;
	t_philo_args	args;
	t_philo_health	*health_data;
}	t_philo_info;

#endif
