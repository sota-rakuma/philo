/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destruct_avl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 18:19:16 by srakuma           #+#    #+#             */
/*   Updated: 2021/12/11 14:21:33 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl_tree.h"

void	destruct_avl(t_avl *node)
{
	if (node == NULL)
		return ;
	if (node->left)
		destruct_avl(node->left);
	if (node->right)
		destruct_avl(node->right);
	free(node);
}
