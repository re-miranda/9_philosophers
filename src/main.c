/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:52 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/15 02:02:39 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	supervise_philosophers(t_philo_info *info_ptr);

int	main(int argc, char *argv[])
{
	t_philo_info	info;

	info.health_data = NULL;
	info.forks = NULL;
	info.tdata = NULL;
	if (parse_input(argc, argv, &info))
		return (-1);
	if (init_health_data(&info))
		return (-1);
	if (init_mutex(&info))
		return (early_destroy(info, -1));
	info.tdata = malloc(sizeof(pthread_t) * info.args.nb_of_philos);
	if (!info.tdata)
		return (early_destroy(info, -1));
	// pthread_mutex_lock(&info.print_mutex);
	if (launch_threads(&info))
		return (early_destroy(info, -1));
	// pthread_mutex_unlock(&info.print_mutex);
	supervise_philosophers(&info);
	if (join_threads(info))
		return (early_destroy(info, -1));
	early_destroy(info, 0);
	return (0);
}

static void	supervise_philosophers(t_philo_info *info_ptr)
{
	long int		elapsed_time_value;
	long int		time_to_die;
	int				interrupt_flag;
	int				philo_id;
	int				stop_counter;
	struct timeval	tv;

	time_to_die = info_ptr->args.time_to_die;
	interrupt_flag = 0;
	while (1)
	{
		pthread_mutex_lock(&info_ptr->index_mutex);
		if (info_ptr->index >= info_ptr->args.nb_of_philos)
			break ;
		pthread_mutex_unlock(&info_ptr->index_mutex);
		usleep(GLOBAL_USLEEP);
	}
	pthread_mutex_unlock(&info_ptr->index_mutex);
	stop_counter = 1;
	while (!interrupt_flag && stop_counter)
	{
		stop_counter = 0;
		philo_id = 0;
		while (!interrupt_flag && philo_id < info_ptr->args.nb_of_philos)
		{
			gettimeofday(&tv, NULL);
			if (info_ptr->health_data[philo_id].meal_count != 0)
			{
				stop_counter++;
				usleep(100);
				pthread_mutex_lock(&info_ptr->health_data_mutex[philo_id]);
				elapsed_time_value = elapsed_time(&info_ptr->health_data[philo_id].meal_tv, &tv);
				if (elapsed_time_value > time_to_die)
				{
					pthread_mutex_lock(&info_ptr->print_mutex);
					info_ptr->print_allowed = 0;
					printf("%ld: ", elapsed_time_value);
					printf("Philosopher %i died.\n", philo_id);
					pthread_mutex_unlock(&info_ptr->print_mutex);
					pthread_mutex_lock(&info_ptr->simulation_mutex);
					info_ptr->simulation_continue = 0;
					pthread_mutex_unlock(&info_ptr->simulation_mutex);
					interrupt_flag++;
				}
				pthread_mutex_unlock(&info_ptr->health_data_mutex[philo_id]);
			}
			philo_id++;
		}
	}
}
