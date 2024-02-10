/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 23:38:04 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/10 23:42:50 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENT_H
# define ELEMENT_H

typedef struct s_wordlist
{
	struct s_wordlist	*next;
	char				*word;
}						t_wordlist;

typedef struct s_heredoc
{
	struct s_heredoc	*next;
	char				*eof;
	char				*contents;
}						t_heredoc;

typedef enum s_redirecttype
{
	RT_INPUT,
	RT_HEREDOC,
	RT_OVERWRITE,
	RT_APPEND,
}						t_redirecttype;

typedef struct s_redirect
{
	struct s_redirect	*next;
	t_redirecttype		type;
	char				*word;
}						t_redirect;

void					dispose_wordlist(t_wordlist *wordlist);
void					dispose_redirect(t_redirect *redirect);

#endif