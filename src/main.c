/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:52 by rmiranda          #+#    #+#             */
/*   Updated: 2023/06/27 17:50:02 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo_info	info;

	info.forks = NULL;
	info.tdata = NULL;
	if (parse_input(argc, argv, &info))
		return (-1);
	if (init_mutex(&info))
		return (-1);
	info.tdata = malloc(sizeof(pthread_t) * info.args.number_of_philosophers);
	if (!info.tdata)
		return (early_destroy(info, -1));
	gettimeofday(&info.start_tv, NULL);
	if (launch_threads(&info))
		return (early_destroy(info, -1));
	if (join_threads(info))
		return (early_destroy(info, -1));
	early_destroy(info, 0);
	return (0);
}

