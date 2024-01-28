/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:15:39 by hshimizu          #+#    #+#             */
/*   Updated: 2024/01/26 23:12:11 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORD_H
# define WORD_H

typedef struct s_wordlist
{
	struct s_wordlist	*next;
	char				*word;
}						t_wordlist;

char					*expand_singlquoted(char *word);
char					*expand_doublequoted(char *word);
char					*expand_dollar(char *word);
char					*expand_asterisk(char *word);

t_wordlist				*expand_word(char *);

char					**stringarray4wordlist(void);

#endif