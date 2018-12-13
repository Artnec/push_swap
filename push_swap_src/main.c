/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 20:44:49 by anesteru          #+#    #+#             */
/*   Updated: 2018/03/31 20:44:51 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		exit_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

static void	quicksort(int *arr, int size)
{
	int i;
	int j;
	int tmp;
	int pivot;

	if (size < 2)
		return ;
	pivot = arr[size / 2];
	i = -1;
	j = size - 1;
	while (++i > -1)
	{
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i >= j)
			break ;
		tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
		j--;
	}
	quicksort(arr, i);
	quicksort(arr + i, size - i);
}

static void	get_a_indexes(t_dlist *list, t_ps *s)
{
	int	arr[s->a_num];
	int	i;

	i = -1;
	while (++i < s->a_num)
	{
		arr[i] = list->data;
		list = list->next;
	}
	quicksort(arr, i);
	list = s->head_a;
	while (list)
	{
		i = -1;
		while (++i < s->a_num)
		{
			if (list->data == arr[i])
			{
				list->data = i + 1;
				break ;
			}
		}
		list = list->next;
	}
}

int			main(int argc, char **argv)
{
	t_ps	s;

	if (argc > 1)
	{
		s.a_num = 0;
		get_stack_a(argc, argv, &s);
		s.out = new_list(-1);
		s.out_head = s.out;
		s.b_num = 0;
		get_a_indexes(s.head_a, &s);
		s.sort = 0;
		if (try_to_sort(&s) == 0)
			main_sorting_function(0, &s);
		print_out(&s);
	}
	return (0);
}
