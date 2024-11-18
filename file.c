/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:06:19 by alex              #+#    #+#             */
/*   Updated: 2024/11/18 12:09:28 by alex             ###   ########.fr       */
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

int main()
{
	printf("%s\n", base_binary(123, 0));
}