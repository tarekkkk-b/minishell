/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:24:46 by ahaarij           #+#    #+#             */
/*   Updated: 2024/08/10 15:15:58 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_invalid(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	if (str[i] == '_' || (!(str[i] >= 'a' && str[i] <= 'z') \
	&& !(str[i] >= 'A' && str[i] <= 'Z')))
		return (1);
	while (str[i] && (str[i] == '_' || (str[i] >= '0' && str[i] <= '9') \
	|| (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')))
		i++;
	return (0);
}

void	splitkeyequalsvalue(const char *str, t_export *export, t_shell *shell)
{
	const char	*equal_sign = ft_strchr(str, '=');
	size_t		key_len;

	if (equal_sign == NULL)
		return ;
	key_len = equal_sign - str;
	export->key = ft_malloc(key_len + 1, shell);
	strncpy(export->key, str, key_len);
	export->key[key_len] = '\0';
	export->equal = ft_strdup("=");
	export->value = ft_strdup(equal_sign + 1);
}

static void	free_export(t_export *export)
{
	if (export)
	{
		if (export->key)
			ft_free((void **)&export->key);
		if (export->value)
			ft_free((void **)&export->value);
		if (export->equal)
			ft_free((void **)&export->equal);
		// if(export)
		// 	ft_free((void **)&export);
	}
}

static void	init_export(t_export *export)
{
	export->key = NULL;
	export->value = NULL;
	export->equal = NULL;
}

int	export(int argc, t_shell *shell, int i)
{
	t_values	*mane;
	t_export	export;
	char		**env_copy;
	int			n;
	int			j;

	init_export(&export);
	if (argc == 1 && shell->environ->env != NULL)
	{
		env_copy = arr(shell->environ->env, shell);
		n = count_values(shell->environ->env);
		sort_it_out(env_copy, n, 0, 0);
		printarray(env_copy, n, shell);
	}
	j = 1;
	while (argc > 1 && shell->exec[i]->cmd[j])
	{
		splitkeyequalsvalue(shell->exec[i]->cmd[j], &export, shell);
		if (export.equal == NULL)
			return (free_export(&export), 1);
		if (check_invalid(export.key) == 1)
		{
			printf("%s Not a valid identifier\n", export.key);
			free_export(&export);
			return (1);
		}
		else
		{
			mane = locate_node(shell->environ->env, export.key);
			if (mane != NULL)
				change_node(mane, export.value);
			else
				custom_node(shell, export.key, export.value);
			free_export(&export);
			init_export(&export);
		}
		j++;
	}
	free_export(&export);
	return (0);
}

// empty environment -> export
//export adsf
//export @ #
//export =
//export = = = ======
//export jksdf=23 @ # ej=55 @
