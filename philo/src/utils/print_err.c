/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:22:17 by srakuma           #+#    #+#             */
/*   Updated: 2021/12/11 15:47:11 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils.h"

static void	ft_putstr_fd(const char *str, int fd)
{
	size_t	len;

	len = ft_strlen(str);
	write(fd, str, len);
}

void	print_err(const char *message, const char filename[], \
									const char funcname[])
{
	ft_putstr_fd(filename, 2);
	write(2, ": ", 3);
	ft_putstr_fd(funcname, 2);
	write(2, ": ", 3);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}
