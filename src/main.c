/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:52 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/18 16:42:54 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo_info	*info_ptr;

	info_ptr = calloc(sizeof(t_philo_info), 1);
	if (!info_ptr)
		return (-1);
	if (parse_input(argc, argv, info_ptr))
		return (-1);
	if (init(info_ptr))
		return (-1);
	if (launch_threads(info_ptr))
		return (early_destroy(info_ptr, -1));
	supervise_philosophers(info_ptr);
	if (join_threads(*info_ptr))
		return (early_destroy(info_ptr, -1));
	early_destroy(info_ptr, 0);
	return (0);
}
