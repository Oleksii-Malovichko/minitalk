/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:41:21 by omalovic          #+#    #+#             */
/*   Updated: 2024/11/19 16:41:22 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int pid;           // Глобальная переменная для PID сервера
char *message;     // Глобальная переменная для строки

// Преобразование строки в число (аналог atoi)
int ft_atoi(const char *str)
{
    unsigned long num = 0;
    int sign = 1;
    size_t i = 0;

    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) // Пропуск пробелов
        i++;
    while (str[i] == '+' || str[i] == '-') // Обработка знака
    {
        if (str[i] == '-')
            sign = -sign;
        i++;
        break;
    }
    while (str[i] >= '0' && str[i] <= '9') // Преобразование чисел
    {
        num = num * 10 + (str[i] - '0');
        i++;
    }
    return ((int)(num * sign));
}

// Функция для подсчета длины строки
int ft_strlen(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}

// Функция для отправки одного символа по битам
void send_char(int pid, char c)
{
    int i = 7;
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

// Функция для отправки одного бита
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
    usleep(100);
}

// Функция для отправки строки
void work_str(int pid, char *message)
{
    int i = 0;
    while (message[i] != '\0')
    {
        send_char(pid, message[i]);
        i++;
    }
}

// Функция для отправки длины строки
void send_number(int pid, int length)
{
    int bit_index = 0;
    int bit;
    while (bit_index < 32) // отправляем 32 бита
    {
        bit = (length >> bit_index) & 1; // определяем значение текущего бита
        send_bit(pid, bit);
        bit_index++;
    }
}

// Функция для начала передачи строки
void start_transfer(int sig)
{
    if (sig == SIGUSR2)
    {
        // Передаем строку на сервер
        work_str(pid, message);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
        return (1);

    pid = ft_atoi(argv[1]);   // Получаем PID сервера
    message = argv[2];         // Получаем строку, которую нужно отправить

    // Отправляем длину сообщения серверу
    send_number(pid, ft_strlen(message));

    // Устанавливаем обработчик сигнала SIGUSR2
    signal(SIGUSR2, start_transfer);

    // Ожидаем сигнал от сервера
    pause(); // Блокируем выполнение, ожидая SIGUSR2 от сервера

    return 0;
}