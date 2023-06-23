/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:52 by rmiranda          #+#    #+#             */
/*   Updated: 2023/06/22 10:45:49 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo_info	info;
	int			*input;
	pthread_t	t_tdata;
	pthread_t	t_tdata2;
	pthread_mutex_t	print_mutex;

	input = parse_input(argc, argv, &);
	if (!input)
		return (-1);
	pthread_mutex_init(&print_mutex, NULL);
	if (pthread_create(&t_tdata, NULL, &philo_brain, (void *)&print_mutex))
		return (-1);
	if (pthread_create(&t_tdata2, NULL, &philo_brain, (void *)&print_mutex))
		return (-1);
	if (pthread_join(t_tdata, NULL))
		return (-1);
	if (pthread_join(t_tdata2, NULL))
		return (-1);
	pthread_mutex_destroy(&print_mutex);
	free(input);
	return (0);
}

static int	assert_is_alive(void *mutex)
{
	static int	counter;

	pthread_mutex_lock(mutex);
	if (counter++ > 9)
	{
		pthread_mutex_unlock(mutex);
		return (0);
	}
	pthread_mutex_unlock(mutex);
	return (1);
}

void	*philo_brain(void *mutex)
{
	while (assert_is_alive(mutex))
	{
		philo_think(mutex);
		philo_eat(mutex);
		philo_sleep(mutex);
		pthread_mutex_lock(mutex);
		ft_putendl_fd("end of brain while block", 1);
		pthread_mutex_unlock(mutex);
	}
	return (NULL);
}
