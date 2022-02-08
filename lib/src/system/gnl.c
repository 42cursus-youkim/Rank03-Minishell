#include "libft.h"

static char	*sliced(char **backup, int nl_idx)
{
	char	*sliced_str;

	sliced_str = new_yslice(*backup, 0, nl_idx + 1);
	ystr_replace(backup, new_yslice(*backup, nl_idx + 1, ystrlen(*backup)));
	return (sliced_str);
}

static char	*result(char **backup, int read_length)
{
	char	*temp;

	if (read_length == ERR || ystrlen(*backup) == 0)
		return (NULL);
	temp = new_ystr(*backup);
	ystr_replace(backup, new_ystr(""));
	return (temp);
}

/*	gnl but with fancy name. returns NULL if no line to read.
	keep in mind that it uses static char*[] to hold the lines.
*/
char	*gnl(int fd)
{
	int			nl_idx;
	int			read_length;
	char		buf[BUFFER_SIZE + 1];
	static char	*backup[OPEN_MAX];

	read_length = 0;
	if (!backup[fd])
		backup[fd] = new_ystr("");
	while (true)
	{
		read_length = yread(fd, buf, BUFFER_SIZE);
		if (read_length == 0)
			break ;
		if (read_length == ERR)
			return (NULL);
		ystr_append(&backup[fd], buf);
		nl_idx = ystrchri(backup[fd], '\n');
		if (nl_idx >= 0)
			return (sliced(&backup[fd], nl_idx));
	}
	return (result(&backup[fd], read_length));
}
