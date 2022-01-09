#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>

/* brainfuck but more succinct
 * About:
 *   Comments are between double quotes, any number repeats the next operator N times. Outputs to regular brainfuck to stdout
 * Example:
 *   input: 8+[>4+[>++>3+>3+>+4<-]>+>+>->>+[<]<-]>>.>3-.7+..3+.>>.<-.<.3+.6-.8-.>>+.>++.
 *  output: ++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.
 */

int main(int argc, const char *argv[]) {
  if (argc < 2)
    return 1; // No argument passed
  for (int x = 1; x < argc; ++x) {
    FILE *f = fopen(argv[x], "r");
    if (!f)
      return 2; // Failed to open file
    int c, n = 1;
    while (f && (c = getc(f)) != EOF) {
NEXT:
      if (isspace(c))
        continue;
      switch (c) {
      case '"':
        while (f) {
          c = getc(f);
          if (c == EOF)
            return 4; // Unexpected EOF
          if (c == '"')
            break;
        }
        break;
      case '>':
      case '<':
      case '+':
      case '-':
      case '.':
      case ',':
      case '[':
      case ']':
        if (n <= 0)
          return 6; // Number too small
        while (n--)
          putc(c, stdout);
        n = 1;
        break;
      default:;
        if (!isdigit(c))
          return 3; // Invalid character
        char buf[11];
        buf[0] = c;
        int i = 1;
        while (f) {
          c = getc(f);
          if (c == EOF)
            return 4; // Unexpected EOF
          if (!isdigit(c)) {
            buf[i + 1] = '\0';
            if ((n = atoi(buf)) > INT_MAX)
              return 5; // Number too large
            if (n <= 0)
              return 6; // Number too small
            memset(buf, 0, 11);
            goto NEXT;
          }
          if (i > 10)
            return 5; // Number too large
          buf[i++] = c;
        }
        return 4; // Unexpected EOF
      }
    }
    fclose(f);
  }
  return 0;
}