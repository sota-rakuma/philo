/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sem_sys_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 00:27:20 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/05 02:51:11 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo_utils_bonus.h"
#include "ft_sem_sys_bonus.h"

void	ft_unlink_multi_sem(sem_t **sem, char **sem_name, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		sem_close(sem[i]);
		sem_unlink((const char *)sem_name[i]);
		i++;
	}
}

void	ft_destructor(t_philo *philo, char **sem_name)
{
	ft_unlink_multi_sem(philo->forks, sem_name, philo->all->philo_num);
	ft_free_dbl_ptr((void **)sem_name, philo->all->philo_num);
	sem_close(philo->all->for_print);
	sem_unlink("for_print");
	free(philo->pid);
	free(philo->all);
	free(philo);
}

static sem_t	**ft_init_sem(t_all *all, char **sem_name)
{
	int		i;
	sem_t	**sem;

	i = 0;
	sem = (sem_t **)malloc(sizeof(sem_t *) * all->philo_num);
	if (!sem)
		return (NULL);
	while (i++ < all->philo_num)
	{
		sem_unlink(sem_name[i - 1]);
		sem[i - 1] = sem_open(sem_name[i - 1], O_CREAT | O_EXCL, 022, 1);
		if (sem[i - 1] == SEM_FAILED)
		{
			ft_print_error_message("sem_open error", __FILE__, __func__);
			ft_unlink_multi_sem(sem, sem_name, i);
			return (NULL);
		}
	}
	return (sem);
}

bool	ft_get_philo_ele(t_philo *philo, t_all *all, char **sem_name)
{
	int		i;
	pid_t	*pid;
	sem_t	**forks;

	forks = ft_init_sem(all, sem_name);
	if (!forks)
		return (false);
	pid = (pid_t *)malloc(sizeof(pid_t *) * all->philo_num);
	if (!pid)
	{
		ft_unlink_multi_sem(forks, sem_name, all->philo_num);
		return (false);
	}
	memset(pid, 0, all->philo_num);
	i = 0;
	while (i++ < all->philo_num)
	{
		philo[i - 1].philo_x = i;
		philo[i - 1].all = all;
		philo[i - 1].pid = pid;
		philo[i - 1].forks[RIGHT] = forks[i - 1];
		philo[i - 1].forks[LEFT] = forks[i % all->philo_num];
	}
	free(forks);
	return (true);
}
