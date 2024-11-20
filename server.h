/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:23:46 by alex              #+#    #+#             */
/*   Updated: 2024/11/19 19:14:31 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   Updated: 2024/11/18 10:26:27 by alex             ###   ########.fr       */
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
	int	bit_index;		// Текущий индекс бита
	int	current_value;	// Собранное значение
} t_server_state;

#endif