/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write_cs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 19:22:07 by srakuma           #+#    #+#             */
/*   Updated: 2021/12/11 15:47:39 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_write_cs.h"

void	write_cs(t_cs *cs, long val)
{
	if (pthread_mutex_lock(&cs->value_mutex))
		print_err("mutex lock error", __FILE__, __func__);
	cs->value = val;
	if (pthread_mutex_unlock(&cs->value_mutex))
		print_err("mutex unlock error", __FILE__, __func__);
}

long	read_cs(t_cs *cs)
{
	long	ret;

	if (pthread_mutex_lock(&cs->value_mutex))
		print_err("mutex lock error", __FILE__, __func__);
	ret = cs->value;
	if (pthread_mutex_unlock(&cs->value_mutex))
		print_err("mutex unlock error", __FILE__, __func__);
	return (ret);
}

void	atomic_read_write(t_cs *cs, long val, t_op op)
{
	if (pthread_mutex_lock(&cs->value_mutex))
		print_err("mutex lock error", __FILE__, __func__);
	if (op == ADD)
		cs->value += val;
	else if (op == SUB)
		cs->value -= val;
	else if (op == MUL)
		cs->value *= val;
	else if (op == DIV)
		cs->value /= val;
	else if (op == MOD)
		cs->value %= val;
	else
		cs->value = val;
	if (pthread_mutex_unlock(&cs->value_mutex))
		print_err("mutex unlock error", __FILE__, __func__);
}

void	atomic_read_write_status(t_loop *loop, int val, t_op op)
{
	if (pthread_mutex_lock(&loop->value_mu))
		print_err("mutex lock error", __FILE__, __func__);
	if (op == ADD)
		loop->value += val;
	else if (op == SUB)
		loop->value -= val;
	else if (op == MUL)
		loop->value *= val;
	else if (op == DIV)
		loop->value /= val;
	else if (op == MOD)
		loop->value %= val;
	else
		loop->value = val;
	if (pthread_mutex_unlock(&loop->value_mu))
		print_err("mutex unlock error", __FILE__, __func__);
}

int	read_status(t_loop *loop)
{
	int	ret;

	if (pthread_mutex_lock(&loop->value_mu))
		print_err("mutex lock error", __FILE__, __func__);
	ret = loop->value;
	if (pthread_mutex_unlock(&loop->value_mu))
		print_err("mutex unlock error", __FILE__, __func__);
	return (ret);
}
