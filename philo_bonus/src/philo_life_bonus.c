/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:50:38 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/08 01:21:19 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include "ft_sem_sys_bonus.h"
#include "philo_utils_bonus.h"

long	read_cs(t_cs *cs)
{
	long	ret;

	sem_wait(cs->sem);
	ret = cs->val;
	sem_post(cs->sem);
	return (ret);
}

void	atomic_read_write(t_cs *cs, long val, t_op op)
{
	sem_wait(cs->sem);
	if (op == ADD)
		cs->val += val;
	else if (op == SUB)
		cs->val -= val;
	else if (op == MUL)
		cs->val *= val;
	else if (op == DIV)
		cs->val /= val;
	else if (op == MOD)
		cs->val %= val;
	else
		cs->val = val;
	sem_post(cs->sem);
}

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

static void	ft_cleanup(t_philo *philo, sem_t *for_eaten_cnt)
{
	static long	eaten_cnt;

	sem_post(philo->forks);
	sem_post(philo->forks);
	eaten_cnt++;
	if (eaten_cnt == philo->all->min_times_eat)
		sem_post(for_eaten_cnt);
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
	sem_post(philo->reservation);
}

void	ft_philo_eat(t_philo *philo, sem_t *for_eaten_cnt)
{
	long	lastmeal;

	if (philo->all->min_times_eat == 0)
		exit (0);
	taking_forks(philo);
	ft_print_philos_status(philo, EAT);
	lastmeal = get_mtime();
	atomic_read_write(&philo->lastmeal, lastmeal, ASSIGN);
	ft_msleep_until_time(lastmeal + philo->all->time_to_eat);
	ft_cleanup(philo, for_eaten_cnt);
}

void	*death_monitor(void *ph)
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
	{
		printf("philo %d\n", philo->philo_x);
		perror(NULL);
		exit(0);
	}
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
