INC_PATH := includes

### NM ###
FT_NM := ft_nm

NM_SRC_PATH := srcs/nm
NM_OBJ_PATH := .bin/nm

#NM_SRCS_NAMES :=	errors.c		\
					main.c			\

NM_SRCS_NAMES :=	errors.c		\
					main.c			\
					object_check.c	\
					print_symbol.c	\
					sort.c			\

NM_INCS :=	nm/nm.h			\

NM_SRCS := $(addprefix $(NM_SRC_PATH)/,$(NM_SRCS_NAMES))
NM_OBJS := $(addprefix $(NM_OBJ_PATH)/,$(NM_SRCS_NAMES:.c=.o))

### OTOOL ###
FT_OTOOL := ft_otool

OTOOL_SRC_PATH := srcs/otool
OTOOL_OBJ_PATH := .bin/otool

OTOOL_SRCS_NAMES :=

OTOOL_INCS :=

OTOOL_SRCS := $(addprefix $(OTOOL_SRC_PATH)/,$(OTOOL_SRCS_NAMES))
OTOOL_OBJS := $(addprefix $(OTOOL_OBJ_PATH)/,$(OTOOL_SRCS_NAMES:.c=.o))

### LIBFT ###
LIBFT_PATH := libft
LIBFT_NAME := ft
LIBFT := $(LIBFT_PATH)/lib$(LIBFT_NAME).a
LIBFT_MODULES := base

### COMMON DEFS ###
CPPFLAGS := -iquote$(INC_PATH) -isystem$(LIBFT_PATH)/includes
CFLAGS :=	-Wall -Wextra -Werror -Wmissing-prototypes -Wsign-conversion -O3
LDFLAGS :=	-L$(LIBFT_PATH) -l$(LIBFT_NAME)

### COMMANDS ##
CC := gcc
RM := rm -f
RMDIR := rmdir -p
MKDIR := mkdir -p

### RULES ###
all: $(LIBFT) $(FT_NM) #$(FT_OTOOL)

$(LIBFT):
	make -C $(LIBFT_PATH) VERBOSE=0 MODULES="$(LIBFT_MODULES)"

$(FT_NM): $(NM_OBJ_PATH) $(NM_OBJS)
	$(CC) $(NM_OBJS) -o $(FT_NM) $(LDFLAGS)

$(NM_OBJ_PATH)/%.o: $(NM_SRC_PATH)/%.c $(addprefix $(INC_PATH)/,$(NM_INCS))
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(FT_OTOOL): $(OTOOL_OBJ_PATH) $(OTOOL_OBJS)
	$(CC) $(OTOOL_OBJS) -o $(FT_OTOOL) $(LDFLAGS)

$(OTOOL_OBJ_PATH)/%.o: $(OTOOL_SRC_PATH)/%.c $(addprefix $(INC_PATH)/,$(OTOOL_INCS))
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(NM_OBJ_PATH) $(OTOOL_OBJ_PATH):
	$(MKDIR) $@

clean:
	$(RM) -r *.dSYM
	$(RM) $(NM_OBJS) 2> /dev/null || true
	$(RMDIR) $(NM_OBJ_PATH) 2> /dev/null || true
	$(RM) $(OTOOL_OBJS) 2> /dev/null || true
	$(RMDIR) $(OTOOL_OBJ_PATH) 2> /dev/null || true
	make -C $(LIBFT_PATH) clean > /dev/null

fclean: clean
	$(RM) $(FT_NM) $(FT_OTOOL) 2> /dev/null || true
	make -C $(LIBFT_PATH) fclean > /dev/null

re: fclean all

.PHONY: all clean fclean re
