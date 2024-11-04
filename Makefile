NAME			=	ircserv

CXX				=	c++
CXXFLAGS		=	-Wall -Wextra -Werror -std=c++98

SRC_DIR			=	src/
SRCS			=	${wildcard ${SRC_DIR}*.cpp}
#SRCS			=	${wildcard *.cpp}

OBJ_DIR			=	obj/
OBJS			=	$(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.o,$(SRCS))

INCLUDE			=	-I./includes

RM				=	rm -rf
MKDIR			=	mkdir -p

TEST_BUILD_DIR		= test/build


all		:	${NAME}

${NAME}: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS}

${OBJ_DIR}%.o : ${SRC_DIR}%.cpp
	${MKDIR} ${OBJ_DIR}
	${CXX} ${CXXFLAGS} ${INCLUDE} -o $@ -c $<

clean	:
	${RM} ${OBJ_DIR} ${TEST_BUILD_DIR}

fclean	:	clean
	${RM} ${NAME}

re		:	fclean all

test	:	re
	cmake -S . -B ${TEST_BUILD_DIR}
	cmake --build ${TEST_BUILD_DIR}
	cd test/build && ctest

.PHONY: all clean fclean re test
