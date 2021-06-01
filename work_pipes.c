#include "minishell.h"

int work_pipes(t_untils *untils, t_command *start)
{
	t_command *save;
	save = start;
		redirect_check(start);
		// while (start) // echo pl | echo hgfda123 | echo 456
		// 	{
		// 		printf("%s  dr = %s  right = %s left = %s ->%d\n", start->command, start->redir_double_right, start->redir_right, start->redir_left, i);
		// 		start = start->next;
		// 	}
		if (check_buildin(start->command))
		{
			untils->command_ex = ft_strdup_b(start->command);
			// start = start->next;
			untils->path = find_path(untils);
			char **bin = ft_split(untils->path, ':');
			char **arguments;
			int i = 0;
			while (start)
			{
				start = start->next;
				i++;
			}
			arguments = (char**)malloc(i * sizeof(char*) + 1);
			start = save;
			i = 0;
			while (start)
			{
				arguments[i] = ft_strdup_b(start->command);
				start = start->next;
				i++;
			}
			arguments[i] = NULL;
			// i = 0;
			// int id;
			// id = fork();
			char *command;
			command = NULL;
			// start = save;
			//дочка
			char *commd;
			commd = ft_strjoin_line("/", untils->command_ex);
			check_redir(save, 2, untils);
			while(bin[i] != NULL)
			{
				command = ft_strjoin_line(bin[i], commd);
				if (execve(command, arguments, untils->env) == 0)
				{
					return (-1);
				}
				i++;
			}
		}
		else
			bsophia_function(save, untils);
		return (0);
}
