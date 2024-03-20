/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:35:37 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/20 15:52:16 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLE_H
# define VARIABLE_H

const char	*getvar(char **vars, const char *key);
int			putvar(char ***vars_ptr, const char *name);
int			setvar(char ***vars_ptr, const char *key, const char *value,
				int overwrite);
int			unsetvar(char **vars, const char *key);

#endif