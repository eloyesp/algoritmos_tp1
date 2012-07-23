#include "utils.h"

char * read_line (char * buf, size_t length) {
	/**** Copyright de home.datacomm.ch/t_wolf/tw/c/getting_input.html#skip
	Read at most 'length'-1 characters from the file 'f' into
	'buf' and zero-terminate this character sequence. If the
	line contains more characters, discard the rest.
	*/
	
	char *p;
	
	if ((p = fgets (buf, length, stdin))) {
		size_t last = strlen (buf) - 1;
		
		if (buf[last] == '\n') {
			/**** Discard the trailing newline */
			buf[last] = '\0';
		} else {
			/**** There's no newline in the buffer, therefore there must be
			more characters on that line: discard them!
			*/
			fscanf (stdin, "%*[^\n]");
			/**** And also discard the newline... */
			(void) fgetc (stdin);
		} /* end if */
	} /* end if */
	return p;
} /* end read_line */

int de_tres_letras(const int i, const int j, const char sentido) {
	/** Verdadero si la cantidad de letras que tiene la palabra correspondiente
		Es 3.
	*/
	int es_tres;
	if (j != 0) {
		es_tres = 0;
	} else {
		if ((sentido == 'H' && (i % 2) == 0) || (sentido == 'V' && (i % 2) == 1))
			es_tres = 0;
		else
			es_tres = 1;
	}
	return es_tres;
}
