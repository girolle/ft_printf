/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rczarfun <rczarfun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:05:19 by rczarfun          #+#    #+#             */
/*   Updated: 2020/12/03 22:05:21 by rczarfun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static intmax_t	get_num(t_printf *tab)
{
	intmax_t	num;

	if (tab->type == 'D')
		num = (long)(va_arg(tab->args, long int));
	else if (ft_strcmp(tab->length, "hh") == 0)
		num = (signed char)(va_arg(tab->args, int));
	else if (ft_strcmp(tab->length, "h") == 0)
		num = (short)(va_arg(tab->args, int));
	else if (ft_strcmp(tab->length, "ll") == 0)
		num = (long long)(va_arg(tab->args, long long int));
	else if (ft_strcmp(tab->length, "l") == 0)
		num = (long)(va_arg(tab->args, long int));
	else if (ft_strcmp(tab->length, "j") == 0)
		num = (intmax_t)(va_arg(tab->args, intmax_t));
	else if (ft_strcmp(tab->length, "z") == 0)
		num = (size_t)(va_arg(tab->args, size_t));
	else
		num = (int)(va_arg(tab->args, int));
	num = (intmax_t)num;
	return (num);
}

static int		get_tens(intmax_t num)
{
	int tens;

	if (num < 0)
		num *= -1;
	tens = 1;
	while ((num /= 10) > 0)
		tens++;
	return (tens);
}

static char		get_negatvity_placeholder(t_printf *tab, int is_negative)
{
	char	*tmp;

	tmp = tab->flags;
	if (is_negative)
		return ('-');
	if (tmp[1] == '+')
		return ('+');
	if (tmp[2] == ' ')
		return (' ');
	return ('\0');
}

static t_printf	*do_d(t_printf *tab, intmax_t num, int num_width, int align_left)
{
	int			not_blank;
	char		negatvity_placeholder;
	int			is_negative;

	is_negative = (num < 0) ? 1 : 0;
	num *= (is_negative && num != (-9223372036854775807 - 1)) ? -1 : 1;
	negatvity_placeholder = get_negatvity_placeholder(tab, is_negative);
	not_blank = num_width;
	if (num_width <= tab->precision && tab->precision >= 0)
		not_blank = tab->precision;
	if (negatvity_placeholder)
		not_blank++;
	tab->ret += (not_blank <= tab->width) ? tab->width : not_blank;
	if (!align_left)
		put_filling(tab, ' ', tab->width - not_blank, 0);
	if (negatvity_placeholder)
		write(1, &negatvity_placeholder, 1);
	put_filling(tab, '0', tab->precision - num_width, 0);
	if (num != (-9223372036854775807 - 1))
		ft_putnbrmax(num);
	else if ((tab->ret += 18) > 0)
		write(1, "9223372036854775808", 19);
	if (align_left)
		put_filling(tab, ' ', tab->width - not_blank, 0);
	return (tab);
}

t_printf			*handle_d(t_printf *tab)
{
	intmax_t	num;
	int			num_width;
	int			align_left;

	num = get_num(tab);
	if (num == 0 && tab->precision == 0)
	{
		if (tab->flags[1] == '+')
			put_wchar_ret('+', tab);
		if (tab->flags[2] == ' ')
			put_wchar_ret(' ', tab);
		put_filling(tab, ' ', tab->width, 1);
		return (tab);
	}
	num_width = get_tens(num);
	align_left = (tab->flags[0] == '-') ? 1 : 0;
	if (tab->flags[3] == '0' && tab->precision == -1 && !tab->flags[0])
	{
		tab->precision = tab->width;
		if (num < 0 || tab->flags[2] || tab->flags[1] || tab->flags[0])
			tab->precision--;
	}
	do_d(tab, num, num_width, align_left);
	return (tab);
}