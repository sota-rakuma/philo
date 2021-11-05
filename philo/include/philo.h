/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:39:11 by srakuma           #+#    #+#             */
/*   Updated: 2021/10/26 15:04:47 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdbool.h>
# include "read_write_cs.h"
# include "philo_utils.h"
# include "ft_struct.h"

# ifndef RIGHT
#  define RIGHT 0
# endif

# ifndef LEFT
#  define LEFT 1
# endif

# ifndef SUCCESS
#  define SUCCESS 0
# endif

# ifndef FAILURE
#  define FAILURE 1
# endif

void		ft_print_philos_status(t_philo *philo, t_status status);
void		*ft_print_status(t_philo *philo);
bool		ft_philo_eat(t_philo *philo);
void		*the_life_of_philo(void *all_info);

#endif