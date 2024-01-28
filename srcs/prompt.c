/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 23:17:12 by hshimizu          #+#    #+#             */
/*   Updated: 2024/01/28 20:34:22 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>
#include <readline.h>
#include <signal.h>

static char	*add_line(char *line, char *new_line);
static void	signal_handler(int n);
static int	event_hook(void);

/*
    struct sigaction sa;

    // ハンドラを設定
    sa.sa_handler = sigint_handler;
    // 他のフラグや設定を行う場合には必要に応じて以下を設定
    // sa.sa_flags = ...;

    // SIGINTに対するハンドラを設定
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
*/

int	put_prompt(t_minishell *gvars)
{
	struct sigaction	sa;
	char				*temp;
	char				*next;

	if (gvars->isinteractive)
		if (!gvars->line)
			gvars->line = readline((char *[]){NULL, PS1}[gvars->isinteractive]);
		else
		{
			temp = gvars->line;
			next = readline((char *[]){NULL, PS2}[gvars->isinteractive]);
			if (next)
				gvars->line = add_line(temp, next);
			free(temp);
			free(next);
		}
	if (!gvars->line)
		return (-1);
	return (0);
}

static char	*add_line(char *line, char *new_line)
{
	char	*ret;
	size_t	size;

	if (!line || !new_line)
		return (NULL);
	size = ft_strlen(line) + ft_strlen(new_line) + 2;
	ret = (char *)malloc(sizeof(char) * size);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, line, size);
	ft_strlcpy(ret, "\n", size);
	ft_strlcpy(ret, new_line, size);
	return (ret);
}

static void	signal_handler(int n)
{
	if (n == SIGINT)
		interruption = 1;
}

static int	event_hook(void)
{
	if (interruption)
		rl_done = 1;
	return (0);
}
