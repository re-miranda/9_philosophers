/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:52 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/21 19:35:26 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	main(int argc, char *argv[])
{
	t_philo_info	*info_ptr;

	info_ptr = ft_calloc(sizeof(t_philo_info), 1);
	if (!info_ptr)
		return (-1);
	if (parse_input(argc, argv, info_ptr))
		return (early_destroy(info_ptr, -1));
	if (init(info_ptr))
		return (early_destroy(info_ptr, -1));
	if (launch_forks(info_ptr))
		return (early_destroy(info_ptr, -1));
	if (join_forks(info_ptr))
		return (early_destroy(info_ptr, -1));
	early_destroy(info_ptr, 0);
	return (0);
}
