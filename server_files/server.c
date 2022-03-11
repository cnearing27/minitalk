#include "../minitalk.h"

int	main(void)
{
	int	server_pid;

	server_pid = getpid();
	ft_printf("PID = %d\n", server_pid);
	pause();
}