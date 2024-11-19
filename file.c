/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:06:19 by alex              #+#    #+#             */
/*   Updated: 2024/11/19 16:25:49 by omalovic         ###   ########.fr       */
=======
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:06:19 by alex              #+#    #+#             */
/*   Updated: 2024/11/18 12:09:28 by alex             ###   ########.fr       */
>>>>>>> a9bf1e9daca069b9da09f10766d2e3ce81ae46c4
/*                                                                            */
/* ************************************************************************** */


#include "client.h"

char *to_binary(int value)
{
	int 	result;
	char	*str = NULL;
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

char* base_binary(int value, int ch)
{
	int 	result;
	char	*str=NULL;
	int		i;
	int 	temp;

	if (ch)
		return (to_binary(value));
	else
	{
		i = 0;
		while (value != 0)
		{
			value = value / 10;
			i++;
		}
		printf("%d\n", i);
	}
	return ("NULL");
}

<<<<<<< HEAD
#define START 0
#define LEN_TRANSFER 4
#define CHAR_TRANSFER 8
#define FINISH 16

int main()
{
	char flag = 0;
	printf("flag before changes: %d, binary form: %s\n", flag, to_binary(flag));
	// flag |= 1 << 1;
	// printf("flag changed: %d, binary form: %s\n", flag, to_binary(flag));
	// flag |= 1 << 2;
	// printf("flag changed: %d, binary form: %s\n", flag, to_binary(flag));
	// flag |= 1 << 4;
	// printf("flag changed: %d, binary form: %s\n", flag, to_binary(flag));
	// if ((flag |= 1 << 2) == LEN_TRANSFER)
	// 	printf("Len transfer is going\n");
=======
int main()
{
	printf("%s\n", base_binary(123, 0));
>>>>>>> a9bf1e9daca069b9da09f10766d2e3ce81ae46c4
}