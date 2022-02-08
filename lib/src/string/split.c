#include "libft.h"

static char	**del_strs(char *strs[])
{
	int	i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
	return (NULL);
}

static int	count_words(char const *s, char delim)
{
	int		i;
	int		count;
	bool	prev_delim;

	i = -1;
	count = 1;
	prev_delim = false;
	while (s[++i])
	{
		if (s[i] == delim)
			prev_delim = true;
		else if (prev_delim)
		{
			prev_delim = false;
			count++;
		}
	}
	return (count);
}

static int	wordlen(int i, char const *s, char const c)
{
	int	len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

static char	**write_words(char **strarr, int words, char const *s, char c)
{
	int	i;
	int	j;
	int	word_idx;

	i = 0;
	word_idx = -1;
	while (++word_idx < words)
	{
		while (s[i] == c)
			i++;
		strarr[word_idx] = malloc((wordlen(i, s, c) + 1) * sizeof(char));
		if (!strarr[word_idx])
			return (del_strs(strarr));
		strarr[word_idx][wordlen(i, s, c)] = '\0';
		j = 0;
		while (s[i] && s[i] != c)
			strarr[word_idx][j++] = s[i++];
	}
	return (strarr);
}

char	**ft_split(char const *s, char c)
{
	char	**strarr;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	strarr = malloc((words + 1) * sizeof(char *));
	if (!strarr)
		return (del_strs(strarr));
	strarr[words] = NULL;
	return (write_words(strarr, words, s, c));
}
