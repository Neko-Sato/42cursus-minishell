/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:55:29 by hshimizu          #+#    #+#             */
/*   Updated: 2024/01/26 22:02:04 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	reader_loop(vars)
{
	while (1)
	{
		if (read_command(vars))
			return -1;
		execute_command(vars);
		dispose_command(vars);
	}
	return 0;
}
