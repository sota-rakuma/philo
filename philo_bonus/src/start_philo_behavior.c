/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_behavior.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 23:39:04 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/06 18:14:25 by srakuma          ###   ########.fr       */
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

static bool	ft_start_child_process(t_philo *philo)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < philo->all->philo_num)
	{
		pid = fork();
		if (pid == -1)
		{
			kill_multi_child_proc(philo, SIGTERM, i + 1);
			return (false);
		}
		else if (pid == 0)
			the_life_of_philo(&philo[i]);
		philo->pid[i] = pid;
		i++;
	}
	return (true);
}

void	start_philo_life(t_philo *philo)
{
	int	status;

	if (ft_start_child_process(philo) == false)
		return ;
	waitpid(-1, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status))
	{
		kill_multi_child_proc(philo, SIGINT, philo->all->philo_num);
		ft_print_philos_status(&philo[(_W_INT(status) >> 8) - 1], DIED);
	}
	return ;
}
