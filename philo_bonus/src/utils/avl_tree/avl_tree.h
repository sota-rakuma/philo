/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_tree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 20:49:14 by srakuma           #+#    #+#             */
/*   Updated: 2021/12/11 14:08:49 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_TREE_H
# define AVL_TREE_H

# include <stdlib.h>
# include <semaphore.h>

typedef struct s_avl
{
	int				depth;
	unsigned int	key;
	int				val;
	struct s_avl	*parent;
	struct s_avl	*left;
	struct s_avl	*right;
}				t_avl;

t_avl	*create_node(int key, int val);
void	destruct_avl(t_avl *node);
int		add_node(t_avl *new, t_avl **node);
int		get_diff_of_depth(t_avl *left, t_avl *right);
int		rotate_avl(t_avl **node);
void	delete_node(t_avl **root, t_avl *target);
void	copy_node(t_avl *dst, t_avl *src);
void	replace_node(t_avl *a, t_avl *b);
t_avl	*search_max_val_node(t_avl *root);
t_avl	*search_min_val_node(t_avl *root);
t_avl	*seach_node(t_avl *node, int val);

#endif /* AVL_TREE_H */
