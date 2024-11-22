/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:06:59 by alex              #+#    #+#             */
/*   Updated: 2024/11/22 18:09:20 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

volatile sig_atomic_t ack_received = 0;

void	stop_programm(int i)
{
	if (i == 0)
		exit(EXIT_SUCCESS);
	if (i == 1)
		exit(EXIT_FAILURE);
}

void	handle_ack(int sig)
{
	(void)sig;
	ack_received = 1;
}

void	wait_for_ack(void)
{
	while (!ack_received)
		pause();
	ack_received = 0;
}

void send_bit(int pid, int bit)
{
    if (bit == 0)
    {
        if (kill(pid, SIGUSR1) == -1)
            stop_programm(1);
    }
    else
    {
        if (kill(pid, SIGUSR2) == -1)
            stop_programm(1);
    }
    wait_for_ack();
}

void send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		int bit = (c >> i) & 1;
		send_bit(pid, bit);
		i++;
	}
}

void	work_str(int pid, char *str)
{
	int	i;
	
	i = 0;
	while (str[i] != '\0')
	{
		send_char(pid, str[i]);
		i++;
	}
	send_char(pid, '\0');
	exit(EXIT_SUCCESS);
}

int main(int n, char *args[])
{
	int pid;
	
	if (n != 3)
		stop_programm(1);
	pid = ft_atoi2(args[1]);
	struct sigaction sa = {0};
	sa.sa_handler = handle_ack;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
        return EXIT_FAILURE;
	work_str(pid, args[2]);
	return (0);
}