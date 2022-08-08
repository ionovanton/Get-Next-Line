/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 20:47:38 by srobt             #+#    #+#             */
/*   Updated: 2021/11/25 12:47:28 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	**store;
	t_nstore	ns;
	t_object	o;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || \
	!init_objects(&o, &ns, &store, fd + 1))
		return (NULL);
	while (o.n > 0)
	{
		o.n = read(fd, o.buffer, BUFFER_SIZE);
		if (o.n < 0)
			break ;
		o.nl = concat_method(&o, &store[fd]);
		if (o.n != BUFFER_SIZE || o.nl == (void *)TRUE)
		{
			if (store[fd][0] == '\0')
				break ;
			free(o.buffer);
			if (!split_method(&o, &store[fd]))
				return (free_two_dimensional(&store, TRUE));
			return (o.line);
		}
	}
	free(o.buffer);
	return (free_two_dimensional(&store, FALSE));
}
