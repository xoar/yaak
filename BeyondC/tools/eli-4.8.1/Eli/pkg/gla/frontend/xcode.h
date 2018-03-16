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
	St_13:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_22;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 3;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 6:	/* Entered on: 0-9 */
	St_10:
		/*  0-9*/
		while(scanTbl[(c= *p++)+0] & 1<< 4);--p;
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 14;
			mkint(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;

case 7:	/* Entered on: { */
	St_16:
			TokenEnd=p=auxPascalComment(TokenStart, p-TokenStart);
			extcode = 15001;
			goto done;

case 8:	/* Entered on: ( */
	St_6:
		if((c= *p++) ==42) {			goto St_16;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			goto done;
			}

case 9:	/* Entered on: % */
	St_5:
		if((c= *p++) ==78) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_21;}
		else if(c ==77) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_20;}
		else if(c ==69) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_19;}
		else if(c ==37) {			goto St_18;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 10:	/* Entered on: $ */
	St_4:
		if( scanTbl[(c= *p++)+0] & 1<< 5){ /*  !-~ 161.-255. */
			goto St_17;}
		else {TokenEnd=TokenStart;--p; goto fallback; }


default: TokenEnd=p; extcode=ExtCodeTbl[c]; goto done; /*  ) + - : ? [ ] */
}
	St_17:
		/*  !-~ 161.-255.*/
		while(scanTbl[(c= *p++)+0] & 1<< 5);--p;
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 4;
			mkstr(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
	St_18:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 8;
			goto done;
	St_19:
		if((c= *p++) ==79) {			goto St_23;}
		else {--p; goto fallback; }
	St_23:
		if((c= *p++) ==70) {			goto St_26;}
		else {--p; goto fallback; }
	St_26:
		if((c= *p++) ==84) {			goto St_29;}
		else {--p; goto fallback; }
	St_29:
		if((c= *p++) ==79) {			goto St_32;}
		else {--p; goto fallback; }
	St_32:
		if((c= *p++) ==75) {			goto St_35;}
		else {--p; goto fallback; }
	St_35:
		if((c= *p++) ==69) {			goto St_38;}
		else {--p; goto fallback; }
	St_38:
		if((c= *p++) ==78) {			goto St_40;}
		else {--p; goto fallback; }
	St_40:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 2;
			goto done;
	St_20:
		if((c= *p++) ==65) {			goto St_24;}
		else {--p; goto fallback; }
	St_24:
		if((c= *p++) ==88) {			goto St_27;}
		else {--p; goto fallback; }
	St_27:
		if((c= *p++) ==67) {			goto St_30;}
		else {--p; goto fallback; }
	St_30:
		if((c= *p++) ==79) {			goto St_33;}
		else {--p; goto fallback; }
	St_33:
		if((c= *p++) ==68) {			goto St_36;}
		else {--p; goto fallback; }
	St_36:
		if((c= *p++) ==69) {			goto St_39;}
		else {--p; goto fallback; }
	St_39:
		if((c= *p++) ==83) {			goto St_41;}
		else {--p; goto fallback; }
	St_41:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 9;
			goto done;
	St_21:
		if((c= *p++) ==79) {			goto St_25;}
		else {--p; goto fallback; }
	St_25:
		if((c= *p++) ==84) {			goto St_28;}
		else {--p; goto fallback; }
	St_28:
		if((c= *p++) ==65) {			goto St_31;}
		else {--p; goto fallback; }
	St_31:
		if((c= *p++) ==66) {			goto St_34;}
		else {--p; goto fallback; }
	St_34:
		if((c= *p++) ==83) {			goto St_37;}
		else {--p; goto fallback; }
	St_37:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 10;
			goto done;
	St_22:
		/*  0-9 A-Z _ a-z*/
		while(scanTbl[(c= *p++)+0] & 1<< 3);--p;
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 3;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
