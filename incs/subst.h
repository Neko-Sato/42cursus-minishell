/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 21:32:18 by hshimizu          #+#    #+#             */
/*   Updated: 2024/02/17 21:32:59 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBST_H
# define SUBST_H

# include "command.h"

int	shell_expend_wordlist(t_wordlist *wordlist, t_wordlist **result,
		char *variable[]);
int	glob_expend_wordlist(t_wordlist *wordlist, t_wordlist **result,
		char *variable[]);

#endif
