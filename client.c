/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:23:23 by alex              #+#    #+#             */
/*   Updated: 2024/11/19 16:22:02 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	pid;
char *message;

int	ft_atoi(const char *str)
{
	unsigned long		num;
	int					sign;
	size_t				i;

	num = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
		break ;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(num * sign));
}

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	send_char(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR2); // отправка бита 1
		else
			kill(pid, SIGUSR1); // отправка бита 0
		usleep(100); // задержка для обработки сервера
		i--;
	}
}

void	send_bit(int pid, int bit)
{
	if (bit == 0)
	{
		if (kill(pid, SIGUSR1) == -1)
			exit(EXIT_FAILURE);
	}
	else
	{
		if (kill(pid, SIGUSR2) == -1)
			exit(EXIT_FAILURE);
	}
	usleep(100);
}

void	work_str(int pid, char *message)
{
	int	i;

	i = 0;
	while (message[i] != '\0')
	{
		send_char(pid, message[i]);
		i++;
	}
}

void	send_number(int pid, int length)
{
	int	bit_index;
	int	bit;

	bit_index = 0;
	while (bit_index < 32)
	{
		bit = (length >> bit_index) & 1; // определяем значение тек бита
		send_bit(pid, bit);
		bit_index++;
	}
}

void	start_transfer(int sig)
{
	if (sig == SIGUSR2)
	{
		work_str(pid, message);
	}
}

int main(int argc, char *argv[])
{	
	if (argc != 3)
		return (1);
	pid = ft_atoi(argv[1]);
	message = argv[2];
	send_number(pid, ft_strlen(argv[2]));
	signal(SIGUSR2, start_transfer);
	pause();
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