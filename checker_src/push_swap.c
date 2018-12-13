/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:20:08 by anesteru          #+#    #+#             */
/*   Updated: 2018/04/17 16:20:10 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void		swap(int n, t_check *v)
{
	int tmp;

	if ((n == 1 || n == 3) && v->a_num > 1)
	{
		tmp = v->head_a->data;
		v->head_a->data = v->head_a->next->data;
		v->head_a->next->data = tmp;
	}
	if ((n == 2 || n == 3) && v->b_num > 1)
	{
		tmp = v->head_b->data;
		v->head_b->data = v->head_b->next->data;
		v->head_b->next->data = tmp;
	}
}

void		rotate(int n, t_check *v)
{
	if ((n == 1 || n == 3) && v->a_num > 1)
	{
		v->tail_a->next = v->head_a;
		v->head_a = v->head_a->next;
		v->head_a->prev = NULL;
		v->tail_a->next->prev = v->tail_a;
		v->tail_a = v->tail_a->next;
		v->tail_a->next = NULL;
	}
	if ((n == 2 || n == 3) && v->b_num > 1)
	{
		v->tail_b->next = v->head_b;
		v->head_b = v->head_b->next;
		v->head_b->prev = NULL;
		v->tail_b->next->prev = v->tail_b;
		v->tail_b = v->tail_b->next;
		v->tail_b->next = NULL;
	}
}

void		reverse_rotate(int n, t_check *v)
{
	if ((n == 1 || n == 3) && v->a_num > 1)
	{
		v->head_a->prev = v->tail_a;
		v->tail_a = v->tail_a->prev;
		v->tail_a->next = NULL;
		v->head_a->prev->next = v->head_a;
		v->head_a = v->head_a->prev;
		v->head_a->prev = NULL;
	}
	if ((n == 2 || n == 3) && v->b_num > 1)
	{
		v->head_b->prev = v->tail_b;
		v->tail_b = v->tail_b->prev;
		v->tail_b->next = NULL;
		v->head_b->prev->next = v->head_b;
		v->head_b = v->head_b->prev;
		v->head_b->prev = NULL;
	}
}

void		push_swap(int index, t_check *v)
{
	while (++index < v->instr_num)
	{
		if (v->instr[index] == SA)
			swap(1, v);
		else if (v->instr[index] == SB)
			swap(2, v);
		else if (v->instr[index] == SS)
			swap(3, v);
		else if (v->instr[index] == PA && v->b_num > 0)
			push_a(v);
		else if (v->instr[index] == PB && v->a_num > 0)
			push_b(v);
		else if (v->instr[index] == RA)
			rotate(1, v);
		else if (v->instr[index] == RB)
			rotate(2, v);
		else if (v->instr[index] == RR)
			rotate(3, v);
		else if (v->instr[index] == RRA)
			reverse_rotate(1, v);
		else if (v->instr[index] == RRB)
			reverse_rotate(2, v);
		else if (v->instr[index] == RRR)
			reverse_rotate(3, v);
	}
}
