/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_behavior.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 23:39:04 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/05 01:01:28 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils_bonus.h"
#include "philo_bonus.h"

void	kill_multi_child_proc(t_philo *philo, int sig, int size)
{
	int	i;

	i = 0;
	while (i++ < size)
	{
		if (kill(philo->pid[i - 1], sig) == EPERM)
		{
			ft_print_error_message("this parent process does not \
					have a permission to send signal\n", __FILE__, __func__);
		}
	}
}

void	kill_child_proc_with_skipping_over(t_philo *philo, int sig, int size, \
											int start)
{
	while (start < size)
	{
		if (kill(philo->pid[start], sig) == EPERM)
		{
			ft_print_error_message("this parent process does \
				not have a permission to send signal\n", __FILE__, __func__);
		}
		start += 2;
	}
}

static bool	start_proc_with_skipping_over(t_philo *philo, int start)
{
	int		i;
	pid_t	pid;

	i = start;
	while (i < philo->all->philo_num)
	{
		pid = fork();
		if (pid == -1)
		{
			kill_child_proc_with_skipping_over(philo, SIGTERM, i + 1, start);
			return (false);
		}
		else if (pid == 0)
			the_life_of_philo(&philo[i]);
		philo->pid[i] = pid;
		i += 2;
	}
	return (true);
}

void	start_philo_life(t_philo *philo)
{
	int	status;

	if (start_proc_with_skipping_over(philo, 0) == false)
		return ;
	usleep(1000);
	if (start_proc_with_skipping_over(philo, 1) == false)
	{
		kill_child_proc_with_skipping_over(philo, SIGTERM, philo->philo_x, 0);
		return ;
	}
	waitpid(-1, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status))
	{
		kill_multi_child_proc(philo, SIGINT, philo->all->philo_num);
		ft_print_philos_status(&philo[(_W_INT(status) >> 8) - 1], DIED);
	}
	return ;
}
