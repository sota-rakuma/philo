/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destruct_avl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 18:19:16 by srakuma           #+#    #+#             */
/*   Updated: 2021/11/30 20:56:46 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl_tree.h"
#include <signal.h>

void	destruct_avl(t_avl *node)
{
	if (node == NULL)
		return ;
	if (node->left)
		destruct_avl(node->left);
	if (node->right)
		destruct_avl(node->right);
	kill(node->val, SIGTERM);
	free(node);
}
