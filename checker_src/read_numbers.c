/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_numbers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 18:04:46 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/08 18:04:51 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static t_dlist	*new_double_link_list(int data, t_dlist *prev, t_dlist *next)
{
	t_dlist *list;

	if (!(list = (t_dlist *)malloc(sizeof(t_dlist))))
		exit_error();
	list->data = data;
	list->next = next;
	list->prev = prev;
	return (list);
}

static void		find_duplicate_numbers(t_dlist *list)
{
	t_dlist *tmp;

	while (list->next)
	{
		tmp = list->next;
		while (tmp)
		{
			if (tmp->data == list->data)
				exit_error();
			tmp = tmp->next;
		}
		list = list->next;
	}
}

static long		ft_atoi(char **str)
{
	long	res;
	int		s;
	int		i;

	i = 0;
	s = 1;
	res = 0;
	if (*str[i] == '-')
	{
		s = -1;
		i++;
	}
	while ((*str)[i] >= '0' && (*str)[i] <= '9')
		res = (res * 10) + (*str)[i++] - '0';
	res *= s;
	if (((*str)[i] != '\0' && (*str)[i] != ' ') || res > 2147483647 ||
		res < -2147483648 || i > 11 || i == 0 || (i == 1 && s == -1))
		exit_error();
	*str += i;
	return (res);
}

static int		check_flag(char **argv, t_check *v)
{
	if (argv[1][0] == '-' && argv[1][1] == 'v' && argv[1][2] == '\0')
	{
		if (argv[2] == NULL)
			exit_error();
		v->v_flag = 1;
		return (2);
	}
	return (1);
}

void			read_numbers(int argc, char **argv, t_check *v)
{
	int		i;
	t_dlist	*list;

	i = check_flag(argv, v);
	list = new_double_link_list(ft_atoi(&argv[i]), NULL, NULL);
	if (*argv[i] == '\0')
		i++;
	v->a_num = 1;
	v->head_a = list;
	while (i < argc)
	{
		if (*argv[i] == '\0')
			exit_error();
		while (*argv[i])
		{
			if (*argv[i] == ' ')
				argv[i] += 1;
			list->next = new_double_link_list(ft_atoi(&argv[i]), list, NULL);
			list = list->next;
			v->a_num += 1;
		}
		i++;
	}
	v->tail_a = list;
	find_duplicate_numbers(v->head_a);
}
