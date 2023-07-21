/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_handler_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:52 by rmiranda          #+#    #+#             */
/*   Updated: 2023/07/20 23:58:18 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static void	add_pid(t_philo_info *info_ptr, int	pid_to_add);
static int	fork_create(t_philo_info *info_ptr, int philo_id);

int	early_destroy(t_philo_info *info_ptr, int return_value)
{
	if (info_ptr->forks_sem != SEM_FAILED)
		sem_close(info_ptr->forks_sem);
	if (info_ptr->print_sem != SEM_FAILED)
		sem_close(info_ptr->print_sem);
	if (info_ptr->simulation_sem != SEM_FAILED)
		sem_close(info_ptr->simulation_sem);
	sem_unlink("/print_sem");
	sem_unlink("/simulation_sem");
	sem_unlink("/forks_sem");
	if (info_ptr->pid_list)
		free(info_ptr->pid_list);
	if (info_ptr->health_data)
		free(info_ptr->health_data);
	if (info_ptr)
		free(info_ptr);
	return (return_value);
}

int	child_destroy(t_philo_info *info_ptr, int return_value)
{
	(void)info_ptr;
	sem_unlink("/print_sem");
	sem_unlink("/simulation_sem");
	sem_unlink("/forks_sem");
	exit (return_value);
}

int	launch_threads(t_philo_info *info_ptr)
{
	int			index;

	index = 0;
	gettimeofday(&info_ptr->start_tv, NULL);
	while (index < info_ptr->args.nb_of_philo)
		if (!fork_create(info_ptr, index++))
			return (-1);
	return (0);
}

int	join_threads(t_philo_info *info_ptr)
{
	int	index;
	int	exit_code;

	exit_code = 0;
	index = -1;
	while (++index < info_ptr->args.nb_of_philo && exit_code == 0)
		waitpid(-1, &exit_code, 0);
	if (exit_code)
	{
		index = -1;
		while (++index < info_ptr->args.nb_of_philo)
			kill(info_ptr->pid_list[index], SIGKILL);
	}
	return (exit_code);
}

static int	fork_create(t_philo_info *info_ptr, int philo_id)
{
	int	value;

	value = fork();
	if (value == 0)
		child_destroy(info_ptr, philo_brain(info_ptr, philo_id));
	else
		add_pid(info_ptr, value);
	return (value);
}

static void	add_pid(t_philo_info *info_ptr, int	pid_to_add)
{
	int	index;

	index = 0;
	while (info_ptr->pid_list[index])
		index++;
	info_ptr->pid_list[index] = pid_to_add;
}
