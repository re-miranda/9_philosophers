/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:52 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/19 23:10:35 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static int	meal_limit(t_philo_info *info_ptr, int philo_id)
{
	int				continue_thread;

	pthread_mutex_lock(&info_ptr->health_mtx[philo_id]);
	if (info_ptr->health_data[philo_id].meal_count > 0)
		info_ptr->health_data[philo_id].meal_count--;
	continue_thread = info_ptr->health_data[philo_id].meal_count;
	pthread_mutex_unlock(&info_ptr->health_mtx[philo_id]);
	return (continue_thread);
}

static int	init_id(t_philo_info *info_ptr)
{
	int	philo_id;

	pthread_mutex_lock(&info_ptr->index_mutex);
	philo_id = info_ptr->index++;
	pthread_mutex_lock(&info_ptr->health_mtx[philo_id]);
	gettimeofday(&info_ptr->health_data[philo_id].start_tv, NULL);
	gettimeofday(&info_ptr->health_data[philo_id].meal_tv, NULL);
	pthread_mutex_unlock(&info_ptr->health_mtx[philo_id]);
	pthread_mutex_unlock(&info_ptr->index_mutex);
	return (philo_id);
}

void	*philo_brain(void *info_void_ptr)
{
	t_philo_info	*info_ptr;
	int				philo_id;

	info_ptr = (t_philo_info *)info_void_ptr;
	philo_id = init_id(info_ptr);
	if (philo_id % 2)
		usleep(5000);
	while (assert_simulation_is_running(info_ptr))
	{
		philo_think(info_ptr, philo_id);
		philo_eat(info_ptr, philo_id);
		philo_sleep(info_ptr, philo_id);
		if (!meal_limit(info_ptr, philo_id))
			break ;
	}
	usleep(60000);
	return (NULL);
}
