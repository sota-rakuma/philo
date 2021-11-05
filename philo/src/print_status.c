/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 23:33:15 by srakuma           #+#    #+#             */
/*   Updated: 2021/10/26 15:00:00 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "read_write_cs.h"

void	ft_print_philos_status(t_philo *philo, t_status status)
{
	long	time;
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
	time = get_mtime();
	printf("%ld %d %s\n", time, philo->number_X, str);
}
