/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:04:10 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/15 00:20:34 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	get_fork_pair(t_philo_info *info_ptr, int philo_id)
{
	if (philo_id % 2)
		pthread_mutex_lock(&info_ptr->forks[philo_id]);
	if (philo_id + 1 != info_ptr->args.nb_of_philos)
		pthread_mutex_lock(&info_ptr->forks[philo_id + 1]);
	else
		pthread_mutex_lock(&info_ptr->forks[0]);
	if (!philo_id % 2)
		pthread_mutex_lock(&info_ptr->forks[philo_id]);
}

static void	set_meal_tv(t_philo_info *info_ptr, int philo_id)
{
	pthread_mutex_lock(&info_ptr->health_data_mutex[philo_id]);
	gettimeofday(&info_ptr->health_data[philo_id].meal_tv, NULL);
	pthread_mutex_unlock(&info_ptr->health_data_mutex[philo_id]);
}

static void	release_fork_pair(t_philo_info *info_ptr, int philo_id)
{
	if (philo_id + 1 != info_ptr->args.nb_of_philos)
		pthread_mutex_unlock(&info_ptr->forks[philo_id + 1]);
	else
		pthread_mutex_unlock(&info_ptr->forks[0]);
	pthread_mutex_unlock(&info_ptr->forks[philo_id]);
}

void	philo_think(t_philo_info *info_ptr, int philo_id)
{
	struct timeval	tv;

	if (!assert_simulation_is_running(info_ptr))
		return ;
	usleep(GLOBAL_USLEEP);
	pthread_mutex_lock(&info_ptr->print_mutex);
	gettimeofday(&tv, NULL);
	if (assert_simulation_is_running(info_ptr))
		printf("%ld: ", elapsed_time(&info_ptr->health_data[philo_id].start_tv, &tv));
	if (assert_simulation_is_running(info_ptr))
		printf("Philosopher %i is thinking\n", philo_id);
	pthread_mutex_unlock(&info_ptr->print_mutex);
}

void	philo_eat(t_philo_info *info_ptr, int philo_id)
{
	struct timeval	got_fork_tv;
	struct timeval	tv;

	if (!assert_simulation_is_running(info_ptr))
		return ;
	usleep(GLOBAL_USLEEP);
	get_fork_pair(info_ptr, philo_id);
	pthread_mutex_lock(&info_ptr->print_mutex);
	gettimeofday(&got_fork_tv, NULL);
	gettimeofday(&tv, NULL);
	if (assert_simulation_is_running(info_ptr))
		printf("%ld: ", elapsed_time(&info_ptr->health_data[philo_id].start_tv, &tv));
	if (assert_simulation_is_running(info_ptr))
		printf("Philosopher %i is eating\n", philo_id);
	pthread_mutex_unlock(&info_ptr->print_mutex);
	while (assert_simulation_is_running(info_ptr) && elapsed_time(&got_fork_tv, &tv) < (long int)info_ptr->args.time_to_eat)
	{
		gettimeofday(&tv, NULL);
		usleep(GLOBAL_USLEEP);
	}
	set_meal_tv(info_ptr, philo_id);
	release_fork_pair(info_ptr, philo_id);
}

void	philo_sleep(t_philo_info *info_ptr, int philo_id)
{
	struct timeval	sleep_start_tv;
	struct timeval	tv;

	if (!assert_simulation_is_running(info_ptr))
		return ;
	usleep(GLOBAL_USLEEP);
	gettimeofday(&sleep_start_tv, NULL);
	pthread_mutex_lock(&info_ptr->print_mutex);
	gettimeofday(&tv, NULL);
	if (assert_simulation_is_running(info_ptr))
		printf("%ld: ", elapsed_time(&info_ptr->health_data[philo_id].start_tv, &tv));
	if (assert_simulation_is_running(info_ptr))
		printf("Philosopher %i is sleeping\n", philo_id);
	pthread_mutex_unlock(&info_ptr->print_mutex);
	while (assert_simulation_is_running(info_ptr) && elapsed_time(&sleep_start_tv, &tv) < (long int)info_ptr->args.time_to_sleep)
	{
		gettimeofday(&tv, NULL);
		usleep(GLOBAL_USLEEP);
	}
}
