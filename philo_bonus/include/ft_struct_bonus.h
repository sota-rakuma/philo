/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:22:56 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/08 01:03:18 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCT_BONUS_H
# define FT_STRUCT_BONUS_H

# include <stdbool.h>
# include <semaphore.h>
# include <semaphore.h>

typedef struct s_cs
{
	long	val;
	sem_t	*sem;
}				t_cs;

typedef struct s_all
{
	int		philo_num;
	long	min_times_eat;
	long	time_to_eat;
	long	time_to_die;
	long	time_to_sleep;
	sem_t	*for_print;
}				t_all;

typedef struct s_philo
{
	int		philo_x;
	sem_t	*reservation;
	sem_t	*forks;
	t_cs	lastmeal;
	//pid_t	*pid;
	t_all	*all;
}				t_philo;

#endif
