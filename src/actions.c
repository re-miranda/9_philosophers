/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:04:10 by rmiranda          #+#    #+#             */
/*   Updated: 2023/06/20 21:35:20 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	get_fork_pair(void)
{
	return (0);
}

static void	release_fork_pair(void)
{
	return ;
}

void	philo_think(void)
{
	while (get_fork_pair())
		continue ;
}

void	philo_eat(void)
{
	usleep(1000000);
	release_fork_pair();
}

void	philo_sleep(void)
{
	usleep(1000000);
}
