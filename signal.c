#include "minishell.h"

void signal_c(int sig_num)
{
	// tputs(tgetstr("rc", 0), 1, ft_putchar); //restore cursor  возмо
	// tputs(tgetstr("ce", 0), 1, ft_putchar);
	write(1, "\n", 1);
	//tputs("$S> ", 1, ft_putchar);
	//if (sig_num == 2)
	g_sig_f = 1;
}

void signal_slash(int sig_num)
{
	(void)(sig_num);
}