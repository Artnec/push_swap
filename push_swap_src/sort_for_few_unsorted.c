/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_for_few_unsorted.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:14:58 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/16 16:14:59 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		swap_three(t_ps *s)
{
	int head_a;
	int next;
	int next_next;

	head_a = s->head_a->data;
	next = s->head_a->next->data;
	next_next = s->head_a->next->next->data;
	if (head_a < next && head_a < next_next)
	{
		do_com(RRA, s);
		do_com(SA, s);
	}
	else if (head_a > next && head_a > next_next)
	{
		do_com(RA, s);
		if (head_a > next)
			do_com(SA, s);
	}
	else
		head_a > next ? do_com(SA, s) : do_com(RRA, s);
}

static int		how_many_unsorted(t_dlist *list, t_ps *s)
{
	int i;
	int n;

	i = 1;
	n = 0;
	while (list)
	{
		if (list->data != s->b_num + i)
			n = i;
		if (n > 3)
			return (4);
		i++;
		list = list->next;
	}
	return (n);
}

static void		sort_biggest_first(int next_data, int next_next_data, t_ps *s)
{
	if (next_data < next_next_data)
	{
		do_com(SA, s);
		do_com(RA, s);
		do_com(SA, s);
		do_com(RRA, s);
	}
	else
	{
		do_com(SA, s);
		do_com(RA, s);
		do_com(SA, s);
		do_com(RRA, s);
		do_com(SA, s);
	}
}

int				sort_for_few_unsorted(int n, t_dlist *l, t_ps *s)
{
	if (s->a_num == 3)
		swap_three(s);
	else if ((n = how_many_unsorted(s->head_a, s)) <= 3)
	{
		if (n == 2)
			do_com(SA, s);
		else if (l->data < l->next->data && l->data < l->next->next->data)
		{
			do_com(RA, s);
			do_com(SA, s);
			do_com(RRA, s);
		}
		else if (l->data > l->next->data && l->data > l->next->next->data)
			sort_biggest_first(l->next->data, l->next->next->data, s);
		else
		{
			do_com(RA, s);
			do_com(SA, s);
			do_com(RRA, s);
			do_com(SA, s);
		}
	}
	else
		return (0);
	return (1);
}
