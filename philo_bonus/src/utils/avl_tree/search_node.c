/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 00:03:04 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/28 00:11:21 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl_tree.h"

t_avl	*search_max_val_node(t_avl *root)
{
	t_avl	*max;

	max = root;
	while (max->right)
		max = max->right;
	return (max);
}

t_avl	*search_min_val_node(t_avl *root)
{
	t_avl	*min;

	min = root;
	while (min->left)
		min = min->left;
	return (min);
}

t_avl	*seach_node(t_avl *node, int val)
{
	if (node == NULL)
		return (NULL);
	if (node->val == val)
		return (node);
	if (node->val < val)
		return (seach_node(node->right, val));
	return (seach_node(node->left, val));
}
