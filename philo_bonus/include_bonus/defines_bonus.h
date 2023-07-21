/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:56 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/20 23:35:29 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_BONUS_H
# define DEFINES_BONUS_H

# define GLOBAL_USLEEP 100
# define USAGE_STR_0 "\nUsage: philo nb_of_philo time_to_die time_to_eat \
time_to_sleep [meals_quota]\n\nphilo: \
error: You must provide 4 or 5 arguments.\n"
# define USAGE_STR_1 "\nUsage: philo nb_of_philo time_to_die time_to_eat \
time_to_sleep [meals_quota]\n\nphilo: \
error: You must provide only numeric characters and positive values.\n"
# define USAGE_STR_2 "\nUsage: philo nb_of_philo time_to_die time_to_eat \
time_to_sleep [meals_quota]\n\nphilo: \
error: You must provide values not grater than MAX INT (2147483647).\n"

typedef struct timeval	t_tv;

typedef struct s_philo_health {
	t_tv	meal_tv;
	int		meal_count;
}	t_philo_health;

typedef struct s_philo_args {
	int	nb_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	has_fifth;
	int	meals_quota;
}	t_philo_args;

typedef struct s_philo_info {
	t_philo_args	args;
	sem_t			*forks_sem;
	sem_t			*print_sem;
	sem_t			*simulation_sem;
	int				*pid_list;
	t_tv			start_tv;
	t_philo_health	*health_data;
}	t_philo_info;

#endif
