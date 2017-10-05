# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/15 19:00:52 by apetitje          #+#    #+#              #
#    Updated: 2017/10/05 03:44:14 by hanguelk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
AR = ar
ARFLAGS = rc
RM = /bin/rm -f

VPATH = ./:builtins:commands:history:input:lexer:line_edition:parser:redirections:struct_func:history_expansion:globbing:expands:completion:generics
INC = ./inc
DIRLIB = ./
DIROBJ = .obj
DIRDEP = .deps

NAME = 42sh

SRCS =		\
			subshell_sub_func.c							\
			init.c										\
			update_shlvl.c								\
			errors.c									\
			comp_dir.c									\
			comp_tilde.c								\
			comp_var.c									\
			quote_removal_sub.c							\
			background_com.c							\
			quote_removal.c								\
			expand_glob.c								\
			word_split_insertion.c						\
			expand_bq_exec.c							\
			word_splitting.c							\
			input_sub_func.c							\
			expansions.c								\
			ast_getters.c								\
			ast_exec.c									\
			command_process.c							\
			expand_bq.c									\
			and_or_com.c								\
			and_or_token.c								\
			history_search.c							\
			subshell.c									\
			history_search_sub_func.c					\
			lexer_redir.c								\
			wait_for_input.c							\
			delete_cap.c								\
			command_redir.c								\
			heredoc.c									\
			main.c										\
			lexer_parenthesis_func.c					\
			handlers.c									\
			command_func.c								\
			env_sub_func.c								\
			cd_sub_func.c								\
			setenv.c									\
			pipe_list_func.c							\
			redir_list_func.c							\
			list_func.c									\
			redirections.c								\
			getters.c									\
			setters.c									\
			lexer.c										\
			term_conf.c									\
			capabilities.c								\
			history.c									\
			history_access.c							\
			cursor_motion.c								\
			curs_and_print.c							\
			line_editing.c								\
			input.c										\
			parse.c										\
			ast_func.c									\
			builtins.c									\
			echo.c										\
			cd_builtin.c								\
			cd_path.c									\
			dir.c										\
			search_func.c								\
			env_func.c									\
			unset.c										\
			exec.c										\
			build_ex.c									\
			lexer_quote_func.c							\
			lexing_sub_func.c							\
			expand_var.c								\
			expand_tilde.c								\
			exit_func.c									\
			i_line_func.c								\
			token_tab_func.c							\
			env_list_func.c								\
			path_func.c									\
			completion.c								\
			completion_ex.c								\
			completion_files.c							\
			completion_disp.c							\
			copy_func.c									\
			word_motion.c								\
			check_grammar.c								\
			pipe.c										\
			hash.c										\
			hashtable.c									\
			hashtable_sub.c								\
			hash_func.c									\
			hash_display.c								\
			sh_brace.c									\
			sh_brace2.c									\
			sh_brcsplt.c								\
			sh_epure.c									\
			sh_glob_parser.c							\
			sh_glob.c									\
			sh_range.c									\
			sh_range2.c									\
			sh_wc_dot.c									\
			history_expansion.c							\
			event_designator.c							\
			arg_designator.c							\
			range_designator.c							\
			word_designator.c							\
			modifier.c									\
			substitute.c								\
			free_event_designator.c						\
			free_word_designator.c						\
			free_modifiers.c							\
			free_range_designator.c						\
			free_arg_designator.c						\
			free_substitute.c							\
			escape_single_quotes.c						\
			apply_expansion.c							\
			apply_word.c								\
			get_command_by_index.c						\
			apply_modifiers.c							\
			apply_range.c								\
			repeat_sub.c								\
			apply_range_x.c								\
			get_event.c									\
			get_typed_line.c							\
			quoting.c									\
			nb_words.c									\
			print_history.c								\
			clear_history.c								\
			jobs.c										\
			jobs_init.c									\
			jobs_delete.c								\
			jobs_update.c								\
			jobs_bt.c									\
			jobs_bt_sub_func.c							\
			jobs_bt_sub_current.c						\
			jobs_bt_spec.c								\
			jobs_exit.c									\
			and_or_sub.c								\
			exec_status.c								\
			pipe_jobs.c									\
			export.c									\
			locales.c									\
			export_func.c								\
			unset_bt.c									\
			apply_substitute.c							\
			modifiers_func.c							\
			check_ifglob.c								\
			builtin_history.c							\
			history_delete.c							\
			bt_read.c									\
			bt_read_readline2.c							\
			bt_read_set_variable.c						\
			bt_read_set_read_opt.c						\
			bt_read_parse_variables.c					\
			bt_read_readline2_sub.c						\
			bt_history_sub.c							\
			bt_history_add_args.c						\
			bt_read_alrm.c								\
			bt_read_usage.c								\
			quick_sub.c									\
			bt_nanoset.c								\
			bt_read_get_nb.c							\
			bt_read_sig.c								\
			bt_read_sub2.c								\

LIBS 	=	\
	   		$(DIRLIB)/libft/libftprintf.a				\

LDFLAGS = 	\
			-L $(DIRLIB)/libft							\

LDLIBS	=	\
			-lftprintf									\
			-lncurses									\
			-lreadline

INCFLAGS = 	\
		   	-I $(DIRLIB)/libft/inc						\
			-I $(INC)									\

CFLAGS = -Wall -Wextra -Werror

DEPFLAGS =	\
			-MT $@ -MMD -MP -MF $(DIRDEP)/$*.Td			\

COMPILE.c =	$(CC) $(DEPFLAGS) $(CFLAGS) $(INCFLAGS) -c

POSTCOMPILE =  mv -f $(DIRDEP)/$*.Td $(DIRDEP)/$*.d && touch $@

SRC = $(SRCS)

OBJ = $(addprefix $(DIROBJ)/, $(SRCS:.c=.o))

$(DIROBJ)	:
	@mkdir -p $(DIROBJ)

$(DIRDEP)	:
	@mkdir -p $(DIRDEP)

all : libs $(NAME)

$(NAME) : $(DIROBJ) $(DIRDEP) $(OBJ) $(LIBS)
	@$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) $(LDLIBS) $(CFLAGS)

libs		:
	@make -C $(DIRLIB)/libft

fcleanlibs	:
	@make -C $(DIRLIB)/libft fclean

clean :
	@make -C $(DIRLIB)/libft clean
	@$(RM) -r $(DIROBJ)
	@$(RM) -r $(DIRDEP)

fclean : clean fcleanlibs
	@$(RM) $(NAME)

re : fcleanlibs fclean all

$(DIROBJ)/%.o	:	%.c
$(DIROBJ)/%.o	:	%.c $(DIRDEP)/%.d
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(word 2,$^))
	@printf "%s %s\n" "$(NAME)" "compiling $<..."
	@$(COMPILE.c) $(OUTPUT_OPTION) $<
	@$(POSTCOMPILE)
	@printf "complete\n"

$(DIRDEP)/%.d	:	;
.PRECIOUS		:	$(DIRDEP)/%.d
-include $(patsubst %,$(DIRDEP)/%.d,$(basename $(SRC)))

.PHONY : all clean fclean re fcleanlibs libs
