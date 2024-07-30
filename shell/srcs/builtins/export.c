/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:24:46 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/29 12:54:17 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_invalid(char *str)
{
	int i = 0;
	if(str[i] == '\0')
		return (0);
	if(str[i] == '_' || (!(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z')))
		return (1);
	while(str[i] && (str[i] == '_' || (str[i] >= '0' && str[i] <= '9')
		|| (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')))
		i++;
	return(0);
}

void splitKeyEqualsValue(const char *str, char **key, char **equals,
				char **value, t_shell *shell)
{
    const char *equal_sign = ft_strchr(str, '=');
    
    if (equal_sign == NULL)
		return ;
    else
	{
        size_t key_len = equal_sign - str;
        *key = ft_malloc(key_len + 1, shell);
        strncpy(*key, str, key_len);
        (*key)[key_len] = '\0';
        *equals = ft_strdup("=");
        *value = ft_strdup(equal_sign + 1);
    }
}

int export(int argc, t_shell *shell, int i)
{
	char	*key = NULL;
	char	*value = NULL;
	char	*equal= NULL;
	char    **env_copy;
    int		n;
	t_values *mane;
	if(argc == 1 && shell->environ->env != NULL)
	{
    	env_copy = arr(shell->environ->env, shell);
    	n = count_values(shell->environ->env);
    	sort_it_out(env_copy, n, 0, 0);
		printArray(env_copy, n, shell);
	}
	int j = 1;
	while(argc > 1 && shell->exec[i]->cmd[j])
	{
		splitKeyEqualsValue(shell->exec[i]->cmd[j], &key, &equal, &value, shell);
		if(equal == NULL)
			return(1);
		if(check_invalid(key) == 1)
		{
			printf("%s Not a valid identifier\n", key);
			free(key);
			free(equal);
			free(value);
			return (1);
		}
		else
		{
			mane = locate_node(shell->environ->env, key);
			if(mane != NULL)
				change_node(mane, value);
			else
				custom_node(shell, key, value);
			free(key);
			free(value);
			free(equal);
		}
		j++;
	}
    return 0;
}

// empty environment -> export
//export adsf
//export @ #
//export =
//export = = = ======
//export jksdf=23 @ # ej=55 @
