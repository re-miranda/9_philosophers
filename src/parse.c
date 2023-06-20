/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:09:26 by rmiranda          #+#    #+#             */
/*   Updated: 2023/06/20 16:09:28 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	assert_there_are_only_digits(char **str_table);

int	*parse_input(int argc, char *argv[])
{
	int	*parsed_input;

	if (argc != 5 || argc != 6)
		return (-1);
	if (assert_there_are_only_digits(argv))
		return (-1);
	parsed_input = ft_calloc(sizeof(int), argc);
	if (!parsed_input)
		return (-1);
	if (ft_atoi_safe(argv[2], parsed_input[0])
		|| (ft_atoi_safe(argv[3], parsed_input[1])
		|| (ft_atoi_safe(argv[4], parsed_input[2])
		|| (ft_atoi_safe(argv[5], parsed_input[3])
		|| (argc == 6 && ft_atoi_safe(argv[6], parsed_inout[4]))
	{
		free(parsed_values);
		return (-1);
	}
	return (parsed_input);
}

static int	assert_there_are_only_digits(char **str_table)
{
	int	index;

	while (str_table[0])
	{
		index = 0;
		while (ft_isdigit(str_table[0][index])
			index++;
		if (str_table[0][index])
			return (-1);
		str_table++;
	}
	return (0);
}
