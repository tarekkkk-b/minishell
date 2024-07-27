/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:36:06 by tabadawi          #+#    #+#             */
/*   Updated: 2024/07/27 18:23:43 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

int	main()
{
	open("/Users/tabadawi/Desktop/minishell/mini_shell/includes/.test_file", O_CREAT | O_TRUNC, 0600);
	sleep(5);
	unlink("/Users/tabadawi/Desktop/minishell/mini_shell/includes/.test_file");
}