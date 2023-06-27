/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:04:10 by rmiranda          #+#    #+#             */
/*   Updated: 2023/06/27 19:55:20 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	get_fork_pair(void)
{
	return (0);
}

static void	release_fork_pair(void)
{
	return ;
}

void	philo_think(void *mutex)
{
	struct timeval	tv;

	pthread_mutex_lock(mutex);
	gettimeofday(&tv, NULL);
	printf("%li Philosopher is thinking\n", tv.tv_usec / 1000);
	pthread_mutex_unlock(mutex);
	while (get_fork_pair())
		continue ;
}

void	philo_eat(void *mutex)
{
	pthread_mutex_lock(mutex);
	printf("Philosopher is eating\n");
	pthread_mutex_unlock(mutex);
	usleep(1000000);
	release_fork_pair();
}

void	philo_sleep(void *mutex)
{
	pthread_mutex_lock(mutex);
	printf("Philosopher is sleeping\n");
	pthread_mutex_unlock(mutex);
	usleep(1000000);
}
