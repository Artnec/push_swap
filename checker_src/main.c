/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 20:45:16 by anesteru          #+#    #+#             */
/*   Updated: 2018/03/31 20:45:17 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void			exit_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

static void		is_sorted(int b_num, t_dlist *list)
{
	if (b_num != 0)
	{
		write(1, "KO\n", 3);
		return ;
	}
	while (list->next)
	{
		if (list->data > list->next->data)
		{
			write(1, "KO\n", 3);
			return ;
		}
		list = list->next;
	}
	write(1, "OK\n", 3);
}

static void		unsort(int index, t_check *v)
{
	while (--index >= 0)
	{
		if (v->instr[index] == SA)
			swap(1, v);
		else if (v->instr[index] == SB)
			swap(2, v);
		else if (v->instr[index] == SS)
			swap(3, v);
		else if (v->instr[index] == PA && v->a_num > 0)
			push_b(v);
		else if (v->instr[index] == PB && v->b_num > 0)
			push_a(v);
		else if (v->instr[index] == RA)
			reverse_rotate(1, v);
		else if (v->instr[index] == RB)
			reverse_rotate(2, v);
		else if (v->instr[index] == RR)
			reverse_rotate(3, v);
		else if (v->instr[index] == RRA)
			rotate(1, v);
		else if (v->instr[index] == RRB)
			rotate(2, v);
		else if (v->instr[index] == RRR)
			rotate(3, v);
	}
}

int				main(int argc, char **argv)
{
	t_check	v;

	if (argc > 1)
	{
		v.v_flag = 0;
		read_numbers(argc, argv, &v);
		v.b_num = 0;
		get_instructions(&v);
		push_swap(-1, &v);
		is_sorted(v.b_num, v.head_a);
		if (v.v_flag && v.a_num <= 1000)
		{
			unsort(v.instr_num, &v);
			visualization(&v);
		}
	}
	return (0);
}
