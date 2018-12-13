/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 14:50:28 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/05 14:50:30 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void		quicksort(int *arr, int size)
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

static void		get_number_indexes(t_dlist *list, t_check *v)
{
	int		arr[v->a_num];
	int		i;

	i = -1;
	while (++i < v->a_num)
	{
		arr[i] = list->data;
		list = list->next;
	}
	quicksort(arr, i);
	list = v->head_a;
	while (list)
	{
		i = -1;
		while (++i < v->a_num)
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

static void		draw_top(t_check *v)
{
	int n;

	n = -1;
	while (++n < 29)
	{
		v->image[1400 * n + 699] = WHITE;
		v->image[1400 * n + 700] = WHITE;
	}
	n = -1;
	while (++n < 1400)
	{
		v->image[1400 * 27 + n] = WHITE;
		v->image[1400 * 28 + n] = WHITE;
	}
}

static int		exit_x(void)
{
	exit(0);
	return (0);
}

void			visualization(t_check *v)
{
	int bits_per_pixel;
	int sl;
	int e;

	v->i = -1;
	v->enter = 0;
	v->shift = 0;
	v->color = 0xffd700;
	v->row_hight_in_pixels = 1000 / v->a_num;
	v->row_width_mult = (float)700 / v->a_num;
	v->win_hight = v->row_hight_in_pixels * v->a_num + 30;
	get_number_indexes(v->head_a, v);
	v->mlx_ptr = mlx_init();
	v->win_ptr = mlx_new_window(v->mlx_ptr, 1400, v->win_hight, "push swap");
	v->img_ptr = mlx_new_image(v->mlx_ptr, 1400, v->win_hight);
	v->image = (int *)mlx_get_data_addr(v->img_ptr, &bits_per_pixel, &sl, &e);
	draw_top(v);
	draw(v);
	mlx_hook(v->win_ptr, 2, 0, &key_hook, v);
	mlx_loop_hook(v->mlx_ptr, &shift_and_enter_hooks, v);
	mlx_hook(v->win_ptr, 17, 1L << 17, exit_x, v->mlx_ptr);
	mlx_loop(v->mlx_ptr);
}
