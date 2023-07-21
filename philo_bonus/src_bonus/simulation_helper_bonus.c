/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_helper_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 23:35:19 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/21 11:07:43 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	interrupt_simulation(t_philo_info *info_ptr, int philo_id, t_tv tv)
{
	long int	e_time;

	e_time = elapsed_time(&info_ptr->start_tv, &tv);
	sem_wait(info_ptr->print_sem);
	sem_wait(info_ptr->simulation_sem);
	printf("%ld %i died\n", e_time, philo_id);
}
