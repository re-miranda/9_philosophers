/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_helper_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 23:35:19 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/19 23:10:55 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static int	hold_supervisor(t_philo_info *info_ptr);
static int	update_simulation_status(t_philo_info *info_ptr, int *check_amount);
static int	interrupt_simulation(t_philo_info *info_ptr);

int	assert_simulation_is_running(t_philo_info *info_ptr)
{
	int	return_value;

	pthread_mutex_lock(&info_ptr->simulation_mutex);
	return_value = info_ptr->simulation_continue;
	pthread_mutex_unlock(&info_ptr->simulation_mutex);
	return (return_value);
}

void	supervise_philosophers(t_philo_info *info_ptr)
{
	int				active_philosophers_count;

	while (hold_supervisor(info_ptr))
		usleep(GLOBAL_USLEEP);
	active_philosophers_count = 1;
	while (active_philosophers_count)
	{
		if (!assert_simulation_is_running(info_ptr))
			break ;
		usleep(5000);
		if (update_simulation_status(info_ptr, &active_philosophers_count))
			break ;
	}
}

static int	hold_supervisor(t_philo_info *info_ptr)
{
	int	value;

	value = 1;
	pthread_mutex_lock(&info_ptr->index_mutex);
	if (info_ptr->index >= info_ptr->args.nb_of_philo)
		value = 0;
	pthread_mutex_unlock(&info_ptr->index_mutex);
	return (value);
}

static int	update_simulation_status(t_philo_info *info_ptr, int *check_amount)
{
	static int		interrupt_flag;
	static int		id;
	static long int	e_time;
	static t_tv		tv;

	id = info_ptr->args.nb_of_philo;
	check_amount[0] = 0;
	while (id-- && !interrupt_flag)
	{
		pthread_mutex_lock(&info_ptr->health_mtx[id]);
		if (info_ptr->health_data[id].meal_count != 0)
		{
			check_amount[0]++;
			gettimeofday(&tv, NULL);
			e_time = elapsed_time(&info_ptr->health_data[id].meal_tv, &tv);
			if (e_time > info_ptr->args.time_to_die)
			{
				interrupt_flag = interrupt_simulation(info_ptr);
				e_time = elapsed_time(&info_ptr->health_data[id].start_tv, &tv);
				printf("%ld %i died\n", e_time, id);
			}
		}
		pthread_mutex_unlock(&info_ptr->health_mtx[id]);
	}
	return (interrupt_flag);
}

static int	interrupt_simulation(t_philo_info *info_ptr)
{
	pthread_mutex_lock(&info_ptr->print_mutex);
	pthread_mutex_lock(&info_ptr->simulation_mutex);
	info_ptr->print_allowed = 0;
	info_ptr->simulation_continue = 0;
	pthread_mutex_unlock(&info_ptr->simulation_mutex);
	pthread_mutex_unlock(&info_ptr->print_mutex);
	return (1);
}
