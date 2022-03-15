/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:44:09 by cnearing          #+#    #+#             */
/*   Updated: 2022/03/15 13:44:10 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	clear(int *len, int *bit, char *byte)
{
	if (len)
		*len = 0;
	if (bit)
		*bit = 0;
	if (byte)
		*byte = 0;
}

void	handle_signal(int sig, siginfo_t	*info, void	*context)
{
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
		ft_printf("%c", byte);
		if (!checker)
			kill(info->si_pid, SIGUSR2);
		clear (&curr_bit, 0, &byte);
	}
	usleep(50);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	int					server_pid;
	struct sigaction	proc;

	server_pid = getpid();
	ft_printf("PID = %d\n", server_pid);
	proc.sa_sigaction = handle_signal;
	proc.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &proc, NULL);
	sigaction(SIGUSR2, &proc, NULL);
	while (1)
		pause();
	return (0);
}
