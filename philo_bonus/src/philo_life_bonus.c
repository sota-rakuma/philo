/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:50:38 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/06 18:42:11 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include "philo_utils_bonus.h"

void	ft_print_philos_status(t_philo *philo, t_status status)
{
	char	*str;

	if (status == EAT)
		str = "is eating";
	else if (status == SLEEP)
		str = "is sleeping";
	else if (status == TAKEN_A_FORK)
		str = "has taken a fork";
	else if (status == THINK)
		str = "is thinking";
	else
		str = "died";
	sem_wait(philo->all->for_print);
	printf("%ld %d %s\n", get_mtime(), philo->philo_x, str);
	sem_post(philo->all->for_print);
}

static void	ft_cleanup(t_philo *philo, int times_eat)
{
	sem_post(philo->forks);
	sem_post(philo->forks);
	if (times_eat == philo->all->min_times_eat)
		exit(0);
}

static void	taking_forks(t_philo *philo, long death_time)
{
	sem_wait(philo->reservation);
	sem_wait(philo->forks);
	if (death_time < get_mtime())
	{
		sem_post(philo->forks);
		exit(philo->philo_x);
	}
	ft_print_philos_status(philo, TAKEN_A_FORK);
	if (philo->all->philo_num == 1)
	{
		sem_post(philo->forks);
		ft_msleep_until_time(death_time);
		exit(philo->philo_x);
	}
	sem_wait(philo->forks);
	if (death_time < get_mtime())
		exit(philo->philo_x);
	ft_print_philos_status(philo, TAKEN_A_FORK);
	sem_post(philo->reservation);
}

long	ft_philo_eat(t_philo *philo, long death_time)
{
	static int	times_eat;

	if (philo->all->min_times_eat == 0)
		exit (0);
	taking_forks(philo, death_time);
	if (death_time < get_mtime())
		exit(philo->philo_x);
	ft_print_philos_status(philo, EAT);
	times_eat++;
	death_time = get_mtime() + philo->all->time_to_die;
	if (death_time < get_mtime() + philo->all->time_to_sleep)
		ft_msleep_until_time(death_time + 1);
	else
		ft_msleep_until_time(get_mtime() + philo->all->time_to_eat);
	ft_cleanup(philo, times_eat);
	return (death_time);
}

void	the_life_of_philo(t_philo *philo)
{
	long	death_time;

	death_time = get_mtime() + philo->all->time_to_die;
	ft_print_philos_status(philo, THINK);
	while (1)
	{
		death_time = ft_philo_eat(philo, death_time);
		if (death_time < get_mtime())
			exit(philo->philo_x);
		ft_print_philos_status(philo, SLEEP);
		if (death_time < get_mtime() + philo->all->time_to_sleep)
			ft_msleep_until_time(death_time + 1);
		else
			ft_msleep_until_time(get_mtime() + philo->all->time_to_sleep);
		if (death_time < get_mtime())
			exit(philo->philo_x);
		ft_print_philos_status(philo, THINK);
	}
}
