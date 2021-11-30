/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:38:48 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/30 02:47:56 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl_tree.h"

void	reconstruct_avl(t_avl *exchange_parent, t_avl *exchange)
{
	int	diff;

	diff = 0;
	while (exchange_parent != exchange->parent)
	{
		rotate_avl(&exchange_parent);
		diff = get_diff_of_depth(exchange_parent->left, \
									exchange_parent->right);
		if (exchange_parent->left == NULL && exchange_parent->right == NULL)
			exchange_parent->depth = 0;
		else if (diff > 0)
			exchange_parent->depth = exchange_parent->left->depth + 1;
		else
			exchange_parent->depth = exchange_parent->right->depth + 1;
		exchange_parent = exchange_parent->parent;
	}
}

static t_avl	*replace_and_del_left(t_avl *target, t_avl *exchange)
{
	t_avl	*parent;

	if (target->right)
		target->right->parent = exchange;
	exchange->right = target->right;
	parent = exchange;
	if (exchange->parent != target)
	{
		exchange->parent->right = exchange->left;
		exchange->left = target->left;
		target->left->parent = exchange;
		parent = exchange->parent;
	}
	exchange->parent = target->parent;
	reconstruct_avl(parent, exchange);
	return (exchange);
}

static t_avl	*replace_and_del(t_avl *target)
{
	t_avl	*exchange;

	exchange = NULL;
	if (target->left)
	{
		exchange = replace_and_del_left(target, \
					search_max_val_node(target->left));
	}
	else if (target->right)
	{
		target->left->parent = target->right;
		target->right->left = target->left;
		exchange = target->right;
	}
	free(target);
	return (exchange);
}

void	delete_node(t_avl **root, t_avl *target)
{
	t_avl	*parent;

	if (target == NULL)
		return ;
	parent = target->parent;
	if (parent == NULL)
		*root = replace_and_del(target);
	else if (parent->val < target->val)
		parent->right = replace_and_del(target);
	else
		parent->left = replace_and_del(target);
}
