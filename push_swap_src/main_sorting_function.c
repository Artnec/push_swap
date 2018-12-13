/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_sorting_function.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 22:01:12 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/15 22:01:13 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		recursive_min_num_to_push_finder(int d, int i, t_ps *s)
{
	t_dlist		*list;
	int			j;
	int			t;

	j = 0;
	t = 0;
	list = s->head_b;
	while (list)
	{
		if (list->data >= s->b_num - d && list->data <= s->b_num)
			j++;
		t++;
		if (j == d + 1 && t != i)
		{
			recursive_min_num_to_push_finder(t / 2 - 1, t, s);
			return ;
		}
		else if (j == d + 1)
		{
			s->min_num = s->b_num - d;
			return ;
		}
		list = list->next;
	}
}

static int		how_many_numbers_to_push(t_dlist *list, t_ps *s)
{
	int i;

	i = 0;
	while (list)
	{
		i++;
		if (list->data == s->b_num)
		{
			recursive_min_num_to_push_finder((i + 1) / 2 - 1, i, s);
			i = 0;
			list = s->head_b;
			while (list)
			{
				if (list->data >= s->min_num)
					i++;
				list = list->next;
			}
			return (i);
		}
		list = list->next;
	}
	return (0);
}

static int		how_many_times_to_rrotate(int min_rotatable_num, t_ps *s)
{
	int			num_of_rotations;
	int			i;
	t_dlist		*list;

	list = s->tail_b;
	num_of_rotations = 0;
	i = 0;
	while (list->data > s->b_num / 2 + 1)
	{
		i++;
		if (list->data > min_rotatable_num)
			num_of_rotations = i;
		list = list->prev;
	}
	return (num_of_rotations);
}

static void		rrotate_from_botom(t_ps *s)
{
	int			num_of_rotations;
	int			min_rotatable_num;
	t_dlist		*list;

	min_rotatable_num = s->head_b->data;
	list = s->head_b;
	while (list)
	{
		if (list->data < s->b_num / 2 + 1 || list->data == s->b_num)
			break ;
		if (list->data < min_rotatable_num)
			min_rotatable_num = list->data;
		list = list->next;
	}
	num_of_rotations = how_many_times_to_rrotate(min_rotatable_num, s);
	while (s->b_num > 2 && num_of_rotations > 0)
	{
		do_com(RRB, s);
		while (s->b_num > 0 && s->head_b->data == s->b_num)
			do_com(PA, s);
		num_of_rotations -= 1;
	}
}

void			main_sorting_function(int sorted, t_ps *s)
{
	int		i;

	while (sorted == 0 || s->b_num > 0)
	{
		if (sorted == 0)
		{
			while (s->sort == 1 && s->tail_a->data != s->a_num + s->b_num)
				do_com(RRA, s);
			push_half_of_unsorted_in_b(s);
		}
		else
		{
			find_and_push_numbers(s);
			if (s->b_num > 0)
			{
				rrotate_from_botom(s);
				i = how_many_numbers_to_push(s->head_b, s);
				while (i > 0)
					do_com(s->head_b->data >= s->min_num && i-- ? PA : RB, s);
			}
		}
		sorted = try_to_sort(s);
		if (sorted == 1)
			s->sort = 1;
	}
}
