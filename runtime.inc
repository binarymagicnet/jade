DECLARE FUNCTION CSTRING LTRIM$ (CSTRING);
DECLARE FUNCTION CSTRING RTRIM$ (CSTRING);
DECLARE FUNCTION CSTRING TRIM$  (CSTRING);
DECLARE FUNCTION CSTRING LEFT$  (CSTRING, INT);
DECLARE FUNCTION CSTRING MID$   (CSTRING, INT, INT);
DECLARE FUNCTION CSTRING RIGHT$ (CSTRING, INT);
DECLARE FUNCTION INT INSTR (CSTRING,CSTRING,size_t=0);
DECLARE FUNCTION CSTRING LCASE$ (CSTRING);
DECLARE FUNCTION CSTRING UCASE$ (CSTRING);
DECLARE FUNCTION CSTRING MCASE$ (CSTRING);
DECLARE FUNCTION CSTRING LOADFILE$ (CSTRING);
DECLARE FUNCTION CSTRING SPLITPATH$ (CSTRING, INT);
DECLARE FUNCTION CSTRING ENC$ (CSTRING,INT=34,INT=34);
DECLARE FUNCTION CSTRING REVERSE$ (CSTRING);
DECLARE FUNCTION CSTRING REPLACE$ (CSTRING subject, CONSTANT CSTRING& search, CONSTANT CSTRING& replace);
DECLARE FUNCTION INT VAL (CSTRING);
DECLARE FUNCTION CSTRING FORMAT$ (CONSTANT CSTRING &fmt, ...);
DECLARE FUNCTION VECTOR<CSTRING> SPLIT (CONSTANT CSTRING input, CONSTANT CSTRING separators, BOOL remove_empty = TRUE);
DECLARE SUB PRINT (CSTRING);
DECLARE SUB SAVEFILE(CSTRING src, CSTRING fname);

FUNCTION VECTOR<CSTRING> SPLIT (CONSTANT CSTRING input, CONSTANT CSTRING separators, BOOL remove_empty) BEGIN
	  DIM VECTOR<CSTRING> lst;
    DIM std::ostringstream word;

    FOR (UINT n = 0 TO n < input.size() STEP n++) BEGIN
        IF (CSTRING::npos == separators.find(input[n])) THEN
            word << input[n];
        ELSE
            IF (NOT word.str().empty() OR NOT remove_empty) lst.push_back(word.str());
            word.str("");
        ENDIF
    END
    IF (NOT word.str().empty() OR NOT remove_empty) lst.push_back(word.str());

	RETURN lst;
ENDFUNCTION

FUNCTION CSTRING FORMAT$ (CONSTANT CSTRING &fmt, ...) BEGIN
    DIM AS VECTOR<char> str(100,'\0');
    DIM AS va_list ap;
    DIM AS INT n;

    WHILE (TRUE) {
        va_start(ap, fmt);
        n = vsnprintf(str.data(), str.size(), fmt.c_str(), ap);
        va_end(ap);
        IF ((n > -1) AND (size_t(n) < str.size())) THEN
            RETURN str.data();
        ENDIF
        IF (n > -1) THEN
            str.resize( n + 1 );
        ELSE
            str.resize( str.size() * 2);
        ENDIF
    WEND

    RETURN str.data();
ENDFUNCTION

FUNCTION CSTRING REVERSE$ (CSTRING src) BEGIN
    RETURN CSTRING( src.rbegin(),src.rend() );
ENDFUNCTION

SUB PRINT (CSTRING A="") BEGIN
  IF (A.empty()) THEN
      std::cout << std::endl;
  ELSE
    std::cout << A << std::endl;
  ENDIF
ENDSUB

FUNCTION CSTRING LTRIM$ (CSTRING s) BEGIN
  s.erase(s.begin(),std::find_if(s.begin(),s.end(),std::not1(std::ptr_fun<INT,INT>(std::isspace))));
  RETURN s;
ENDFUNCTION


FUNCTION CSTRING RTRIM$ (CSTRING s) BEGIN
  s.erase(std::find_if(s.rbegin(),s.rend(),std::not1(std::ptr_fun<INT,INT>(std::isspace))).base(),s.end());
  RETURN s;
ENDFUNCTION


FUNCTION CSTRING TRIM$ (CSTRING s) BEGIN
  RETURN LTRIM$ (RTRIM$ (s));
ENDFUNCTION


FUNCTION CSTRING LEFT$ (CSTRING s, INT length) BEGIN
  RETURN s.substr(0,length);
ENDFUNCTION


FUNCTION CSTRING MID$ (CSTRING s, INT start, INT length) BEGIN
  RETURN s.substr(start,length);
ENDFUNCTION


FUNCTION CSTRING RIGHT$ (CSTRING s, INT length) BEGIN
  RETURN s.substr(s.size()-length);
ENDFUNCTION


FUNCTION INT INSTR (CSTRING  s,CSTRING  match, size_t offset) BEGIN
  IF (s.empty() OR match.empty() OR offset>s.length()) THEN
      RETURN 0;
  ENDIF
  RETURN s.find(match,offset);
ENDFUNCTION


FUNCTION CSTRING LCASE$ (CSTRING str) BEGIN
  DIM AS CSTRING  name(str);
  std::transform(name.begin(),name.end(),name.begin(),::tolower);
  RETURN name;
ENDFUNCTION


FUNCTION CSTRING UCASE$ (CSTRING str) BEGIN
  DIM AS CSTRING  name(str);
  std::transform(name.begin(),name.end(),name.begin(),::toupper);
  RETURN name;
ENDFUNCTION


FUNCTION CSTRING MCASE$ (CSTRING S) BEGIN
  DIM AS CSTRING tmpStr(S);
  DIM AS bool capFlag = FALSE;
  DIM AS register size_t i;


  std::transform(tmpStr.begin(),tmpStr.end(),tmpStr.begin(),::tolower);

  FOR (i=0 TO i<=tmpStr.length() STEP i++) BEGIN
      IF (std::ispunct(tmpStr[i]) OR std::isspace(tmpStr[i])) THEN
          capFlag=FALSE;
      ENDIF

      IF (capFlag==FALSE AND std::isalpha(tmpStr[i])) THEN
          tmpStr[i]=std::toupper(tmpStr[i]);
          capFlag=TRUE;
      ENDIF
  END
  RETURN tmpStr;
ENDFUNCTION


FUNCTION CSTRING LOADFILE$ (CSTRING N) BEGIN
  DIM AS CSTRING line, tmpStr;
  DIM AS std::ifstream  myFile(N.c_str());

  IF( NOT myFile.good()) BEGIN
      PRINT("Error opening file");
      RETURN "ERROR";
  ENDIF

  WHILE ( NOT myFile.eof()) BEGIN
      getline(myFile,line);
      line+=LF;
      tmpStr+=line;
  WEND

  myFile.close();

  RETURN tmpStr;

ENDFUNCTION

SUB SAVEFILE (CSTRING src, CSTRING fname) BEGIN
  DIM AS std::ofstream outfile;

  outfile.open(fname.c_str());
  outfile << src;
  outfile.close();

ENDSUB

FUNCTION CSTRING SPLITPATH$ (CSTRING FPATH, INT mask) BEGIN
  DIM AS CSTRING  fullPath(FPATH);
  DIM AS CSTRING  path, filename, extension;
  DIM AS CSTRING::size_type  lastSlashPos, extPos;

  lastSlashPos=fullPath.find_last_of("/");
  extPos=fullPath.find_last_of(".");
  IF (lastSlashPos==CSTRING::npos) THEN
      path.empty();
      filename=fullPath;
  ELSE
      path=fullPath.substr(0,lastSlashPos);
      filename=fullPath.substr(lastSlashPos+1,(extPos-lastSlashPos)-1);
  ENDIF

  IF (extPos==CSTRING::npos) THEN
      extension.empty();
  ELSE
      extension=fullPath.substr(extPos+1,fullPath.size()-extPos-1);
  ENDIF

  SELECT (mask) BEGIN
    CASE 4:
      RETURN path;
    ENDCASE

    CASE 8:
      RETURN filename;
    ENDCASE

    CASE 12:
      RETURN path.append("/").append(filename);
    ENDCASE

    CASE 16:
      RETURN extension;
    ENDCASE

    CASE_ELSE:
      RETURN "";

  ENDSELECT

ENDFUNCTION


FUNCTION CSTRING ENC$ (CSTRING  A, INT L, INT R) BEGIN
  DIM AS std::stringstream  buf;
  buf<<(char)L<<A<<(char)R;
  RETURN buf.str();
ENDFUNCTION

FUNCTION CSTRING REPLACE$ (CSTRING subject, CONSTANT CSTRING& search, CONSTANT CSTRING& replace) BEGIN
	DIM AS size_t pos = 0;


    WHILE( ( pos = subject.find(search, pos) ) != CSTRING::npos) BEGIN
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    END
    RETURN subject;
ENDFUNCTION

FUNCTION INT VAL (CSTRING str) BEGIN
    RETURN atoi(str.c_str());
ENDFUNCTION
