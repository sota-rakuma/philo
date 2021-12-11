/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:50:38 by srakuma           #+#    #+#             */
/*   Updated: 2021/12/11 15:02:16 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils_bonus.h"
#include "read_write_cs.h"
#include "philo_life.h"

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

static void	taking_forks(t_philo *philo)
{
	sem_wait(philo->reservation);
	sem_wait(philo->forks);
	ft_print_philos_status(philo, TAKEN_A_FORK);
	if (philo->all->philo_num == 1)
	{
		sem_post(philo->forks);
		ft_msleep_until_time(philo->lastmeal.val + philo->all->time_to_die);
		exit(philo->philo_x);
	}
	sem_wait(philo->forks);
	ft_print_philos_status(philo, TAKEN_A_FORK);
}

void	ft_philo_eat(t_philo *philo, sem_t *for_eaten_cnt)
{
	static long	eaten_cnt;
	long		lastmeal;

	if (philo->all->min_times_eat == 0)
		exit (0);
	taking_forks(philo);
	ft_print_philos_status(philo, EAT);
	lastmeal = get_mtime();
	atomic_read_write(&philo->lastmeal, lastmeal, ASSIGN);
	ft_msleep_until_time(lastmeal + philo->all->time_to_eat);
	sem_post(philo->reservation);
	sem_post(philo->forks);
	sem_post(philo->forks);
	eaten_cnt++;
	if (eaten_cnt == philo->all->min_times_eat)
		sem_post(for_eaten_cnt);
}
