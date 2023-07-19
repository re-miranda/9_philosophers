/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:04:10 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/18 21:31:03 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_time_str(t_philo_info *info_ptr, int philo_id, char *str)
{
	struct timeval	tv;
	struct timeval	start_tv;
	long int		elapsed_time;

	pthread_mutex_lock(&info_ptr->print_mutex);
	gettimeofday(&tv, NULL);
	start_tv = info_ptr->health_data[philo_id].start_tv;
	pthread_mutex_unlock(&info_ptr->print_mutex);
	elapsed_time = get_elapsed_time(&start_tv, &tv);
	if (assert_simulation_is_running(info_ptr))
		printf("%ld %i %s\n", elapsed_time, philo_id, str);
}

void	get_fork_pair(t_philo_info *info_ptr, int philo_id)
{
	if (philo_id % 2)
	{
		pthread_mutex_lock(&info_ptr->forks[philo_id]);
		print_time_str(info_ptr, philo_id, "has taken a fork");
	}
	if (philo_id + 1 != info_ptr->args.nb_of_philos)
	{
		pthread_mutex_lock(&info_ptr->forks[philo_id + 1]);
		print_time_str(info_ptr, philo_id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&info_ptr->forks[0]);
		print_time_str(info_ptr, philo_id, "has taken a fork");
	}
	if (!philo_id % 2)
	{
		pthread_mutex_lock(&info_ptr->forks[philo_id]);
		print_time_str(info_ptr, philo_id, "has taken a fork");
	}
}

void	release_fork_pair(t_philo_info *info_ptr, int philo_id)
{
	if (philo_id + 1 != info_ptr->args.nb_of_philos)
		pthread_mutex_unlock(&info_ptr->forks[philo_id + 1]);
	else
		pthread_mutex_unlock(&info_ptr->forks[0]);
	pthread_mutex_unlock(&info_ptr->forks[philo_id]);
}

void	set_meal_tv(t_philo_info *info_ptr, int philo_id)
{
	pthread_mutex_lock(&info_ptr->health_data_mutex[philo_id]);
	gettimeofday(&info_ptr->health_data[philo_id].meal_tv, NULL);
	pthread_mutex_unlock(&info_ptr->health_data_mutex[philo_id]);
}
