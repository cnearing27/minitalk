#include "../minitalk.h"

void	clear(int *len, int *bit, char *byte)
{
	if (len)
		*len = 0;
	if (bit)
		*bit = 0;
	if (byte)
		*byte = NULL;
}

void	out(int pid, int checker, char	*buf)
{
	ft_printf("%s", buf);
	if (!checker)
		kill(pid, SIGUSR2);
}

void	handle_signal(int sig, siginfo_t	*info, void	*context)
{
	static char	buf[128];
	static char	byte;
	static int	curr_bit;
	static int	len;
	static int	checker;

	context = NULL;
	if (checker != 1)
		clear(&len, &curr_bit, &byte);
	checker = 1;
	if (sig == SIGUSR1)
		byte = (byte | (1 << curr_bit));
	if (curr_bit++ == 7)
	{
		if (byte == 0)
			checker = 0;
		buf[len++] = byte;
		clear (&curr_bit, 0, &byte);
	}
	if (len == 127 || !checker)
		out(info->si_pid, checker, buf);
	usleep(50);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	int					server_pid;
	struct sigaction	proc;

	server_pid = getpid();
	proc.sa_sigaction = handle_signal;
	proc.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &proc, NULL);
	sigaction(SIGUSR2, &proc, NULL);
	ft_printf("PID = %d\n", server_pid);
	while (1)
		pause();
	return (0);
}
