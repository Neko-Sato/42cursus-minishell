/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:42:25 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/08 11:33:11 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBS_H
# define JOBS_H

# include <sys/types.h>

typedef struct s_proc
{
	struct s_proc			*next;
	pid_t					pid;
	int						status;
	int						running;
}							t_proc;

typedef struct s_minishell	t_minishell;

pid_t						make_child(t_minishell *shell);
int							wait_for(t_minishell *shell, pid_t pid);

#endif