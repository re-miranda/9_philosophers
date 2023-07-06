/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:52 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/05 03:42:58 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	assert_is_alive(void)
{
	static int	counter;

	if (counter++ > 30)
		return (0);
	return (1);
}

static int	reserve_id(t_philo_info *info_ptr)
{
	int	current_index;

	if (pthread_mutex_lock(&info_ptr->index_mutex))
		printf("HERE\n");
	current_index = info_ptr->index++;
	pthread_mutex_unlock(&info_ptr->index_mutex);
	return (current_index);
}

static void	announce_id(t_philo_info *info_ptr, int philo_id)
{
	pthread_mutex_lock(&info_ptr->print_mutex);
	printf("Philosopher %i was created.\n", philo_id);
	pthread_mutex_unlock(&info_ptr->print_mutex);
}

void	*philo_brain(void *info_void_ptr)
{
	t_philo_info	*info_ptr;
	int				philo_id;

	info_ptr = (t_philo_info *)info_void_ptr;
	philo_id = reserve_id(info_ptr);
	announce_id(info_ptr, philo_id);
	while (assert_is_alive())
	{
		philo_think(info_ptr, philo_id);
		philo_eat(info_ptr, philo_id);
		philo_sleep(info_ptr, philo_id);
	}
	return (NULL);
}
