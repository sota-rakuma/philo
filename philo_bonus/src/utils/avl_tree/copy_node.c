/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 00:15:03 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/29 04:37:18 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl_tree.h"

void	copy_node(t_avl *dst, t_avl *src)
{
	if (src->parent && (src->parent != dst))
	{
		if (src->parent->val < src->val)
			src->parent->right = dst;
		else
			src->parent->left = dst;
	}
	dst->parent = src->parent;
	dst->left = src->left;
	dst->right = src->right;
	dst->depth = src->depth;
	dst->key = src->key;
	dst->val = src->val;
}
