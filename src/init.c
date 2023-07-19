/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 02:01:10 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/18 22:00:56 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	init_health_data(t_philo_info *info_ptr);
static int	init_mutex(t_philo_info *info_ptr);

int	init(t_philo_info *info_ptr)
{
	info_ptr->health_data = NULL;
	info_ptr->forks = NULL;
	info_ptr->tdata = NULL;
	if (init_health_data(info_ptr))
		return (-1);
	if (init_mutex(info_ptr))
		return (early_destroy(info_ptr, -1));
	info_ptr->tdata = malloc(sizeof(pthread_t) * info_ptr->args.nb_of_philos);
	if (!info_ptr->tdata)
		return (early_destroy(info_ptr, -1));
	return (0);
}

static int	init_health_data(t_philo_info *info_ptr)
{
	int	index;
	int	meal_arg;

	index = 0;
	info_ptr->health_data = ft_calloc(sizeof(t_philo_health), info_ptr->args.nb_of_philos);
	if (!info_ptr->health_data)
		return (-1);
	if (info_ptr->args.has_fifth)
		meal_arg = info_ptr->args.meals_quota;
	else
		meal_arg = -1;
	while (index < info_ptr->args.nb_of_philos)
		info_ptr->health_data[index++].meal_count = meal_arg;
	return (0);
}

static int	init_mutex(t_philo_info *info_ptr)
{
	info_ptr->index = 0;
	info_ptr->print_allowed = 1;
	info_ptr->simulation_continue = 1;
	if (pthread_mutex_init(&info_ptr->index_mutex, NULL))
		return (-1);
	if (pthread_mutex_init(&info_ptr->print_mutex, NULL))
		return (-1);
	if (pthread_mutex_init(&info_ptr->simulation_mutex, NULL))
		return (-1);
	info_ptr->forks = malloc(sizeof(pthread_mutex_t) * info_ptr->args.nb_of_philos);
	if (!info_ptr->forks)
		return (-1);
	while (info_ptr->index < info_ptr->args.nb_of_philos)
		if (pthread_mutex_init(&info_ptr->forks[info_ptr->index++], NULL))
			return (-1);
	info_ptr->index = 0;
	info_ptr->health_data_mutex = malloc(sizeof(pthread_mutex_t) * info_ptr->args.nb_of_philos);
	if (!info_ptr->health_data_mutex)
		return (-1);
	while (info_ptr->index < info_ptr->args.nb_of_philos)
		if (pthread_mutex_init(&info_ptr->health_data_mutex[info_ptr->index++], NULL))
			return (-1);
	info_ptr->index = 0;
	return (0);
}
