#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *read_line (char *buf, size_t length);

int main(void) {
	char string[10];
	char *other_string;
	
	other_string = "hola";
	puts(other_string);
	other_string = read_line(string, 8);
	printf("%s\n%s\nnumero: %i", string, other_string, atoi(string));
	
	return 0;
}
// robado de home.datacomm.ch/t_wolf/tw/c/getting_input.html#skip

char *read_line (char *buf, size_t length)
	/**** Read at most 'length'-1 characters from the file 'f' into
	'buf' and zero-terminate this character sequence. If the
	line contains more characters, discard the rest.
	*/
{
	char *p;
	
	if (p = fgets (buf, length, stdin)) {
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
