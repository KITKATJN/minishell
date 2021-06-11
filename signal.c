#include "minishell.h"

void	signal_c(int sig_num)
{
	g_sig_f = 1;
}
