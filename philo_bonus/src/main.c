/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:28:38 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/05 03:40:40 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils_bonus.h"
#include "philo_init_bonus.h"
#include "ft_sem_sys_bonus.h"
#include "philo_bonus.h"

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
	all->for_print = sem_open("for_print", O_CREAT | O_EXCL, 022, 1);
	if (all->for_print == SEM_FAILED)
		ft_print_error_message("sem open error", __FILE__, __func__);
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

static t_all	*ft_init_elements(int ac, char **av)
{
	t_all	*all;

	all = (t_all *)malloc(sizeof(t_all));
	if (!all)
	{
		ft_print_error_message("failure of malloc", __FILE__, __func__);
		exit(FAILURE);
	}
	if ((ft_get_all_elements(all, ac, av) == false)
		| (ft_check_arg(ac, av, all) == false))
	{
		free(all);
		ft_print_error_message("init t_all error", __FILE__, __func__);
		exit(FAILURE);
	}
	return (all);
}

char	**ft_get_sem_names(int number_of_philos)
{
	char	**forks;
	int		i;

	forks = (char **)malloc(sizeof(char *) * number_of_philos);
	if (!forks)
		return (NULL);
	i = 0;
	while (i++ < number_of_philos)
	{
		forks[i - 1] = ft_itoa(i);
		if (!forks[i - 1])
		{
			ft_free_dbl_ptr((void **)forks, i);
			return (NULL);
		}
	}
	return (forks);
}

int	main(int ac, char **av)
{
	t_all	*all;
	t_philo	*philo;
	char	**sem_name;

	if (ac < 5 || 6 < ac)
	{
		ft_print_error_message("input right argument", __FILE__, __func__);
		return (FAILURE);
	}
	all = ft_init_elements(ac, av);
	sem_name = ft_get_sem_names(all->philo_num);
	if (!sem_name)
	{
		free(all);
		exit(FAILURE);
	}
	philo = ft_init_philo(all, sem_name);
	start_philo_life(philo);
	ft_destructor(philo, sem_name);
	return (0);
}
