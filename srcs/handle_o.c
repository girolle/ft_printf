/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_o.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rczarfun <rczarfun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:05:37 by rczarfun          #+#    #+#             */
/*   Updated: 2020/12/03 22:05:38 by rczarfun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			print_leading_zero(uintmax_t num, char hash)
{
	if (hash == '#' && num)
		write(1, "0", 1);
}

static uintmax_t	get_num(t_printf *tab)
{
	uintmax_t	num;

	if (tab->type == 'O')
		num = (unsigned long)(va_arg(tab->args, unsigned long int));
	else if (ft_strcmp(tab->length, "hh") == 0)
		num = (unsigned char)(va_arg(tab->args, unsigned int));
	else if (ft_strcmp(tab->length, "h") == 0)
		num = (unsigned short)(va_arg(tab->args, unsigned int));
	else if (ft_strcmp(tab->length, "ll") == 0)
		num = (unsigned long long)(va_arg(tab->args, unsigned long long int));
	else if (ft_strcmp(tab->length, "l") == 0)
		num = (unsigned long)(va_arg(tab->args, unsigned long int));
	else if (ft_strcmp(tab->length, "j") == 0)
		num = (uintmax_t)(va_arg(tab->args, uintmax_t));
	else if (ft_strcmp(tab->length, "z") == 0)
		num = (size_t)(va_arg(tab->args, size_t));
	else
		num = (unsigned int)(va_arg(tab->args, unsigned int));
	num = (uintmax_t)num;
	return (num);
}

static t_printf		*print_u(t_printf *tab, uintmax_t num, char *str, int left)
{
	int			not_blank;
	int			num_width;

	num_width = ft_strlen(str);
	if (tab->flags[4] == '#' && num)
		num_width++;
	not_blank = num_width;
	if (num_width <= tab->precision && tab->precision > 0)
		not_blank = tab->precision;
	tab->ret += (not_blank <= tab->width) ? tab->width : not_blank;
	if (!left)
		put_filling(tab, ' ', tab->width - not_blank, 0);
	print_leading_zero(num, tab->flags[4]);
	put_filling(tab, '0', tab->precision - num_width, 0);
	ft_putstr(str);
	free(str);
	if (left)
		put_filling(tab, ' ', tab->width - not_blank, 0);
	return (tab);
}

t_printf				*handle_o(t_printf *tab)
{
	char		*str;
	uintmax_t	num;
	int			left;

	left = 0;
	num = get_num(tab);
	if (num == 0 && tab->precision == 0 && tab->flags[4] != '#')
	{
		put_filling(tab, ' ', tab->width, 1);
		return (tab);
	}
	if (!(str = ft_itoa_base(num, 8, 'a')))
		exit(-1);
	if (tab->flags[0] == '-')
		left = 1;
	if (tab->flags[3] == '0' && tab->precision == -1 && !tab->flags[0])
		tab->precision = tab->width;
	print_u(tab, num, str, left);
	return (tab);
}