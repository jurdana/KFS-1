/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:13:27 by pjurdana          #+#    #+#             */
/*   Updated: 2024/10/31 12:13:31 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printk.h"

int	ft_type(va_list *ap, char type)
{
	int	len;

	len = 0;
	if (type == 'c')
		len += ft_printchar(va_arg(*ap, int));
	else if (type == 's')
		len += ft_printstr(va_arg(*ap, char *));
	else if (type == 'p')
		len += ft_printnil(va_arg(*ap, unsigned long int));
	else if (type == 'd' || type == 'i')
		len += ft_printnbr(va_arg(*ap, int));
	else if (type == 'u')
		len += ft_print_unsigned_nbr(va_arg(*ap, unsigned int));
	else if (type == 'x')
		len += ft_printhexa_l(va_arg(*ap, unsigned int));
	else if (type == 'X')
		len += ft_printhexa_u(va_arg(*ap, unsigned int));
	else if (type == '%')
		len += ft_printchar('%');
	return (len);
}

int	printk(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		total;

	if (!str)
		return (-1);
	i = 0;
	total = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			total += ft_type(&ap, str[i + 1]);
			i++;
		}
		else
		{
			vga_putchar(str[i], current_color);
			total++;
		}
		i++;
	}
	va_end(ap);
	return (total);
}
