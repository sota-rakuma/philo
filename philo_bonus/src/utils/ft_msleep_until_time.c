/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msleep_until_time.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:49:03 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/25 23:32:10 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils_bonus.h"

void	ft_msleep_until_time(long time)
{
	time -= 50;
	while (get_mtime() < time)
		usleep(1000);
	time += 50;
	while (get_mtime() < time)
		usleep(500);
}
