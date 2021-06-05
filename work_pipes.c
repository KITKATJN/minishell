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
			arguments = (char**)malloc(sizeof(char*) * (i + 1));
			start = save;
			i = 0;
			while (start)
			{
				arguments[i] = ft_strdup_b(start->command);
				// printf("!!! %s !!!\n", start->command);
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
			//д]очка
			char *commd;
			commd = ft_strjoin_line("/", untils->command_ex);
			check_redir(save, 2, untils);
			// printf("DOSTAL\n");
			while(bin[i])
			{
				command = ft_strjoin_line(bin[i], commd);
				execve(command, arguments, untils->env);
				i++;
			}
			exit(0);
		}
		else
			bsophia_function(save, untils);
		return (0);
}
