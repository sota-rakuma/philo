/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:33:58 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/04 17:21:27 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <semaphore.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include "ft_struct_bonus.h"

# ifndef SUCCESS
#  define SUCCESS 0
# endif

# ifndef FAILURE
#  define FAILURE 1
# endif

typedef enum e_status
{
	TAKEN_A_FORK,
	EAT,
	SLEEP,
	THINK,
	DIED,
}			t_status;

typedef enum e_op
{
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
}			t_op;

void	the_life_of_philo(t_philo *philo);
void	kill_multi_child_proc(t_philo *philo, int sig, int size);
void	start_philo_life(t_philo *philo);
void	ft_print_philos_status(t_philo *philo, t_status status);

#endif