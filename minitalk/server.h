/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:06:31 by alex              #+#    #+#             */
/*   Updated: 2024/11/22 11:59:42 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SERVER_H
#define SERVER_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include "ft_printf/ft_printf.h"

int	ft_atoi1(const char *str);
void	*ft_calloc1(size_t count, size_t size);

typedef struct s_server_state
{
	int	bit_index;		// Текущий индекс бита
	int	current_value;	// Собранное значение
	int pid;
	struct s_server_state *next;
} t_server_state;

typedef enum
{
	WAIT_HANDSHAKE,
	WAIT_DATA
} t_server_mode;

#endif