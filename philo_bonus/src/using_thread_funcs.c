/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   using_thread_funcs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 02:52:08 by srakuma           #+#    #+#             */
/*   Updated: 2021/12/11 14:36:53 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "philo_life.h"
#include "using_thread_func.h"

void	kill_multi_child_proc(t_avl *childlen, int sig)
{
	if (childlen == NULL)
		return ;
	if (childlen->left)
		destruct_avl(childlen->left);
	if (childlen->right)
		destruct_avl(childlen->right);
	if (kill(childlen->val, sig) == EPERM)
		ft_print_error_message("this parent process does not \
			have a permission to send signal\n", __FILE__, __func__);
}

static void	*wait_all_childlen_ate(void *val)
{
	int				i;
	t_node_and_sem	*data;

	data = (t_node_and_sem *)val;
	i = 0;
	while (i++ < data->size)
		sem_wait(data->sem);
	kill_multi_child_proc(data->avl, SIGTERM);
	return (NULL);
}

static void	philo_die_proc(t_avl *childlen, int status, pid_t pid)
{
	sem_t	*for_print;

	for_print = sem_open(FOR_PRINT, 0);
	if (for_print == SEM_FAILED)
	{
		ft_print_error_message("sem for print open error", __FILE__, __func__);
		return ;
	}
	sem_wait(for_print);
	if (WEXITSTATUS(status))
		printf("%ld %d died\n", get_mtime(), seach_node(childlen, pid)->key);
	kill_multi_child_proc(childlen, SIGTERM);
	sem_post(for_print);
	sem_close(for_print);
}

void	wait_for_childlen(t_node_and_sem *data)
{
	pthread_t		tid;
	int				status;
	pid_t			pid;

	pthread_create(&tid, NULL, wait_all_childlen_ate, (void *)&data);
	pid = waitpid(-1, &status, 0);
	if (WIFEXITED(status))
	{
		philo_die_proc(data->avl, status, pid);
		pthread_detach(tid);
	}
	else
		pthread_join(tid, NULL);
	destruct_avl(data->avl);
}

static void	*death_monitor(void *ph)
{
	long	death_time;
	long	before_eaten_time;
	long	after_eaten_time;
	t_philo	*philo;

	philo = (t_philo *)ph;
	before_eaten_time = get_mtime();
	after_eaten_time = before_eaten_time + 1;
	atomic_read_write(&philo->lastmeal, before_eaten_time, ASSIGN);
	while (before_eaten_time < after_eaten_time)
	{
		before_eaten_time = after_eaten_time;
		death_time = read_cs(&philo->lastmeal) + philo->all->time_to_die;
		ft_msleep_until_time(death_time);
		after_eaten_time = read_cs(&philo->lastmeal);
	}
	exit(philo->philo_x);
}

void	the_life_of_philo(t_philo *philo)
{
	sem_t		*sync_sem;
	pthread_t	tid;

	sync_sem = sem_open(SYNC, 0);
	if (sync_sem == SEM_FAILED)
		exit(0);
	sem_wait(sync_sem);
	pthread_create(&tid, NULL, death_monitor, (void *)philo);
	pthread_detach(tid);
	ft_print_philos_status(philo, THINK);
	while (1)
	{
		ft_philo_eat(philo, sync_sem);
		ft_print_philos_status(philo, SLEEP);
		ft_msleep_until_time(get_mtime() + philo->all->time_to_sleep);
		ft_print_philos_status(philo, THINK);
	}
}
