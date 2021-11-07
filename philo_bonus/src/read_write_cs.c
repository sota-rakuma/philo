/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write_cs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 02:39:42 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/08 02:42:31 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_write_cs.h"

long	read_cs(t_cs *cs)
{
	long	ret;

	sem_wait(cs->sem);
	ret = cs->val;
	sem_post(cs->sem);
	return (ret);
}

void	atomic_read_write(t_cs *cs, long val, t_op op)
{
	sem_wait(cs->sem);
	if (op == ADD)
		cs->val += val;
	else if (op == SUB)
		cs->val -= val;
	else if (op == MUL)
		cs->val *= val;
	else if (op == DIV)
		cs->val /= val;
	else if (op == MOD)
		cs->val %= val;
	else
		cs->val = val;
	sem_post(cs->sem);
}
