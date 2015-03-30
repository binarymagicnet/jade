#include "jade.h"

    
FUNCTION STRARRAY merge (STRARRAY str1, STRARRAY str2) BEGIN
	DIM STRARRAY result;
	DIM AS INTEGER leftIndex=0, rightIndex=0;
	
	WHILE ( (leftIndex < LEN(str1)) AND (rightIndex < LEN(str2)) ) DO
		IF (str1[leftIndex] <= str2[rightIndex]) THEN
			result.push_back(str1[leftIndex]);
			++leftIndex;
		ELSE
			result.push_back(str2[rightIndex]);
			++rightIndex;	
		ENDIF
	WEND
	
	IF (leftIndex < LEN(str1)) THEN
		result.push_back(str1[leftIndex]);
	ENDIF
	
	IF (rightIndex < LEN(str2)) THEN
		result.push_back(str2[rightIndex]);
	ENDIF
	
	RETURN result;
ENDFUNCTION


FUNCTION STRARRAY merge_sort(STRARRAY m) DO
	DIM INTEGER middle;
	
    IF (LEN(m) <= 1) RETURN m;
 
    middle = LEN(m) / 2;

	DIM STRARRAY left(m.begin(), m.begin() + middle);
    DIM STRARRAY right(m.begin() + middle, m.end());
 
    left = merge_sort(left);
    right = merge_sort(right);
    RETURN merge(left, right);
ENDFUNCTION

MAIN
	DIM AS CSTRING Bible;
	DIM AS STRARRAY Array, Result;
	DIM AS INTEGER CNT;
	
// 	Bible = LOADFILE$("bible.txt");
// 	Array = SPLIT(Bible,"\n");
	Array = SPLIT("pear,cranberry,orange,apple,carrot,banana,grape,peaches,tangerines",",");
	Result = merge_sort(Array);
	FOR (CNT = 0 TO CNT < LEN(Result) STEP ++CNT) DO
		PRINT (Result[CNT]);
	NEXT

std::cout << Result.size() << std::endl;
ENDMAIN

