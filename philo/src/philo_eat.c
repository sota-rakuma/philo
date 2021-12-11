/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:17:16 by srakuma           #+#    #+#             */
/*   Updated: 2021/12/11 16:48:46 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_cleanup(t_philo *philo)
{
	pthread_mutex_unlock(philo->forks[RIGHT]);
	pthread_mutex_unlock(philo->forks[LEFT]);
	if (read_status(&philo->all->loop) == philo->all->philo_num)
		return (false);
	if (read_cs(&philo->eaten) == philo->all->min_times_eat)
		atomic_read_write_status(&philo->all->loop, 1, ADD);
	return (true);
}

static bool	taken_fork(t_philo *philo, int index)
{
	pthread_mutex_lock(philo->forks[index]);
	if (read_status(&philo->all->loop) == philo->all->philo_num)
	{
		pthread_mutex_unlock(philo->forks[index]);
		return (false);
	}
	ft_print_philos_status(philo, TAKEN_A_FORK);
	return (true);
}

static bool	taken_forks_at_both_side_of_philo(t_philo *philo)
{
	if (taken_fork(philo, LEFT) == false)
		return (false);
	if (taken_fork(philo, RIGHT) == false)
	{
		pthread_mutex_unlock(philo->forks[LEFT]);
		return (false);
	}
	return (true);
}

bool	ft_philo_eat(t_philo *philo)
{
	if (philo->all->min_times_eat == 0)
		return (false);
	if (taken_forks_at_both_side_of_philo(philo) == false)
		return (false);
	if (read_status(&philo->all->loop) == philo->all->philo_num)
	{
		pthread_mutex_unlock(philo->forks[RIGHT]);
		pthread_mutex_unlock(philo->forks[LEFT]);
		return (false);
	}
	ft_print_philos_status(philo, EAT);
	atomic_read_write(&philo->eaten, 1, ADD);
	atomic_read_write(&philo->lm, get_mtime(), ASSIGN);
	ft_msleep_until_time(get_mtime() + philo->all->time_to_eat);
	return (ft_cleanup(philo));
}
