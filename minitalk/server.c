/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:07:08 by alex              #+#    #+#             */
/*   Updated: 2024/11/22 18:12:53 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	stop_programm(int i, t_server_state **state1)
{
	if (*state1)
	{
		free(*state1);
		*state1 = NULL;
	}
	if (i == 0)
		exit(EXIT_SUCCESS);
	if (i == 1)
		exit(EXIT_FAILURE);
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	(void)context;
	static t_server_state *state = NULL;

	if (!state)
	{
		state = ft_calloc1(1, sizeof(t_server_state));
		if (!state)
			stop_programm(1, &state);
		state->bit_index = 0;
		state->current_value = 0;
		state->pid = info->si_pid;
	}
	if (sig == SIGUSR2)
		state->current_value |= (1 << state->bit_index);
	state->bit_index++;
	if (state->bit_index == 8)
	{
		if (state->current_value == '\0')
		{
			if (kill(state->pid, SIGUSR1) == -1)
				stop_programm(1, &state);
			write(1, "\n", 1);
			free(state);
			state = NULL;
			return ;
		}
		else
			write(1, &state->current_value, 1);
		state->current_value = 0;
		state->bit_index = 0;
	}
	if (kill(state->pid, SIGUSR1) == -1)
		stop_programm(1, &state);
}

int main(void)
{
	struct sigaction sa;
	
	ft_printf("%d\n", getpid());
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
		return (EXIT_FAILURE);
	while(1)
		pause();
}
