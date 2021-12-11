/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:53:19 by srakuma           #+#    #+#             */
/*   Updated: 2021/12/11 15:47:39 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "destroy.h"
#include "philo_init.h"

static bool	launch_threads(int start, int number_of_philo, pthread_t *tid, \
							t_philo *philo)
{
	int	index;

	index = start;
	while (index < number_of_philo)
	{
		if (pthread_create(&tid[index], NULL, the_life_of_philo, \
								(void *)&philo[index]))
		{
			index = 0;
			while (index++ < number_of_philo)
				pthread_join(tid[index - 1], NULL);
			ft_destroy_philo(philo, index, 1);
			return (false);
		}
		index += 2;
	}
	return (true);
}

static void	ft_controlling_thread(t_philo *philo, int number_of_philo)
{
	int			cnt;
	pthread_t	*tid;

	tid = (pthread_t *)malloc(sizeof(pthread_t) * number_of_philo);
	if (!tid)
		return ;
	if (launch_threads(0, number_of_philo, tid, philo) == false)
		return (free(tid));
	usleep(1000);
	if (launch_threads(1, number_of_philo, tid, philo) == false)
	{
		if (number_of_philo % 2 == 1)
			ft_destroy_philo(philo, number_of_philo - 1, 1);
		else
			ft_destroy_philo(philo, number_of_philo - 2, 1);
		return (free(tid));
	}
	cnt = 0;
	while (cnt++ < number_of_philo)
		pthread_join(tid[cnt - 1], NULL);
	return (free(tid));
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac < 5 || 6 < ac)
	{
		print_err("input right argument", __FILE__, __func__);
		return (FAILURE);
	}
	philo = ft_init_philo(ac, av);
	if (!philo)
	{
		print_err("init philo error", __FILE__, __func__);
		return (FAILURE);
	}
	ft_controlling_thread(philo, philo->all->philo_num);
	ft_end_proc(philo, philo->all, philo->forks[0]);
	return (SUCCESS);
}
