NAME			=	ircserv

CXX			=	c++
CXXFLAGS		=	-Wall -Wextra -Werror -std=c++98

SRC_DIR			=	src/
SRCS			=	${wildcard ${SRC_DIR}*.cpp}
#SRCS			=	${wildcard *.cpp}

OBJ_DIR			=	obj/
OBJS			=	$(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.o,$(SRCS))

INCLUDE			=	-I./includes

RM			=	rm -rf
MKDIR			=	mkdir -p

all		:	${NAME}

${NAME}: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS}

${OBJ_DIR}%.o : ${SRC_DIR}%.cpp
	${MKDIR} ${OBJ_DIR}
	${CXX} ${CXXFLAGS} ${INCLUDE} -o $@ -c $<

clean	:
	${RM} ${OBJ_DIR}

fclean	:	clean
	${RM} ${NAME} ${OBJ_DIR}

re		:	fclean all

test	:
	cd test && cmake -S . -B build && cmake --build build
	cd test/build && ctest

.PHONY: all clean fclean re test
