/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_behavior.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 23:39:04 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/08 03:36:58 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "start_philo_behavior.h"
#include "using_thread_func.h"

static bool	ft_start_child_process(t_philo *philo, t_childlen *childlen)
{
	childlen->size = 0;
	while (childlen->size < philo->all->philo_num)
	{
		childlen->pid[childlen->size] = fork();
		if (childlen->pid[childlen->size] == -1)
		{
			kill_multi_child_proc(childlen, SIGTERM);
			ft_print_error_message("could not make a child process", \
														__FILE__, __func__);
			return (false);
		}
		else if (childlen->pid[childlen->size] == 0)
			the_life_of_philo(&philo[childlen->size]); // prepare, term_sem
		childlen->size++;
	}
	return (true);
}

static t_childlen	*init_childlen(t_philo *philo)
{
	t_childlen *childlen;

	childlen = (t_childlen *)malloc(sizeof(t_childlen));
	if (!childlen)
		return (NULL);
	childlen->pid = (pid_t *)malloc(sizeof(pid_t *) * philo->all->philo_num);
	if (!childlen->pid)
	{
		free(childlen);
		return (NULL);
	}
	memset(childlen->pid, 0, philo->all->philo_num);
	sem_unlink(TERM_SEM);
	childlen->term_sem = sem_open(TERM_SEM, O_CREAT | O_EXCL, \
									700, philo->all->philo_num);
	if (childlen->term_sem == SEM_FAILED)
	{
		free(childlen);
		free(childlen->pid);
		return (NULL);
	}
	return (childlen);
}

static bool	synchronize_all_proc(t_philo *philo, sem_t *prepare, \
												t_childlen *childlen)
{
	int	i;

	i = 0;
	while (i++ < philo->all->philo_num)
		sem_wait(prepare);
	if (ft_start_child_process(philo, childlen) == false)
		return (false);
	i = 0;
	while (i++ < philo->all->philo_num)
		sem_post(prepare);
	usleep(1000);
	return (true);
}

void	start_philo_life(t_philo *philo)
{
	t_childlen	*childlen;
	sem_t		*prepare;

	sem_unlink(PREPARE);
	prepare = sem_open(PREPARE, O_CREAT | O_EXCL, 700, philo->all->philo_num);
	if (prepare == SEM_FAILED)
	{
		ft_print_error_message("sem_open error", __FILE__, __func__);
		return ;
	}
	childlen = init_childlen(philo);
	if (childlen == NULL)
		return (ft_print_error_message("init t_childlen error", \
											__FILE__, __func__));
	if (synchronize_all_proc(philo, prepare, childlen) == false)
	{
		free(childlen->pid);
		free(childlen);
		return ;
	}
	return (wait_for_childlen(childlen));
}
