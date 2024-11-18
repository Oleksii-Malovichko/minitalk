/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_coding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:09:19 by alex              #+#    #+#             */
/*   Updated: 2024/11/18 14:19:31 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#define FLAG_A 0x01 // 0001
#define FLAG_B 0x02 // 0010
#define FLAG_C 0x04 // 0100

int main()
{
	unsigned char flags = 0; // Изначально все флаги сброшены
	// Кодируем несколько значений в одно
	flags |= FLAG_A; // Устанавливаем флаг A
	flags |= FLAG_C; // Устанавливаем флаг C

	printf("Encoded flags: 0x%X; binary form: %s\n", flags, to_binary(flags));

	if (flags & FLAG_A)
	{
		printf("Flag A is set\n");
	}
	if (flags & FLAG_B)
	{
		printf("Flag B is set\n");
	}
	if (flags & FLAG_C)
	{
		printf("Flag C is set\n");
	}
}
