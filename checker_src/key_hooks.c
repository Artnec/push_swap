/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 14:49:52 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/05 14:49:54 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void		rotate_or_reverse_rotate(int key, t_check *v)
{
	if (v->instr[v->i] == RA)
		(key == 124) ? rotate(1, v) : reverse_rotate(1, v);
	else if (v->instr[v->i] == RB)
		(key == 124) ? rotate(2, v) : reverse_rotate(2, v);
	else if (v->instr[v->i] == RR)
		(key == 124) ? rotate(3, v) : reverse_rotate(3, v);
	else if (v->instr[v->i] == RRA)
		(key == 124) ? reverse_rotate(1, v) : rotate(1, v);
	else if (v->instr[v->i] == RRB)
		(key == 124) ? reverse_rotate(2, v) : rotate(2, v);
	else if (v->instr[v->i] == RRR)
		(key == 124) ? reverse_rotate(3, v) : rotate(3, v);
}

static void		execute_instruction(int key, t_check *v)
{
	if ((v->i == -1 && key == 123) || (v->i + 1 == v->instr_num && key == 124))
		return ;
	if (key == 124)
		v->i++;
	if (v->instr[v->i] == RA || v->instr[v->i] == RB || v->instr[v->i] == RR ||
		v->instr[v->i] == RRA || v->instr[v->i] == RRB || v->instr[v->i] == RRR)
		rotate_or_reverse_rotate(key, v);
	else if (v->instr[v->i] == SA)
		swap(1, v);
	else if (v->instr[v->i] == SB)
		swap(2, v);
	else if (v->instr[v->i] == SS)
		swap(3, v);
	else if (v->instr[v->i] == PA)
		(key == 124) ? push_a(v) : push_b(v);
	else if (v->instr[v->i] == PB)
		(key == 124) ? push_b(v) : push_a(v);
	if (key == 123)
		v->i--;
	if (v->enter == 1 && v->i + 1 == v->instr_num)
		v->enter = 0;
	if (v->shift == 1 && v->i == -1)
		v->shift = 0;
}

static void		change_color(t_check *v)
{
	if (v->color == 0xffd700)
		v->color = 0x4eff84;
	else if (v->color == 0x4eff84)
		v->color = 0xb70e4d;
	else if (v->color == 0xb70e4d)
		v->color = 0xffe1d6;
	else if (v->color == 0xffe1d6)
		v->color = 0xffd700;
}

int				shift_and_enter_hooks(t_check *v)
{
	if (v->enter == 1)
	{
		execute_instruction(124, v);
		draw(v);
	}
	else if (v->shift == 1)
	{
		execute_instruction(123, v);
		draw(v);
	}
	return (0);
}

int				key_hook(int key, t_check *v)
{
	if (key == 53)
		exit(0);
	else if (key == 36)
	{
		v->enter = (v->enter == 0) ? 1 : 0;
		if (v->enter == 1)
			v->shift = 0;
	}
	else if (key == 258)
	{
		v->shift = (v->shift == 0) ? 1 : 0;
		if (v->shift == 1)
			v->enter = 0;
	}
	else if ((key == 124 || key == 123) && v->enter == 0)
		execute_instruction(key, v);
	else if (key == 8)
		change_color(v);
	else if (key == 15)
		while (v->i >= 0)
			execute_instruction(123, v);
	else
		return (0);
	draw(v);
	return (0);
}
