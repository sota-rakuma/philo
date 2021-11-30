/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 00:11:51 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/29 04:42:22 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl_tree.h"

void	replace_node(t_avl *a, t_avl *b)
{
	int	tmp_key;
	int	tmp_val;
	int	tmp_depth;

	if ((a == NULL) || (b == NULL))
		return ;
	tmp_depth = a->depth;
	tmp_key = a->key;
	tmp_val = a->val;
	a->depth = b->depth;
	a->key = b->key;
	a->val = b->val;
	b->depth = tmp_depth;
	b->key = tmp_key;
	b->val = tmp_val;
}
