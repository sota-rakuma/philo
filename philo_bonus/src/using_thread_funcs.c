/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   using_thread_funcs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 02:52:08 by srakuma           #+#    #+#             */
/*   Updated: 2021/12/01 01:31:35 by srakuma          ###   ########.fr       */
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
	t_sem_and_size	*data;

	data = (t_sem_and_size *)val;
	i = 0;
	while (i++ < data->size)
		sem_wait(data->sem);
	return (NULL);
}

void	wait_for_childlen(t_avl *childlen, int sem_size)
{
	pthread_t		tid2;
	int				status;
	pid_t			val;
	t_sem_and_size	data;

	data.sem = childlen->term_sem;
	data.size = sem_size;
	pthread_create(&tid2, NULL, wait_all_childlen_ate, (void *)&data);
	val = waitpid(-1, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status))
			printf("%ld %d died\n", get_mtime(), seach_node(childlen, val)->key);
		pthread_detach(tid2);
		destruct_avl(childlen);
		return ;
	}
	pthread_join(tid2, NULL);
	destruct_avl(childlen);
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
	sem_t		*prepare;
	sem_t		*term_sem;
	pthread_t	tid;

	prepare = sem_open(PREPARE, 0);
	term_sem = sem_open(TERM_SEM, 0);
	if (prepare == SEM_FAILED | term_sem == SEM_FAILED)
		exit(0);
	sem_wait(term_sem);
	sem_wait(prepare);
	pthread_create(&tid, NULL, death_monitor, (void *)philo);
	pthread_detach(tid);
	ft_print_philos_status(philo, THINK);
	while (1)
	{
		ft_philo_eat(philo, term_sem);
		ft_print_philos_status(philo, SLEEP);
		ft_msleep_until_time(get_mtime() + philo->all->time_to_sleep);
		ft_print_philos_status(philo, THINK);
	}
}
