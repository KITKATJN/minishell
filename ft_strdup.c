#include "minishell.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*b;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i] != '\0')
		i++;
	b = (char*)malloc(sizeof(char) * (i + 1));
	if (b == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		b[i] = src[i];
		i++;
	}
	b[i] = '\0';
	return (b);
}
