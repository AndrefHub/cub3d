/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 00:02:35 by lsherry           #+#    #+#             */
/*   Updated: 2021/12/02 00:02:39 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printstring(va_list **ap)
{
	int		i;
	char	*s;

	s = va_arg(**ap, char *);
	if (s)
		i = ft_putstring(s, 1);
	else
		i = ft_putstring("(null)", 1);
	return (i);
}

static int	ft_printnbr(va_list **ap, char c)
{
	long int	d;
	int			i;

	if (c == 'd' || c == 'i')
	{
		d = va_arg(**ap, int);
		i = ft_putnumber(d, 1);
	}
	else if (c == 'u')
	{
		d = va_arg(**ap, unsigned int);
		i = ft_putnumber(d, 1);
	}
	else if (c == 'x' || c == 'X')
	{
		d = va_arg(**ap, int);
		i = ft_puthexnbr(d, c);
	}
	else if (c == 'p')
		i = ft_putptr(va_arg(**ap, void *));
	else
		i = 0;
	return (i);
}

static int	ft_doprint(const char *format, va_list *ap)
{
	int	i;

	i = 0;
	while (*(format))
	{
		if (*(format) != '%')
			i += write(1, format, 1);
		else
		{
			if (*(format + 1) == '%')
				i += write(1, "%", 1);
			else if (*(format + 1) == 's')
				i += ft_printstring(&ap);
			else if (*(format + 1) == 'd' || *(format + 1) == 'p'
				|| *(format + 1) == 'i' || *(format + 1) == 'u'
				|| *(format + 1) == 'x' || *(format + 1) == 'X')
				i += ft_printnbr(&ap, *(format + 1));
			else if (*(format + 1) == 'c')
				i += ft_putchar((char) va_arg(*ap, int));
			format++;
		}
		format++;
	}
	return (i);
}

char	ft_hex_digit(int v, char x)
{
	if (v >= 0 && v < 10)
		return ('0' + v);
	else
	{
		if (x == 'x')
			return ('a' + v - 10);
		return ('A' + v - 10);
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;

	va_start(ap, format);
	i = ft_doprint(format, &ap);
	va_end(ap);
	return (i);
}
