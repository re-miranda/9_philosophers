/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:52 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/21 06:13:04 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	philo_brain(t_philo_info *info_ptr, int id)
{
	info_ptr->health_data[id].meal_tv.tv_sec = info_ptr->start_tv.tv_sec;
	info_ptr->health_data[id].meal_tv.tv_usec = info_ptr->start_tv.tv_usec;
	if (id % 2)
		usleep(5000);
	while (info_ptr->health_data[id].meal_count != 0)
	{
		philo_think(info_ptr, id);
		philo_eat(info_ptr, id);
		if (set_meal_tv(info_ptr, id))
			return (-1);
		philo_sleep(info_ptr, id);
	}
	return (0);
}
