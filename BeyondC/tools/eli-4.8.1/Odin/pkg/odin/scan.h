INCLUDE "inc/GMC.h"

SCANNER
  EOF		= EOFTOK
  ERR		= ERRTOK
  "Word"	= WORDTK	=> "WORD"
  "EPString"	= HOSTWD	=> "HOSTWD"
  "ObjectID"	= OBJTID	=> "OBJTID"
  '!'		= EXCLPT
  ';'		= SCOLON
  '?'		= QUESMK
  '%'		= PERCNT
  '<'		= LANGLE
  '>'		= RANGLE
  ':'		= COLON
  '('		= LPAREN
  ')'		= RPAREN
  '+'		= PLUS
  '='		= EQUALS
  '/'		= SLASH
