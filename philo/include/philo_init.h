/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:56:51 by srakuma           #+#    #+#             */
/*   Updated: 2021/10/26 15:04:19 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_INIT_H
# define PHILO_INIT_H

# ifndef RIGHT
#  define RIGHT 0
# endif

# ifndef LEFT
#  define LEFT 1
# endif

# include "ft_struct.h"

t_philo	*ft_init_philo(int ac, char **av);

#endif