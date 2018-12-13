/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_half_of_unsorted_in_b.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 20:31:38 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/15 20:31:40 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		get_max_unsorted_pushed_number(int n, t_dlist *l)
{
	int max;
	int min;

	min = l->data;
	max = l->data;
	while (l->next)
	{
		if (l->next->data - l->data != 1)
		{
			if (l->data > max || l->next->data > max)
				max = (l->data > l->next->data) ? l->data : l->next->data;
			if (l->data < min || l->next->data < min)
				min = (l->data < l->next->data) ? l->data : l->next->data;
		}
		l = l->next;
	}
	return (((min + max) / 2 > n - 3) ? n - 3 : (min + max) / 2);
}

static int		how_many_numbers_to_push(int n, t_dlist *list)
{
	int i;

	i = 0;
	while (list)
	{
		if (list->data <= n)
			i++;
		list = list->next;
	}
	return (i);
}

void			push_half_of_unsorted_in_b(t_ps *s)
{
	int t;
	int i;
	int n;

	t = 0;
	n = get_max_unsorted_pushed_number(s->a_num + s->b_num, s->head_a);
	i = how_many_numbers_to_push(n, s->head_a);
	while (i > 0)
	{
		if (s->head_a->data <= n && s->head_a->data > n / 2 && t++ && t > 0)
			while (s->head_b->data <= n / 2)
				do_com(RB, s);
		else if (s->head_a->data > n && s->head_b->data <= n / 2 && t > 0)
			do_com(RB, s);
		s->head_a->data <= n && i-- ? do_com(PB, s) : do_com(RA, s);
	}
	if (t > 0)
		while (s->head_b->data <= n / 2)
			do_com(RB, s);
}
