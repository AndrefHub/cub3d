/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 21:08:42 by lsherry           #+#    #+#             */
/*   Updated: 2022/05/14 22:03:21 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_reverse(char *s)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = ft_strlen(s) - 1;
	while (i < j)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		i++;
		j--;
	}
}

static int	ft_nbrlen(int n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*ft_zero(void)
{
	char	*nbr;

	nbr = (char *) malloc(2);
	if (!nbr)
		return (NULL);
	nbr[0] = '0';
	nbr[1] = '\0';
	return (nbr);
}

char	*ft_itoa(int n)
{
	int			len;
	char		*arr;
	int			z;
	int			i;
	long int	nbr;

	if (n == 0)
		return (ft_zero());
	nbr = n;
	i = 0;
	z = -2 * (nbr < 0) + 1;
	len = 1 * (nbr < 0) + ft_nbrlen(nbr);
	arr = (char *) malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (NULL);
	while (nbr != 0)
	{
		arr[i++] = z * (nbr % 10) + '0';
		nbr /= 10;
	}
	if (z < 0)
		arr[i++] = '-';
	arr[i] = '\0';
	ft_reverse(arr);
	return (arr);
}
