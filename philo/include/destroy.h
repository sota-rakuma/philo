/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:33:04 by srakuma           #+#    #+#             */
/*   Updated: 2021/10/26 13:59:46 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DESTROY_H
# define DESTROY_H

# include <stdlib.h>
# include "ft_struct.h"

void	ft_free_cs(t_cs *cs, size_t num);
int		ft_destroy_mutex(t_mutex *mutexes, size_t size);
void	ft_destroy_philo(t_philo *philo, int cnt, int flag);
void	ft_end_proc(t_philo *philo, t_all *all, t_mutex *forks);

#endif