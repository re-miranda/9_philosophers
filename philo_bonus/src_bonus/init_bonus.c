/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 02:01:10 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/20 23:36:03 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static int	init_health_data(t_philo_info *info_ptr);
static int	init_semaphores(t_philo_info *info_ptr);
static void	unlink_semaphores(void);

int	init(t_philo_info *info_ptr)
{
	if (init_health_data(info_ptr))
		return (-1);
	info_ptr->pid_list = ft_calloc(sizeof(int), info_ptr->args.nb_of_philo);
	if (!info_ptr->pid_list)
		return (early_destroy(info_ptr, -1));
	if (init_semaphores(info_ptr))
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
	info_ptr->health_data = NULL;
	info_ptr->health_data = ft_calloc(sizeof(t_philo_health), nb_of_philo);
	if (!info_ptr->health_data)
		return (-1);
	if (info_ptr->args.has_fifth)
		meal_arg = info_ptr->args.meals_quota;
	else
		meal_arg = -1;
	while (index < info_ptr->args.nb_of_philo)
	{
		info_ptr->health_data[index].meal_tv.tv_sec = 0;
		info_ptr->health_data[index].meal_tv.tv_usec = 0;
		info_ptr->health_data[index].meal_count = meal_arg;
		index++;
	}
	return (0);
}

static int	init_semaphores(t_philo_info *info)
{
	int	philo_amount;

	philo_amount = info->args.nb_of_philo;
	unlink_semaphores();
	info->print_sem = sem_open("/print_sem", O_CREAT, 0777, 1);
	if (info->print_sem == SEM_FAILED)
		return (-1);
	info->simulation_sem = sem_open("/simulation_sem", O_CREAT, 0777, 1);
	if (info->simulation_sem == SEM_FAILED)
		return (-1);
	info->forks_sem = sem_open("/forks_sem", O_CREAT, 0777, philo_amount);
	if (info->forks_sem == SEM_FAILED)
		return (-1);
	return (0);
}

static void	unlink_semaphores(void)
{
	sem_unlink("/index_sem");
	sem_unlink("/print_sem");
	sem_unlink("/simulation_sem");
	sem_unlink("/forks_sem");
	sem_unlink("/health_sem");
}
