/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 03:12:06 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/02 14:02:27 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stddef.h>

int	get_word(char **line, size_t *pos, char **word);
int	skip_space(char **line, size_t *pos);
int	skip_word(char **line, size_t *pos);

#endif
