/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 20:14:45 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/08 20:14:47 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void		draw_stack_a(t_dlist *stack_a, int a_num, t_check *v)
{
	int		indent;
	int		row_width;
	int		line;
	int		i;
	int		n;

	line = v->win_hight - 2;
	while (--a_num >= 0 && stack_a != NULL)
	{
		row_width = stack_a->data * v->row_width_mult;
		indent = 350 - row_width / 2;
		i = -1;
		while (++i < v->row_hight_in_pixels)
		{
			n = -1;
			while (++n < row_width)
				v->image[line * 1400 + n + indent] = v->color;
			line--;
		}
		stack_a = stack_a->prev;
	}
}

static void		draw_stack_b(t_dlist *stack_b, int b_num, t_check *v)
{
	int		indent;
	int		row_width;
	int		line;
	int		i;
	int		n;

	line = v->win_hight - 2;
	while (--b_num >= 0 && stack_b != NULL)
	{
		row_width = stack_b->data * v->row_width_mult;
		indent = 1050 - row_width / 2;
		i = -1;
		while (++i < v->row_hight_in_pixels)
		{
			n = -1;
			while (++n < row_width)
				v->image[line * 1400 + n + indent] = v->color;
			line--;
		}
		stack_b = stack_b->prev;
	}
}

static void		num_to_str(int num, int n, char *arr)
{
	int l;

	l = 1;
	while (n /= 10)
		l++;
	arr[l] = '\0';
	while (--l >= 0)
	{
		arr[l] = num % 10 + 48;
		num /= 10;
	}
}

int				draw(t_check *v)
{
	int		n;
	char	num[11];

	n = 1400 * (v->win_hight - 1);
	while (n > 40600)
		v->image[n--] = 0;
	n = 28;
	while (++n < v->win_hight - 1)
	{
		v->image[1400 * n + 699] = WHITE;
		v->image[1400 * n + 700] = WHITE;
	}
	draw_stack_a(v->tail_a, v->a_num, v);
	draw_stack_b(v->tail_b, v->b_num, v);
	mlx_put_image_to_window(v->mlx_ptr, v->win_ptr, v->img_ptr, 0, 0);
	mlx_string_put(v->mlx_ptr, v->win_ptr, 10, 3, WHITE, "operations: ");
	num_to_str(v->i + 1, v->i + 1, num);
	mlx_string_put(v->mlx_ptr, v->win_ptr, 124, 3, v->color, num);
	num_to_str(v->a_num, v->a_num, num);
	mlx_string_put(v->mlx_ptr, v->win_ptr, 260, 3, WHITE, "numbers in stack A");
	mlx_string_put(v->mlx_ptr, v->win_ptr, 455, 3, v->color, num);
	num_to_str(v->b_num, v->b_num, num);
	mlx_string_put(v->mlx_ptr, v->win_ptr, 960, 3, WHITE, "numbers in stack B");
	mlx_string_put(v->mlx_ptr, v->win_ptr, 1155, 3, v->color, num);
	return (0);
}
