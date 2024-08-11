/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:55:07 by ahaarij           #+#    #+#             */
/*   Updated: 2024/08/11 12:55:33 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**set_up_path(t_shell *shell)
{
	t_values	*locate;
	char		**path;

	locate = locate_node(shell->environ->env, "PATH");
	if (!locate)
		return (NULL);
	path = ft_split(locate->value, ':');
	path[0] = ft_strtrim(path[0], "PATH=", 1);
	return (path);
}
