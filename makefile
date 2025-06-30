NAME=text_editor
FILES=main.c
LIBS=

default:
	gcc ${FILES} -o ${NAME} ${LIBS} -Wall