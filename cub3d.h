/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 11:23:47 by irodrigo          #+#    #+#             */
/*   Updated: 2021/03/14 00:51:54 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUB3D_H
# define _CUB3D_H

# include "./libft/libft.h"
# include "./colors.h"
# include "./lst_errors.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>

# ifdef __APPLE__
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_W 13
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_DOWN 125
#  define KEY_ESC 53
#  define KEY_SHIFT 257
#  include "./mlx_ios/mlx.h"
# elif define __UNIX__
#  define KEY_A 97
#  define KEY_W 119
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_UP 65362
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_DOWN 65364
#  define KEY_ESC 65307
#  define KEY_SHIFT 65507
#  include <X11/Xlib.h>
#  include "./minilibx_linux/mlx.h"
# endif

# define BUFFER_SIZE 1

/*
** max resolution
*/
# define MAXWIDTH 1920
# define MAXHEIGHT 1080

/*
**Resolution structure
*/
typedef struct		s_resol
{
	int				h;
	int				w;
}					t_resol;

/*
**Drawing point structure
*/
typedef struct		s_dpoint
{
	double			x;
	double			y;
}					t_dpoint;

typedef struct		s_ipoint
{
	int				x;
	int				y;
}					t_ipoint;

/*
**texture control structure
*/
typedef struct		s_cnt_txts
{
	int				north;
	int				south;
	int				east;
	int				west;
	int				sprite;

	char			*path_no;
	char			*path_so;
	char			*path_ea;
	char			*path_we;
	char			*path_spr;

	unsigned int	floor;
	unsigned int	ceil;

}					t_cnt_txts;

/*
**raycast control structure
*/
typedef struct		s_raycast
{
	int				x;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	double			camerax;
	double			raydirx;
	double			raydiry;
	int				mapx;
	int				mapy;
	double			deltadistx;
	double			deltadisty;
	int				hit;
	int				stepx;
	int				stepy;
	double			sidedistx;
	double			sidedisty;
	int				side;
	double			perpwalldist;
	int				lineheight;
	int				drawstart;
	int				drawend;
	double			wallx;
	int				texx;
	int				texy;
	double			movespeed;
	double			rotspeed;
	double			oldplanex;
	double			olddirx;
}					t_raycast;

/*
**texture container structure
*/
typedef struct		s_textures
{
	int				id;
	int				width[8];
	int				height[8];
	char			*wlone[8];
	char			*wdata[8];
	int				wbpp[8];
	int				wendian[8];
	int				wsl[8];
	double			step;
	double			texpos;
}					t_textures;

/*
**Individual sprite definition and usage
*/
typedef struct		s_sprite
{
	int				sprn;
	double			spr_dist;
	t_dpoint		spr_pos;
}					t_sprite;

/*
**gamer control structure
*/
typedef struct		s_gamer
{
	t_ipoint		pos;
	int				count;
	char			spr_dir;
}					t_gamer;

/*
**Keyboard control structures
*/
typedef struct		s_key_ctrl
{
	int				a_status;
	int				d_status;
	int				esc_status;
	int				s_status;
	int				w_status;
	int				lf_status;
	int				rg_status;
	int				up_status;
	int				dw_status;
	int				sh_status;
}					t_key_ctrl;

/*
**bmp image format header
*/
typedef struct		s_bmp_hdr
{
	unsigned int	f_size;
	unsigned char	rsvd_1;
	unsigned char	rsvd_2;
	unsigned int	offs_bts;
	unsigned int	sz_headr;
	t_resol			dimens;
	short int		planes;
	short int		bt_count;
	unsigned int	compress;
	unsigned int	img_bt_size;
	unsigned int	ppm_x;
	unsigned int	ppm_y;
	unsigned int	clr_used;
	unsigned int	clr_importnt;
}					t_bmp_hdr;

/*
**Principal game control structure
**
**win				window dimensions
**screenshot		control screen captures
**stat_txt			texture status
**map_char			temporal map threatment
**map_read			control prerequisites
**map_dim			map dimensions
**spr_total			sprites coubnt
**worldmap			map matrix
**gamer				your position on the world
**spriteorder		order of sprites in game world
**spritedistance	distance of sprites based on gamer pos
**el_count			count
**aux_elcount		countb
**segment			stripe
**idx_pos			pos
*/

typedef struct		s_game_draw
{
	t_resol			win;
	int				screenshot;
	t_cnt_txts		stat_txt;
	char			*mapchar;
	int				map_read;
	t_resol			map_dim;
	int				spr_total;
	int				spr_totalb;
	char			**worldmap;
	t_gamer			gamer;

	void			*mlx_ptr;
	void			*mlx_win;

	t_raycast		rc;
	t_textures		tx;
	t_sprite		*sprite;

	void			**canvas;
	char			*canvas_ptr;
	int				c_bpp;
	int				c_sline;
	int				c_endian;

	t_key_ctrl		key;

	int				map_err;
	int				n_err;
	int				idx_pos;
	int				segment;
	int				el_count;
	int				aux_elcount;
	double			zbuffer[4000];
	int				obj;
	int				*allspr_pos;
	double			*allspr_dist;
	int				dirok;

	double			spritex;
	double			spritey;
	double			inv_det;
	double			transformx;
	double			transformy;
	int				scrnx;
	int				spr_height;
	int				spr_width;
	int				draw_startx;
	int				draw_endx;
	int				draw_starty;
	int				draw_endy;
	int				stripe;
	int				tex_x;
	int				tex_y;
}					t_game_draw;

int					checkmap(t_game_draw *mygame);
void				more_texture(t_game_draw *mygame);
void				put_pxl_to_img(t_game_draw *mygame, int x, int y);
void				calcularobj(t_game_draw *mygame);
void				draw_sprite(t_game_draw *mygame);
void				raysprite(t_game_draw *mygame);
void				spritepos(t_game_draw *mygame, int x, int y);
int					ft_atoi_color(char *line, int *i);
int					ft_atoi_cub(char *line, int *pos);
void				ft_freearray(char **str);

/*
**set initial variable values
*/
void				ft_pre_var(t_game_draw *mygame);

/*
**definition of error printing functions
*/
int					ft_put_error (char *err_tit, char *errmsg, int err_n);
void				ft_write_error(char *err_tit, char *errmsg);

/*
**initial checking functions
*/
int					ft_chk_read(char *fname);
int					ft_checkfilestatus(int status, char *elmt,
							t_game_draw *mygame);
void				ft_set_txt_path(char *path, char *elmt,
							t_game_draw *mygame);
int					parsename(const char *text, const char *compare);

/*
**game file parsing
*/
int					get_next_line(int fd, char **line);
int					get_info(t_game_draw *mygame, char *line);
int					read_file(int argc, char *pathname, t_game_draw *mygame);
int					ft_chk_texture(t_game_draw *mygame, char *line, char *elmt);
int					ft_file_error(int fd);

/*
**map parsing
*/
int					read_map(t_game_draw *mygame);
int					get_width(char *str);
int					get_height(char *str);
void				ft_changetab(t_game_draw *mygame);
void				ft_create_matrix (t_game_draw *mygame);
int					ft_get_line_width(char *mapchar, int pos);
int					ft_setmap_ch(t_game_draw *mygame, int mat_pos,
							int line, int pos);
int					ft_parse_map(t_game_draw *mygame);
int					ft_check_gamer(t_game_draw *mygame);
int					ft_check_close(t_game_draw *mygame);
int					ft_check_content (t_game_draw *game);
void				ft_checkborder(int x, int y, char **str, t_game_draw *err);

/*
** game init function
*/
void				ft_init_game(t_game_draw *mygame);

/*
**raycasting functions
*/
void				ft_init_rc(t_game_draw *mygame);
int					ft_load_txt(t_game_draw *mygame);
void				raycasting(t_game_draw *mygame);
void				ft_calc_step(t_game_draw *mygame);
void				ft_perf_dda(t_game_draw *mygame);
void				ft_perp_dist(t_game_draw *mygame);
void				ft_id_texture(t_game_draw *mygame);
void				ft_texturing_calc(t_game_draw *mygame);
void				ft_draw_vertline(t_game_draw *mygame);
void				to_img(t_game_draw *mygame);

/*
**screenshot functions
*/
int					write_bmp_header(int fd, int filesize,
							t_game_draw *mygame);
int					write_bmp_data(int file, t_game_draw *mygame, int pad);

/*
**Keyboard functions
*/
int					nopulsed(int key, t_game_draw *mygame);
int					pulsed(int key, t_game_draw *mygame);
int					deal_key(t_game_draw *mygame);
void				w_and_s(t_game_draw *mygame);
void				a_and_d(t_game_draw *mygame);
void				l_and_r(t_game_draw *kbd);
void				kbd_right(t_game_draw *kbd);

/*
**aux functions
*/
int					ft_isspace(char ch);
int					ft_take_width(char **str, int pos);
int					ft_charge_txt(t_game_draw *mygame, int elm, char *path);
void				ft_swap_int(int *a, int *b);
void				ft_swap_double(double *a, double *b);
int					ft_skip_spaces(char *line, int *i);

/*
**mlx functions
*/
int					ft_getpixel(t_game_draw *map, int x, int y);
void				ft_mlx_pixel_put(t_game_draw *mygame, int x,
							int y, int color);
int					ft_close(t_game_draw *mygame, int win);
/*
**function ft_close daba anteriormente un segfault
*/

/*
**cleaning memory functions
*/
void				ft_clean_arr(char *data);
void				ft_freemap(t_game_draw *mygame);
void				ft_fretable(char **fra);

#endif
