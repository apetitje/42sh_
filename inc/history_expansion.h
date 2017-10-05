/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansion.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 10:30:29 by oyagci            #+#    #+#             */
/*   Updated: 2017/09/27 20:35:18 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_EXPANSION_H
# define HISTORY_EXPANSION_H

/*
** Event Designator
*/

enum				e_event_designator
{
	ED_PREVIOUS,
	ED_KEYWORD,
	ED_STRING,
	ED_LINE
};

typedef struct		s_event_designator
{
	enum e_event_designator		type;
	char						*data;
}					t_event_designator;

/*
** Arg Designator
*/

enum				e_arg_designator
{
	AD_NUMBER,
	AD_LAST,
	AD_FIRST
};

typedef struct		s_arg_designator
{
	enum e_arg_designator	type;
	int						number;
}					t_arg_designator;

/*
** Range
*/

enum				e_range_designator
{
	R_RANGE,
	R_X_RANGE
};

typedef struct		s_range_designator
{
	enum e_range_designator	type;
	t_arg_designator		*left;
	t_arg_designator		*right;
}					t_range_designator;

enum				e_word_designator
{
	WD_RANGE,
	WD_LAST_MATCHED
};

typedef struct		s_word_designator
{
	enum e_word_designator	type;
	t_range_designator		*range;
}					t_word_designator;

/*
** Modifier
*/

enum				e_modifier
{
	MOD_NONE = 0,
	MOD_GLOBAL = 1,
	MOD_REMOVE_TRAILING_PATHNAME_COMPONENT = 2,
	MOD_REMOVE_ALL_LEADING_PATHNAME_COMPONENT = 4,
	MOD_REMOVE_SUFFIX = 8,
	MOD_REMOVE_ALL_BUT_TRAILING_SUFFIX = 16,
	MOD_PRINT = 32,
	MOD_QUOTE_WORDS = 64,
	MOD_SPLIT_AND_QUOTE = 128,
	MOD_UNKNOWN = 256,
	MOD_SUBSTITUTE = 512,
	MOD_REPEAT = 1024
};

typedef struct		s_sub
{
	char	*left;
	char	*right;
}					t_sub;

typedef struct		s_modifier
{
	enum e_modifier	type;
	t_sub			*sub;
}					t_modifier;

typedef struct		s_expansion
{
	int						start_index;
	int						end_index;
	t_event_designator		*event_designator;
	t_word_designator		*word_designator;
	t_list					*modifiers;
	char					*event;
}					t_expansion;

typedef struct		s_hist_tok
{
	int					start;
	int					end;
	t_event_designator	*ed;
	t_word_designator	*wd;
}					t_hist_tok;

char				*history_expansion(char *line);
t_event_designator	*event_designator(char *input, int *index);
t_word_designator	*word_designator(char *input, int *index);
t_arg_designator	*arg_designator(char *input, int *index);
t_range_designator	*range_designator(char *input, int *index);
t_word_designator	*word_designator(char *input, int *index);
t_list				*modifier(char *input, int *index);
t_sub				*substitute(char *input, int *index);

void				free_event_designator(t_event_designator *event);
void				free_word_designator(t_word_designator *wd);
void				free_range_designator(t_range_designator *event);
void				free_arg_designator(t_arg_designator *arg);
void				free_modifiers(t_list *modifiers);
void				free_substitute(t_sub *sub);

char				*get_event(t_event_designator *e, char *line,
		int start_index);
int					apply_expansion(t_expansion *e, char **line);
int					apply_word(t_word_designator *e, char **event);
int					apply_modifiers(t_list *modifiers, char **event);
int					apply_range(t_range_designator *r, char **event);
int					apply_range_x(t_range_designator *r, char **event);
int					get_index(t_arg_designator *arg, char **words);
int					set_range(int low, int high, char **event, char **words);
int					nb_words(char **words);
char				*get_typed_line(char *line, int start_index);
int					apply_substitute(t_sub *sub, char **event, int global);

void				rm_all_but_trailing_suffix(char **event);
void				rm_suffix(char **event);
void				rm_all_leading_pathname_component(char **event);
void				rm_trailing_pathname_component(char **event);
void				repeat_sub(char **event, int global);

void				quote_split(char **event);
void				quote_current_word(char **str, int *i);
void				quote_words(char **event);

char				*get_prev_line(void);
int					quick_sub(char *line, int *index);

void				escape_single_quotes(char **str);
int					is_number(char *s);
char				*get_command_by_index(int index);

#endif
