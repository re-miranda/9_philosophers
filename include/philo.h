/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:59 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/14 23:39:25 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <string.h>
# include "defines.h"

int			ft_isdigit(char c);
void		*ft_calloc(size_t variable_size, int amount);
int			ft_atoi_safe(char *str, int *result_ptr);

int			parse_input(int argc, char *argv[], t_philo_info *philo_info_ptr);
void		*philo_brain(void *info_ptr);
void		philo_think(t_philo_info *info, int philo_id);
void		philo_eat(t_philo_info *info, int philo_id);
void		philo_sleep(t_philo_info *info, int philo_id);

int			init_mutex(t_philo_info *info_ptr);
int			launch_threads(t_philo_info *info);
int			early_destroy(t_philo_info info, int return_value);
int			join_threads(t_philo_info info);

long int	elapsed_time(struct timeval *past, struct timeval *present);
int			assert_simulation_is_running(t_philo_info *info_ptr);

#endif
