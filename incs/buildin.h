/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:35:37 by hshimizu          #+#    #+#             */
/*   Updated: 2023/12/09 06:57:54 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDIN_H
# define BUILDIN_H

int builtin_cho(int argc, char *argv[], char *envp[]);
int builtin_cd(int argc, char *argv[], char *envp[]);
int builtin_pwd(int argc, char *argv[], char *envp[]);
int builtin_export(int argc, char *argv[], char *envp[]);
int builtin_unset(int argc, char *argv[], char *envp[]);
int builtin_env(int argc, char *argv[], char *envp[]);
int builtin_exit(int argc, char *argv[], char *envp[]);

#endif