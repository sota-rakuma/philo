/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sem_sys_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 00:27:20 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/08 00:46:25 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo_utils_bonus.h"
#include "ft_sem_sys_bonus.h"

void	ft_destructor(t_philo *philo)
{
	//free(philo->pid);
	free(philo->all);
	free(philo);
}

static bool	ft_init_sem(t_all *all, sem_t **forks, sem_t **reservation)
{
	sem_unlink(FORK);
	*forks = sem_open(FORK, O_CREAT | O_EXCL, 700, all->philo_num);
	if (*forks == SEM_FAILED)
		return (false);
	sem_unlink(RESERVE);
	*reservation = sem_open(RESERVE, O_CREAT | O_EXCL, 700, all->philo_num / 2);
	if (*reservation == false)
	{
		sem_close(*forks);
		sem_unlink(FORK);
		return (false);
	}
	return (true);
}

bool	ft_get_philo_ele(t_philo *philo, t_all *all)
{
	int		i;
	sem_t	*reservation;
	sem_t	*forks;

	if (ft_init_sem(all, &forks, &reservation) == false)
		return (false);
	i = 0;
	while (i++ < all->philo_num)
	{
		philo[i - 1].philo_x = i;
		philo[i - 1].all = all;
		//philo[i - 1].term_sem = term_sem;
		//philo[i - 1].pid = pid;
		philo[i - 1].reservation = reservation;
		philo[i - 1].forks = forks;
	}
	return (true);
}
