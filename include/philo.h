/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:59 by rmiranda          #+#    #+#             */
/*   Updated: 2023/06/27 19:55:48 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include "defines.h"

int		ft_isdigit(char c);
void	*ft_calloc(size_t variable_size, int amount);
int		ft_atoi_safe(char *str, int *result_ptr);

int		parse_input(int argc, char *argv[], t_philo_info *philo_info_ptr);
void	*philo_brain(void *mutex);
void	philo_think(void *mutex);
void	philo_eat(void *mutex);
void	philo_sleep(void *mutex);

int		join_threads(t_philo_info info);
int		launch_threads(t_philo_info *info);
int		init_destroy(t_philo_info info, int return_value);
int		init_mutex(t_philo_info *info_ptr);

#endif
