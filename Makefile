NAME			=	ircserv

CXX				=	c++
CXXFLAGS		=	-Wall -Wextra -Werror -std=c++98

SRC_DIR			=	src/
SRCS			=	${wildcard ${SRC_DIR}*.cpp}

OBJ_DIR			=	obj/
OBJS			=	${addprefix ${OBJ_DIR}, ${SRCS:.cpp=.o}}

#vpath %.cpp ${SRC_DIR}
#vpath %.o ${OBJ_DIR}

INCLUDE			=	-I./includes

RM				=	rm -rf	
MKDIR			=	mkdir -p

all		:	${NAME}

${NAME}: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS}

${OBJ_DIR}%.o : %.cpp
	${MKDIR} ${OBJ_DIR}
	${CXX} ${CXXFLAGS} ${INCLUDE} -o $@ -c $<

clean	:
	${RM} ${OBJ_DIR}

fclean	:	clean
	${RM} ${NAME} ${OBJ_DIR}

re		:	fclean all

.PHONY: all clean fclean re
