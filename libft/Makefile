# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clabouri <clabouri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/09 02:33:20 by clabouri          #+#    #+#              #
#    Updated: 2017/09/29 15:01:16 by clabouri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libftprintf.a

ifndef V
SIL			=	@
endif

CC			=	/usr/bin/clang
MK			=	/bin/mkdir -p
MV			=	/bin/mv
RM			=	/bin/rm -f
AC			=	/usr/bin/ar rc
RA			=	/usr/bin/ranlib

O1			=	\033[0;38;5;166m
O2			=	\033[0;2;38;5;166m
G1			=	\033[0;38;5;82m
G2			=	\033[0;2;38;5;82m
R			=	\033[0m

DINC		=	inc
INC			=	$(addsuffix /,$(addprefix -I./,$(DINC)))

DOBJ		=	.objs
DDEP		=	.deps
DSRC		=	src

NSRC		=	ft_printf/ft_free.c ft_printf/ft_wide.c ft_printf/ft_asprintf.c \
 				ft_printf/ft_pad.c ft_printf/ft_func.c ft_printf/ft_format.c \
				ft_printf/ft_modifier.c ft_printf/ft_output_func.c \
				ft_printf/ft_flags.c ft_printf/ft_alpha.c ft_printf/ft_num.c \
				ft_printf/ft_printf.c ft_printf/ft_dprintf.c \
				ft_wide_strlen.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
				ft_itoa_base.c ft_isdigit.c ft_isprint.c ft_memalloc.c ft_memdel.c \
				ft_strrev.c ft_putchar.c ft_putstr.c ft_strcat.c ft_strcmp.c ft_strcpy.c \
				ft_strdel.c ft_strdup.c ft_strlcat.c ft_strlen.c ft_strncat.c \
				ft_strncmp.c ft_strncpy.c ft_strnew.c ft_tolower.c \
				ft_toupper.c ft_atoi.c ft_putnbr.c ft_putendl.c ft_itoa.c \
				ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
				ft_memchr.c ft_memcmp.c ft_strchr.c ft_strrchr.c ft_strstr.c \
				ft_strnstr.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c \
				ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c \
				ft_strtrim.c ft_strsplit.c ft_putchar_fd.c ft_putstr_fd.c \
				ft_putendl_fd.c ft_putnbr_fd.c ft_lstmap.c ft_lstiter.c \
				ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_sqrt.c ft_realloc.c \
				ft_strndup.c ft_dtoa.c ft_pow.c ft_strjoinf.c ft_lstaddback.c \
				ft_lstjoin.c ft_strnum.c ft_sort_wordtab.c \
				ft_revsort_wordtab.c ft_list_at.c ft_list_index.c ft_lstnew.c \
				ft_ilen.c ft_strrcmp.c get_next_line.c \
				ft_lstaddbackcirc.c ft_list_index_circ.c ft_lstaddcirc.c \
				ft_lstappend.c ft_tabfree.c ft_tablen.c ft_lstfree_elem.c \
				ft_lstfree.c ft_lstsort.c ft_lstswap.c ft_itoac.c \
				ft_isspace.c ft_line_len.c

NOBJ		=	$(NSRC:.c=.o)
NDEP		= 	$(NSRC:.c=.d)

SRC			=	$(addprefix $(DSRC)/,$(NSRC))
OBJ			=	$(addprefix $(DOBJ)/,$(NOBJ))
DEP			=	$(addprefix $(DDEP)/,$(NDEP))

CFLAGS		=	-Wall -Wextra -Werror
DEPFLGS		=	-MMD -MP -MF $(DDEP)/$*.Td
COMP		=	$(CC) $(CFLAGS) $(INC)
PCOMP		=	$(MV) $(DDEP)/$*.Td $(DDEP)/$*.d && touch $@

DDOBJ		=	$(sort $(dir $(OBJ)))
DDDEP		=	$(sort $(DDEP) $(dir $(DEP)))

all: $(NAME)

$(NAME): $(DOBJ) $(DDEP) $(OBJ)
	$(SIL)$(AC) $@ $(OBJ)
	$(SIL)$(RA) $@

$(DDEP):
	$(SIL)$(MK) $(DDDEP)

$(DOBJ):
	$(SIL)$(MK) $(DDOBJ)

$(DOBJ)/%.o: $(DSRC)/%.c
$(DOBJ)/%.o: $(DSRC)/%.c $(DDEP)/%.d
	$(SIL)$(COMP) $(DEPFLGS) -o $@ -c $<
	$(SIL)$(PCOMP)

$(DDEP)/%.d:	;
-include $(DEP)

clean:
	$(SIL)$(RM) -r $(DOBJ) $(DDEP)

fclean: clean
	$(SIL)$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
.PRECIOUS: $(DOBJ)/%.d
