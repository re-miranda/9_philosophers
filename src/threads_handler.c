/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:52 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/14 23:38:29 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_philo_info *info_ptr)
{
	int	index;

	index = 0;
	info_ptr->index = 0;
	info_ptr->print_allowed = 1;
	info_ptr->simulation_continue = 1;
	if (pthread_mutex_init(&info_ptr->index_mutex, NULL))
		return (-1);
	if (pthread_mutex_init(&info_ptr->print_mutex, NULL))
		return (-1);
	if (pthread_mutex_init(&info_ptr->simulation_mutex, NULL))
		return (-1);
	info_ptr->forks = malloc(sizeof(pthread_mutex_t) * info_ptr->args.nb_of_philos);
	if (!info_ptr->forks)
		return (-1);
	while (index < info_ptr->args.nb_of_philos)
		if (pthread_mutex_init(&info_ptr->forks[index++], NULL))
			return (-1);
	index = 0;
	info_ptr->health_data_mutex = malloc(sizeof(pthread_mutex_t) * info_ptr->args.nb_of_philos);
	if (!info_ptr->health_data_mutex)
		return (-1);
	while (index < info_ptr->args.nb_of_philos)
		if (pthread_mutex_init(&info_ptr->health_data_mutex[index++], NULL))
			return (-1);
	return (0);
}

int	early_destroy(t_philo_info info, int return_value)
{
	int	index;

	index = 0;
	pthread_mutex_destroy(&info.index_mutex);
	pthread_mutex_destroy(&info.print_mutex);
	while (index < info.args.nb_of_philos && info.forks)
		pthread_mutex_destroy(&info.forks[index++]);
	index = 0;
	while (index < info.args.nb_of_philos && info.health_data_mutex)
		pthread_mutex_destroy(&info.health_data_mutex[index++]);
	if (info.health_data)
		free(info.health_data);
	if (info.forks)
		free(info.forks);
	if (info.tdata)
		free(info.tdata);
	if (info.health_data_mutex)
		free(info.health_data_mutex);
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
