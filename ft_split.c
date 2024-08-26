/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: largenzi <largenzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:17:24 by largenzi          #+#    #+#             */
/*   Updated: 2024/08/24 13:44:03 by largenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((char *)s + i) = c;
		i++;
	}
	return (s);
}


size_t	ft_strlen(const char *s)
{
	const char	*initial;
	size_t		count;

	initial = s;
	count = 0;
	while (*s != '\0')
	{
		count++;
		s++;
	}
	s = initial;
	return (count);
}


char	*ft_strdup(const char *s)
{
	size_t	size_malloc;
	char	*new;
	char	*initial;

	size_malloc = (ft_strlen(s) + 1) * sizeof(char);
	new = malloc(size_malloc);
	if (new == NULL)
	{
		return (NULL);
	}
	else
		initial = new;
	while (*s != '\0')
	{
		*new = *s;
		new++;
		s++;
	}
	*new = '\0';
	new = initial;
	return (new);
}


void	*ft_calloc(size_t count, size_t size)
{
	void	*memory;
	size_t	len_memory;

	if (size != 0 && count > 2147483647 / size)
		return (0);
	len_memory = count * size;
	memory = (void *)malloc(len_memory);
	if (memory == NULL)
	{
		return (NULL);
	}
	else
		ft_memset(memory, '\0', len_memory);
	return (memory);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_length;
	size_t	i;
	char	*initial;

	initial = (char *)src;
	src_length = ft_strlen(src);
	if (dstsize != 0)
	{
		i = dstsize - 1;
		while (*src != '\0' && i > 0)
		{
			*dst = *src;
			src++;
			dst++;
			i--;
		}
		*dst = '\0';
	}
	src = initial;
	return (src_length);
}


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*p_in_s;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	substr = ft_calloc(len + 1, sizeof(char));
	if (substr == NULL)
		return (NULL);
	p_in_s = (char *)s + start;
	ft_strlcpy(substr, p_in_s, (len + 1));
	return (substr);
}


static unsigned int	how_many_words(char const *s, char c)
{
	unsigned int	count_words;
	unsigned int	i;

	i = 0;
	count_words = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	if (s[i] != '\0')
		count_words = 1;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i +1] != c && s[i + 1] != '\0')
			count_words++;
		i++;
	}
	return (count_words);
}

static char	**set_initial_output(const char *s, char c)
{
	char	**output;

	if (s == NULL)
		return (NULL);
	output = malloc((how_many_words(s, c) + 1) * sizeof(char *));
	if (output == NULL)
		return (NULL);
	return (output);
}

static char	**delete(int n, char **output)
{
	while (n > 0)
	{
		free(output[n]);
		n--;
	}
	free(output[n]);
	free(output);
	return (NULL);
}

static void	finding_len(unsigned int *i, char c, unsigned int *initial,
	const char *s)
{
	while (s[*i] == c)
		*i = *i + 1;
	if (s[*i] != '\0')
		*initial = *i;
	while (s[*i] != c && s[*i] != '\0')
		*i = *i + 1;
}

char	**ft_split(const char *s, char c)
{
	unsigned int	initial;
	unsigned int	n;
	unsigned int	i;
	size_t			len;
	char			**output;

	output = set_initial_output(s, c);
	if (!output)
		return (NULL);
	initial = 0;
	i = 0;
	n = 0;
	while (n < (how_many_words(s, c) + 1) - 1)
	{
		finding_len(&i, c, &initial, s);
		len = (size_t)(i - initial);
		output[n] = ft_substr(s, (unsigned int)initial, len);
		if (output[n] == NULL)
			return (delete(n, output));
		n++;
	}
	output[n] = NULL;
	return (output);
}
