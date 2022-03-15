/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:44:37 by cnearing          #+#    #+#             */
/*   Updated: 2022/03/15 13:47:18 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	content(int sig)
{
	(void)sig;
	usleep(20);
}

void	success(int sig)
{
	(void)sig;
	write(1, "Your message has been sent!\n", 28);
}

void	handle_simbol(int server_pid, char a)
{
	int	count;
	int	check;

	count = 0;
	check = 0;
	while (count < 8)
	{
		if ((a >> count) & 1)
			check = kill(server_pid, SIGUSR1);
		else
			check = kill(server_pid, SIGUSR2);
		if (check == -1)
		{
			write(1, "Wrong PID\n", 10);
			exit (1);
		}
		pause();
		count++;
	}
}

int	main(int argc, char	**argv)
{
	int	server_pid;
	int	i;

	if (argc != 3)
	{
		write(1, "You must write server pid and message.\n", 39);
		return (0);
	}
	server_pid = ft_atoi(argv[1]);
	signal(SIGUSR1, content);
	signal(SIGUSR2, success);
	i = 0;
	while (argv[2][i])
	{
		handle_simbol(server_pid, argv[2][i]);
		i++;
	}
	handle_simbol(server_pid, '\0');
	return (0);
}
