/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 20:47:45 by srobt             #+#    #+#             */
/*   Updated: 2021/11/25 12:45:51 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*free_two_dimensional(char ***arr, t_bool to_remove)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (!to_remove && (*arr)[i])
	{
		while ((*arr)[i][j])
		{
			j++;
			if (j > 0)
				return (NULL);
		}
		i++;
	}
	i = 0;
	while ((*arr)[i])
		free((*arr)[i++]);
	free((*arr));
	(*arr) = NULL;
	return (NULL);
}

void	*realloc_store(char ***store, t_nstore *ns, size_t fd)
{
	while ((*store)[ns->i])
		ns->i++;
	if (fd > ns->i)
	{
		ns->new = (char **)malloc(sizeof(char *) * (fd + 1));
		if (!ns->new)
			return (NULL);
		ns->new[fd] = NULL;
		while ((fd--) - ns->i)
		{
			ns->new[fd] = (char *)malloc(sizeof(char));
			if (!ns->new[fd])
				return (free_two_dimensional(&ns->new, TRUE));
			ns->new[fd][0] = '\0';
		}
		while (ns->i--)
			ns->new[ns->i] = (*store)[ns->i];
		free((*store));
		(*store) = ns->new;
	}
	return ((void *)TRUE);
}

void	*init_objects(t_object *o, t_nstore *ns, char ***store, size_t fd)
{
	o->nl = (void *)FALSE;
	o->n = 1;
	o->i = 0;
	o->j = 0;
	ns->i = 0;
	if (!(*store))
	{
		(*store) = (char **)malloc(sizeof(char *) * (fd + 1));
		if (!(*store))
			return (NULL);
		(*store)[fd] = NULL;
		while (ns->i < fd)
		{
			(*store)[ns->i] = (char *)malloc(sizeof(char));
			if (!(*store)[ns->i])
				return (free_two_dimensional(&(*store), TRUE));
			(*store)[ns->i++][0] = '\0';
		}
	}
	if (!realloc_store(&(*store), &(*ns), fd))
		return (NULL);
	o->buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!o->buffer)
		return (free_two_dimensional(&(*store), TRUE));
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
	(*store) = string;
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
