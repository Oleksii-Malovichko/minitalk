/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:06:13 by alex              #+#    #+#             */
/*   Updated: 2024/11/19 21:52:27 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CLIENT_H
#define CLIENT_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

typedef struct s_server_state
{
	int	bit_index;		// Текущий индекс бита
	int	current_value;	// Собранное значение
	int pid;
} t_server_state;

#endif