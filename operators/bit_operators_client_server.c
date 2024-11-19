/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_operators_client_server.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:34:09 by alex              #+#    #+#             */
/*   Updated: 2024/11/18 14:09:42 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
// Пример 2. Протокол передачи данных с кодированием и декодированием
/* У нас есть структура для сообщения, в которой исплользуются флаги и другие данные, например, длина сообщения и тип сообщения.
Мы можем использовать побитовые операции для кодирования и декодирования этих данных*/

#define FLAG_ACK 0x01 // 0001 - Acknowledgment flag
#define FLAG_ERR 0x02 // 0020 - Error flag

// Структура для сообщения
struct message
{
	unsigned char flags;	// флаги состояния
	unsigned char type;		// тип сообщения
	unsigned short length;	// Длина сообщения
	char	data[256];		// данные
};

// Ф-я для установки флага
void set_flag(struct message* msg, unsigned char flag)
{
	msg->flags |= flag; // Устанавливаем флаг
	// 0000 - какой флаг был
	// 0001 - флаг на который мы хотим установить
	// 0001 - результат
}

// Ф-я для сброса флага
void clear_flag(struct message* msg, unsigned char flag)
{
	msg->flags &= ~flag; // сбрасываем флаг
	// 0101 - какой флаг был 
	// 1010 - флаг, с которым мы сравниваем
	// 0000 - результат
}

int check_flag(struct message* msg, unsigned char flag)
{
	return ((msg->flags & flag) == flag);
	// 0101 - если флаги равны
	// 0101
	// 0101

	// 0001 - если флаги разные
	// 0101
	// 0001 == result -> 0
}

/* int main()
{
	struct message msg = {0, 1, 5, "Hello"};
	set_flag(&msg, FLAG_ACK);

	if (check_flag(&msg, FLAG_ACK))
	{
		printf("Acknowlegment flag is set.\n");
	}

	clear_flag(&msg, FLAG_ERR);
	if (!check_flag(&msg, FLAG_ERR))
	{
		printf("Error flag is not set\n");
	}
} */