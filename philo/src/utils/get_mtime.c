/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mtime.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:50:52 by srakuma           #+#    #+#             */
/*   Updated: 2021/10/26 14:55:28 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils.h"

long	get_mtime(void)
{
	struct timeval	tv;
	long			num;

	gettimeofday(&tv, NULL);
	num = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (num);
}
