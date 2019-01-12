/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 13:52:50 by anesteru          #+#    #+#             */
/*   Updated: 2018/04/17 13:52:52 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int		check_instruction(int bytes_read, char *buf)
{
	if (buf[2] != '\0' && (bytes_read == 4 && buf[3] != '\0'))
		return (-1);
	else if (bytes_read == 3 && buf[0] == 's' && buf[1] == 'a')
		return (0);
	else if (bytes_read == 3 && buf[0] == 's' && buf[1] == 'b')
		return (1);
	else if (bytes_read == 3 && buf[0] == 's' && buf[1] == 's')
		return (2);
	else if (bytes_read == 3 && buf[0] == 'p' && buf[1] == 'a')
		return (3);
	else if (bytes_read == 3 && buf[0] == 'p' && buf[1] == 'b')
		return (4);
	else if (bytes_read == 3 && buf[0] == 'r' && buf[1] == 'a')
		return (5);
	else if (bytes_read == 3 && buf[0] == 'r' && buf[1] == 'b')
		return (6);
	else if (bytes_read == 3 && buf[0] == 'r' && buf[1] == 'r')
		return (7);
	else if (bytes_read == 4 && buf[0] == 'r' && buf[1] == 'r' && buf[2] == 'a')
		return (8);
	else if (bytes_read == 4 && buf[0] == 'r' && buf[1] == 'r' && buf[2] == 'b')
		return (9);
	else if (bytes_read == 4 && buf[0] == 'r' && buf[1] == 'r' && buf[2] == 'r')
		return (10);
	return (-1);
}

static t_list	*new_instruction_list(int bytes_read, char *buf)
{
	t_list	*list;
	int		n;

	if (bytes_read < 3 || bytes_read > 4)
		exit_error();
	if ((n = check_instruction(bytes_read, buf)) == -1)
		exit_error();
	if (!(list = (t_list *)malloc(sizeof(t_list))))
		exit_error();
	list->data = n;
	list->next = NULL;
	return (list);
}

static int		gnl(char *line)
{
	char	buf[4];
	int		bytes_read;

	bytes_read = read(0, buf, 3);
	if (bytes_read == 0)
		return (0);
	if (bytes_read < 3)
		exit_error();
	if (buf[2] != '\n')
	{
		read(0, &buf[3], 1);
		if (buf[3] != '\n')
			exit_error();
		line[0] = buf[0];
		line[1] = buf[1];
		line[2] = buf[2];
		line[3] = '\0';
		return (4);
	}
	line[0] = buf[0];
	line[1] = buf[1];
	line[2] = '\0';
	return (3);
}

void			rewrite_and_free(t_list *head, t_check *v)
{
	t_list	*tmp;
	int		i;

	if (!(v->instr = (int *)malloc(sizeof(int) * v->instr_num)))
		exit_error();
	i = -1;
	tmp = head;
	while (++i < v->instr_num)
	{
		v->instr[i] = tmp->data;
		tmp = tmp->next;
		free(head);
		head = tmp;
	}
}

void			get_instructions(t_check *v)
{
	char	buf[4];
	int		i;
	t_list	*list;
	t_list	*head;

	v->instr_num = 0;
	if ((i = gnl(buf)) == 0)
		return ;
	list = new_instruction_list(i, buf);
	head = list;
	v->instr_num += 1;
	while ((i = gnl(buf)) > 0)
	{
		list->next = new_instruction_list(i, buf);
		list = list->next;
		v->instr_num++;
	}
	rewrite_and_free(head, v);
}
