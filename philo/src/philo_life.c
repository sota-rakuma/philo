/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:49:33 by srakuma           #+#    #+#             */
/*   Updated: 2021/12/11 17:39:50 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_get_philo_ele(t_philo *philo)
{
	if (pthread_mutex_init(&philo->eaten.value_mutex, NULL))
		return ;
	if (pthread_mutex_init(&philo->lm.value_mutex, NULL))
	{
		pthread_mutex_destroy(&philo->eaten.value_mutex);
		return ;
	}
	if (pthread_mutex_init(&philo->dl.value_mutex, NULL))
	{
		pthread_mutex_destroy(&philo->eaten.value_mutex);
		pthread_mutex_destroy(&philo->lm.value_mutex);
		return ;
	}
}

static void	*ft_death_monitor(void *val)
{
	long	deadline;
	long	lastmeal_time;
	t_philo	*philo;

	philo = (t_philo *)val;
	atomic_read_write(&philo->lm, get_mtime(), ASSIGN);
	lastmeal_time = 0;
	while (lastmeal_time < read_cs(&philo->lm))
	{
		if (read_status(&philo->all->loop) == philo->all->philo_num)
			return (NULL);
		lastmeal_time = read_cs(&philo->lm);
		deadline = lastmeal_time + philo->all->time_to_die;
		ft_msleep_until_time(deadline);
	}
	ft_print_philos_status(philo, DIED);
	pthread_mutex_unlock(philo->forks[LEFT]);
	pthread_mutex_unlock(philo->forks[RIGHT]);
	return (NULL);
}

void	*the_life_of_philo(void *ph)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)ph;
	ft_get_philo_ele(philo);
	if (ft_print_philos_status(philo, THINK) == false)
		return (NULL);
	pthread_create(&tid, NULL, ft_death_monitor, ph);
	while (1)
	{
		if (ft_philo_eat(philo) == false
			|| ft_print_philos_status(philo, SLEEP) == false)
			break ;
		ft_msleep_until_time(get_mtime() + philo->all->time_to_sleep);
		if (ft_print_philos_status(philo, THINK) == false)
			break ;
	}
	pthread_join(tid, NULL);
	return (NULL);
}
