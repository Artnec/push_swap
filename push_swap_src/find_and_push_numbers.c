/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_and_push_numbers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 20:37:54 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/15 20:37:55 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		find_numbers_to_push(int j, int i, t_ps *s)
{
	int			n;
	int			t;
	t_dlist		*list;

	n = 0;
	t = 0;
	list = s->head_b;
	while (list)
	{
		if (list->data >= s->head_a->data - j)
			n++;
		t++;
		if (t > i)
			return (0);
		if (n == j)
			break ;
		list = list->next;
	}
	return (list ? 1 : 0);
}

static void		push_numbers(int smallest_sorted, int i, int n, t_ps *s)
{
	while (i > 0)
	{
		if (s->head_b->data >= smallest_sorted - 2 && i--)
		{
			while (s->head_a->data < smallest_sorted - 2)
				do_com(RA, s);
			do_com(PA, s);
			if (s->head_a->data > s->head_a->next->data)
				do_com(SA, s);
		}
		else if (s->head_b->data >= smallest_sorted - n && i--)
		{
			if (s->head_b->data > s->head_a->data)
				do_com(RA, s);
			do_com(PA, s);
		}
		else
			do_com(RB, s);
	}
	while (s->tail_a->data < s->a_num + s->b_num)
		do_com(RRA, s);
	if (s->head_a->data > s->head_a->next->data)
		do_com(SA, s);
}

static void		reverse_rotate_b_if_needed(t_ps *s)
{
	int		i;
	int		n;
	t_dlist	*list;

	n = 1;
	while (n--)
	{
		i = 1;
		list = s->tail_b;
		while (list && list->data > s->b_num / 2 + 1)
		{
			if (list->data == s->b_num)
			{
				while (i--)
					do_com(RRB, s);
				do_com(PA, s);
				n = 1;
			}
			list = list->prev;
			i++;
		}
	}
}

int				find_and_push_numbers(t_ps *s)
{
	int i;
	int n;

	i = -1;
	while (++i < 6)
	{
		n = 5;
		while (--n)
		{
			if (i <= n + 2 && find_numbers_to_push(n, n + i, s))
			{
				push_numbers(s->head_a->data, n, n, s);
				reverse_rotate_b_if_needed(s);
				n = 4;
				i = 0;
			}
		}
	}
	return (i);
}
