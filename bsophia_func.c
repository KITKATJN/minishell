#include "minishell.h"

static void	echo_2(t_command *list, t_untils *untils)
{
	int		i;
	char	*line;
	char	*tmp;

	i = 1;
	line = NULL;
	if (!list->next)
	{
		write(1, "\n", 1);
		return ;
	}
	list = list->next;
	// if (!(ft_strcmp(list->command, "$?")))
	// {
	// 	printf("%d\n", untils->status);
	// 	return ;
	// }
	untils->status = 0;
	if ((!(ft_strcmp(list->command, "-n"))))
	{
		i = 0;
		list = list->next;
	}
	while (list && ft_strcmp(list->command, "|") && ft_strcmp(list->command, ";"))
	{
		line = ft_strjoin_line(line, list->command);
		if (ft_lstsize_2(list) != 1)
		{
			tmp = line;
			line = ft_strjoin_line(line, " ");
			ft_free(tmp);
		}
		list = list->next;
	}
	f_echo(line, i);
	ft_free(line);
}

int check_redir(t_command *list, int i, t_untils *untils)
{
	// struct stat buf;

	if (list->redir_right != NULL && i == 2)
	{
		untils->fd_out = open(list->redir_right, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (untils->fd_out < 0)
		{
			printf("! %s !\n", strerror(errno));
			untils->status = 1;
			// printf("%s : Permission denied\n", list->redir_right);
			// exit(1);
			return (0);
		}
		untils->std_out = dup(1);
		dup2(untils->fd_out, 1);
		close(untils->fd_out);
	}
	if (list->redir_double_right != NULL && i == 2)
	{
		//проверка на нет прав
		untils->fd_out = open(list->redir_double_right, O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (untils->fd_out < 0)
		{
			printf("! %s !\n", strerror(errno));
			// printf("%s : Permission denied\n", list->redir_double_right);
			// exit(1);
			untils->status = 1;
			return (0);
		}
		untils->std_out = dup(1);
		dup2(untils->fd_out, 1);
		close(untils->fd_out);
	}
	if (list->redir_left != NULL && i == 2)
	{
		// if (buf.st_mode & S_IXUSR) S_IFREG указывает простой ли это файл
		// {
		// 	printf("mode = %o\n", buf.st_mode);
		// 	printf("est dostupa\n");
		// }
		//проверить есть ли файл и доступ к файлу
		// stat(list->redir_left, &buf);
		untils->fd_in = open(list->redir_left, O_RDWR);
		if (untils->fd_in < 0)
		{
			printf("! %s !\n", strerror(errno));
			untils->status = 1;
			// exit(1);
			return (0);
		}
		untils->std_in = dup(0);
		dup2(untils->fd_in, 0);
		close(untils->fd_in);
	}
	if (i == 1)
	{
		if (untils->fd_out != 99)
		{
			close(untils->fd_out);
			dup2(untils->std_out, 1);
			close(untils->std_out);
		}
		if (untils->fd_in != 99)
		{
			close(untils->fd_in);
			dup2(untils->std_in, 0);
			close(untils->std_in);
		}
	}
	return (1);
}

void bsophia_function(t_command *list, t_untils *untils)
{
	int i = 0;
	
	if (!check_redir(list, 2, untils))
		return ;
	while (list->command[i])
	{
		list->command[i] = ft_tolower(list->command[i]);
		i++;
	}
	// printf("bsophia first command =====> %s\n", list->command);
	if (!(ft_strcmp(list->command, "echo")))
		echo_2(list, untils);
	untils->status = 0;
	if (!(ft_strcmp(list->command, "pwd")))
		get_pwd(); //сместить указатель и установить после пайпа или редиректа(до следующей исполняющей команды)
	if (!(ft_strcmp(list->command, "cd")))
	{
		f_cd(list, untils);//при ошибках возвращает -1 и ставит errno в должное значение/ сделать менеджмент ошибок
	}
	if (!(ft_strcmp(list->command, "env")))
		print_env(untils->env);
	if (!(ft_strcmp(list->command, "export")))
	{
		if (!(list->next))
		{
			print_export(untils->env);
			check_redir(list, 1, untils);
			return ;
		}
		list = list->next;
		while (list->next)
		{
			if (check_name(list->command))
				check_redir(list, 1, untils);
			list = list->next;
		}
		if (check_name(list->command))
			check_redir(list, 1, untils);
		while (list->back)
		{
			if (!(ft_strcmp(list->command, "export")))
			{
				check_redir(list, 1, untils);
				break ;
			}
			list = list->back;
		}
		while (list->next)
		{
			if (list->next)
			{
				list = list->next;
				export_add(untils->env, list->command, untils);
			}
		}
	}
	if (!(ft_strcmp(list->command, "unset")))
	{
		while (list->next)
		{
			list = list->next;
			untils->env = f_unset_line(untils->env, list->command, untils);
		}
	}
	if(!ft_strcmp(list->command, "exit"))
		ft_exit(list, untils);
	check_redir(list, 1, untils);
}
