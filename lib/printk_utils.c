/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:58:53 by pjurdana          #+#    #+#             */
/*   Updated: 2024/11/01 11:58:55 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printk.h"

int	ft_printchar(char c)
{
	vga_putchar(c, current_color);
	return (1);
}

int	ft_printstr(char *s)
{
	if (!s)
	{
		vga_putstr("(null)", current_color);
		return (6);
	}

	vga_putstr(s, current_color);
	return (ft_strlen(s));
}

int	ft_printnbr(int n)
{
	int	i;
	int	j;

	j = 0;
	i = n;
	if (i == -2147483648)
	{
		vga_putstr("-2147483648", current_color);
		return (11);
	}
	if (i < 0)
	{
		j += ft_printchar('-');
		i = -i;
	}
	if (i <= 9)
		j += ft_printchar(i + '0');
	else
	{
		j += ft_printnbr(i / 10);
		j += ft_printnbr(i % 10);
	}
	return (j);
}

int	ft_printhexa_l(unsigned int n)
{
	int		j;
	char	*hexa;

	hexa = "0123456789abcdef";
	j = 0;
	if (n <= 15)
		j += ft_printchar(hexa[n]);
	else
	{
		j += ft_printhexa_l(n / 16);
		j += ft_printhexa_l(n % 16);
	}
	return (j);
}
