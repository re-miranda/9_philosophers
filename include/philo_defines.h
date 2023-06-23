/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_defines.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:56 by rmiranda          #+#    #+#             */
/*   Updated: 2023/06/08 10:06:03 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_DEFINES_H
# define PHILO_DEFINES_H

typedef struct	s_philo_info {
	t_philo_args	args;
	t_pthread_mutex	print_mutex;
	t_pthread_mutex	*forks;
}	t_philo_info;

typedef struct	s_philo_args {
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	has_fifth;
	int	number_of_times_each_philosopher_must_eat;
}	t_philo_args;

#endif
