/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:58:17 by hshimizu          #+#    #+#             */
/*   Updated: 2024/01/28 20:36:26 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPL_H
# define REPL_H

# include "command.h"
# include <stddef.h>

extern int	interruption;

typedef struct s_heredoc
{
	struct s_heredoc	*next;
	char				*eof;
	char				*contents;
}						t_heredoc;


#endif