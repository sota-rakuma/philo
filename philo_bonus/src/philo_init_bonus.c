/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:22:25 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/05 01:37:46 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_init_bonus.h"
#include "philo_utils_bonus.h"
#include "ft_sem_sys_bonus.h"

t_philo	*ft_init_philo(t_all *all, char **sem_name)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * all->philo_num);
	if (!philo)
	{
		ft_free_dbl_ptr((void **)sem_name, all->philo_num);
		free(all);
		exit(FAILURE);
	}
	if (ft_get_philo_ele(philo, all, sem_name) == false)
	{
		ft_free_dbl_ptr((void **)sem_name, all->philo_num);
		free(all);
		free(philo);
		exit(FAILURE);
	}
	return (philo);
}
