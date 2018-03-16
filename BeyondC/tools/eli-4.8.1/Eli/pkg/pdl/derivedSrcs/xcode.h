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

case 5:	/* Entered on:  A-S U-Z _ a-z */
	St_16:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 6:	/* Entered on: { */
	St_20:
			TokenEnd=p=Ctext(TokenStart, p-TokenStart);
			extcode = 9;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;

case 7:	/* Entered on: T */
	St_17:
		if( scanTbl[(c= *p++)+0] & 1<< 4){ /*  0-9 A-X Z _ a-z */
			goto St_25;}
		else if(c ==89) {			goto St_26;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 8:	/* Entered on: / */
	St_12:
		if((c= *p++) ==42) {			goto St_24;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 9:	/* Entered on: . */
	St_11:
		if((c= *p++) ==46) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_23;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 10:	/* Entered on: - */
	St_10:
		if((c= *p++) ==62) {			goto St_22;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 11:	/* Entered on: $ */
	St_6:
		if((c= *p++) ==76) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_21;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 12:	/* Entered on: # */
	St_5:
			TokenEnd=p=auxEOL(TokenStart, p-TokenStart);
			extcode = 15001;
			goto done;

case 13:	/* Entered on: " */
	St_4:
			TokenEnd=p=auxCString(TokenStart, p-TokenStart);
			extcode = 2;
			mkstr(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;


default: TokenEnd=p; extcode=ExtCodeTbl[c]; goto done; /*  (-) , :-; = [ ] */
}
	St_21:
		if((c= *p++) ==73) {			goto St_27;}
		else {--p; goto fallback; }
	St_27:
		if((c= *p++) ==66) {			goto St_30;}
		else {--p; goto fallback; }
	St_30:
		if((c= *p++) ==82) {			goto St_32;}
		else {--p; goto fallback; }
	St_32:
		if((c= *p++) ==65) {			goto St_33;}
		else {--p; goto fallback; }
	St_33:
		if((c= *p++) ==82) {			goto St_34;}
		else {--p; goto fallback; }
	St_34:
		if((c= *p++) ==89) {			goto St_35;}
		else {--p; goto fallback; }
	St_35:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 13;
			goto done;
	St_22:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 12;
			goto done;
	St_23:
		if((c= *p++) ==46) {			goto St_28;}
		else {--p; goto fallback; }
	St_28:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 8;
			goto done;
	St_24:
			TokenEnd=p=auxCComment(TokenStart, p-TokenStart);
			extcode = 15001;
			goto done;
	St_26:
		if( scanTbl[(c= *p++)+0] & 1<< 5){ /*  0-9 A-O Q-Z _ a-z */
			goto St_25;}
		else if(c ==80) {			goto St_29;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_29:
		if( scanTbl[(c= *p++)+0] & 1<< 6){ /*  0-9 A-D F-Z _ a-z */
			goto St_25;}
		else if(c ==69) {			goto St_31;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_31:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 14;
			goto done;
			}
	St_25:
		/*  0-9 A-Z _ a-z*/
		while(scanTbl[(c= *p++)+0] & 1<< 3);--p;
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
