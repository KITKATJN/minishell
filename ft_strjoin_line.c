#include "minishell.h"

char		*ft_strjoin_line(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	result = malloc(ft_strlen_b((char*)s1) + ft_strlen_b((char*)s2) + 1);
	if (!result)
		return (NULL);
	while (s1 && s1[i] != '\0')
		result[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i] != '\0')
		result[j++] = s2[i++];
	result[j] = '\0';
	return (result);
}
