/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:23:27 by alex              #+#    #+#             */
/*   Updated: 2024/11/20 12:07:16 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	ft_putchar(char ch)
{
	write(1, &ch, 1);
}

void handler(int signum)
{
	static int bit_count = 0;
	static char byte = 0;
	
	if (bit_count == 8)
	{
		ft_putchar(byte);
		bit_count = 0;
		byte = 0;		
	}
	if (signum == SIGUSR1)
	{
		byte = byte << 1; // сдвиг влево, то есть установка нуля в конце
	}
	else if (signum == SIGUSR2)
	{
		byte = (byte << 1) | 1; // сдвиг влево и установка 1 в конце
	}
	bit_count++;
}

int main()
{
	printf("Server PID: %d\n", getpid());
	struct sigaction sa;
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask); // очистили маски, так как мы не хотим блокировать никакие сигналы

	sigaction(SIGUSR1, &sa, NULL); // те сигналы которые будут перехвачены и обработаны
	sigaction(SIGUSR2, &sa, NULL);

	while (1) {
		pause();  // Ожидаем сигналы
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:23:27 by alex              #+#    #+#             */
/*   Updated: 2024/11/19 16:26:07 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

// siginfo_t содержит pid клиента, подтверждение успешной передачи сигнала, детали о сигнале
// context — это указатель на структуру, которая может содержать дополнительные данные о контексте выполнения, когда сигнал был обработан (но она не используется)

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
		flag = 0;
		if (kill(client_pid, SIGUSR2) == -1)
			exit(EXIT_FAILURE);
		
	}
}

void	handle_signal_str(int sig)
{
	
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

/* План

что должно быть:
1) передача длины строки со стороны клиента 
2) начало передачи бит
3) после передачи каждого байта сервер должен отсылать клиенту сигнал SIGUSR1
4) как только сервер получает окончательный символ: \0, сервер отсылает клиенту SIGUSR2, что означает, что все данные были переданы успешно
5) cервер должен поддерживать получение строк сразу от клиентов
6) как только строка получена, сервер должен вывести ее в stdout
*/
