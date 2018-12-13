/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_rotate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:30:31 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/09 15:30:32 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list			*new_list(int data)
{
	t_list	*list;

	if (!(list = (t_list *)malloc(sizeof(t_list))))
		exit_error();
	list->data = data;
	list->next = NULL;
	return (list);
}

static void		swap_ps(int com, t_ps *s)
{
	int tmp;

	if (com == SA && s->b_num > 1 && s->head_b->data < s->head_b->next->data)
		com = SS;
	if ((com == SA || com == SS) && s->a_num > 1)
	{
		tmp = s->head_a->data;
		s->head_a->data = s->head_a->next->data;
		s->head_a->next->data = tmp;
	}
	if ((com == SB || com == SS) && s->b_num > 1)
	{
		tmp = s->head_b->data;
		s->head_b->data = s->head_b->next->data;
		s->head_b->next->data = tmp;
	}
	s->out->next = new_list(com);
	s->out = s->out->next;
}

static void		rotate_ps(int com, t_ps *s)
{
	if ((com == RA || com == RR) && s->a_num > 1)
	{
		s->tail_a->next = s->head_a;
		s->head_a = s->head_a->next;
		s->head_a->prev = NULL;
		s->tail_a->next->prev = s->tail_a;
		s->tail_a = s->tail_a->next;
		s->tail_a->next = NULL;
	}
	if ((com == RB || com == RR) && s->b_num > 1)
	{
		s->tail_b->next = s->head_b;
		s->head_b = s->head_b->next;
		s->head_b->prev = NULL;
		s->tail_b->next->prev = s->tail_b;
		s->tail_b = s->tail_b->next;
		s->tail_b->next = NULL;
	}
	s->out->next = new_list(com);
	s->out = s->out->next;
}

static void		reverse_rotate_ps(int com, t_ps *s)
{
	if ((com == RRA || com == RRR) && s->a_num > 1)
	{
		s->head_a->prev = s->tail_a;
		s->tail_a = s->tail_a->prev;
		s->tail_a->next = NULL;
		s->head_a->prev->next = s->head_a;
		s->head_a = s->head_a->prev;
		s->head_a->prev = NULL;
	}
	if ((com == RRB || com == RRR) && s->b_num > 1)
	{
		s->head_b->prev = s->tail_b;
		s->tail_b = s->tail_b->prev;
		s->tail_b->next = NULL;
		s->head_b->prev->next = s->head_b;
		s->head_b = s->head_b->prev;
		s->head_b->prev = NULL;
	}
	s->out->next = new_list(com);
	s->out = s->out->next;
}

void			do_com(int com, t_ps *s)
{
	if (com == SA || com == SB || com == SS)
		swap_ps(com, s);
	else if (com == PA)
		push_in_a(s);
	else if (com == PB)
		push_in_b(s);
	else if (com == RA || com == RB || com == RR)
		rotate_ps(com, s);
	else if (com == RRA || com == RRB || com == RRR)
		reverse_rotate_ps(com, s);
}
