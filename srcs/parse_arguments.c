/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rczarfun <rczarfun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 19:44:48 by dhojt             #+#    #+#             */
/*   Updated: 2020/12/02 15:30:37 by rczarfun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_tab		*parse_arguments(t_tab *tab)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (ARGUMENTS[i] != '\0')
	{
		while (ARGUMENTS[i] == tab->f_treat[tab->i])
		{
			tab->argument_flag[j] = tab->f_treat[tab->i];
			tab->argument_flag[j + 1] = '\0';
			tab->i++;
			j++;
		}
		i++;
	}
	return (tab);
}