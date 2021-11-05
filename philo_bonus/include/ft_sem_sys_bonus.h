/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sem_sys_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 00:27:49 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/05 01:36:25 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SEM_SYS_BONUS_H
# define FT_SEM_SYS_BONUS_H

# ifndef RIGHT
#  define RIGHT 0
# endif

# ifndef LEFT
#  define LEFT 1
# endif

# include <semaphore.h>
# include <stdio.h>
# include "ft_struct_bonus.h"

void	ft_unlink_multi_sem(sem_t **sem, char **sem_name, size_t size);
void	ft_destructor(t_philo *philo, char **sem_name);
bool	ft_get_philo_ele(t_philo *philo, t_all *all, char **sem_name);
t_philo	*ft_init_philo(t_all *all, char **sem_name);

#endif