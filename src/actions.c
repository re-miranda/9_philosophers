/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:04:10 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/05 04:18:19 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	get_fork_pair(t_philo_info *info_ptr, int philo_id)
{
	// 0 [1,0]
	// 1 [1,2]
	// 2 [3,2]
	// 3 [3,4]
	// 4 [5,4]
	// 5 [5,6]
	// 6 [7,6]
	// 7 [7,8] if (id == number_of_philosophers) 8 = 0
	// 8 [9,8] if (id == number_of_philosophers) 9 = 0
	printf("start of philo %i", philo_id);
	if (philo_id % 2)
	{
		printf(" [%i]", philo_id);
		pthread_mutex_lock(&info_ptr->forks[philo_id]);
	}
	if (philo_id + 1 != info_ptr->args.number_of_philosophers)
	{
		printf(" [%i]", philo_id + 1);
		pthread_mutex_lock(&info_ptr->forks[philo_id + 1]);
	}
	else
	{
		printf(" [0]");
		pthread_mutex_lock(&info_ptr->forks[0]);
	}
	if (!philo_id % 2)
	{
		printf(" [%i]", philo_id);
		pthread_mutex_lock(&info_ptr->forks[philo_id]);
	}
	printf(" end of philo %i\n", philo_id);
}

static void	release_fork_pair(t_philo_info *info_ptr, int philo_id)
{
	pthread_mutex_unlock(&info_ptr->forks[philo_id + 1]);
	pthread_mutex_unlock(&info_ptr->forks[philo_id]);
	printf("released forks from philo %i\n", philo_id);
}

void	philo_think(t_philo_info *info_ptr, int philo_id)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	pthread_mutex_lock(&info_ptr->print_mutex);
	printf("%li Philosopher %i is thinking\n", tv.tv_usec / 1000, philo_id);
	pthread_mutex_unlock(&info_ptr->print_mutex);
	get_fork_pair(info_ptr, philo_id);
}

void	philo_eat(t_philo_info *info_ptr, int philo_id)
{
	pthread_mutex_lock(&info_ptr->print_mutex);
	printf("Philosopher %i is eating\n", philo_id);
	pthread_mutex_unlock(&info_ptr->print_mutex);
	usleep(info_ptr->args.time_to_eat);
	release_fork_pair(info_ptr, philo_id);
}

void	philo_sleep(t_philo_info *info_ptr, int philo_id)
{
	pthread_mutex_lock(&info_ptr->print_mutex);
	printf("Philosopher %i is sleeping\n", philo_id);
	pthread_mutex_unlock(&info_ptr->print_mutex);
	usleep(info_ptr->args.time_to_sleep);
}
