#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <setjmp.h>
#include <time.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifndef _WIN32
	#include <sys/wait.h>
	#include <dlfcn.h>
#endif
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>

/* DEFINES */
#define MAIN int main (int argc, char** argv) {
#define ENDMAIN }
#define DECLARE
#define FUNCTION
#define ENDFUNCTION }
#define DIM
#define AS
#define DEF
#define SUB void
#define ENDSUB }
#define BEGIN {
#define END }
#define AND &&
#define OR ||
#define CLASS class
#define TYPE typedef struct
#define ADDR &
#define INCR ++
#define DECR --
#define BYREF *
#define PTR *
#define NOT not
#define IF if
#define THEN {
#define ELSE } else {
#define ENDIF }
#define FOR for
#define TO ;
#define STEP ;
#define SELECT switch
#define CASE case
#define _TO_ ...
#define ENDCASE break;
#define CASE_ELSE default
#define CLS printf("\33[2J\33[H")
#define ENDSELECT }
#define WHILE while
#define WEND }
#define RETURN return
#define CONSTANT const
// #define STR$( x ) dynamic_cast< std::ostringstream & >( ( std::ostringstream() << std::dec << x ) ).str()
#define STR$(x) std::to_string(x)
#define BOOL bool
#define INT int
#define INTEGER int
#define UINT unsigned int
#define VECTOR std::vector
#define ARRAY std::vector
#define MAP std::map
#define CHAR char
#define ENUM enum {
#define ENDENUM };
#define EXIT exit
#define BREAK break;
#define SHORT short
#define LPCHAR char*
#define CLASS class
#define ENDCLASS };
#define CONSTRUCTOR
#define ENDCONSTRUCTOR }
#define DO {
#define NEXT }
#define STRARRAY VECTOR<CSTRING>
#define LEN(x) x.size()
#define REGQUERY std::regex
#define REGMATCH std::smatch
#define PRINTNL printf("\n")
#define NL std::endl





#ifndef TRUE
  #define TRUE 1
#endif

#ifndef FALSE
  #define FALSE 0
#endif

/* TYPEDEFS */
typedef std::string CSTRING;


char    LF  [2]= {10,0};  // Line Feed


