/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_behavior.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 23:39:04 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/08 01:18:07 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils_bonus.h"
#include "ft_sem_sys_bonus.h"
#include "philo_bonus.h"

void	kill_multi_child_proc(t_childlen *childlen, int sig)
{
	int	i;

	i = 0;
	while (i++ < childlen->size)
	{
		if (kill(childlen->pid[i - 1], sig) == EPERM)
		{
			ft_print_error_message("this parent process does not \
					have a permission to send signal\n", __FILE__, __func__);
		}
	}
}

static bool	ft_start_child_process(t_philo *philo, t_childlen *childlen)
{
	childlen->size = 0;
	while (childlen->size < philo->all->philo_num)
	{
		childlen->pid[childlen->size] = fork();
		if (childlen->pid[childlen->size] == -1)
		{
			kill_multi_child_proc(childlen, SIGTERM);
			ft_print_error_message("could not make a child process", __FILE__, __func__);
			return (false);
		}
		else if (childlen->pid[childlen->size] == 0)
			the_life_of_philo(&philo[childlen->size]); // prepare, term_sem
		childlen->size++;
	}
	return (true);
}

void	*wait_all_childlen_ate(void *val)
{
	int	j;
	t_childlen	*childlen;

	childlen = (t_childlen *)val;
	j = 0;
	while (j++ < childlen->size)
		sem_wait(childlen->term_sem);
	printf("in wait thread: time: %ld\n", get_mtime());
	kill_multi_child_proc(childlen, SIGINT);
	return (NULL);
}

void	start_philo_life(t_philo *philo)
{
	t_childlen	childlen;
	sem_t		*prepare;

	childlen.pid = (pid_t *)malloc(sizeof(pid_t *) * philo->all->philo_num);
	if (!childlen.pid)
	{
		ft_print_error_message("pid malloc error", __FILE__, __func__);
		return ;
	}
	memset(childlen.pid, 0, philo->all->philo_num);

	sem_unlink(PREPARE);
	prepare = sem_open(PREPARE, O_CREAT | O_EXCL, 700, philo->all->philo_num);

	sem_unlink(TERM_SEM);
	childlen.term_sem = sem_open(TERM_SEM, O_CREAT | O_EXCL, 700, philo->all->philo_num);

	if (prepare == SEM_FAILED | childlen.term_sem == SEM_FAILED)
	{
		free(childlen.pid);
		/*sem_close(prepare);
		sem_close(childlen.term_sem);
		sem_unlink(PREPARE);
		sem_unlink(TERM_SEM);*/
		ft_print_error_message("sem_open error", __FILE__, __func__);
		return ;
	}


	int	i;

	i = 0;
	while (i++ < philo->all->philo_num)
		sem_wait(prepare);
	if (ft_start_child_process(philo, &childlen) == false)
	{
		free(childlen.pid);
		sem_close(prepare);
		sem_unlink(PREPARE);
		return ;
	}
	i = 0;
	while (i++ < philo->all->philo_num)
		sem_post(prepare);
	usleep(1000);


	pthread_t	tid2;

	pthread_create(&tid2, NULL, wait_all_childlen_ate, (void *)&childlen);

	pid_t		child;
	int			status;

	child = waitpid(-1, &status, 0);
	if (WIFEXITED(status))
	{
		kill_multi_child_proc(&childlen, SIGINT);
		if (WEXITSTATUS(status))
			printf("%ld %d died\n", get_mtime(), _W_INT(status) >> 8);
		pthread_detach(tid2);
		free(childlen.pid);
		return ;
	}
	printf("after wait time: %ld, philo->x: %d\n", get_mtime(), _W_INT(status) >> 8);
	//if (WIFSIGNALED(status))
	pthread_join(tid2, NULL);
	free(childlen.pid);
	return ;
}
