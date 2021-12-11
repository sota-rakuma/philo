/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:28:38 by srakuma           #+#    #+#             */
/*   Updated: 2021/12/11 15:47:39 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_init_t_all.h"
#include "start_philo_behavior.h"

static void	ft_all_sem_unlink(void)
{
	sem_unlink(FORK);
	sem_unlink(SYNC);
	sem_unlink(RESERVE);
	sem_unlink(FOR_PRINT);
}

static void	main_process(int ac, char **av)
{
	t_all	*all;
	t_philo	*philo;

	all = ft_init_elements(ac, av);
	philo = ft_init_philo(all);
	start_philo_life(philo);
	free(philo->all);
	free(philo);
	exit(0);
}

int	main(int ac, char **av)
{
	pid_t	pid;

	if (ac < 5 || 6 < ac)
	{
		print_err("input right argument", __FILE__, __func__);
		return (FAILURE);
	}
	pid = fork();
	if (pid == 0)
		main_process(ac, av);
	waitpid(pid, NULL, 0);
	ft_all_sem_unlink();
	return (0);
}
