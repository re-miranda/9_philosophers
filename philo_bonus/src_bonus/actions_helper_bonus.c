/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_helper_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:04:10 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/20 23:36:26 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	print_time_str(t_philo_info *info_ptr, int philo_id, char *str)
{
	t_tv		tv;
	t_tv		start_tv;
	long int	e_time;

	sem_wait(info_ptr->print_sem);
	gettimeofday(&tv, NULL);
	start_tv = info_ptr->start_tv;
	e_time = elapsed_time(&start_tv, &tv);
	printf("%ld %i %s\n", e_time, philo_id, str);
	sem_post(info_ptr->print_sem);
}

void	get_fork_pair(t_philo_info *info_ptr, int philo_id)
{
	sem_wait(info_ptr->forks_sem);
	print_time_str(info_ptr, philo_id, "has taken a fork");
	sem_wait(info_ptr->forks_sem);
	print_time_str(info_ptr, philo_id, "has taken a fork");
}

void	release_fork_pair(t_philo_info *info_ptr)
{
	sem_post(info_ptr->forks_sem);
	sem_post(info_ptr->forks_sem);
}

int	set_meal_tv(t_philo_info *info_ptr, int philo_id)
{
	t_tv		tv;
	long int	e_time;

	gettimeofday(&tv, NULL);
	e_time = elapsed_time(&info_ptr->health_data[philo_id].meal_tv, &tv);
	if (e_time > info_ptr->args.time_to_die)
	{
		interrupt_simulation(info_ptr, philo_id, tv);
		return (-1);
	}
	if (info_ptr->health_data[philo_id].meal_count > 0 )
		info_ptr->health_data[philo_id].meal_count--;
	info_ptr->health_data[philo_id].meal_tv.tv_sec = tv.tv_sec;
	info_ptr->health_data[philo_id].meal_tv.tv_usec = tv.tv_usec;
	return (0);
}

long int	elapsed_time(t_tv *past, t_tv *present)
{
	long int	result_mseconds;

	result_mseconds = (present->tv_sec - past->tv_sec) * 1000;
	result_mseconds += (present->tv_usec - past->tv_usec) / 1000;
	return (result_mseconds);
}
