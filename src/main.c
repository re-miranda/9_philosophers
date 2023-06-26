/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:52 by rmiranda          #+#    #+#             */
/*   Updated: 2023/06/22 22:45:24 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_info(t_philo_info *info_ptr)
{
	pthread_mutex_t	*mutex_ptr;

	mutex_ptr = &info_ptr->print_mutex;
	pthread_mutex_init(mutex_ptr, NULL);
}

void	init_destroy(t_philo_info *info_ptr)
{
	pthread_mutex_t	*mutex_ptr;

	mutex_ptr = &info_ptr->print_mutex;
	pthread_mutex_destroy(mutex_ptr);
}

int	main(int argc, char *argv[])
{
	t_philo_info	info;
	pthread_t	t_tdata;
	pthread_t	t_tdata2;

	if (parse_input(argc, argv, &info))
		return (-1);
	init_info(&info);
	if (pthread_create(&t_tdata, NULL, &philo_brain, (void *)&info.print_mutex))
		return (-1);
	if (pthread_create(&t_tdata2, NULL, &philo_brain, (void *)&info.print_mutex))
		return (-1);
	if (pthread_join(t_tdata, NULL))
		return (-1);
	if (pthread_join(t_tdata2, NULL))
		return (-1);
	init_destroy(&info);
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
