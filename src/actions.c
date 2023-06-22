/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:04:10 by rmiranda          #+#    #+#             */
/*   Updated: 2023/06/21 17:36:51 by rmiranda         ###   ########.fr       */
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
	pthread_mutex_lock(mutex);
	ft_putendl_fd("Philosopher is thinking", 1);
	pthread_mutex_unlock(mutex);
	while (get_fork_pair())
		continue ;
}

void	philo_eat(void *mutex)
{
	pthread_mutex_lock(mutex);
	ft_putendl_fd("Philosopher is eating", 1);
	pthread_mutex_unlock(mutex);
	usleep(1000000);
	release_fork_pair();
}

void	philo_sleep(void *mutex)
{
	pthread_mutex_lock(mutex);
	ft_putendl_fd("Philosopher is sleeping", 1);
	pthread_mutex_unlock(mutex);
	usleep(1000000);
}
