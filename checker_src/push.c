/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 19:18:14 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/04 19:18:18 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void		push_into_empty_a(t_check *v)
{
	v->head_a = v->head_b;
	v->head_b = v->head_b->next;
	v->head_b->prev = NULL;
	v->tail_a = v->head_a;
	v->head_a->prev = NULL;
	v->head_a->next = NULL;
}

void			push_a(t_check *v)
{
	if (v->a_num == 0)
		push_into_empty_a(v);
	else
	{
		v->head_a->prev = v->head_b;
		if (v->b_num == 1)
		{
			v->head_a->prev->next = v->head_a;
			v->head_b = NULL;
			v->tail_b = NULL;
		}
		else
		{
			v->head_b = v->head_b->next;
			v->head_b->prev = NULL;
			v->head_a->prev->next = v->head_a;
		}
		v->head_a = v->head_a->prev;
		v->head_a->prev = NULL;
	}
	v->a_num += 1;
	v->b_num -= 1;
}

static void		push_into_empty_b(t_check *v)
{
	v->head_b = v->head_a;
	v->head_a = v->head_a->next;
	v->head_a->prev = NULL;
	v->tail_b = v->head_b;
	v->head_b->prev = NULL;
	v->head_b->next = NULL;
}

void			push_b(t_check *v)
{
	if (v->b_num == 0)
		push_into_empty_b(v);
	else
	{
		v->head_b->prev = v->head_a;
		if (v->a_num == 1)
		{
			v->head_b->prev->next = v->head_b;
			v->head_a = NULL;
			v->tail_a = NULL;
		}
		else
		{
			v->head_a = v->head_a->next;
			v->head_a->prev = NULL;
			v->head_b->prev->next = v->head_b;
		}
		v->head_b = v->head_b->prev;
		v->head_b->prev = NULL;
	}
	v->b_num += 1;
	v->a_num -= 1;
}
