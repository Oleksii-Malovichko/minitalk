/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:06:59 by alex              #+#    #+#             */
/*   Updated: 2024/11/20 17:00:01 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "libft.h"
#include "ft_printf.h"

volatile int flag;

/* int ft_atoi(const char *str)
{
    unsigned long num = 0;
    int sign = 1;
    size_t i = 0;

    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    while (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign = -sign;
        i++;
        break;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        num = num * 10 + (str[i] - '0');
        i++;
    }
    return ((int)(num * sign));
}

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
} */

void	stop_programm(int i)
{
	if (i == 0)
		exit(EXIT_SUCCESS);
	if (i == 1)
		exit(EXIT_FAILURE);
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
    usleep(500);
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

void send_sig(int pid, char state)
{
    int bit_index;
    int bit;

    bit_index = 0;
    while (bit_index < 8)
    {
        bit = (state >> bit_index) & 1;
		send_bit(pid, bit);
        bit_index++;
    }
}

void	handler(int sig, siginfo_t *info, void *context)
{
	static t_server_state *state = NULL;
	
	if (state == NULL)
	{
		state = malloc(sizeof(t_server_state));
		if (!state)
			exit(EXIT_FAILURE);
		state->bit_index = 0;
		state->current_value = 0;
		state->pid = info->si_pid;
	}
	if (sig == SIGUSR2)
		state->current_value |= (1 << state->bit_index);
	state->bit_index++;
	if (state->bit_index == 8)
	{
		if (state->current_value == 1)
			send_sig(state->pid, 2);
		flag = 1;
	}
}

int main(int n, char *args[])
{
	int pid;
	struct sigaction sa;
	
	flag = 0;
	if (n != 3)
	{
		stop_programm(1);
		return (1);
	}
	pid = ft_atoi(args[1]);

	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
		return (EXIT_FAILURE);
	send_sig(pid, 0);
	while (flag == 0)
		pause();
	work_str(pid, args[2]);
	return (0);
}