#include "minishell.h"

int ft_putchar(int c)
{
	write(1, &c, 1);
	return(0);
}

int ft_strlen_b(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while(str[i] != '\0')
		i++;
	return (i);
}

char *ft_strjoin_b(char *s1, char *s2)
{
	char *result;
	int i;
	int j;

	i = 0;
	j = 0;
	if (!(result = malloc(ft_strlen_b(s1) + ft_strlen_b(s2) + 1)))
		return (NULL);
	while (s1 && s1[i] != '\0')
		result[j++] = s1[i++];
	i = 0;
	result[j++] = s2[i];
	result[j] = '\0';
	ft_free(s1);
	return (result);
}

int		ft_lstsize_2(t_command *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
