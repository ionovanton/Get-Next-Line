/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:48:37 by srobt             #+#    #+#             */
/*   Updated: 2021/11/25 12:48:03 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h> // ssize_t, read
# include <stdlib.h> // malloc, free
# include <limits.h> // OPEN_MAX
# include <stdint.h> // uint8_t

// Linux specific
# ifndef OPEN_MAX
#  define OPEN_MAX 10240
# endif // OPEN_MAX

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif // BUFFER_SIZE

/* Boolean type */
typedef uint8_t	*t_bool;
# define TRUE 1
# define FALSE 0

typedef struct s_object
{
	char	*buffer;
	char	*line;
	char	*remainder;
	t_bool	*nl;
	ssize_t	n;
	size_t	i;
	size_t	j;
}	t_object;

void	*init_objects(t_object *o, char **store);
char	*split_method(t_object *o, char **store);
void	*concat_method(t_object *o, char **store);
char	*get_next_line(int fd);

#endif // GET_NEXT_LINE_H
