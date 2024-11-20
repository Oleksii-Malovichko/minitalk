/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:07:08 by alex              #+#    #+#             */
/*   Updated: 2024/11/20 15:48:29 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int flag;
#define WAIT_HANDSHAKE 0
#define HANDLE_DATA 1

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
            return (stop_programm(1));
    }
    else
    {
        if (kill(pid, SIGUSR2) == -1)
            return (stop_programm(1));
    }
    usleep(300);
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

void	handle_signal_handshake(int sig, siginfo_t *info, void *context)
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
		if (state->current_value == 0 && flag == 0)
			send_sig(state->pid, 1);
		if (state->current_value == 2 && flag == 0)
		{
			flag = 1;
			printf("Handshake completed\n");
		}
		if (state->current_value == '\0' && flag == 1)
		{
			printf("\nReceived all data. Cleaning up...\n");
			flag = 0;
			free(state);
			state = NULL;
			return ;
		}
		else
			write(1, &state->current_value, 1);
		state->current_value = 0;
		state->bit_index = 0;
	}
}

int main(void)
{
	struct sigaction sa;
	
	printf("The pid: %d\n", getpid());
	flag = 0;
	sa.sa_sigaction = handle_signal_handshake;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
		return (EXIT_FAILURE);
	while(1)
		pause();
}

/* 
HANDSHAKE:
0000 0000 - client
0000 0001 - server
0000 0010 - client
010100101..... - data from client
*/