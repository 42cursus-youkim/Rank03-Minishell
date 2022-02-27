#include "libft.h"

static char	*sliced(char **backup, int nl_idx)
{
	char	*sliced_str;

	sliced_str = new_str_slice(*backup, 0, nl_idx + 1);
	ft_str_replace(
		backup, new_str_slice(*backup, nl_idx + 1, ft_strlen(*backup)));
	return (sliced_str);
}

static char	*result(char **backup, int read_length)
{
	char	*temp;

	if (read_length == ERR || ft_strlen(*backup) == 0)
		return (NULL);
	temp = new_str(*backup);
	ft_str_replace(backup, new_str(""));
	return (temp);
}

/*	returns NULL if no line to read. does not keep '\n'.
	it uses static char*[] to hold the lines.
*/
char	*ft_gnl(int fd)
{
	int			nl_idx;
	int			read_length;
	char		buf[BUFFER_SIZE + 1];
	static char	*backup[OPEN_MAX];

	read_length = 0;
	if (!backup[fd])
		backup[fd] = new_str("");
	while (true)
	{
		read_length = ft_read(fd, buf, BUFFER_SIZE);
		if (read_length == 0)
			break ;
		if (read_length == ERR)
			return (NULL);
		ft_str_extend(&backup[fd], buf);
		nl_idx = ft_strchr_i(backup[fd], '\n');
		if (nl_idx >= 0)
			return (sliced(&backup[fd], nl_idx));
	}
	return (result(&backup[fd], read_length));
}
