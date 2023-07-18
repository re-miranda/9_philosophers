/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:52 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/15 02:57:41 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	early_destroy(t_philo_info *info_ptr, int return_value)
{
	int	index;

	index = 0;
	if (info_ptr->forks)
		while (index < info_ptr->args.nb_of_philos)
			pthread_mutex_destroy(&info_ptr->forks[index++]);
	index = 0;
	if (info_ptr->health_data_mutex)
		while (index < info_ptr->args.nb_of_philos)
			pthread_mutex_destroy(&info_ptr->health_data_mutex[index++]);
	pthread_mutex_destroy(&info_ptr->index_mutex);
	pthread_mutex_destroy(&info_ptr->print_mutex);
	if (info_ptr->forks)
		free(info_ptr->forks);
	if (info_ptr->health_data_mutex)
		free(info_ptr->health_data_mutex);
	if (info_ptr->health_data)
		free(info_ptr->health_data);
	if (info_ptr->tdata)
		free(info_ptr->tdata);
	if (info_ptr)
		free(info_ptr);
	return (return_value);
}

int	launch_threads(t_philo_info *info)
{
	int	index;

	index = 0;
	while (index < info->args.nb_of_philos)
		if (pthread_create(&info->tdata[index++], NULL, &philo_brain, (void *)info))
			return (-1);
	index = 0;
	// while (index < info->args.nb_of_philos)
	// 	if (pthread_detach(info->tdata[index++]))
	// 		return (-1);
	return (0);
}

int	join_threads(t_philo_info info)
{
	int	index;

	index = 0;
	while (index < info.args.nb_of_philos)
		if (pthread_join(info.tdata[index++], NULL))
			return (-1);
	return (0);
}
