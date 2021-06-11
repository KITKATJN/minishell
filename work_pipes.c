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
		while (save)
		{
			//printf("dsfsdfsd*************\n");
			//printf("start->command  = %s\n", start->command );
			save->command = replace_dollar_que_into_code(save->command, untils);
			//printf("dsfsdfsd+++\n");
			save = save->next;
		}
		save = start;
		if (check_buildin(start->command))
		{
			untils->command_ex = ft_strdup_b(start->command);
			// start = start->next;
			if (check_bin(start->command))
			{
				if (!check_redir(start, 2, untils))
					exit(1);
				work_bin(start, untils);
			}
			if (!(find_path(untils)) && !(check_bin(start->command)))
			{
				printf("123\n");
				exit(127);
			}
			untils->path = find_path(untils);
			if (!untils->path)
				exit(1);
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
			start = save;
			commd = ft_strjoin_line("/", untils->command_ex);
			if (!check_redir(start, 2, untils))
				exit(1);
			// printf("DOSTAL\n");
			while(bin[i])
			{
				//проверка на наличие PATH;
				command = ft_strjoin_line(bin[i], commd);
				execve(command, arguments, untils->env);
				i++;
			}
			if (bin[i] == NULL && ft_strcmp(untils->command_ex, "minishell") && ft_strcmp(untils->command_ex, "./minishell") && ft_strcmp(untils->command_ex, "$?"))
				exit(127);
			if (ft_strcmp(untils->command_ex, "$?"))
				printf("0 : command not found");
		}
		else
		{
			bsophia_function(save, untils);
			exit(0);
		}
		return (1);
}
