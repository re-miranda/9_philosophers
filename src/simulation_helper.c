/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 23:35:19 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/14 23:38:39 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	assert_simulation_is_running(t_philo_info *info_ptr)
{
	int	return_value;

	pthread_mutex_lock(&info_ptr->simulation_mutex);
	return_value = info_ptr->simulation_continue;
	pthread_mutex_unlock(&info_ptr->simulation_mutex);
	return (return_value);
}

long int	elapsed_time(struct timeval *past, struct timeval *present)
{
	long int	result_mseconds;

	result_mseconds = (present->tv_sec - past->tv_sec) * 1000;
	result_mseconds += (present->tv_usec - past->tv_usec) / 1000;
	return (result_mseconds);
}
