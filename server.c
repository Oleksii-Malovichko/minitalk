/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:23:27 by alex              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/19 20:13:12 by alex             ###   ########.fr       */
=======
/*   Updated: 2024/11/20 12:07:16 by omalovic         ###   ########.fr       */
>>>>>>> f326d01667b7051385a1fe6526630803fff79602
/*                                                                            */
/* ************************************************************************** */

// int main(void)
// {
// 	struct sigaction sa;
// 	printf("Server PID: %d\n", getpid());
// 	sa.sa_sigaction = handle_signal_len;
// 	sa.sa_flags = SA_SIGINFO;
// 	sigemptyset(&sa.sa_mask);
// 	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
// 		return (EXIT_FAILURE);
// 	while (1)
// 		pause();
// 	return (0);
// }

#include "server.h"

// siginfo_t содержит pid клиента, подтверждение успешной передачи сигнала, детали о сигнале
// context — это указатель на структуру, которая может содержать дополнительные данные о контексте выполнения, когда сигнал был обработан (но она не используется)

void	handle_signal_len(int sig, siginfo_t *info, void *context);
void	handle_signal_str(int sig, siginfo_t *info, void *context);

void	handle_signal_len(int sig, siginfo_t *info, void *context)
{
	static	t_server_state *state = NULL;
	pid_t	client_pid;

	if (state == NULL)
	{
		state = malloc(sizeof(t_server_state));
		if (!state)
			exit(EXIT_FAILURE);
		state->bit_index = 0;
		state->current_value = 0;
	}
	client_pid = info->si_pid;
	if (sig == SIGUSR2) // устанавливаем бит в зависимости от сигнала
		state->current_value |= (1 << state->bit_index);
	state->bit_index++;
	if (state->bit_index == 32)
	{
		printf("Received int: %d\n", state->current_value);
		free(state);
		state = NULL;
		sleep(1);
		if (kill(client_pid, SIGUSR2) == -1) // после получения длины мы отправляем сигнал клиенту
			exit(EXIT_FAILURE);
		
<<<<<<< HEAD
		//
		struct sigaction sa;
        sa.sa_sigaction = handle_signal_str;
        sa.sa_flags = SA_SIGINFO;
        sigemptyset(&sa.sa_mask);
        if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
            exit(EXIT_FAILURE);
=======
>>>>>>> f326d01667b7051385a1fe6526630803fff79602
	}
}

void	handle_signal_str(int sig, siginfo_t *info, void *context)
{
	static int bit_count = 0;
	static char value = 0;
	pid_t	client_pid;

	if (sig == SIGUSR2)
		value |= (1 << bit_count);
	bit_count++;
	client_pid = info->si_pid;
	if (bit_count == 8)
	{
		if (value == '\0')
		{
			if (kill(client_pid, SIGUSR2) == -1)
				exit(EXIT_FAILURE);
		}
		else
			write(1, &value, 1);
		value = 0;
		bit_count = 0;
	}
}

int main(void)
{
	struct sigaction sa;
	printf("Server PID: %d\n", getpid());

	sa.sa_sigaction = handle_signal_len;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
		return (EXIT_FAILURE);
	while (1)
		pause();
	return (0);
}

<<<<<<< HEAD
=======
char	flag = 0;
#define START 0
#define LEN_TRANSFER 4
#define CHAR_TRANSFER 8
#define FINISH 16

int main(void)
{
	struct sigaction sa;
	printf("Server PID: %d\n", getpid());
	if ((flag |= 1 << 2) == LEN_TRANSFER)
	{
		sa.sa_sigaction = handle_signal_len;
		sa.sa_flags = SA_SIGINFO;ŒŒ
		sigemptyset(&sa.sa_mask);
	}
	if ((flag |= 1 << 2) == CHAR_TRANSFER)
	{
		sa.sa_sigaction = handle_signal_str;
		sa.sa_flags = SA_SIGINFO;
		sigemptyset(&sa.sa_mask);
	}
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
		return (EXIT_FAILURE);
	while (1)
		pause();
	return (0);
}

>>>>>>> f326d01667b7051385a1fe6526630803fff79602
/* План

что должно быть:
1) передача длины строки со стороны клиента 
2) начало передачи бит
3) после передачи каждого байта сервер должен отсылать клиенту сигнал SIGUSR1
4) как только сервер получает окончательный символ: \0, сервер отсылает клиенту SIGUSR2, что означает, что все данные были переданы успешно
5) cервер должен поддерживать получение строк сразу от клиентов
6) как только строка получена, сервер должен вывести ее в stdout
*/
