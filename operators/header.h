/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:33:13 by alex              #+#    #+#             */
/*   Updated: 2024/11/18 14:15:08 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
int binary_to_decimal(char *binary);
char *to_binary(int value);

#endif