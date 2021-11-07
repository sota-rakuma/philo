/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   using_thread_func.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 02:52:47 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/08 03:43:46 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USING_THREAD_FUNC_H
# define USING_THREAD_FUNC_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>
# include "start_philo_behavior.h"

typedef struct s_childlen
{
	int		size;
	pid_t	*pid;
	sem_t	*term_sem;
}				t_childlen;

void	wait_for_childlen(t_childlen *childlen);
void	the_life_of_philo(t_philo *philo);
void	kill_multi_child_proc(t_childlen *childlen, int sig);

#endif