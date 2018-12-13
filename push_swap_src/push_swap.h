#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>

# define SA 0
# define SB 1
# define SS 2
# define PA 3
# define PB 4
# define RA 5
# define RB 6
# define RR 7
# define RRA 8
# define RRB 9
# define RRR 10


typedef struct		s_list
{
	int				data;
	struct s_list	*next;
}					t_list;

typedef struct		s_dlist
{
	int				data;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;

typedef struct		s_ps
{
	t_list			*given_numbers;
	t_list			*given_numbers_head;
	t_dlist			*head_a;
	t_dlist			*tail_a;
	int				a_num;
	t_dlist			*head_b;
	t_dlist			*tail_b;
	int				b_num;
	t_list			*out;
	t_list			*out_head;
	int				min_num;
	int				sort;
}					t_ps;


t_list				*new_list(int data);
void				get_stack_a(int argc, char **argv, t_ps *s);
void				push_in_a(t_ps *s);
void				push_in_b(t_ps *s);
int					try_to_sort(t_ps *s);
int					sort_for_few_unsorted(int n, t_dlist *l, t_ps *s);
void				push_half_of_unsorted_in_b(t_ps *s);
int					find_and_push_numbers(t_ps *s);
void				main_sorting_function(int sorted, t_ps *s);
void				do_com(int com, t_ps *s);
void				print_out(t_ps *s);
void				exit_error(void);

#endif
