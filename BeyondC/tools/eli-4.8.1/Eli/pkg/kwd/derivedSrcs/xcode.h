switch (CaseTbl[c = *p++]) {
case 0:	/* sentinel - probably EOB */
  if (c == '\0') {
    p = TokenStart = TokenEnd = auxNUL(TokenStart, 0);
    if (*p) extcode = NORETURN;
    else {
      p = TokenStart = TokenEnd = auxEOF(TokenStart, 0);
      if (*p) extcode = NORETURN;
      else { extcode = EOFTOKEN; EndOfText(p, 0, &extcode, v); }
    }
    goto done;
  } else {
    obstack_grow(Csm_obstk, "char '", 6);
    obstack_cchgrow(Csm_obstk, c);
    message(
      ERROR,
      (char *)obstack_copy0(Csm_obstk, "' is not a token", 16),
      0,
      &curpos);
    TokenEnd = p;
    continue;
  }
  
case 1:	/* space */
  while (scanTbl[c = *p++] & 1<<0) ;
  TokenEnd = p - 1;
  continue;
case 2:	/* tab */
  do { StartLine -= TABSIZE(p - StartLine); }
  while (scanTbl[c = *p++] & 1<<1);
  TokenEnd = p - 1;
  continue;
case 4:	/* carriage return */
  if (*p == '\n') { TokenEnd = p; continue; }
case 3:	/* newline */
  do { LineNum++; } while (scanTbl[c = *p++] & 1<<2);
  StartLine = (TokenEnd = p - 1) - 1;
  continue;

case 5:	/* Entered on:  A-Z _ a-z */
	St_9:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_14;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 6:	/* Entered on: { */
	St_12:
			TokenEnd=p=auxPascalComment(TokenStart, p-TokenStart);
			extcode = 15001;
			goto done;

case 7:	/* Entered on: ( */
	St_6:
		if((c= *p++) ==42) {			goto St_12;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			goto done;
			}

case 8:	/* Entered on: $ */
	St_5:
		if( scanTbl[(c= *p++)+0] & 1<< 4){ /*  !-~ 161.-255. */
			goto St_13;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 9:	/* Entered on: # */
	St_4:
			TokenEnd=p=auxEOL(TokenStart, p-TokenStart);
			extcode = 15001;
			goto done;


default: TokenEnd=p; extcode=ExtCodeTbl[c]; goto done; /*  ) : [ ] */
}
	St_13:
		/*  !-~ 161.-255.*/
		while(scanTbl[(c= *p++)+0] & 1<< 4);--p;
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 8;
			mkstr(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
	St_14:
		/*  0-9 A-Z _ a-z*/
		while(scanTbl[(c= *p++)+0] & 1<< 3);--p;
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
