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
	if (philo_id % 2)
		pthread_mutex_lock(&info_ptr->forks[philo_id]);
	if (philo_id + 1 != info_ptr->args.number_of_philosophers)
		pthread_mutex_lock(&info_ptr->forks[philo_id + 1]);
	else
		pthread_mutex_lock(&info_ptr->forks[0]);
	if (!philo_id % 2)
		pthread_mutex_lock(&info_ptr->forks[philo_id]);
}

static void	release_fork_pair(t_philo_info *info_ptr, int philo_id)
{
	if (philo_id + 1 != info_ptr->args.number_of_philosophers)
		pthread_mutex_unlock(&info_ptr->forks[philo_id + 1]);
	else
		pthread_mutex_unlock(&info_ptr->forks[0]);
	pthread_mutex_unlock(&info_ptr->forks[philo_id]);
}

void	philo_think(t_philo_info *info_ptr, int philo_id)
{
	struct timeval	tv;

	pthread_mutex_lock(&info_ptr->print_mutex);
	gettimeofday(&tv, NULL);
	printf("%ld Philosopher %i is thinking\n", elapsed_time_in_msec(info_ptr, tv), philo_id);
	pthread_mutex_unlock(&info_ptr->print_mutex);
	get_fork_pair(info_ptr, philo_id);
}

void	philo_eat(t_philo_info *info_ptr, int philo_id)
{
	struct timeval	tv;

	pthread_mutex_lock(&info_ptr->print_mutex);
	gettimeofday(&tv, NULL);
	printf("%ld Philosopher %i is eating\n", elapsed_time_in_msec(info_ptr, tv), philo_id);
	pthread_mutex_unlock(&info_ptr->print_mutex);
	usleep(info_ptr->args.time_to_eat);
	release_fork_pair(info_ptr, philo_id);
}

void	philo_sleep(t_philo_info *info_ptr, int philo_id)
{
	struct timeval	tv;

	pthread_mutex_lock(&info_ptr->print_mutex);
	gettimeofday(&tv, NULL);
	printf("%ld Philosopher %i is sleeping\n", elapsed_time_in_msec(info_ptr, tv), philo_id);
	pthread_mutex_unlock(&info_ptr->print_mutex);
	usleep(info_ptr->args.time_to_sleep);
}
