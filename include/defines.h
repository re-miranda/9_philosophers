/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:56 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/18 22:28:42 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define GLOBAL_USLEEP 100
# define USAGE_STR_0 "\nUsage: philo nb_of_philos time_to_die time_to_eat \
time_to_sleep [meals_quota]\n\nphilo: \
error: You must provide 4 or 5 arguments.\n"
# define USAGE_STR_1 "\nUsage: philo nb_of_philos time_to_die time_to_eat \
time_to_sleep [meals_quota]\n\nphilo: \
error: You must provide only numeric characters.\n"
# define USAGE_STR_2 "\nUsage: philo nb_of_philos time_to_die time_to_eat \
time_to_sleep [meals_quota]\n\nphilo: \
error: You must provide values not grater than MAX INT (2147483647).\n"

typedef struct timeval t_tv;

typedef struct s_philo_health {
	t_tv	start_tv;
	t_tv	meal_tv;
	int				meal_count;
}	t_philo_health;

typedef struct s_philo_args {
	int	nb_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	has_fifth;
	int	meals_quota;
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
