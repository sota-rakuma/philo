/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 03:30:29 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/08 03:47:00 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_LIFE_H
# define PHILO_LIFE_H

# include "start_philo_behavior.h"

typedef enum e_status
{
	TAKEN_A_FORK,
	EAT,
	SLEEP,
	THINK,
	DIED,
}			t_status;

void	ft_print_philos_status(t_philo *philo, t_status status);
void	ft_philo_eat(t_philo *philo, sem_t *for_eaten_cnt);

#endif