/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:56:19 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/24 19:11:41 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void splitKeyValue(const char *str, char **key, char **value, t_shell *shell)
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
        
        *value = ft_strdup(equal_sign + 1);
    }
}

static void swap(char **a, char **b)
{
	char *temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int count_values(t_values *env)
{
	int count = 0;
	while (env != NULL)
	{
		count++;
		env = env->next;
	}
	return count;
}

void sort_it_out(char **arr, int n, int i, int j)
{
	if (n == 1)
		return;
	if (j == n - 1) {
		sort_it_out(arr, n - 1, 0, 0);
		return;
	}
	if (strcmp(arr[j], arr[j + 1]) > 0) {
		swap(&arr[j], &arr[j + 1]);
	}
	sort_it_out(arr, n, i, j + 1);
}


void printArray(char **arr, int n, t_shell *shell)
{
    if (n == 0) 
		return;
	char *key = NULL;
	char *value = NULL;
	splitKeyValue(*arr, &key, &value, shell);
    printf("declare -x %s=\"%s\"\n", key, value);
	free(key); // hehe freaky;
	free(value);
    printArray(arr + 1, n - 1, shell);
}