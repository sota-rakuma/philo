/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:32:08 by srakuma           #+#    #+#             */
/*   Updated: 2021/12/11 15:47:39 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "destroy.h"
#include "philo_utils.h"

void	ft_free_cs(t_cs *cs, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(&cs[i].value_mutex);
		i++;
	}
	free(cs);
}

int	ft_destroy_mutex(t_mutex *mutexes, size_t size)
{
	size_t	index;

	index = 0;
	while (index++ < size)
	{
		if (pthread_mutex_destroy(&mutexes[index - 1]))
		{
			print_err("mutex_destroy_error", __FILE__, __func__);
			return (1);
		}
	}
	return (0);
}

static void	ft_destroy_mutexes_of_philo(t_philo *philo)
{
	pthread_mutex_destroy(&philo->dl.value_mutex);
	pthread_mutex_destroy(&philo->lm.value_mutex);
	pthread_mutex_destroy(&philo->eaten.value_mutex);
}

/*
	flag == 0 => all, else just odd or even
	if you destroy all elements, pass this func number of philos as cnt,
	else pass this func the index which is processed in last
*/
void	ft_destroy_philo(t_philo *philo, int cnt, int flag)
{
	if (flag == 0)
	{
		while (cnt--)
			ft_destroy_mutexes_of_philo(&philo[cnt]);
	}
	else
	{
		while (cnt >= 0)
		{
			ft_destroy_mutexes_of_philo(&philo[cnt]);
			cnt -= 2;
		}
	}
	free(philo);
}

void	ft_end_proc(t_philo *philo, t_all *all, t_mutex *forks)
{
	ft_destroy_mutex(forks, all->philo_num);
	free(forks);
	pthread_mutex_destroy(&all->loop.value_mu);
	ft_destroy_philo(philo, all->philo_num, 0);
	free(all);
}
