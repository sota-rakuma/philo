/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_t_all.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 00:27:49 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/08 03:28:51 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SEM_SYS_BONUS_H
# define FT_SEM_SYS_BONUS_H

# ifndef SUCCESS
#  define SUCCESS 0
# endif

# ifndef FAILURE
#  define FAILURE 1
# endif

# ifndef SEM_NAME
#  define FORK "fork"
#  define RESERVE "reservation"
#  define FOR_PRINT "for_print"
#  define PREPARE "prepare"
#  define FOR_EATEN_CNT "for_eaten_cnt"
#  define TERM_SEM "term_sem"
# endif

# include <stdio.h>
# include <semaphore.h>
# include <stdbool.h>
# include "philo_utils_bonus.h"

typedef struct s_all
{
	int		philo_num;
	long	min_times_eat;
	long	time_to_eat;
	long	time_to_die;
	long	time_to_sleep;
	sem_t	*for_print;
}				t_all;

t_all	*ft_init_elements(int ac, char **av);

#endif