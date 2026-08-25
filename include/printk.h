/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:33:40 by pjurdana          #+#    #+#             */
/*   Updated: 2024/11/05 13:33:48 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTK_H
# define PRINTK_H

# include "vga.h"
# include <stdarg.h>

int	printk(const char *str, ...);
int	ft_printchar(char c);
int	ft_printnbr(int n);
int	ft_printhexa_l(unsigned int n);
int	ft_printhexa_u(unsigned int n);
int	ft_print_unsigned_nbr(int n);
int	ft_printhexa_p(unsigned long int n);
int	ft_printnil(unsigned long int n);
int	ft_printstr(char *s);
int	ft_strlen(char *s);


#endif
