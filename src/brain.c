/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:52 by rmiranda          #+#    #+#             */
/*   Updated: 2023/06/27 17:50:19 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	assert_is_alive(void *mutex)
{
	static int	counter;

	pthread_mutex_lock(mutex);
	if (counter++ > 9)
	{
		pthread_mutex_unlock(mutex);
		return (0);
	}
	pthread_mutex_unlock(mutex);
	return (1);
}

void	*philo_brain(void *mutex)
{
	while (assert_is_alive(mutex))
	{
		philo_think(mutex);
		philo_eat(mutex);
		philo_sleep(mutex);
		pthread_mutex_lock(mutex);
		ft_putendl_fd("end of brain while block", 1);
		pthread_mutex_unlock(mutex);
	}
	return (NULL);
}
