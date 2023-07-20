/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:04:10 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/19 23:08:37 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static void	wait_dinner(t_philo_info *info_ptr, t_tv tv1, t_tv tv2);
static void	wait_sleep(t_philo_info *info_ptr, t_tv tv1, t_tv tv2);

void	philo_think(t_philo_info *info_ptr, int philo_id)
{
	print_time_str(info_ptr, philo_id, "is thinking");
}

void	philo_eat(t_philo_info *info_ptr, int philo_id)
{
	t_tv	got_fork_tv;
	t_tv	tv;

	usleep(GLOBAL_USLEEP);
	get_fork_pair(info_ptr, philo_id);
	if (!assert_simulation_is_running(info_ptr))
	{
		release_fork_pair(info_ptr, philo_id);
		return ;
	}
	gettimeofday(&got_fork_tv, NULL);
	gettimeofday(&tv, NULL);
	print_time_str(info_ptr, philo_id, "is eating");
	wait_dinner(info_ptr, got_fork_tv, tv);
	release_fork_pair(info_ptr, philo_id);
	set_meal_tv(info_ptr, philo_id);
}

void	philo_sleep(t_philo_info *info_ptr, int philo_id)
{
	t_tv	sleep_start_tv;
	t_tv	tv;

	gettimeofday(&sleep_start_tv, NULL);
	gettimeofday(&tv, NULL);
	print_time_str(info_ptr, philo_id, "is sleeping");
	wait_sleep(info_ptr, sleep_start_tv, tv);
}

static void	wait_dinner(t_philo_info *info_ptr, t_tv tv1, t_tv tv2)
{
	while (elapsed_time(&tv1, &tv2) < (long int)info_ptr->args.time_to_eat)
	{
		gettimeofday(&tv2, NULL);
		usleep(GLOBAL_USLEEP);
	}
}

static void	wait_sleep(t_philo_info *info_ptr, t_tv tv1, t_tv tv2)
{
	while (elapsed_time(&tv1, &tv2) < (long int)info_ptr->args.time_to_eat)
	{
		gettimeofday(&tv2, NULL);
		usleep(GLOBAL_USLEEP);
	}
}
