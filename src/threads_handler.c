/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:52 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/18 23:10:00 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	early_destroy(t_philo_info *info_ptr, int return_value)
{
	int	index;

	index = 0;
	if (info_ptr->forks)
		while (index < info_ptr->args.nb_of_philo)
			pthread_mutex_destroy(&info_ptr->forks[index++]);
	index = 0;
	if (info_ptr->health_mtx)
		while (index < info_ptr->args.nb_of_philo)
			pthread_mutex_destroy(&info_ptr->health_mtx[index++]);
	pthread_mutex_destroy(&info_ptr->index_mutex);
	pthread_mutex_destroy(&info_ptr->print_mutex);
	if (info_ptr->forks)
		free(info_ptr->forks);
	if (info_ptr->health_mtx)
		free(info_ptr->health_mtx);
	if (info_ptr->health_data)
		free(info_ptr->health_data);
	if (info_ptr->tdata)
		free(info_ptr->tdata);
	if (info_ptr)
		free(info_ptr);
	return (return_value);
}

int	launch_threads(t_philo_info *info_ptr)
{
	int			index;
	pthread_t	*tdata;

	index = 0;
	tdata = info_ptr->tdata;
	while (index < info_ptr->args.nb_of_philo)
		if (pthread_create(&tdata[index++], NULL, &philo_brain, info_ptr))
			return (-1);
	// index = 0;
	// while (index < info_ptr->args.nb_of_philo)
	// 	if (pthread_detach(tdata[index++]))
	// 		return (-1);
	return (0);
}

int	join_threads(t_philo_info info)
{
	int	index;

	index = 0;
	while (index < info.args.nb_of_philo)
		if (pthread_join(info.tdata[index++], NULL))
			return (-1);
	return (0);
}
