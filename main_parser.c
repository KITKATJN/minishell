#include "minishell.h"

t_command		*redirect_check(t_command *com, t_untils *untils)
{
	t_command	*start;

	start = com;
//printf("1.1---------------------\n");
while (start != 0 && (start->command[0] == '>' || start->command[0] == '<'))
{
	//printf("1---------------------\n");
	if (com->command[0] == '>' && com->command[1] == '>')
	{
		start = com->next->next;
		if (start != 0)
			start->redir_double_right = ft_strdup(com->next->command);
		int gf = open(com->next->command, O_CREAT | O_WRONLY | O_APPEND, 0777);
		close (gf);
		if (start == 0)
			return (start);
	}
	//printf("2---------------------\n");
	if (com->command[0] == '>' && com->command[1] == '\0')
	{
		start = com->next->next;
		int ff = open(com->next->command, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		close (ff);
		if (start == 0)
			return (start);
	}
	//printf("3---------------------\n");
	if (com->command[0] == '<' && com->command[1] == '\0')
	{
		start = com->next->next;
		if (start != 0)
			start->redir_double_right = ft_strdup(com->next->command);
		int gg = open(com->next->command, O_RDWR);
		if (gg == -1)
		{
			untils->status = 1;
			printf("%s: no such file or directory\n", com->next->command);
			return (0);
		}
		close(gg);
		if (start == 0)
			return (start);
	}
	com = start;
}
//printf("1.2---------------------\n");
	//printf_command_list(com);
	//start = com;
	while (start)
	{
		if (start->command[0] == '>' && start->command[1] == '>')
		{
			ft_free(com->redir_double_right);
			com->redir_double_right = ft_strdup(start->next->command);
			int gf = open(com->redir_double_right, O_CREAT | O_WRONLY | O_APPEND, 0777);
			close (gf);
			delete_current_parser(start->next);
			if (start->back != 0)
			{
				start = start->back;
				delete_current_parser(start->next);
			}
			else
			{
				start = start->next;
				if (start)
				{
					delete_current_parser(start->back);
					start->back = 0;
				}
			}
		}
		else if (start->command[0] == '>')
		{
			ft_free(com->redir_right);
			com->redir_right = ft_strdup(start->next->command);
			int ff = open(com->redir_right, O_CREAT | O_WRONLY | O_TRUNC, 0777);
			close (ff);
			delete_current_parser(start->next);
			if (start->back != 0)
			{
				start = start->back;
				delete_current_parser(start->next);
			}
			else
			{
				start = start->next;
				if (start)
				{
					delete_current_parser(start->back);
					start->back = 0;
				}
			}
		}
		else if (start->command[0] == '<')
		{
			com->redir_left = ft_strdup(start->next->command);
			int gg = open(com->redir_left, O_RDWR);
			close(gg);
			delete_current_parser(start->next);
			if (start->back != 0)
			{
				start = start->back;
				delete_current_parser(start->next);
			}
			else
			{
				start = start->next;
				if (start)
				{
					delete_current_parser(start->back);
					start->back = 0;
				}
			}
		}
		start = start->next;
	}
	return (com);
}

void	connect_stdio_to_pipes(int prev_fds[], int next_fds[])
{
    if (prev_fds[0] >= 0)
    {
        dup2(prev_fds[0], 0);
        close(prev_fds[0]);
        close(prev_fds[1]);
    }
    if (next_fds[1] >= 0)
    {
        dup2(next_fds[1], 1);
        close(next_fds[1]);
        close(next_fds[0]);
    }
}

int	count_pp(t_command *start)
{
	int	count_pipes;

	count_pipes = 0;
	while (start)
	{
		if (start->command[0] == '|' && start->command[1] == '\0')
			count_pipes++;
		start = start->next;
	}
	return (count_pipes);
}

void	bsopia_func(t_command *com, int i, t_untils *untils)
{
	t_command	*start;
	char		*tmp;
	int			count_pipes;

	start = com;
	count_pipes = count_pp(start);
	start = com;
	if (count_pipes == 0)
	{
		if (fork_without_pip(com, untils))
			return ;
		if (check_buildin(start->command))
			child_without_pip(start, untils);
		else
			bsophia_function(com, untils);
	}
	else
		children_pip(start, count_pipes, untils);

}

void	main_parser(char *str, t_untils *untils)
{
	t_command	*start;
	t_command	*current_command;

	start = 0;
	start = parser_into_list(str, untils);
	if (start != 0 )//&& start->command[0] == 'e' && start->command[1] == 'r')
		printf("%s\n", start->command);
	ft_free(start);
}
