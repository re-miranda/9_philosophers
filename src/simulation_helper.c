/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 23:35:19 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/18 22:39:28 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	hold_supervisor(t_philo_info *info_ptr);
static int	update_simulation_status(t_philo_info *info_ptr, int *check_amount);
static void	interrupt_simulation(t_philo_info *info_ptr, int *int_flag);

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
	if (!active_philosophers_count)
		printf("Everyone have eatten their quota.\n");
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
	static int		philo_id;
	static long int	elapsed_time;
	static t_tv		tv;

	philo_id = info_ptr->args.nb_of_philo;
	check_amount[0] = 0;
	while (philo_id-- && !interrupt_flag)
	{
		if (info_ptr->health_data[philo_id].meal_count != 0)
		{
			check_amount[0]++;
			pthread_mutex_lock(&info_ptr->health_mtx[philo_id]);
			gettimeofday(&tv, NULL);
			elapsed_time = get_elapsed_time(&info_ptr->health_data[philo_id].meal_tv, &tv);
			if (elapsed_time > info_ptr->args.time_to_die)
			{
				interrupt_simulation(info_ptr, &interrupt_flag);
				elapsed_time = get_elapsed_time(&info_ptr->health_data[philo_id].start_tv, &tv);
				printf("%ld %i died\n", elapsed_time, philo_id);
			}
			pthread_mutex_unlock(&info_ptr->health_mtx[philo_id]);
		}
	}
	return (interrupt_flag);
}

static void	interrupt_simulation(t_philo_info *info_ptr, int *int_flag)
{
	pthread_mutex_lock(&info_ptr->print_mutex);
	pthread_mutex_lock(&info_ptr->simulation_mutex);
	info_ptr->print_allowed = 0;
	info_ptr->simulation_continue = 0;
	pthread_mutex_unlock(&info_ptr->simulation_mutex);
	pthread_mutex_unlock(&info_ptr->print_mutex);
	int_flag[0]++;
}
