#include "minishell.h"

void signal_c(int sig_num)
{
	write(1, "\n", 1);
	g_sig_f = 1;
}

void signal_slash(int sig_num)
{
	(void)(sig_num);
}