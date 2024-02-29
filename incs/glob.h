/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 04:35:49 by hshimizu          #+#    #+#             */
/*   Updated: 2024/03/01 01:01:54 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOB_H
# define GLOB_H

char	**globfilename(char *pattern);
char	**glob_vector(char *filename, char *dirname);

int		glob_testdir(char *dir);
int		glob_match(char *filename, char *pattern);
int		glob_pattern(char *stirng);
char	**glob_dir_to_array(char *dir, char **arry);

#endif