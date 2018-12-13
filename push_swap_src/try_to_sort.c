/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_to_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 20:23:49 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/15 20:23:50 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		is_sorted(t_dlist *list)
{
	while (list->next)
	{
		if (list->data > list->next->data)
			return (0);
		list = list->next;
	}
	return (1);
}

static int		try_to_rotate(t_dlist *list, t_ps *s)
{
	int i;
	int n;
	int max;
	int min;

	max = s->a_num + s->b_num;
	min = s->b_num + 1;
	i = 1;
	while (list->next)
	{
		if (list->data == max && list->next->data != min)
			return (0);
		else if (list->data == max)
			n = i;
		else if (list->data - list->next->data != -1)
			return (0);
		i++;
		list = list->next;
	}
	i = (n <= max - min - n) ? n : max - min - n + 1;
	while (i--)
		n <= max - min - n ? do_com(RA, s) : do_com(RRA, s);
	return (1);
}

static void		swap_and_rotate(int n, int t, t_ps *s)
{
	if (t * 2 > s->a_num)
	{
		while (n > 0)
		{
			if (s->tail_a->prev->data - s->tail_a->data == 1 && n--)
			{
				do_com(RRA, s);
				do_com(RRA, s);
				do_com(SA, s);
			}
			else
				do_com(RRA, s);
		}
	}
	else
	{
		while (n > 0)
			do_com(s->head_a->data - s->head_a->next->data == 1
				&& n-- ? SA : RA, s);
	}
	if (is_sorted(s->head_a) == 1)
		return ;
	try_to_rotate(s->head_a, s);
}

static int		try_swap_and_rotate(int i, int n, t_dlist *list, t_ps *s)
{
	int			arr[s->a_num];
	int			t;
	int			tmp;

	while (list)
	{
		arr[i++] = list->data;
		list = list->next;
	}
	i = -1;
	t = -1;
	while (++i < s->a_num - 1)
		if (arr[i] - arr[i + 1] == 1 && ++n)
		{
			tmp = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = tmp;
			t = (t == -1) ? i : t;
		}
	i = -1;
	while (++i < s->a_num - 1)
		if (arr[i + 1] - arr[i] != 1 && arr[i] != s->a_num + s->b_num)
			return (0);
	swap_and_rotate(n, t, s);
	return (1);
}

int				try_to_sort(t_ps *s)
{
	if (is_sorted(s->head_a) || try_to_rotate(s->head_a, s))
		return (1);
	else if (sort_for_few_unsorted(0, s->head_a, s))
		return (1);
	else if (s->b_num == 0 && s->a_num > 3)
	{
		if (try_swap_and_rotate(0, 0, s->head_a, s) == 1)
			return (1);
	}
	return (0);
}
