/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_t_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 00:27:20 by srakuma           #+#    #+#             */
/*   Updated: 2021/12/11 15:47:39 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo_utils_bonus.h"
#include "ft_init_t_all.h"

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

static bool	ft_get_all_elements(t_all *all, int ac, char **av)
{
	sem_unlink("for_print");
	all->for_print = sem_open("for_print", O_CREAT | O_EXCL, 700, 1);
	if (all->for_print == SEM_FAILED)
	{
		print_err("sem open error", __FILE__, __func__);
		return (false);
	}
	all->philo_num = ft_atoi(av[1]);
	all->time_to_die = (long)ft_atoll(av[2]);
	all->time_to_eat = (long)ft_atoll(av[3]);
	all->time_to_sleep = (long)ft_atoll(av[4]);
	if (ac == 6)
		all->min_times_eat = (long)ft_atoll(av[5]);
	else
		all->min_times_eat = -1;
	return (true);
}

t_all	*ft_init_elements(int ac, char **av)
{
	t_all	*all;

	all = (t_all *)malloc(sizeof(t_all));
	if (!all)
	{
		print_err("failure of malloc", __FILE__, __func__);
		exit(FAILURE);
	}
	if ((ft_get_all_elements(all, ac, av) == false)
		| (ft_check_arg(ac, av, all) == false))
	{
		free(all);
		print_err("init t_all error", __FILE__, __func__);
		exit(FAILURE);
	}
	return (all);
}
