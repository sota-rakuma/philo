/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write_cs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 02:40:12 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/08 03:11:01 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_WRITE_CS_H
# define READ_WRITE_CS_H

# include <semaphore.h>

typedef enum e_op
{
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	ASSIGN,
}			t_op;

typedef struct s_cs
{
	long	val;
	sem_t	*sem;
}				t_cs;

long	read_cs(t_cs *cs);
void	atomic_read_write(t_cs *cs, long val, t_op op);

#endif