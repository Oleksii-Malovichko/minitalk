/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:41:21 by omalovic          #+#    #+#             */
/*   Updated: 2024/11/19 20:10:23 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int pid;
char *message;

int ft_atoi(const char *str)
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
}

void send_char(int pid, char c)
{
    int i = 7;
    while (i >= 0)
    {
        if ((c >> i) & 1)
        {
            if (kill(pid, SIGUSR2) == -1)
                exit(EXIT_FAILURE);
        }
        else
        {
            if (kill(pid, SIGUSR1) == -1)
                exit(EXIT_FAILURE);
        }
        usleep(300);
        i--;
    }
}

void work_str(int pid, char *message)
{
    int i;

    i = 0;
    while (message[i] != '\0')
    {
        send_char(pid, message[i]);
        i++;
    }
    send_char(pid, '\0');
}

void start_transfer(int sig)
{
    if (sig == SIGUSR2)
        work_str(pid, message);
}

void send_bit(int pid, int bit)
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
    usleep(300);
}

void send_number(int pid, int length)
{
    int bit_index;
    int bit;

    bit_index = 0;
    while (bit_index < 32)
    {
        bit = (length >> bit_index) & 1;
		send_bit(pid, bit);
        bit_index++;
    }
}

int main(int argc, char *argv[])
{
	int length;

	if (argc != 3)
		return (1);
	pid = ft_atoi(argv[1]);
	message = argv[2];
	length = ft_strlen(message);
	send_number(pid, length);
	printf("I'm here");
	struct sigaction sa;
	sa.sa_handler = start_transfer;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		exit(EXIT_FAILURE);
	pause();
	return 0;
}