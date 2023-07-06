/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:52 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/05 01:50:54 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_philo_info *info_ptr)
{
	int	index;

	index = 0;
	info_ptr->index = 0;
	if (pthread_mutex_init(&info_ptr->index_mutex, NULL))
		return (-1);
	if (pthread_mutex_init(&info_ptr->print_mutex, NULL))
		return (-1);
	info_ptr->forks = malloc(sizeof(pthread_mutex_t) * info_ptr->args.number_of_philosophers);
	if (!info_ptr->forks)
		return (-1);
	while (index < info_ptr->args.number_of_philosophers)
		if (pthread_mutex_init(&info_ptr->forks[index++], NULL))
			return (-1);
	return (0);
}

int	init_destroy(t_philo_info info, int return_value)
{
	pthread_mutex_destroy(&info.print_mutex);
	if (info.forks)
		free(info.forks);
	if (info.tdata)
		free(info.tdata);
	return (return_value);
}

int	launch_threads(t_philo_info *info)
{
	int	index;

	index = 0;
	while (index < info->args.number_of_philosophers)
		if (pthread_create(&info->tdata[index++], NULL, &philo_brain, (void *)info))
			return (-1);
	return (0);
}

int	join_threads(t_philo_info info)
{
	int	index;

	index = 0;
	while (index < info.args.number_of_philosophers)
		if (pthread_join(info.tdata[index++], NULL))
			return (-1);
	return (0);
}

