/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_behavior.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 03:03:05 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/08 03:44:20 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef START_PHILO_BEHAVIOR_H
# define START_PHILO_BEHAVIOR_H

# include "ft_init_t_all.h"
# include "read_write_cs.h"

typedef struct s_philo
{
	int		philo_x;
	sem_t	*reservation;
	sem_t	*forks;
	t_cs	lastmeal;
	t_all	*all;
}				t_philo;

t_philo	*ft_init_philo(t_all *all);
void	start_philo_life(t_philo *philo);

#endif