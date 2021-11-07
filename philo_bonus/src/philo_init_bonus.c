/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:22:25 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/08 03:40:34 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils_bonus.h"
#include "start_philo_behavior.h"

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

static bool	ft_get_philo_ele(t_philo *philo, t_all *all)
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
		philo[i - 1].reservation = reservation;
		philo[i - 1].forks = forks;
	}
	return (true);
}

t_philo	*ft_init_philo(t_all *all)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * all->philo_num);
	if (!philo)
	{
		sem_close(all->for_print);
		sem_unlink(FOR_PRINT);
		free(all);
		exit(FAILURE);
	}
	if (ft_get_philo_ele(philo, all) == false)
	{
		sem_close(all->for_print);
		sem_unlink(FOR_PRINT);
		free(all);
		free(philo);
		exit(FAILURE);
	}
	return (philo);
}
