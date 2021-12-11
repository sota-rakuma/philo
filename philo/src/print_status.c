/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 23:33:15 by srakuma           #+#    #+#             */
/*   Updated: 2021/12/11 17:42:15 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "read_write_cs.h"

bool	ft_print_philos_status(t_philo *philo, t_status status)
{
	char	*str;
	bool	flag;

	pthread_mutex_lock(&philo->all->loop.value_mu);
	flag = true;
	str = NULL;
	if (philo->all->loop.value == philo->all->philo_num)
		flag = false;
	else if (status == EAT)
		str = "is eating";
	else if (status == SLEEP)
		str = "is sleeping";
	else if (status == TAKEN_A_FORK)
		str = "has taken a fork";
	else if (status == THINK)
		str = "is thinking";
	else
	{
		philo->all->loop.value = philo->all->philo_num;
		str = "died";
	}
	if (flag)
		printf("%ld %d %s\n", get_mtime(), philo->number_X, str);
	pthread_mutex_unlock(&philo->all->loop.value_mu);
	return (flag);
}
