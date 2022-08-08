/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:48:37 by srobt             #+#    #+#             */
/*   Updated: 2021/11/25 12:47:31 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

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

// Boolean type
typedef uint8_t	t_bool;
# define TRUE 1
# define FALSE 0

typedef struct s_nstore
{
	char	**new;
	size_t	i;
}	t_nstore;

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

void	*init_objects(t_object *o, t_nstore *ns, char ***store, size_t fd);
char	*split_method(t_object *o, char **store);
void	*concat_method(t_object *o, char **store);
char	*get_next_line(int fd);
void	*realloc_store(char ***store, t_nstore *ns, size_t fd);
void	*free_two_dimensional(char ***arr, t_bool to_remove);

#endif // GET_NEXT_LINE_BONUS_H
