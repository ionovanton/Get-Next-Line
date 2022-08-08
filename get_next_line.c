/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:25:22 by srobt             #+#    #+#             */
/*   Updated: 2021/11/25 12:47:58 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*store;
	t_object	o;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || !init_objects(&o, &store))
		return (NULL);
	while (o.n > 0)
	{
		o.n = read(fd, o.buffer, BUFFER_SIZE);
		if (o.n < 0)
			break ;
		o.nl = concat_method(&o, &store);
		if (o.n != BUFFER_SIZE || o.nl == (void *)TRUE)
		{
			if (store[0] == '\0')
				break ;
			free(o.buffer);
			return (split_method(&o, &store));
		}
	}
	free(store);
	free(o.buffer);
	return (store = NULL);
}
