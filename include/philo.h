/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:59 by rmiranda          #+#    #+#             */
/*   Updated: 2023/06/21 13:03:00 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include "philo_defines.h"

int		ft_isdigit(char c);
void	*ft_calloc(size_t variable_size, int amount);
int		ft_atoi_safe(char *str, int *result_ptr);

int		*parse_input(int argc, char *argv[]);
void	*philo_brain(void *arg);
void	philo_think(void);
void	philo_eat(void);
void	philo_sleep(void);

#endif
