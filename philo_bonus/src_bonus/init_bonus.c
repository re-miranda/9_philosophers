/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 02:01:10 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/19 23:10:42 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static int	init_health_data(t_philo_info *info_ptr);
static int	init_mutex(t_philo_info *info_ptr);

int	init(t_philo_info *info_ptr)
{
	info_ptr->health_data = NULL;
	info_ptr->forks = NULL;
	info_ptr->tdata = NULL;
	info_ptr->index = 0;
	info_ptr->print_allowed = 1;
	info_ptr->simulation_continue = 1;
	if (init_health_data(info_ptr))
		return (-1);
	if (init_mutex(info_ptr))
		return (early_destroy(info_ptr, -1));
	info_ptr->tdata = malloc(sizeof(pthread_t) * info_ptr->args.nb_of_philo);
	if (!info_ptr->tdata)
		return (early_destroy(info_ptr, -1));
	return (0);
}

static int	init_health_data(t_philo_info *info_ptr)
{
	int	index;
	int	meal_arg;
	int	nb_of_philo;

	index = 0;
	nb_of_philo = info_ptr->args.nb_of_philo;
	info_ptr->health_data = ft_calloc(sizeof(t_philo_health), nb_of_philo);
	if (!info_ptr->health_data)
		return (-1);
	if (info_ptr->args.has_fifth)
		meal_arg = info_ptr->args.meals_quota;
	else
		meal_arg = -1;
	while (index < info_ptr->args.nb_of_philo)
		info_ptr->health_data[index++].meal_count = meal_arg;
	return (0);
}

static int	init_mutex(t_philo_info *info)
{
	if (pthread_mutex_init(&info->index_mutex, NULL))
		return (-1);
	if (pthread_mutex_init(&info->print_mutex, NULL))
		return (-1);
	if (pthread_mutex_init(&info->simulation_mutex, NULL))
		return (-1);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->args.nb_of_philo);
	if (!info->forks)
		return (-1);
	while (info->index < info->args.nb_of_philo)
		if (pthread_mutex_init(&info->forks[info->index++], NULL))
			return (-1);
	info->index = 0;
	info->health_mtx = malloc(sizeof(pthread_mutex_t) * info->args.nb_of_philo);
	if (!info->health_mtx)
		return (-1);
	while (info->index < info->args.nb_of_philo)
		if (pthread_mutex_init(&info->health_mtx[info->index++], NULL))
			return (-1);
	info->index = 0;
	return (0);
}
