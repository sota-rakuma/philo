/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_avl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 19:05:34 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/30 03:21:37 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl_tree.h"

int	get_diff_of_depth(t_avl *left, t_avl *right)
{
	int	left_depth;
	int	right_depth;

	left_depth = -1;
	if (left)
		left_depth = left->depth;
	right_depth = -1;
	if (right)
		right_depth = right->depth;
	return (left_depth - right_depth);
}

/*
* Pass the nodes hanging on root and target
* through node_1 and node_2 to this func.
*/
static void	recalcu_depth(t_avl *top, t_avl *target,
							t_avl *node_1, t_avl *node_2)
{
	if (node_1 == NULL && node_2 == NULL)
		top->depth = 0;
	else if (get_diff_of_depth(node_1, node_2) < 0)
		top->depth = node_2->depth + 1;
	else
		top->depth = node_1->depth + 1;
	if (target->depth < top->depth + 1)
		target->depth = top->depth + 1;
}

static void	right_rotation(t_avl **top)
{
	t_avl	*target;
	t_avl	*right_node_of_target;

	target = (*top)->left;
	right_node_of_target = NULL;
	if (target->right)
		right_node_of_target = target->right;
	target->parent = (*top)->parent;
	target->right = (*top);
	recalcu_depth(*top, target, right_node_of_target, (*top)->right);
	(*top)->left = right_node_of_target;
	if (right_node_of_target)
		right_node_of_target->parent = *top;
	(*top)->parent = target;
	*top = target;
}

static void	left_rotation(t_avl **top)
{
	t_avl	*target;
	t_avl	*left_node_of_target;

	target = (*top)->right;
	left_node_of_target = NULL;
	if (target->left)
		left_node_of_target = target->left;
	target->parent = (*top)->parent;
	target->left = (*top);
	recalcu_depth(*top, target, left_node_of_target, (*top)->left);
	(*top)->right = left_node_of_target;
	if (left_node_of_target)
		left_node_of_target->parent = *top;
	(*top)->parent = target;
	*top = target;
}

int	rotate_avl(t_avl **node)
{
	int	diff;

	diff = get_diff_of_depth((*node)->left, (*node)->right);
	if (1 < diff)
	{
		if (get_diff_of_depth((*node)->left->left, (*node)->left->right) < 0)
			left_rotation(&(*node)->left);
		right_rotation(node);
	}
	else if (diff < -1)
	{
		if (0 < get_diff_of_depth((*node)->right->left, (*node)->right->right))
			right_rotation(&(*node)->right);
		left_rotation(node);
	}
	return ((*node)->depth);
}
