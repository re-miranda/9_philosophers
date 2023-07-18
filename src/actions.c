/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:04:10 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/18 16:56:33 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	philo_think(t_philo_info *info_ptr, int philo_id)
{
	print_time_str(info_ptr, philo_id, "is thinking");
}

void	philo_eat(t_philo_info *info_ptr, int philo_id)
{
	struct timeval	got_fork_tv;
	struct timeval	tv;

	if (!assert_simulation_is_running(info_ptr))
		return ;
	usleep(GLOBAL_USLEEP);
	get_fork_pair(info_ptr, philo_id);
	gettimeofday(&got_fork_tv, NULL);
	gettimeofday(&tv, NULL);
	print_time_str(info_ptr, philo_id, "is eating");
	while (get_elapsed_time(&got_fork_tv, &tv) < (long int)info_ptr->args.time_to_eat)
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

	gettimeofday(&sleep_start_tv, NULL);
	gettimeofday(&tv, NULL);
	print_time_str(info_ptr, philo_id, "is sleeping");
	while (get_elapsed_time(&sleep_start_tv, &tv) < (long int)info_ptr->args.time_to_sleep)
	{
		gettimeofday(&tv, NULL);
		usleep(GLOBAL_USLEEP);
	}
}
