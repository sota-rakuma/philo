/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sem_sys_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 00:27:49 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/06 18:15:19 by srakuma          ###   ########.fr       */
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

# ifndef SEM_NAME
#  define FORK "fork"
#  define RESERVE "reservation"
#  define FOR_PRINT "for_print"
# endif


# include <semaphore.h>
# include <stdio.h>
# include "ft_struct_bonus.h"

void	ft_destructor(t_philo *philo);
bool	ft_get_philo_ele(t_philo *philo, t_all *all);
t_philo	*ft_init_philo(t_all *all);

#endif