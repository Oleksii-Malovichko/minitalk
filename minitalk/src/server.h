/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:06:31 by alex              #+#    #+#             */
/*   Updated: 2024/11/20 14:05:05 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SERVER_H
#define SERVER_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

typedef struct s_server_state
{
	int	flag;
	int	bit_index;		// Текущий индекс бита
	int	current_value;	// Собранное значение
	int pid;
} t_server_state;

typedef enum
{
	WAIT_HANDSHAKE,
	WAIT_DATA
} t_server_mode;

#endif