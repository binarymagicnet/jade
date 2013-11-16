
/* CHANGE THIS PATH TO WHERE "jade.h" IS LOCATED */
#include "jade.h"

MAIN
	  DIM CSTRING sep = " ";
	  DIM CSTRING s = "This is an example that should be split!";
	  DIM VECTOR<CSTRING> ret;

	  ret = SPLIT(s, sep);

	  FOR (UINT i = 0 TO i < ret.size() STEP i++) BEGIN
		    PRINT( ret[i] );
	  END

	  RETURN 0;
ENDMAIN
