/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stack_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 18:28:10 by anesteru          #+#    #+#             */
/*   Updated: 2018/04/18 18:28:12 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_dlist	*new_dlist(int data, t_dlist *prev, t_dlist *next)
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

void			get_stack_a(int argc, char **argv, t_ps *s)
{
	int		i;
	t_dlist	*list;

	i = 1;
	list = new_dlist(ft_atoi(&argv[i]), NULL, NULL);
	if (*argv[i] == '\0')
		i++;
	s->a_num = 1;
	s->head_a = list;
	while (i < argc)
	{
		if (*argv[i] == '\0')
			exit_error();
		while (*argv[i])
		{
			if (*argv[i] == ' ')
				argv[i] += 1;
			list->next = new_dlist(ft_atoi(&argv[i]), list, NULL);
			list = list->next;
			s->a_num += 1;
		}
		i++;
	}
	s->tail_a = list;
	find_duplicate_numbers(s->head_a);
}
