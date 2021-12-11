/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_behavior.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 23:39:04 by srakuma           #+#    #+#             */
/*   Updated: 2021/12/11 15:09:34 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "start_philo_behavior.h"
#include "using_thread_func.h"
#include "./utils/avl_tree/avl_tree.h"

static t_avl	*ft_start_child_process(t_philo *philo)
{
	t_avl	*root;
	t_avl	*node;
	int		i;

	i = 0;
	root = NULL;
	while (i++ < philo->all->philo_num)
	{
		node = create_node(i, fork());
		if (node->val == -1)
		{
			kill_multi_child_proc(root, SIGTERM);
			destruct_avl(root);
			ft_print_error_message("could not make a child process", \
														__FILE__, __func__);
			return (NULL);
		}
		else if (node->val == 0)
			the_life_of_philo(&philo[i - 1]);
		else
			add_node(node, &root);
	}
	return (root);
}

static t_avl	*synchronize_all_proc(t_philo *philo, sem_t *sync_sem)
{
	int		i;
	t_avl	*childlen;

	i = 0;
	while (i++ < philo->all->philo_num)
		sem_wait(sync_sem);
	childlen = ft_start_child_process(philo);
	if (childlen == NULL)
		return (NULL);
	i = 0;
	while (i++ < philo->all->philo_num)
		sem_post(sync_sem);
	usleep(1000);
	return (childlen);
}

void	start_philo_life(t_philo *philo)
{
	t_avl	*childlen;
	sem_t	*sync_sem;

	sem_unlink(SYNC);
	sync_sem = sem_open(SYNC, O_CREAT | O_EXCL, 700, philo->all->philo_num);
	if (sync_sem == SEM_FAILED)
	{
		ft_print_error_message("sem_open error", __FILE__, __func__);
		return ;
	}
	childlen = synchronize_all_proc(philo, sync_sem);
	if (childlen == NULL)
		return ;
	return (wait_for_childlen((t_node_and_sem){childlen, \
				sync_sem, philo->all->philo_num}));
}
