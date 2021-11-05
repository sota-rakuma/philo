/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:51:15 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/05 03:19:51 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_UTILS_BONUS_H
# define PHILO_UTILS_BONUS_H

# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

# ifndef RIGHT
#  define RIGHT 0
# endif

# ifndef LEFT
#  define LEFT 1
# endif

long		get_mtime(void);
size_t		ft_strlen(const char *str);
void		ft_print_error_message(const char *message, const char filename[], \
									const char funcname[]);
long long	ft_atoll(const char *str);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
void		ft_msleep_until_time(long time);
void		ft_free_dbl_ptr(void **ptr, size_t size);
int			ft_isdigit(int c);

#endif