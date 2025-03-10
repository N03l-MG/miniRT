/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:00:30 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/25 16:43:32 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"

void	handle_character(int fd, int c, int *retval);
void	handle_string(int fd, char *s, int *retval);
void	handle_pointer(int fd, void *p, int *retval);
void	handle_integer(int fd, int n, int *retval);
void	handle_unsigned_decimal(int fd, int ud, int *retval);
void	handle_hex_lower(int fd, unsigned int hexl, int *retval);
void	handle_hex_upper(int fd, unsigned int hexu, int *retval);

char	*hex_to_string(unsigned int address);
char	*address_to_string(uintptr_t address);

#endif
