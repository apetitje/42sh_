/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:03:30 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/05 15:01:32 by clabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <string.h>
# include <wchar.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

# define NORM		"\x1B[0m"
# define RED		"\x1B[31m"
# define GREEN		"\x1B[32m"
# define YELLOW		"\x1B[33m"
# define BLUE		"\x1B[34m"
# define MAGENTA	"\x1B[35m"
# define CYAN		"\x1B[36m"
# define WHITE  	"\x1B[37m"
# define MAX_FD		255

/*
** h = short int ;
** d = int;
** D = long int;
** L = long long int;
** y = unsigned short int;
** u = unsigned int;
** U = unsigned long int;
** K = unsigned long long int;
** c = char;
** s = char*;
** w = unsigned char;
** z = signed char;
** C = wchar_t;
** S = wchar_t*;
** f = double;
*/

# define BUFF_SIZE 			1000
# define BUFFSIZE			4096
# define TESTZERO(x) (((x) - 0x0101010101010101) & ~(x) & 0x8080808080808080)

typedef struct s_fd			t_fd;
struct						s_fd
{
	char					save[BUFF_SIZE + 1];
};

typedef struct				s_lst
{
	int						fd;
	char					*stock;
	struct s_lst			*next;
}							t_lst;

typedef struct				s_out
{
	int						len;
	int						stocked;
	char					out1[BUFFSIZE];
	char					*out;
}							t_out;

typedef struct				s_col
{
	char					str[20];
	int						len;
	char					*code;
	int						codelen;
}							t_col;

typedef struct				s_data
{
	int						d;
	unsigned int			u;
	unsigned long int		lu;
	unsigned long long int	llu;
	void					*p;
	long int				ld;
	wchar_t					lc;
	char					c;
	long long int			ll;
	unsigned char			uc;
	long double				f;
}							t_data;

typedef	struct				s_arg
{
	int						nul;
	char					type;
	char					format;
	struct s_data			data;
	char					modifier;
	int						pad;
	char					padchar;
	int						precision;
	int						len;
	int						padleft;
	int						hash;
	int						plus;
	int						space;
	int						wild;
	int						zero;
	int						sharp;
	int						unsign;
}							t_arg;

typedef struct				s_list
{
	size_t					data_size;
	void					*data;
	int						index;
	int						last;
	struct s_list			*next;
	struct s_list			*prev;
}							t_list;

int							ft_line_len(const char *str);
void						ft_list_index_circ(t_list *list);
void						ft_lstaddbackcirc(t_list **alst, t_list *new);
void						ft_lstaddcirc(t_list **alst, t_list *new);
int							get_next_line(const int fd, char **line);
int							ft_dprintf(int fd, const char *format, ...);
size_t						ft_ilen(int n);
t_list						*ft_lstnew(void *content,
								size_t content_size);
void						ft_list_index(t_list **list);
t_list						*ft_list_at(t_list *lst, int index);
void						ft_revsort_wordtab(char **tabl);
void						ft_sort_wordtab(char **tabl);
char						*ft_strjoinf(void *s1, void *s2,
								int to_free);
double						ft_pow(double pow, int nb);
int							ft_wide_strlen(const wchar_t *s);
char						*ft_strndup(const char *s1, size_t len);
void						*ft_realloc(void *ptr, size_t size,
								size_t old_size);
int							ft_sqrt(int nb);
void						ft_lstadd(t_list **alst, t_list *new);
void						ft_lstaddback(t_list **alst, t_list *new);
void						ft_lstjoin(t_list *l1, t_list *l2);
void						ft_itoa(long long int n, t_arg *ele, t_out *tmp);
void						ft_dtoa(double n, int prec, t_arg *ele, t_out *tmp);
void						ft_itoa_base(unsigned long int nb, t_arg *ele,
								t_out *tmp);
void						ft_lstdelone(t_list **alst,
								void (*del)(void *, size_t));
void						ft_lstdel(t_list **alst,
								void (*del)(void *, size_t));
void						ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list						*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void						ft_strclr(char *s);
void						ft_striter(char *s, void (*f)(char *));
void						ft_striteri(char *s,
								void (*f)(unsigned int, char *));
char						*ft_strmap(char const *s, char (*f)(char));
char						*ft_strmapi(char const *s,
								char (*f)(unsigned int, char));
int							ft_strequ(char const *s1, char const *s2);
int							ft_strnequ(char const *s1, char const *s2,
								size_t n);
char						*ft_strsub(char const *s, unsigned int start,
								size_t len);
char						*ft_strjoin(char const *s1, char const *s2);
char						*ft_strtrim(char const *s);
char						**ft_strsplit(char const *s, char c);
char						*ft_strstr(const char *big, const char *little);
char						*ft_strnstr(const char *big, const char *little,
								size_t len);
char						*ft_strchr(const char *s, int c);
char						*ft_strrchr(const char *s, int c);
int							ft_memcmp(const void *s1, const void *s2, size_t n);
void						*ft_memchr(const void *s, int c, size_t n);
void						*ft_memcpy(void *dst, const void *src, size_t n);
void						*ft_memccpy(void *dst, const void *src, int c,
								size_t n);
void						*ft_memmove(void *dst, const void *src, size_t len);
void						ft_bzero(void *s, size_t n);
void						*ft_memset(void *b, int c, size_t len);
void						ft_putendl(char const *s);
void						ft_putnbr(int n);
void						ft_putendl_fd(char const *s, int fd);
void						ft_putnbr_fd(int n, int fd);
void						*ft_memset(void *b, int c, size_t len);
void						ft_bzero(void *s, size_t n);
void						*ft_memcpy(void *dst, const void *src, size_t n);
void						*ft_memccpy(void *dst, const void *src, int c,
								size_t n);
void						*ft_memmove(void *dst, const void *src, size_t len);
int							ft_memcmp(const void *s1, const void *s2, size_t n);
void						*ft_memchr(const void *s, int c, size_t n);
size_t						ft_strlen(const char *s);
char						*ft_strdup(const char *s1);
char						*ft_strcpy(char *dst, const char *src);
char						*ft_strncpy(char *dst, const char *src, size_t len);
char						*ft_strcat(char *s1, const char *s2);
char						*ft_strncat(char *s1, const char *s2, size_t n);
size_t						ft_strlcat(char *dst, const char *src, size_t size);
char						*ft_strchr(const char *s, int c);
char						*ft_strrchr(const char *s, int c);
char						*ft_strstr(const char *big, const char *little);
char						*ft_strnstr(const char *big, const char *little,
								size_t len);
int							ft_strcmp(const char *s1, const char *s2);
int							ft_strrcmp(const char *s1, const char *s2);
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
int							ft_atoi(const char *str);
int							ft_isalpha(int c);
int							ft_isdigit(int c);
int							ft_isalnum(int c);
int							ft_isascii(int c);
int							ft_isprint(int c);
int							ft_toupper(int c);
int							ft_tolower(int c);
int							ft_putchar(int c);
void						ft_putstr(char const *s);
void						ft_putchar_fd(char c, int fd);
void						ft_putstr_fd(char const *s, int fd);
void						*ft_memalloc(size_t size);
void						ft_memdel(void **ap);
char						*ft_strnew(size_t size);
void						ft_strdel(char **as);
int							ft_asprintf(char **strp, const char *format, ...);
void						ft_modifier(t_arg *ele);
void						ft_pad(t_out *output, char *flag, t_arg *ele);
void						ft_flags_num(t_out *output, t_arg *ele);
int							ft_printf(const char *format, ...);
void						ft_percent(t_out *output, t_out *tmp, t_arg *ele);
void						ft_alpha(t_out *output, t_out *tmp, t_arg *ele);
void						ft_asalpha(t_out *output, t_out *tmp, t_arg *ele);
void						ft_num(t_out *output, t_out *tmp, t_arg *ele);
void						ft_wide(t_out *output, t_out *tmp, t_arg *ele);
void						ft_aswide(t_out *output, t_out *tmp, t_arg *ele);
void						ft_point(unsigned long int nb, t_out *output,
								t_out *tmp, t_arg *ele);
void						ft_fill_out(t_out *output,
								const char *format, int len);
void						ft_init_out(t_out *out);
void						ft_free_out(t_out *out);
void						ft_join_before(t_out *out, const char *s, int len);
void						ft_free_ele(t_arg **arg);
void						ft_float(t_out *output, t_out *tmp, t_arg *ele);
void						ft_nonspec(t_out *output, t_out *tmp, t_arg *ele);
t_arg						*ft_find_modif(const char **str, va_list ap);
t_arg						*ft_arg(void);
char						*ft_init_base(char type, size_t *base);
t_arg						*ft_print(t_out *out, const char **str, va_list ap);
int							ft_find_pad(t_arg *ele, int i, const char *str);
void						ft_color(t_out *out, const char **str);
void						ft_print_wide(t_out *tmp, t_arg *ele, wchar_t **ls,
								int *put);
int							ft_precision(t_arg *ele, int i, const char *str);
void						ft_wild(const char *str, int i, t_arg *ele,
								va_list ap);

void						ft_lstappend(t_list **alst, t_list *new);
int							ft_tablen(char **ltab);
void						ft_tabfree(char **ltab);
void						ft_lstfree_elem(t_list **lst);
t_list						*ft_or_lstnew(const void *content,
		const size_t content_size);
void						ft_lstfree(t_list **lst);
char						*ft_strjoinfree(char *s1, char *s2, int which);
t_list						*ft_or_lstnew(const void *content,
											const size_t content_size);
void						ft_lstsort(t_list *lst, int (*cmp)(void*, void*));
void						ft_lstswap(t_list *a, t_list *b);
int							ft_strnum(const char *s);
char						*ft_itoac(int n);
char						*ft_strrev(char *s);

int							ft_isspace(char c);

#endif
