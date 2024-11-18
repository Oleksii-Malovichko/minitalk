/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:23:23 by alex              #+#    #+#             */
/*   Updated: 2024/11/18 19:58:26 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

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

int ft_atoi(char *str)
{
	int len;
	int result;
	int i;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

int main(int argc, char *argv[])
{
	int pid;
	char *message;
	int i;

	if (argc != 3)
		return (1);
	pid = atoi(argv[1]);
	message = argv[2];
	i = 0;
	while (message[i] != '\0')
	{
		send_char(pid, message[i]);
		i++;
	}
	
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