/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:23:27 by alex              #+#    #+#             */
/*   Updated: 2024/11/18 19:43:39 by alex             ###   ########.fr       */
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
