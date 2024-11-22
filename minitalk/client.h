/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:06:13 by alex              #+#    #+#             */
/*   Updated: 2024/11/22 11:25:01 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CLIENT_H
#define CLIENT_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include "ft_printf/ft_printf.h"

int	ft_atoi2(const char *str);
void	*ft_calloc2(size_t count, size_t size);

typedef struct s_server_state
{
	int	bit_index;		// Текущий индекс бита
	int	current_value;	// Собранное значение
	int pid;
} t_server_state;

#endif