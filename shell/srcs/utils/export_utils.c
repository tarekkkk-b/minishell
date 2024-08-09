/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:56:19 by ahaarij           #+#    #+#             */
/*   Updated: 2024/08/09 16:55:11 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	splitkeyvalue(const char *str, char **key, char **value, t_shell *shell)
{
	const char	*equal_sign = ft_strchr(str, '=');
	size_t		key_len;

	if (equal_sign == NULL)
		return ;
	else
	{
		key_len = equal_sign - str;
		*key = ft_malloc(key_len + 1, shell);
		strncpy(*key, str, key_len);
		// ADD THIS TO AARIJ
		(*key)[key_len] = '\0';
		*value = ft_strdup(equal_sign + 1);
	}
}

static void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	count_values(t_values *env)
{
	int	count;

	count = 0;
	while (env != NULL)
	{
		count++;
		env = env->next;
	}
	return (count);
}

void	sort_it_out(char **arr, int n, int i, int j)
{
	if (n == 1)
		return ;
	if (j == n - 1)
	{
		sort_it_out(arr, n - 1, 0, 0);
		return ;
	}
	if (strcmp(arr[j], arr[j + 1]) > 0)
		swap(&arr[j], &arr[j + 1]);
	sort_it_out(arr, n, i, j + 1);
}

void	printarray(char **arr, int n, t_shell *shell)
{
	char	*key;
	char	*value;

	value = NULL;
	key = NULL;
	if (n == 0)
		return ;
	splitKeyValue(*arr, &key, &value, shell);
	printf("declare -x %s=\"%s\"\n", key, value);
	free(key);
	free(value);
	printArray(arr + 1, n - 1, shell);
}
