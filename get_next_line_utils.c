/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:27:55 by srobt             #+#    #+#             */
/*   Updated: 2021/11/25 12:45:56 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*init_objects(t_object *o, char **store)
{
	o->nl = (void *)FALSE;
	o->n = 1;
	o->i = 0;
	o->j = 0;
	if (!(*store))
	{
		*store = (char *)malloc(sizeof(char));
		if (!(*store))
			return (NULL);
		(*store)[0] = '\0';
	}
	o->buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!o->buffer)
	{
		free(store);
		return (NULL);
	}
	return ((void *)TRUE);
}

void	*concat_method(t_object *o, char **store)
{
	char	*string;

	o->buffer[o->n] = '\0';
	while (o->i < (size_t)o->n)
	{
		if (o->buffer[o->i] == '\n')
			o->nl = (void *)TRUE;
		o->i++;
	}
	while ((*store)[o->j])
		o->j++;
	string = (char *)malloc(sizeof(char) * (o->i + o->j + 1));
	if (!string)
		return (NULL);
	string[o->i + o->j] = '\0';
	while (o->i--)
		string[o->i + o->j] = o->buffer[o->i];
	while (o->j--)
		string[o->j] = (*store)[o->j];
	free((*store));
	o->i = 0;
	o->j = 0;
	*store = string;
	return (o->nl);
}

char	*split_method(t_object *o, char **store)
{
	while ((*store)[o->i] != '\0' && (*store)[o->i] != '\n')
		o->i++;
	o->j = o->i;
	while ((*store)[o->j] != '\0')
		o->j++;
	o->line = malloc(sizeof(char) * (o->i + ((*store)[o->i] == '\n') + 1));
	if (!o->line)
		return (NULL);
	o->remainder = malloc(sizeof(char) * (o->j - o->i + 1));
	if (!o->remainder)
	{
		free(o->line);
		return (NULL);
	}
	o->i += ((*store)[o->i] == '\n');
	o->line[o->i] = '\0';
	o->remainder[(o->j++) - o->i] = '\0';
	while ((o->j--) - o->i)
		o->remainder[o->j - o->i] = (*store)[o->j];
	while (o->i--)
		o->line[o->i] = (*store)[o->i];
	free((*store));
	*store = o->remainder;
	return (o->line);
}
