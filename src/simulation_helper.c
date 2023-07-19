/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 23:35:19 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/18 21:13:21 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	update_simulation_status(t_philo_info *info_ptr, int *check_amount);

int	assert_simulation_is_running(t_philo_info *info_ptr)
{
	int	return_value;

	pthread_mutex_lock(&info_ptr->simulation_mutex);
	return_value = info_ptr->simulation_continue;
	pthread_mutex_unlock(&info_ptr->simulation_mutex);
	return (return_value);
}

long int	get_elapsed_time(struct timeval *past, struct timeval *present)
{
	long int	result_mseconds;

	result_mseconds = (present->tv_sec - past->tv_sec) * 1000;
	result_mseconds += (present->tv_usec - past->tv_usec) / 1000;
	return (result_mseconds);
}

int	hold_supervisor(t_philo_info *info_ptr)
{
	int	value;

	value = 1;
	pthread_mutex_lock(&info_ptr->index_mutex);
	if (info_ptr->index >= info_ptr->args.nb_of_philos)
		value = 0;
	pthread_mutex_unlock(&info_ptr->index_mutex);
	return (value);
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

static int	update_simulation_status(t_philo_info *info_ptr, int *check_amount)
{
	static int		interrupt_flag;
	static int				philo_id;
	static long int		elapsed_time;
	static struct timeval	tv;

	philo_id = info_ptr->args.nb_of_philos;
	check_amount[0] = 0;
	while (philo_id-- && !interrupt_flag)
	{
		if (info_ptr->health_data[philo_id].meal_count != 0)
		{
			check_amount[0]++;
			pthread_mutex_lock(&info_ptr->health_data_mutex[philo_id]);
			gettimeofday(&tv, NULL);
			elapsed_time = get_elapsed_time(&info_ptr->health_data[philo_id].meal_tv, &tv);
			if (elapsed_time > info_ptr->args.time_to_die)
			{
				pthread_mutex_lock(&info_ptr->print_mutex);
				pthread_mutex_lock(&info_ptr->simulation_mutex);
				elapsed_time = get_elapsed_time(&info_ptr->health_data[philo_id].start_tv, &tv);
				info_ptr->print_allowed = 0;
				info_ptr->simulation_continue = 0;
				printf("%ld %i died\n", elapsed_time, philo_id);
				pthread_mutex_unlock(&info_ptr->simulation_mutex);
				pthread_mutex_unlock(&info_ptr->print_mutex);
				interrupt_flag++;
			}
			pthread_mutex_unlock(&info_ptr->health_data_mutex[philo_id]);
		}
	}
	return (interrupt_flag);
}
