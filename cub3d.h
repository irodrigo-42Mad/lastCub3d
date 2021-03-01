/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 11:23:47 by irodrigo          #+#    #+#             */
/*   Updated: 2021/03/01 11:01:02 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUB3D_H
# define _CUB3D_H

# ifdef __linux__
# define KEY_A 97
# define KEY_W 119
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define KEY_ESC 65307
# define KEY_SHIFT 65507
# include <X11/Xlib.h>
# include "./minilibx_linux/mlx.h"
# endif


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

/*# include "key.h"*/

# ifdef __APPLE__
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_UP 126
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_ESC 53
# define KEY_SHIFT 257
# include "./mlx_ios/mlx.h"//"./mlx_ios/mlx.h"
#endif

# define BUFFER_SIZE 1
# define MAXWIDTH 1920      //ojo res maxima linux
# define MAXHEIGHT 1080     //ojo res maxima linux

/*
**window control structures
*/
typedef struct  	s_syswin
{
     void        	*mlx_ptr;
     void        	*mlx_win;
}               	t_syswin;

typedef struct		s_resol
{
	int				h;
	int				w;
}					t_resol;

/*
**Drawing point structures
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
**texture structure
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

typedef struct		s_raycast
{
	int				x;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	double 			camerax;
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

typedef struct 		s_textures
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




	//antiguo
	//unsigned int	*no;  //revisar
	//unsigned int	*so;  //revisar
	//unsigned int	*we;  //revisar
	//unsigned int	*ea;  //revisar
	//unsigned int	*s;   //revisar
	//unsigned int	f;
	//unsigned int	c;
}					t_textures;

/*
**Sprite definition and usage
*/
typedef struct		s_sprite
{
	t_resol			spr_dimens;
	t_dpoint		spr_pos;
	t_dpoint		sp_act_pos;
	t_dpoint		transform;
	t_ipoint		spr_initial;
	t_ipoint		spr_texture;
	t_ipoint		spr_trace;
	int				scrn;
}					t_sprite;

/*
**gamer control structure
*/
typedef struct 		s_gamer
{
	t_ipoint		pos;
	int				count;
	char			spr_dir;
}					t_gamer;

/*
**Keyboard control structures
*/
 typedef struct		s_key_ctrl
{	int 			a_status;
	int 			d_status;
 	int 			esc_status;
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
typedef struct      s_bmp_hdr{
	unsigned int    f_size;
	unsigned char   rsvd_1;
	unsigned char   rsvd_2;
	unsigned int    offs_bts;
	unsigned int    sz_headr;
	t_resol         dimens;
	short int       planes;
	short int       bt_count;
	unsigned int    compress;
	unsigned int    img_bt_size;
	unsigned int    ppm_x;
	unsigned int    ppm_y;
	unsigned int    clr_used;
	unsigned int    clr_importnt;
}                   t_bmp_hdr;

/*
**Principal game control structure
*/
typedef struct		s_game_draw
{
	// desde aqui todo ok
	t_resol			win;	  	//window dimensions
	int				screenshot;	//control screen captures
	t_cnt_txts		stat_txt;	//texture status
	char			*mapchar;	//temporal map threatment
	int				map_read;	//control prerequisites
	t_resol			map_dim;	//map dimensions
	int				spr_total;	//sprites count
	char			**worldmap;	//map matrix
	t_gamer			gamer;		//your position on the world

/*
**Window control variables
*/
	void        	*mlx_ptr;
    void        	*mlx_win;

	t_raycast		rc;
	t_textures		tx;
	t_sprite		*sprite;

	void			**canvas;
	char			*canvas_ptr;
	int				c_bpp;
	int				c_sline;
	int				c_endian;

	t_key_ctrl		key;			//all_status

	int				map_err;
	int				n_err;
	int				idx_pos;  		// pos
	int				segment;     	//stripe;
	int				el_count;	 	//count;
	int				aux_elcount; 	//countb;
	double			zbuffer[4000];
	int				obj;
	int				*allspr_pos;	//spriteorder;
	double			*allspr_dist;	//spritedistance;


	// lo de encima está revisado y sin leaks


	/*








	int				lineheight;
	int				drawstart;
	int				drawend;
	int				color;
	int				j;

	void			**img;
	char			*img_ptr;

	int				id;
	double			x_wall;  // wall_x
	int				x_text;  //x_texture
	int				y_text;	 //y_texture
	int				tex_pos; // aux for position y of texture
	double			tex_stp; // pasos de la textura

	int				bpp;
	int				sl;
	int				endian;
	int				alturalinea;
	double			oldplanex;
	double			olddirx;
	int				obj;

	int				n_err;


	t_color			el_color;

	int				r;
	int				g;
	int				b;*/
}					t_game_draw;

int					checkmap(t_game_draw *mygame);
void				more_texture(t_game_draw *mygame);
void				ft_verline(t_game_draw *mygame);
void				put_pxl_to_img(t_game_draw *mygame, int x, int y);
void				to_img(t_game_draw *mygame);
void				calcularobj(t_game_draw *mygame);
void				draw_sprite(t_game_draw *mygame);
void				raysprite(t_game_draw *mygame);
void				spritepos(t_game_draw *mygame, int x, int y);
int					ft_atoi_color(char *line, int *i);
int					ft_atoi_cub(char *line, int *pos);
void 				ft_freearray(char **str);
int    				error(int i);

/*
**set initial variable values
*/
void				ft_pre_var(t_game_draw *mygame);	//prerequisites variable init

/*
**definition of error printing functions
*/
int 				ft_put_error (char *err_tit, char *errmsg, int err_n);
void				ft_write_error(char *err_tit, char *errmsg);

/*
**initial checking functions
*/
int					ft_chk_read(char *fname);
int					ft_checkfilestatus(int status, char *elmt, t_game_draw *mygame);
void				ft_set_txt_path(char *path, char *elmt, t_game_draw *mygame); //NEW
int					parsename(const char *text, const char *compare);

/*
**game file parsing
*/
int					get_next_line(int fd, char **line);
int					get_info(t_game_draw *mygame, char *line);
int					read_file(int argc, char *pathname, t_game_draw *mygame);
int					ft_chk_texture(t_game_draw *mygame, char *line, char *elmt);

/*
**map parsing
*/
void				read_map(t_game_draw *mygame);
int					get_width(char *str);
int					get_height(char *str);
void				ft_changetab(t_game_draw *mygame);
void				ft_create_matrix (t_game_draw *mygame);
int					ft_get_line_width(char *mapchar, int pos);
int					ft_setmap_ch(t_game_draw *mygame, int mat_pos, int line, int pos);
int					ft_parse_map(t_game_draw *mygame);
int					ft_check_gamer(t_game_draw *mygame);
int					ft_check_close(t_game_draw *mygame);
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

/*
**screenshot functions
*/
int					write_bmp_header(int fd, int filesize, t_game_draw *mygame); //rev
int					write_bmp_data(int file, t_game_draw *mygame, int pad);

/*
**Keyboard functions
*/
int					nopulsed(int key, t_game_draw *mygame);
int					pulsed(int key, t_game_draw *mygame);
int					deal_key(t_game_draw *mygame);

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
int             	ft_getpixel(t_game_draw *map, int x, int y);
void            	ft_mlx_pixel_put(t_game_draw *mygame, int x, int y, int color);
int					ft_close(t_game_draw *mygame, int win); //segfault

/*
**cleaning memory functions
*/
void				ft_clean_arr(char *data);
void				ft_freemap(t_game_draw *mygame);
void				ft_fretable(char **fra);

#endif

/*

/*
**Color structure
*/
/*ypedef struct		s_color
{
	int				r;
	int				g;
	int				b;
	int				alpha;
}					t_color;*/
/*
**
**double		camerax;  	// camera
**int			hit;	  	// hit
**int			side;  		// side;
**t_dpoint		raydir;	  	//raydirx 		// raydiry
**t_dpoint		dir;      	// dirx    		// diry
**t_dpoint		deltadist;	//deltadistx  	// deltadisty
**t_dpoint		sidedist; 	//sidedistx		// sidedisty
**double		perpwalldist;
**t_ipoint		mygamer;
**t_textures	maptx;
**t_resol		screen;   // height  	// width
**char			p_dir;	  // dir
**int			idx_pos;  // pos
**t_dpoint		pos;	  // posx		// posy
**t_dpoint		plane;	  //planex		// planey
**t_ipoint		step;	  //stepx		// stepy
**t_resol		screen;   // height  	// width
**char			p_dir;	  // dir
**int			idx_pos;  // pos
**t_dpoint		pos;	  // posx		// posy
**t_dpoint		plane;	  //planex		// planey
**t_ipoint		step;	  //stepx		// stepy
**t_ipoint		map;	  //mapx		// mapy
**t_ipoint		fr_pos;	  //fpposx		// fpposy
**t_ipoint		mtx;	  //x			// y
**t_sprite		*sprite;
**int			*allspr_pos;	//spriteorder;
**double		*allspr_dist;	//spritedistance;
**double		my_speed;		//movespeed;
**double		my_rotspeed;	//rotspeed;
**t_key_ctrl	key;			//all_status
**int			initialdir;
**int			screenshot; //veremos a ver
**int			n;			//cambiar nombre
**char			*wlone[8];  //wallone
**char			*wdata[8];	//walldata
**int			wbpp[8]; 	//wallbpp
**int			wendian[8];
**int			wsl[8];
**int			segment;     	//stripe;
**int			el_count;	 	//count;
**int			aux_elcount; 	//countb;



	//t_resol				size;
	int				height[8];  //h[8];
	int				width[8];	//w[8];

	int				col;

**
**
**
**
**
**
**
**int				gamename(char **argv);
**int				ft_texture_check (char *name);
**void				read_file(int argc, char **file_name, t_game_draw *mygame);
**int				ft_chk_texture(t_game_draw *mygame, char *line, int *pos, unsigned int **path, int elm);
**void				stringtoarray(t_game_draw *mygame);
**int				wall_texture(t_game_draw *mygame, char *path, unsigned int **elmt, int elm);
**void				matrix(t_game_draw *mygame);
**void				openall(t_game_draw *mygame);
**void				initvar(t_game_draw *mygame);
**void				raycauxtwo(t_game_draw *mygame);
**void				auxline(t_game_draw *mygame);
**void				auxlinetwo(t_game_draw *mygame);
**void				raycauxthree(t_game_draw *mygame);// mal
**char				*ft_right(const char *mystr, int len);
**void 				prepare_line(char *line);
**void				printhp(t_game_draw *mygame);
**
**
**
**
*/
