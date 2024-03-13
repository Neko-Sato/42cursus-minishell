/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:35:37 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/11 19:28:26 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLE_H
# define VARIABLE_H

char	*getvar(char **vars, char *key);
int		putvar(char ***vars_ptr, char *name);
int		setvar(char ***vars_ptr, char *key, char *value, int overwrite);
int		unsetvar(char **vars, char *key);

#endif