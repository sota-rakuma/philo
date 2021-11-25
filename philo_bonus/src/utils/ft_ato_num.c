/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ato_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:54:41 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/25 23:31:30 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils_bonus.h"
#include <limits.h>

static int	is_ok(long long num, int c, int flag)
{
	long long	ov_div;
	long long	ov_mod;
	int			nxt;

	nxt = c - '0';
	if (flag == -1)
	{
		ov_div = LLONG_MAX / 10;
		ov_mod = LLONG_MAX % 10 + 1;
	}
	else
	{
		ov_div = LLONG_MAX / 10;
		ov_mod = LLONG_MAX % 10;
	}
	if ((ov_div < num) || (ov_div == num && ov_mod < nxt))
		return (1);
	return (0);
}

static int	ft_isspace(int c)
{
	return (('\t' <= c && c <= '\r') || c == ' ');
}

int	ft_atoi(const char *str)
{
	int						i;
	int						minus;
	long					tmp;

	i = 0;
	tmp = 0;
	minus = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		minus = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		minus += is_ok((long long)tmp, *str, minus);
		if (minus == 0)
			return (-1);
		else if (minus == 2)
			return (0);
		tmp = 10 * tmp + (str[i] - '0');
		i++;
	}
	return ((int)(tmp * minus));
}

long long	ft_atoll(const char *str)
{
	long long	num;
	int			flag;

	flag = 1;
	num = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		flag = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
	{
		flag += is_ok(num, *str, flag);
		if (flag == 0)
			return (LLONG_MIN);
		else if (flag == 2)
			return (LLONG_MAX);
		num = 10 * num + (*str - '0');
		str++;
	}
	return (num * flag);
}
