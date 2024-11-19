/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:39:31 by alex              #+#    #+#             */
/*   Updated: 2024/11/18 14:58:47 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int ft_strlen(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char *to_binary(int value)
{
	int 	result;
	char	*str;
	int		i;
	int 	temp;

	i = 0;
	temp = value;
	if (value <= 0)
		return ("0");
	while (value != 0)
	{
		value = value / 2;
		i++;
	}
	str = (char *)malloc(sizeof(char) * (i+1));
	if (!str)
		return (NULL);
	value = temp;
	str[i] = '\0';
	while (value != 0 && i >= 0)
	{
		result = (value % 2) + '0';
		value = value / 2;
		str[i-1] = result;
		i--;
	}
	return (str);
}

int binary_to_decimal(char *binary)
{
	int result=0, i=0;
	while (binary[i] != '\0')
	{
		result = result * 2 + (binary[i] - '0');
		i++;
	}
	return (result);
}

void right_to(void) // сдвиг направо (удаление последнего бита) - это количество раз деление изначального числа на 2 (1 - 1 раз поделить на 2; 2 - 2 раза ...)
{
	int	value1;
	int	result1, result2, result3, result4;

	value1 = 16;
	printf("value: %d; binary form: %s\n", value1, to_binary(value1));
	result1 = value1 >> 1;
	result2 = value1 >> 2;
	result3 = value1 >> 3;
	result4 = value1 >> 4;
	printf("result1: %d; binary form: %s\n", result1, to_binary(result1)); // 8
	printf("result2: %d; binary form: %s\n", result2, to_binary(result2)); // 4
	printf("result3: %d; binary form: %s\n", result3, to_binary(result3)); // 2
	printf("result4: %d; binary form: %s\n", result4, to_binary(result4)); // 1
}

void left_to(void) // сдвиг влево (добавление одного бита сзади) - это количесвто раз умножения числа на 2
{
	int value1;
	int result1, result2, result3, result4;

	value1 = 1;
	printf("value: %d; binary form: %s\n", value1, to_binary(value1));
	result1 = value1 << 1;
	result2 = value1 << 2;
	result3 = value1 << 3;
	result4 = value1 << 4;
	printf("result1: %d; binary form: %s\n", result1, to_binary(result1)); // 2
	printf("result2: %d; binary form: %s\n", result2, to_binary(result2)); // 4
	printf("result3: %d; binary form: %s\n", result3, to_binary(result3)); // 8
	printf("result4: %d; binary form: %s\n", result4, to_binary(result4)); // 16
}

void bit_and(void) // если биты совпадают, то 1, в других случаях 0 (учитывается только бит 1)
{
	int	value1, value2, value3, value4;
	int	mask1, result1, mask2, result2, mask3, result3, mask4, result4;

	value1 = 5; // 101
	mask1 = 1;	// 001
				// 001
	result1 = value1 & mask1;
	
	value2 = 11;// 1011
	mask2 = 3;	// 0011
				// 0011
	result2 = value2 & mask2;
	printf("result1: %d; binary form: %s\n", result1, to_binary(result1)); // 1
	printf("result2: %d; binary form: %s\n", result2, to_binary(result2)); // 3
}

void bit_or(void) // Сравнивает каждый бит двух чисел. Результат 1, если хотя бы один из битов равен 1 (если два бита равны 1, то результат будет 1)
{
	int value = 4; // 0100
	int mask = 2;  // 0010
				   // 0110
	int result = value | mask;

	int value2 = 5;// 0101
	int mask2 = 3; // 0011
				   // 0111
	int result2 = value2 | mask2;
	printf("result: %d; binary form: %s\n", result, to_binary(result)); // 6
	printf("result: %d; binary form: %s\n", result2, to_binary(result2)); // 7

}

void bit_xor(void) // Исключающее ИЛИ. Результат один ТОЛЬКО если биты не совпадают
{
	int value = 5; // 0101
	int mask = 3;  // 0011
				   // 0110
	int result = value ^ mask;
	printf("result: %d; binary form: %s\n", result, to_binary(result));
}

void bit_negation(void) // Инвертирует все биты числа: 1 становится 0 и наоборот
{
	int value = 5; // 0000 0101
	int result = ~value; // 1111 1010
	printf("result: %d; binary form: %s\n", result, to_binary(result));
}

// Практика. Пример 1
// Определяем флаги
#define FLAG_CONNECTED  0x01  // 0001
#define FLAG_SENDING    0x02  // 0010
#define FLAG_RECEIVING  0x04  // 0100
#define FLAG_ERROR      0x08  // 1000

void print_flags(int flags)
{
	if (flags & FLAG_CONNECTED)
		printf("Connection established\n");
	if (flags & FLAG_SENDING)
		printf("Sending data\n");
	if (flags & FLAG_RECEIVING)
		printf("Receiving data\n");
	if (flags & FLAG_ERROR)
		printf("Error occurred\n");
}

void some_work(void)
{
	int connection_status = 0; // Изначально все флаги сброшены

	// Устанавливаем флаг соединения и флаг отправки данных
	connection_status |= FLAG_CONNECTED;
	connection_status |= FLAG_SENDING;
	// Печатаем текущие флаги
	print_flags(connection_status);

	// Сбрасываем флаг отправки данных, т.к. отправка завершена
	connection_status &= ~FLAG_SENDING;
	// Печатаем флаги после изменения
	printf("After sending data\n");
	print_flags(connection_status);
}

int main()
{
	printf("Сдвиг вправо: \n");
	right_to(); // 4 (0000 0100)
	printf("\nСдвиг влево: \n");
	left_to();
	printf("\nПобитовый AND\n");
	bit_and();
	printf("\nПобитовое OR\n");
	bit_or();
	printf("\nПобитовое XOR\n");
	bit_xor();
	printf("\nПобитовое отрицание\n");
	bit_negation();
	
	// practice
	printf("-----PRACTISE-----\n");
	some_work();

	printf("\n\n%s\n", to_binary(255));
}