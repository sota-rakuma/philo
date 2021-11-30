/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   using_thread_func.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 02:52:47 by srakuma           #+#    #+#             */
/*   Updated: 2021/12/01 01:25:49 by srakuma          ###   ########.fr       */
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
# include "avl_tree.h"

typedef struct s_sem_and_size
{
	sem_t	*sem;
	int		size;
}				t_sem_and_size;

void	wait_for_childlen(t_avl *childlen, int sem_size);
void	the_life_of_philo(t_philo *philo);
void	kill_multi_child_proc(t_avl *childlen, int sig);

#endif