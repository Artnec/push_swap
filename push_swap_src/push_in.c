/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 14:38:28 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/16 14:38:30 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		pppush_in_empty_a(t_ps *s)
{
	s->head_a = s->head_b;
	s->head_b = s->head_b->next;
	s->head_b->prev = NULL;
	s->tail_a = s->head_a;
	s->head_a->prev = NULL;
	s->head_a->next = NULL;
}

void			push_in_a(t_ps *s)
{
	if (s->a_num == 0)
		pppush_in_empty_a(s);
	else
	{
		s->head_a->prev = s->head_b;
		if (s->b_num == 1)
		{
			s->head_a->prev->next = s->head_a;
			s->head_b = NULL;
			s->tail_b = NULL;
		}
		else
		{
			s->head_b = s->head_b->next;
			s->head_b->prev = NULL;
			s->head_a->prev->next = s->head_a;
		}
		s->head_a = s->head_a->prev;
		s->head_a->prev = NULL;
	}
	s->a_num += 1;
	s->b_num -= 1;
	s->out->next = new_list(PA);
	s->out = s->out->next;
}

static void		pppush_in_empty_b(t_ps *s)
{
	s->head_b = s->head_a;
	s->head_a = s->head_a->next;
	s->head_a->prev = NULL;
	s->tail_b = s->head_b;
	s->head_b->prev = NULL;
	s->head_b->next = NULL;
}

void			push_in_b(t_ps *s)
{
	if (s->b_num == 0)
		pppush_in_empty_b(s);
	else
	{
		s->head_b->prev = s->head_a;
		if (s->a_num == 1)
		{
			s->head_b->prev->next = s->head_b;
			s->head_a = NULL;
			s->tail_a = NULL;
		}
		else
		{
			s->head_a = s->head_a->next;
			s->head_a->prev = NULL;
			s->head_b->prev->next = s->head_b;
		}
		s->head_b = s->head_b->prev;
		s->head_b->prev = NULL;
	}
	s->b_num += 1;
	s->a_num -= 1;
	s->out->next = new_list(PB);
	s->out = s->out->next;
}
