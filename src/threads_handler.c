/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:52 by rmiranda          #+#    #+#             */
/*   Updated: 2023/06/27 17:54:35 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_philo_info *info_ptr)
{
	pthread_mutex_t	*mutex_ptr;

	mutex_ptr = &info_ptr->print_mutex;
	if (pthread_mutex_init(mutex_ptr, NULL))
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
		if (pthread_create(&info->tdata[index++], NULL, &philo_brain, (void *)&info->print_mutex))
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

