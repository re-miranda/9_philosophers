/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:08:58 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/19 23:10:09 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	ft_isdigit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void	*ft_calloc(size_t variable_size, int amount)
{
	void	*return_ptr;

	return_ptr = malloc(amount * variable_size);
	if (return_ptr)
		memset(return_ptr, 0, variable_size * amount);
	return (return_ptr);
}

int	ft_atoi_safe(char *str, int *result_ptr)
{
	int			sign;
	long int	output;

	sign = 1;
	output = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		output *= 10;
		output += (int)(*str) - 48;
		str++;
	}
	output *= sign;
	if (output > 2147483647 || output < -2147483648)
		return (1);
	if (result_ptr)
		*result_ptr = (int)output;
	return (0);
}
