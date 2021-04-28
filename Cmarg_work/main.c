#include <stdio.h>

#include "head.h"
#include "libft.h"

t_command	*ft_lstnew_parser(void *command, void *flag)
{
	t_command	*lst;

	lst = (t_command*)malloc(sizeof(t_command));
	if (lst)
	{
		lst->command = command;
		lst->flag = flag;
		lst->next = 0;
	}
	return (lst);
}

void	ft_lstadd_back_parser(t_command **lst, t_command *new)
{
	t_command	*list;

	if (lst && new)
	{
		if (*lst == 0)
			*lst = new;
		else
		{
			list = *lst;
			while (list->next)
				list = list->next;
			list->next = new;
			new->back = list;
		}
	}
}

char *ft_check_command(char *command)
{
	if (command[0] == 'e')
	{
		if(!ft_strncmp(command, "echo", ft_strlen("echo")))
			return ("echo");
		if(!ft_strncmp(command, "env", ft_strlen("env")))
			return ("env");
		if(!ft_strncmp(command, "exit", ft_strlen("exit")))
			return ("exit");
		if(!ft_strncmp(command, "export", ft_strlen("export")))
			return ("export");
		return ("err");
	}
	if(!ft_strncmp(command, "cd", ft_strlen("cd")))
		return ("cd");
	if(!ft_strncmp(command, "pwd", ft_strlen("pwd")))
		return ("pwd");
	if(!ft_strncmp(command, "unset", ft_strlen("unset")))
		return ("unset");
	return ("err");
}

int delete_spaces(char **arr_of_command, char *argv, int i, char delimiter)
{
	int j;

	j = i + 1;
	while (j < ft_strlen(argv))
	{
		if (arr_of_command[j][0] == delimiter)
			break;
		j++;
	}
	free(arr_of_command[i + 1]);
	printf("->%d\n", j + 1);
	arr_of_command[i + 1] = ft_substr(argv, i, j - i + 1);
	arr_of_command[i][0] = '\0';
	i += 2;
	while (i < j + 1)
	{
		arr_of_command[i][0] = '\0';
		i++;
	}
	return (i);
}

t_command *parser(char *argv)
{
	int i = 0;
	char **arr_of_command;

	arr_of_command = malloc(sizeof(char*) * ft_strlen(argv));
	printf("before\n");
	while (i < ft_strlen(argv))
	{
		arr_of_command[i] = malloc(sizeof(char) * 2);
		arr_of_command[i][0] = argv[i];
		arr_of_command[i][1] = '\0';
		printf("i = %d str = !%s!\n", i, arr_of_command[i]);
		i++;
	}

	i = 0;
	int j;
	while (i < ft_strlen(argv))
	{
		if (arr_of_command[i][0] == ' ')
			arr_of_command[i][0] = '\0';

		if (arr_of_command[i][0] == '\'')
		{
			i = delete_spaces(arr_of_command, argv, i, '\'');
			// j = i + 1;
			// while (j < ft_strlen(argv))
			// {
			// 	if (arr_of_command[j][0] == '\'')
			// 		break;
			// 	j++;
			// }
			// free(arr_of_command[i + 1]);
			// printf("->%d\n", j + 1);
			// arr_of_command[i + 1] = ft_substr(argv, i + 1, j - i - 1);
			// arr_of_command[i + 2][0] = '\'';
			// i += 3;
			// while (i < j + 1)
			// {
			// 	arr_of_command[i][0] = '\0';
			// 	i++;
			// }
			continue ;
		}
		if (arr_of_command[i][0] == '\"')
		{
			i = delete_spaces(arr_of_command, argv, i, '\"');
			continue ;
		}
		i++;
	}

	i = 0;
	while (i < ft_strlen(argv))
	{
		if (arr_of_command[i][0] != '\0' && arr_of_command[i][0] != '\'' && arr_of_command[i][0] != '\"')
		{
			j = i;
			while (j < ft_strlen(argv))
			{
				if (arr_of_command[j][0] == '\0')
					break ;
				j++;
			}
			free(arr_of_command[i]);
			arr_of_command[i] = ft_substr(argv, i, j - i);
			i++;
			while (i < j)
			{
				arr_of_command[i][0] = '\0';
				i++;
			}
			continue ;
		}
		i++;
	}


	i = 0;
	printf("after\n");
	while (i < ft_strlen(argv))
	{
		printf("i = %d str = !%s!\n", i, arr_of_command[i]);
		i++;
	}

	t_command *start = 0;
	t_command *new_element = 0;
	i = 0;
	while (i < ft_strlen(argv))
	{
		if (arr_of_command[i][0] != '\0')
		{
			new_element = ft_lstnew_parser(ft_strdup(arr_of_command[i]), 0);
			ft_lstadd_back_parser(&start, new_element);
			printf("num of operation = %d cont = %s\n", i, new_element->command);
		}
		i++;
	}
	i = 0;
	while(i < ft_strlen(argv))
	{
		free(arr_of_command[i]);
		i++;
	}
	free(arr_of_command);

	return start;
}


int main(int argc, char** argv)
{
	t_command	*start;


	start = 0;
	start = parser("echo  -n     'y   sdf jghmj' \"f dfsds\"  h    ffvx sdf ft        mkk");
	while (start)
	{
		printf("final=!%s!\n", start->command);
		start = start->next;
	}
	return 0;
}
