/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sem_sys_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 00:27:20 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/06 18:17:06 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo_utils_bonus.h"
#include "ft_sem_sys_bonus.h"

void	ft_destructor(t_philo *philo)
{
	sem_close(philo->forks);
	sem_close(philo->reservation);
	sem_close(philo->all->for_print);
	sem_unlink(FORK);
	sem_unlink(RESERVE);
	sem_unlink(FOR_PRINT);
	free(philo->pid);
	free(philo->all);
	free(philo);
}

static bool	ft_init_sem(t_all *all, sem_t **forks, sem_t **reservation)
{
	sem_unlink(FORK);
	*forks = sem_open(FORK, O_CREAT | O_EXCL, 022, all->philo_num);
	if (forks == SEM_FAILED)
		return (false);
	sem_unlink(RESERVE);
	*reservation = sem_open(RESERVE, O_CREAT | O_EXCL, 022, all->philo_num / 2);
	if (reservation == false)
	{
		sem_close(forks);
		sem_unlink(FORK);
		return (false);
	}
	return (true);
}

bool	ft_get_philo_ele(t_philo *philo, t_all *all)
{
	int		i;
	pid_t	*pid;
	sem_t	*reservation;
	sem_t	*forks;

	pid = (pid_t *)malloc(sizeof(pid_t *) * all->philo_num);
	if (!pid)
		return (false);
	memset(pid, 0, all->philo_num);
	if (ft_init_sem(all, &forks, &reservation) == false)
	{
		free(pid);
		return (false);
	}
	i = 0;
	while (i++ < all->philo_num)
	{
		philo[i - 1].philo_x = i;
		philo[i - 1].all = all;
		philo[i - 1].pid = pid;
		philo[i - 1].reservation = reservation;
		philo[i - 1].forks = forks;
	}
	return (true);
}
