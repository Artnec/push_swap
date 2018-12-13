#ifndef CHECKER_H
# define CHECKER_H

# include <unistd.h>
# include <stdlib.h>
# include "mlx.h"

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
# define WHITE 0xffffff


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

typedef struct		s_check
{
	int				v_flag;
	int				*instr;
	int				instr_num;
	t_dlist			*head_a;
	t_dlist			*tail_a;
	int				a_num;
	t_dlist			*head_b;
	t_dlist			*tail_b;
	int				b_num;
	void			*mlx_ptr;
	void			*win_ptr;
	int				*image;
	void			*img_ptr;
	float			row_width_mult;
	int				row_hight_in_pixels;
	int				win_hight;
	int				color;
	int				enter;
	int				shift;
	int				i;
}					t_check;


void				read_numbers(int argc, char **argv, t_check *v);
void				get_instructions(t_check *v);
void				push_swap(int index, t_check *v);
void				swap(int n, t_check *v);
void				rotate(int n, t_check *v);
void				reverse_rotate(int n, t_check *v);
void				push_a(t_check *v);
void				push_b(t_check *v);
int					key_hook(int key, t_check *v);
int					shift_and_enter_hooks(t_check *v);
void				visualization(t_check *v);
int					draw(t_check *v);
void				exit_error(void);

#endif
