/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:56:32 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/05 23:16:31 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_init.h"
#include "philo_utils.h"
#include "destroy.h"

static bool	ft_check_arg(int ac, char **av, t_all *all)
{
	int	i;
	int	j;

	i = 0;
	while (i++ < ac - 1)
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (false);
			j++;
		}
	}
	if (all->philo_num < 1 || all->time_to_die < 0 || all->time_to_eat < 0
		|| all->time_to_sleep < 0 || (ac == 6 && all->min_times_eat < 0))
		return (false);
	return (true);
}

static t_mutex	*ft_init_mutexes(int size)
{
	int		index;
	t_mutex	*mutexes;

	mutexes = (t_mutex *)malloc(sizeof(t_mutex) * size);
	if (!mutexes)
		return (NULL);
	index = 0;
	while (index++ < size)
	{
		if (pthread_mutex_init(&mutexes[index - 1], NULL))
		{
			ft_destroy_mutex(mutexes, index);
			ft_print_error_message("mutex_init error", __FILE__, __func__);
			return (NULL);
		}
	}
	return (mutexes);
}

static t_all	*ft_init_elements(int ac, char **av)
{
	t_all	*all;

	all = (t_all *)malloc(sizeof(t_all));
	if (!all)
	{
		ft_print_error_message("failure of malloc", __FILE__, __func__);
		return (NULL);
	}
	all->philo_num = ft_atoi(av[1]);
	all->time_to_die = (long)ft_atoll(av[2]);
	all->time_to_eat = (long)ft_atoll(av[3]);
	all->time_to_sleep = (long)ft_atoll(av[4]);
	if (ac == 6)
		all->min_times_eat = (long)ft_atoll(av[5]);
	else
		all->min_times_eat = -1;
	all->loop.value = 0;
	if ((ft_check_arg(ac, av, all) == false)
		| pthread_mutex_init(&all->loop.value_mu, NULL))
	{
		free(all);
		ft_print_error_message("init t_all error", __FILE__, __func__);
		return (NULL);
	}
	return (all);
}

static void	ft_get_philo_ele(t_philo *philo, t_all *all, t_mutex *forks)
{
	int	cnt;

	cnt = 0;
	while (cnt++ < all->philo_num)
	{
		philo[cnt - 1].eaten.value = 0;
		philo[cnt - 1].number_X = cnt;
		philo[cnt - 1].all = all;
		philo[cnt - 1].forks[LEFT] = &forks[cnt % all->philo_num];
		philo[cnt - 1].forks[RIGHT] = &forks[cnt - 1];
	}
}

t_philo	*ft_init_philo(int ac, char **av)
{
	t_all	*all;
	t_mutex	*forks;
	t_philo	*philo;

	all = ft_init_elements(ac, av);
	if (!all)
		return (NULL);
	philo = (t_philo *)malloc(sizeof(t_philo) * all->philo_num);
	if (!philo)
	{
		pthread_mutex_destroy(&all->loop.value_mu);
		free(all);
		return (NULL);
	}
	forks = ft_init_mutexes(all->philo_num);
	if (!forks)
	{
		pthread_mutex_destroy(&all->loop.value_mu);
		free(all);
		free(philo);
		return (NULL);
	}
	ft_get_philo_ele(philo, all, forks);
	return (philo);
}
