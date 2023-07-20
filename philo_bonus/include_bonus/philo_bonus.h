/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:59 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/19 23:10:02 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <string.h>
# include <stddef.h>
# include "defines_bonus.h"
// PARSE_BONUS.C
int			parse_input(int argc, char *argv[], t_philo_info *philo_info_ptr);
// INIT_BONUS.C
int			init(t_philo_info *info_ptr);
// THREADS_HANDLER_BONUS.C
int			launch_threads(t_philo_info *info);
int			early_destroy(t_philo_info *info_ptr, int return_value);
int			join_threads(t_philo_info info);
// ACTIONS_HELPER_BONUS.C
void		print_time_str(t_philo_info *info_ptr, int philo_id, char *str);
void		get_fork_pair(t_philo_info *info_ptr, int philo_id);
void		release_fork_pair(t_philo_info *info_ptr, int philo_id);
void		set_meal_tv(t_philo_info *info_ptr, int philo_id);
// ACTIONS_BONUS.C
void		*philo_brain(void *info_ptr);
void		philo_think(t_philo_info *info, int philo_id);
void		philo_eat(t_philo_info *info, int philo_id);
void		philo_sleep(t_philo_info *info, int philo_id);
// SIMULATION_HELPER_BONUS.C
int			assert_simulation_is_running(t_philo_info *info_ptr);
long int	elapsed_time(t_tv *past, t_tv *present);
void		supervise_philosophers(t_philo_info *info_ptr);
// FT_BONUS.C
int			ft_isdigit(char c);
void		*ft_calloc(size_t variable_size, int amount);
int			ft_atoi_safe(char *str, int *result_ptr);

#endif
