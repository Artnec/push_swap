/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 21:00:05 by anesteru          #+#    #+#             */
/*   Updated: 2018/04/30 21:00:07 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		trim_commands(t_list *list, t_list *n, t_list *nn)
{
	if ((n->data == RA && nn->data == RRA) || (n->data == RRA &&
		nn->data == RA) || (n->data == RB && nn->data == RRB) ||
		(n->data == RRB && nn->data == RB) || (n->data == PA && nn->data == PB)
		|| (n->data == PB && nn->data == PA))
	{
		list->next = nn->next;
		free(n);
		free(nn);
		return (1);
	}
	else if ((n->data == RA && nn->data == RB) ||
		(n->data == RB && nn->data == RA))
	{
		free(n);
		nn->data = RR;
		list->next = nn;
	}
	else if ((n->data == RRA && nn->data == RRB) ||
		(n->data == RRB && nn->data == RRA))
	{
		free(n);
		nn->data = RRR;
		list->next = nn;
	}
	return (0);
}

static void		trim_out(t_ps *s)
{
	int		j;

	j = 1;
	if (s->out_head->next == NULL)
	{
		free(s->out_head);
		s->out_head = NULL;
		return ;
	}
	s->out = s->out_head->next;
	free(s->out_head);
	s->out_head = s->out;
	if (s->out->next)
	{
		while (j-- > 0)
		{
			while (s->out->next && s->out->next->next)
			{
				if (trim_commands(s->out, s->out->next, s->out->next->next))
					j = 1;
				s->out = s->out->next;
			}
			s->out = s->out_head;
		}
	}
}

static int		write_command_to_str(char *com, char *str)
{
	int i;

	i = 0;
	while (com[i])
	{
		str[i] = com[i];
		i++;
	}
	return (i);
}

static int		write_command(int com, char *str)
{
	if (com == SA)
		return (write_command_to_str("sa\n", str));
	else if (com == SB)
		return (write_command_to_str("sb\n", str));
	else if (com == SS)
		return (write_command_to_str("ss\n", str));
	else if (com == PA)
		return (write_command_to_str("pa\n", str));
	else if (com == PB)
		return (write_command_to_str("pb\n", str));
	else if (com == RA)
		return (write_command_to_str("ra\n", str));
	else if (com == RB)
		return (write_command_to_str("rb\n", str));
	else if (com == RR)
		return (write_command_to_str("rr\n", str));
	else if (com == RRA)
		return (write_command_to_str("rra\n", str));
	else if (com == RRB)
		return (write_command_to_str("rrb\n", str));
	return (write_command_to_str("rrr\n", str));
}

void			print_out(t_ps *s)
{
	t_list	*lst;
	char	*str;
	int		l;
	int		i;

	trim_out(s);
	l = 0;
	lst = s->out_head;
	while (lst)
	{
		l += (lst->data == RRA || lst->data == RRB || lst->data == RRR) ? 4 : 3;
		lst = lst->next;
	}
	str = (char *)malloc(l);
	i = 0;
	lst = s->out_head;
	while (lst)
	{
		i += write_command(lst->data, str + i);
		lst = lst->next;
	}
	write(1, str, i);
	free(str);
}
