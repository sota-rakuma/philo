/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write_cs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:20:17 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/06 20:04:50 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_WRITE_CS_H
# define READ_WRITE_CS_H

# include <pthread.h>
# include "ft_struct.h"
# include "philo_utils.h"

typedef enum e_status
{
	TAKEN_A_FORK,
	EAT,
	SLEEP,
	THINK,
	DIED,
}			t_status;

typedef enum e_op
{
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	ASSIGN,
}			t_op;

void	write_cs(t_cs *cs, long val);
long	read_cs(t_cs *cs);
void	atomic_read_write(t_cs *cs, long val, t_op op);
int		read_status(t_loop *st);
void	atomic_read_write_status(t_loop *loop, int val, t_op op);

#endif