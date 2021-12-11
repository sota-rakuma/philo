/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   using_thread_func.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 02:52:47 by srakuma           #+#    #+#             */
/*   Updated: 2021/12/11 15:10:31 by srakuma          ###   ########.fr       */
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
# include "../src/utils/avl_tree/avl_tree.h"

typedef struct s_node_and_sem
{
	t_avl	*avl;
	sem_t	*sem;
	int		size;
}				t_node_and_sem;

void	wait_for_childlen(t_node_and_sem data);
void	the_life_of_philo(t_philo *philo);
void	kill_multi_child_proc(t_avl *childlen, int sig);

#endif