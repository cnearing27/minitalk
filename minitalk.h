#ifndef MINITALK_H
# define MINITALK_H
# include <unistd.h> //для write, getpid, pause, usleep
# include <signal.h> //signal, sigemptyset, sigaddset, sigaction, kill, sleep, exit
# include <stdlib.h> //malloc, free
# include <stdio.h> //убрать!
# include "ft_printf/ft_printf.h"

long long int	ft_atoi(const char	*str);

#endif