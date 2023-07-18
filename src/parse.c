/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:09:26 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/18 17:03:50 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	assert_there_are_only_digits(char **str_table);

int	parse_input(int argc, char *argv[], t_philo_info *philo_info_ptr)
{
	t_philo_args	*philo_args;

	philo_args = &philo_info_ptr->args;
	if (argc != 5 && argc != 6)
	{
		printf(USAGE_STR_0);
		return (-1);
	}
	if (assert_there_are_only_digits(argv))
	{
		printf(USAGE_STR_1);
		return (-1);
	}
	if (ft_atoi_safe(argv[1], &philo_args->nb_of_philos)
		|| (ft_atoi_safe(argv[2], &philo_args->time_to_die))
		|| (ft_atoi_safe(argv[3], &philo_args->time_to_eat))
		|| (ft_atoi_safe(argv[4], &philo_args->time_to_sleep)))
	{
		printf(USAGE_STR_2);
		return (-1);
	}
	if (argc == 6)
	{
		philo_args->has_fifth = 1;
		if (ft_atoi_safe(argv[5], &philo_args->meals_quota))
		{
			printf(USAGE_STR_3);
			return (-1);
		}
	}
	else
		philo_args->has_fifth = 0;
	return (0);
}

static int	assert_there_are_only_digits(char **str_table)
{
	int	index;

	str_table++;
	while (str_table[0])
	{
		index = 0;
		while (ft_isdigit(str_table[0][index]))
			index++;
		if (str_table[0][index])
			return (-1);
		str_table++;
	}
	return (0);
}
