/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:34:45 by srakuma           #+#    #+#             */
/*   Updated: 2021/10/30 15:26:38 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCT_H
# define FT_STRUCT_H

# include <pthread.h>
# include <stdbool.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_loop
{
	bool		value;
	t_mutex		value_mu;
}				t_loop;

typedef struct s_all
{
	int		philo_num;
	long	min_times_eat;
	long	time_to_eat;
	long	time_to_die;
	long	time_to_sleep;
	t_loop	loop;
}				t_all;

typedef struct s_cs
{
	long	value;
	t_mutex	value_mutex;
}				t_cs;

typedef t_cs			t_eaten;
typedef t_cs			t_lastmeal;
typedef t_cs			t_deadline;

typedef struct s_philo
{
	int				number_X;
	t_eaten			eaten;
	t_lastmeal		lm;
	t_deadline		dl;
	t_mutex			*forks[2];
	t_all			*all;
}				t_philo;

#endif