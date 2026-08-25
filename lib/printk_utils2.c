/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:31:21 by pjurdana          #+#    #+#             */
/*   Updated: 2024/11/01 16:31:23 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printk.h"

int	ft_printhexa_u(unsigned int n)
{
	int		j;
	char	*hexa;

	hexa = "0123456789ABCDEF";
	j = 0;
	if (n <= 15)
		j += ft_printchar(hexa[n]);
	else
	{
		j += ft_printhexa_u(n / 16);
		j += ft_printhexa_u(n % 16);
	}
	return (j);
}

int	ft_print_unsigned_nbr(int n)
{
	unsigned int	i;
	int				j;

	j = 0;
	i = n;
	if (i <= 9)
		j += ft_printchar(i + '0');
	else
	{
		j += ft_print_unsigned_nbr(i / 10);
		j += ft_print_unsigned_nbr(i % 10);
	}
	return (j);
}

int	ft_printhexa_p(unsigned long int n)
{
	int		j;
	char	*hexa;

	j = 0;
	hexa = "0123456789abcdef";
	if (n <= 15)
		j += ft_printchar(hexa[n]);
	else
	{
		j += ft_printhexa_p(n / 16);
		j += ft_printhexa_p(n % 16);
	}
	return (j);
}

int	ft_printnil(unsigned long int n)
{
	int	j;

	if (!n)
	{
		vga_putstr("(nil)", current_color);
		return (5);
	}
	vga_putstr("0x", current_color);
	return (2 + ft_printhexa_p(n));
}
