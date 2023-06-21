/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:52 by rmiranda          #+#    #+#             */
/*   Updated: 2023/06/21 12:43:55 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	int			*input;
	pthread_t	t_tdata;

	input = parse_input(argc, argv);
	if (!input)
		return (-1);
	if (pthread_create(&t_tdata, NULL, &philo_brain, NULL))
		return (-1);
	if (pthread_join(t_tdata, NULL))
		return (-1);
	free(input);
	return (0);
}

static int	assert_is_alive(void)
{
	return (1);
}

void	*philo_brain(void *arg)
{
	while (assert_is_alive())
	{
		philo_think();
		philo_eat();
		philo_sleep();
	}
	(void)arg;
	return (NULL);
}
