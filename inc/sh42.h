/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 16:50:15 by apetitje          #+#    #+#             */
/*   Updated: 2017/10/05 02:45:13 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH42_H
# define SH42_H

# define _GNU_SOURCE
# include "ft_printf.h"
# include "sh_glob.h"
# include "history_expansion.h"
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <signal.h>
# include <pwd.h>
# include <sys/param.h>
# include <sys/ioctl.h>

# define SIZE			4096
# define NBBUILTINS 	15

/*
** History builtin options:
*/

# define HIST_PRINTHIST		0
# define HIST_CLEAR			1
# define HIST_DELETE		2
# define HIST_APPEND		3
# define HIST_NEWLINES		4
# define HIST_READHIST		5
# define HIST_WRITEHIST		6
# define HIST_PRINTSUB		7
# define HIST_ADDARGS		8
# define HIST_ERRTYPE		9
# define HIST_HISTNB		10
# define HIST_HISTERR		11

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct termios	t_termios;
typedef struct winsize	t_winsize;
typedef struct passwd	t_passwd;

typedef enum			e_tok_type
{
	TOKEN_STR,
	TOKEN_SEMI,
	TOKEN_PIPE,
	TOKEN_REDIR_R,
	TOKEN_REDIR_L,
	TOKEN_REDIR_BOTH,
	TOKEN_DB_REDIR_R,
	TOKEN_HEREDOC,
	TOKEN_REDIR_COPY,
	TOKEN_SUBSH,
	TOKEN_BQ,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_VAR,
	TOKEN_NULL,
	TOKEN_ESPER,
	TOKEN_VAR_EXP,
	TOKEN_EXPANDED,
	TOKEN_VOID,
	TOKEN_EOF
}						t_tok_type;

typedef enum			e_redir_type
{
	REDIR_TO,
	REDIR_TO_DUO,
	REDIR_APPEND_DUO,
	REDIR_FROM,
	REDIR_BOTH,
	REDIR_FROM_FD,
	REDIR_APPEND_FD,
	REDIR_TO_FD,
	REDIR_BOTH_FD,
	REDIR_CLOSE,
	REDIR_APPEND,
	REDIR_HEREDOC
}						t_redir_type;

typedef enum			e_ast_type
{
	AST_TOKEN,
	AST_COMMAND,
	AST_SUBSH
}						t_ast_type;

typedef struct			s_path
{
	int					is_primary;
	char				**path;
}						t_path;

typedef struct			s_pipe_lists
{
	t_list				*fd_list;
	t_list				*pid_list;
}						t_pipe_lists;

typedef struct			s_redir
{
	int					redirs[3];
	char				*word;
}						t_redir;

typedef struct			s_token
{
	char				*word;
	size_t				size;
	t_tok_type			type;
}						t_token;

typedef struct			s_command
{
	size_t				tok_size;
	int					argc;
	int					is_bg;
	t_token				*tokens;
	char				**argv;
	char				**locales;
	char				*heredoc;
	t_list				*redirs;
}						t_command;

typedef struct			s_subsh
{
	int					beg_com;
	int					end_com;
}						t_subsh;

typedef struct			s_ast
{
	struct s_ast		*left;
	struct s_ast		*right;
	t_ast_type			type;
	void				*item;
}						t_ast;

typedef struct			s_buff
{
	int					len;
	int					stocked;
	char				data1[SIZE];
	char				*data;
}						t_buff;

typedef struct			s_hist
{
	char				*content;
	int					select;
}						t_hist;

typedef struct			s_pos
{
	int					x;
	int					y;
}						t_pos;

typedef struct			s_infos
{
	t_termios			old_conf;
	t_termios			term;
}						t_infos;

typedef struct			s_var
{
	char				*var;
	char				*content;
}						t_var;

typedef struct			s_i_line
{
	int					tmp_len;
	char				*tmp;
	t_pos				cursor;
	t_winsize			ws;
	t_buff				input;
}						t_i_line;

typedef struct			s_bckt
{
	int					key;
	char				*skey;
	char				*data;
	int					hits;
	struct s_bckt		*next;
}						t_bckt;

typedef struct			s_hashtable
{
	t_bckt				*table;
	int					nbbckt;
}						t_hashtable;

/*
** Note: pstat = 1-> Running 2-> Stopped 3-> Completed
*/

typedef struct			s_process
{
	struct s_process	*next;
	pid_t				cpid;
	char				pstat;
	int					stat;
	char				*cmd;
}						t_process;

/*
** Note: active = 1-> Running 2-> Stopped 3-> Terminated
*/

typedef struct			s_job
{
	struct s_job		*next;
	struct s_process	*first;
	char				*cmdline;
	char				active;
	char				subsh;
	char				current;
	pid_t				pgid;
	int					index;
	int					code;
	char				bg;
	char				ao;
	char				notified;
	char				bgnot;
	char				pipeline;
}						t_job;

typedef	struct			s_bt_args
{
	t_command			*cmd;
	t_list				*env;
}						t_bt_args;

typedef struct			s_hist_opt
{
	int					type;
	char				*value;
	char				**av;
}						t_hist_opt;

typedef struct			s_read_opt
{
	char				delim;
	int					use_readline;
	int					nb_char_active;
	int					nb_char;
	char				*prompt;
	int					ign_bslash;
	int					silent;
	int					timeout;
	int					fd_in;
	int					errcode;
}						t_read_opt;

typedef struct			s_builtins_tuple
{
	char				*name;
	int					(*func)(t_bt_args);
}						t_builtins_tuple;

/*
** Init
*/

void					init_main(void);
void					signal_init(void);
void					init_vars(void);
void					read_hist(t_list **hist);

/*
**	Setters
*/

void					set_select(t_list *ele, int val);
void					set_var(t_list *ele, char *content);
void					set_hist(t_list *ele, char *content);
void					set_content(t_list *ele, char *content);

/*
**	Getters
*/

char					*get_hist(t_list *ele);
int						get_select(t_list *ele);
char					*get_var(t_list *ele);
char					*get_content(t_list *ele);

/*
**	AST functions
*/

t_tok_type				get_tok_type(t_ast *root);
int						ast_construct(t_token *tok_tab, t_ast **root);
int						do_left(t_token *line, t_ast *root, int left_size);
t_ast					*ast_create_node(void *item, t_ast_type type);
void					free_ast(t_ast *root);
int						all_token_are_var(t_command *root);

/*
**	Expansions
*/

void					expand_glob(t_token **tok_tab, size_t *token_size);
int						expands(t_token **tok_tab, size_t *token_size);
int						expand_var(t_token *tok_tab, char *input, size_t *i,
		size_t *j);
int						expand_tilde(char *input, t_token *tok_tab, size_t *i,
		size_t *j);
void					expand_bq(t_token *tok_tab, size_t *i);
void					redir_command_bq(char *com_line, char **line);
void					word_splitting(t_token **tok_tab, size_t *token_size);
void					split_and_insert(char **to_split, t_token **tok_tab,
		size_t *token_size, size_t *j);
void					copy_tab(t_token **tabl, t_token *to_copy,
		size_t *tab_size, size_t token_size);
void					copy_end_tab(t_token **tabl, size_t tab_size,
		t_token *tok_tab);
void					quote_removal(t_token *tok_tab, size_t token_size);
void					add_to_content(char **content, size_t *c_size,
		size_t *len, const char inp);
void					remove_db_quotes(char **word, size_t *i, char **content,
		char **end);
void					remove_quotes(char **word, size_t *i, char quote);

/*
**	Command exec functions
*/

int						ast_sub_command(t_ast *root, int code);
int						ast_sub_cmd_pipe(t_ast *root, int code);
int						ast_do_pipe(t_ast *root);
int						ast_do_commands(t_ast *root);
int						background_com(t_ast *root, int code);
int						open_subshell(char **line, int code);
void					prepare_job_subsh_child(void);
void					subsh_close_and_exit(int pipe_fds[], int code);
void					free_subsh_vars(t_token **tok_tab, t_ast *root,
		char **com_line);
void					subsh_command_pipe(int pipe_fds[], char *line);
int						and_or_com(t_ast *root, int *exit);
int						open_exec(t_command *command, char **environ,
		t_path path_struc, int code);

/*
**	Token tab functions
*/

void					init_tok_tab(t_token **tok_tab, size_t size);
void					extend_tok_tab(t_token **tok_tab, size_t *old_size,
		size_t new_size);
void					free_tok_tab(t_token **tok_tab);
void					free_tok_tab_content(t_token *tok_tab);

/*
**	Lexing functions
*/

int						redirect(char *input, size_t *i, size_t *j,
		t_token *tok_tab);
char					*wait_for_character(size_t *i, char character,
		size_t *j, t_token *tok_tab);
char					*wait_for_bracket(size_t *i, size_t *j,
		t_token *tok_tab, int *brackets);
int						is_bracket(char *input, size_t i);
int						process_input(char **input, size_t *i, size_t *j,
		t_token *tok_tab);
int						check_grammar(t_token *tok_tab);
int						add_to_token(char *input, size_t *i, size_t *j,
		t_token *tok_tab);
int						parse_line(char **input, t_token **tok_tab,
		size_t *token_size);
int						b_quote(char **input, size_t *i, size_t *j,
		t_token *tok_tab);
int						check_quotes(char **input, size_t *i, size_t *j,
		t_token *tok_tab);
int						check_parenthesis(char **input, size_t *i, size_t *j,
		t_token *tok_tab);
int						split_tokens(char *input, size_t *i, size_t *j,
		t_token *tok_tab);
int						echap(char **input, size_t *i, size_t *j,
		t_token *tok_tab);
int						token_and(char *input, size_t *i, size_t *j,
		t_token *tok_tab);
int						token_or(char *input, size_t *i, size_t *j,
		t_token *tok_tab);
int						token_esper(char *input, size_t *i, size_t *j,
		t_token *tok_tab);

/*
**	Curs and print functions
*/

void					print_and_progress_curs(char *out, t_i_line *i_line);
void					print_and_restore_curs(char *out, t_i_line *i_line);
void					curs_erase_command(t_i_line *i_line);

/*
**	Cursor motion functions
*/

void					curs_end_command(t_i_line *i_line);
void					curs_beg_command(t_i_line *i_line);
void					curs_end_line_one_up(t_i_line *i_line);

/*
**	Input functions
*/

char					*read_line(t_list **hist);
void					input_printable(t_i_line *i_line, char buff[]);
char					*send_input(t_list **hist, t_i_line *i_line);
char					*send_eof(t_i_line *i_line);

/*
**	Input buffer functions
*/

void					del_tmp(t_i_line *i_line);
void					ft_fill_buff(t_buff *buff, const char *src, int len);
void					ft_free_buff(t_buff *buff);
void					ft_free_i_line(t_i_line *i_line);
void					ft_init_i_line(t_i_line *i_line);

/*
**	Input capabilities functions
*/

void					completion(t_i_line *i_line);
void					complete_first(t_list **mtch, char *to_find,
		size_t find_len, char **before);
void					comp_dir(t_list **mtch, char *to_find, size_t find_len,
		char **before);
void					complete_second(char *input, char **before,
		t_list **matches);
void					expand_home_in_comp(char **to_find);
void					cmpl_cols(t_i_line *il, t_list *matches);
void					comp_var(t_list **mtch, char *to_find, size_t find_len,
		int code);
int						ft_termcap(char buff[], t_i_line *i_line,
		t_list **hist);

/*
**	Word motion
*/

void					word_motion(t_i_line *i_line, char com);
void					line_motion(t_i_line *i_line, char arrow);

/*
**	Line edit functions
*/

void					delete_backward(t_i_line *i_line);
void					delete_forward(t_i_line *i_line);
void					arrow_func(char com, t_i_line *i_line);
void					home_func(t_i_line *i_line);
void					end_func(t_i_line *i_line);

/*
**	Line copy functions
*/

void					copy_before(t_i_line *i_line);
void					copy_after(t_i_line *i_line);
void					paste_clipboard(t_i_line *i_line);

/*
**	List functions
*/

int						count_list_ele(t_list *list);
void					free_list(t_list **list);

/*
**	History functions
*/

int						open_hist(int flags1, int flags2);
void					hist_func(char buff[], t_i_line *i_line, t_list **hist);
void					unselect_hist(t_list **hist);
void					stock_hist(t_i_line *i_line, t_list **hist);
void					free_hist(t_list **hist);
void					history_search(t_i_line *i_line, char buff[]);
void					erase_line(t_i_line *i_line);
void					find_matches(char *word, t_list **matches);
void					fill_search(char *word, t_i_line *i_line,
		t_list **matches);
void					print_search_result(t_i_line *i_line, char *word);

/*
**	Env and locale list functions
*/

t_list					*env_list(char **environ);
t_list					*copy_env(t_list *env);
void					free_env(t_list **env);
char					**build_env(t_list *env);
void					add_to_env(const char *var, char *content,
		t_list **env);
int						add_local_var(t_command *cmd);
char					*return_local_content(char *name, t_list *env2);
int						unset_var(t_list **tmp);
int						del_multi_var(char **var, char gflag, char flag);
void					update_last_exit_status(int stat);

/*
**	Path functions
*/

void					free_path(char ***path);
char					**build_path(t_list *env, char *path_name);

/*
**	General functions
*/

void					update_shlvl(t_list **env);
int						error_and_return(char *msg);
char					*error_in_waiting(char **sequence);
void					free_all(void);
int						term_conf(t_infos *g_infos, int code);
int						is_builtin(char *name);

/*
**	Handlers
*/

void					exit_handler(int sig);
void					handler(int sig);

/*
**	Dir functions
*/

void					change_dir(char *path, char w_dir[], int flag);
int						is_dir(const char *dir);
char					*find_dir(t_command *comm, int *is_path,
		int f[2], t_list *env);

/*
**	Command functions
*/

int						command_tree(t_token *tok_tab, int begin, t_ast **root,
		int end_com);
int						command_process(t_command *command);

/*
**	Redirections
*/

int						heredoc_build(char *input, size_t *i, size_t *j,
		t_token *tok_tab);
void					add_to_redir_list(t_token *tok_tab,
		t_list **redirs_list, int first, int type);
int						parse_redirs(t_list **redirs, t_token *tok_tab, int i);
int						do_redirect(t_command *command);
int						do_heredoc(t_command *command);
void					close_redirs(t_list *red);

/*
**	Pipe
*/

int						pipe_com(t_ast *root, int code, int *stdin_save);
int						pipe_first_run(t_ast *root, int code);

/*
** Hashtable related functions
*/

t_hashtable				*init_hashtable(void);
t_bckt					*hashtable_add(t_hashtable *ht, char *skey, char *value,
		int hit);
t_bckt					*hashtable_lookup(t_hashtable *ht, char *skey);
t_bckt					*init_bckt(char *skey, char *val, int hit);
int						compute_key(char *s);
int						hashtable_free(t_hashtable *ht);
int						hashtable_remove(t_hashtable *ht, char *skey);
int						hashtable_print_data(char **elem);
int						hashtable_removecell(char **elem);
int						hash_search(char **elem, t_list *env);
void					make_stdfd_bk(int *bk_fd);
void					display_hashusage(char c);
int						display_hashtable(short flag);
int						hashtable_notfound(char *name);
int						display_found(char **elem);
void					restore_stdfd(int *bk_fd);

/*
**	Builtins
*/

int						ft_echo(t_bt_args ar);
int						get_env(t_bt_args ar);
int						set_env(t_bt_args ar);
int						unset_env(t_bt_args ar);
int						builtin_history(t_bt_args ar);
int						exit_func(t_bt_args ar);
int						ft_hash(t_bt_args ar);
int						ft_jobs(t_bt_args ar);
int						fg_jobs(t_bt_args ar);
int						bg_jobs(t_bt_args ar);
int						bt_export(t_bt_args ar);
int						unset_bt(t_bt_args ar);
int						bt_nanoset(t_bt_args ar);
int						bt_read(t_bt_args ar);
int						ft_cd(t_bt_args ar);
int						return_exit_status(int stat, int code, pid_t pid);
int						is_exec(const char *ex);
char					*cd_home_old(int which, int *is_path, int *stat,
		t_list *env2);
void					parse_dot(char **dir, int *i, int *j);
int						parse_dot_dot(char **dir, int *i, int *j);
int						convert_dir(char **dir);
void					exit_prog(int code, char *err);
char					*find_in_path(t_command *command, int *is_path,
		t_list *env2);
char					*search_var_in_env(t_list *env, char *var);
int						do_command(t_command *command, int code);
char					*exists_in_directory(char *dir_path, char *name);
void					new_argv(t_command *command, int j);
int						parse_opt_export(t_command *cmd, t_list *env);
int						export_variable(t_command *args, t_list *env2, int j);
int						export_all(t_list *env);
int						jobs_usage(char c);
void					adjust_list(t_list **ev, char flag, char gflag);
int						find_env_flags(t_command *command, int *j, int *empty);
void					find_locales(t_command *command, int *j, t_list **env2,
		t_path *path_struc);
int						print_env(t_list *env);
char					*find_ex(char *exec, t_path path_struc);
int						build_ex(t_command *command, char **ex,
		t_path path_struc, int *is_path);
int						is_error(int ret, t_command *command, int is_path,
		char *ex);
void					update_current_bt(t_job *j, int current_id);
void					resume_default(char g, t_job *tmp);
void					loop_for_current(int current_id);
int						check_valid_identifier(char *id);

/*
** Job control related
*/

void					ignore_jobsignal(void);
void					setdfl_jobsignal(void);
int						is_completed(t_job *task);
int						is_stopped(t_job *task);
int						is_last_proc(t_job *task, pid_t pid);
void					process_add_to_job(t_job *j, pid_t pid,
		t_command *args, char *cmd);
void					update_process_stat(t_job *task, char stopped,
		pid_t pid);
t_job					*job_add(t_job **j, char *input);
int						resume_if_shellpgid(t_job *j);
int						display_exit_jobs(void);
int						subshell_arithmetic(t_ast *root, char drct, char *line);
void					init_subsh_jobs(void);
void					set_foreground_job(void);
void					del_job(t_job *j);
void					update_jobs_stat(void);
void					wait_nonblock(void);
void					update_current(void);
void					check_pipe_ret(void);
void					resume_pid_fg(t_job *task);
void					resume_pid_bg(t_job *task);
void					create_inline_job(t_command *args);
char					*recompute_cmd(t_command *args);
void					compute_pipeline_cmd(t_command *cmd, int code);
void					wait_last(int *stat);
void					create_pipe_jobs(void);
void					if_stopped(pid_t pid);
int						if_signaled(int stat, pid_t pid);

/*
** Builtin history
*/

int						print_history(void);
void					erase_last(t_list **hist);
void					add_hist(t_list **hist, char *line, int count);
int						clear_history(void);
int						history_delete(t_hist_opt *opt);
int						history_add_args(t_hist_opt *opt);
int						get_hist_count(t_list *hist);
int						print_expected(void);
int						history_usage(void);
int						history_read(t_hist_opt *opt);
int						write_history(t_hist_opt *opt);

/*
** Builtin read
*/

char					*restore_and_return(t_i_line *i_line, int i);
char					*end_input(t_list **hist, t_i_line *i_line, int i,
		int ret);
char					*receive_input(t_i_line *i_line, t_list **hist);
void					ins_l(t_i_line *il);
char					*readline(const char *prompt);
char					*readline2(t_read_opt *opt);
int						set_variable(char *name, char *value);
int						set_read_opt(char **argv[], int *argc, t_read_opt *opt);
char					**parse_variables(char *str, int ac);
int						term_conf_read(t_infos *infos, int code, int fd_in);
void					input_printable_read(t_i_line *i_line, char buff[],
		t_read_opt *opt);
void					set_alrm(void);
unsigned int			ft_alarm(unsigned int seconds);
void					read_usage(void);
int						check_ifglob(char *line, char *op_ptr);
int						is_opt_c(char *s, char c);
int						get_nb(char *s);
char					*ft_stradd(char *s1, char *s2);
void					read_set_signals(t_read_opt *opt);
char					*get_input(t_read_opt *opt);

#endif
