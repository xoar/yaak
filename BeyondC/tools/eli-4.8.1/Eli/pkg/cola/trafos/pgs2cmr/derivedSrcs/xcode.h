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
	St_19:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_31;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 15;
			mkidnwod(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 6:	/* Entered on: 0-9 */
	St_14:
		/*  0-9*/
		while(scanTbl[(c= *p++)+0] & 1<< 4);--p;
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 6;
			mkint(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;

case 7:	/* Entered on: | */
	St_22:
		if((c= *p++) ==124) {			goto St_32;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			goto done;
			}

case 8:	/* Entered on: < */
	St_16:
		if((c= *p++) ==36) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_30;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 9:	/* Entered on: : */
	St_15:
		if((c= *p++) ==58) {		extcode = 25;/* remember fallback*/
		TokenEnd = p-1;

		scan = NULL;
		proc = NULL;
			goto St_29;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 25;
			goto done;
			}

case 10:	/* Entered on: / */
	St_13:
		if((c= *p++) ==47) {			goto St_28;}
		else if(c ==42) {			goto St_27;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 3;
			goto done;
			}

case 11:	/* Entered on: ' */
	St_7:
			TokenEnd=p=auxPascalString(TokenStart, p-TokenStart);
			extcode = 10;
			mkidnwod(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;

case 12:	/* Entered on: $ */
	St_5:
		if((c= *p++) ==83) {		extcode = 18;/* remember fallback*/
		TokenEnd = p-1;

		scan = NULL;
		proc = NULL;
			goto St_26;}
		else if(c ==71) {		extcode = 18;/* remember fallback*/
		TokenEnd = p-1;

		scan = NULL;
		proc = NULL;
			goto St_25;}
		else if(c ==67) {		extcode = 18;/* remember fallback*/
		TokenEnd = p-1;

		scan = NULL;
		proc = NULL;
			goto St_24;}
		else if(c ==66) {		extcode = 18;/* remember fallback*/
		TokenEnd = p-1;

		scan = NULL;
		proc = NULL;
			goto St_23;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 18;
			goto done;
			}

case 13:	/* Entered on: # */
	St_4:
			TokenEnd=p=auxEOL(TokenStart, p-TokenStart);
			extcode = 15001;
			goto done;


default: TokenEnd=p; extcode=ExtCodeTbl[c]; goto done; /*  & (-+ . = @ [ ] */
}
	St_23:
		if((c= *p++) ==82) {			goto St_33;}
		else {--p; goto fallback; }
	St_33:
		if((c= *p++) ==65) {			goto St_41;}
		else {--p; goto fallback; }
	St_41:
		if((c= *p++) ==67) {			goto St_48;}
		else {--p; goto fallback; }
	St_48:
		if((c= *p++) ==75) {			goto St_55;}
		else {--p; goto fallback; }
	St_55:
		if((c= *p++) ==69) {			goto St_58;}
		else {--p; goto fallback; }
	St_58:
		if((c= *p++) ==84) {			goto St_61;}
		else {--p; goto fallback; }
	St_61:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 4;
			goto done;
	St_24:
		if((c= *p++) ==79) {			goto St_34;}
		else {--p; goto fallback; }
	St_34:
		if((c= *p++) ==68) {			goto St_42;}
		else {--p; goto fallback; }
	St_42:
		if((c= *p++) ==69) {			goto St_49;}
		else {--p; goto fallback; }
	St_49:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 8;
			goto done;
	St_25:
		if((c= *p++) ==82) {			goto St_35;}
		else {--p; goto fallback; }
	St_35:
		if((c= *p++) ==65) {			goto St_43;}
		else {--p; goto fallback; }
	St_43:
		if((c= *p++) ==77) {			goto St_50;}
		else {--p; goto fallback; }
	St_50:
		if((c= *p++) ==77) {			goto St_56;}
		else {--p; goto fallback; }
	St_56:
		if((c= *p++) ==65) {			goto St_59;}
		else {--p; goto fallback; }
	St_59:
		if((c= *p++) ==82) {			goto St_62;}
		else {--p; goto fallback; }
	St_62:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 16;
			goto done;
	St_26:
		if((c= *p++) ==84) {			goto St_38;}
		else if(c ==75) {			goto St_37;}
		else if(c ==69) {			goto St_36;}
		else {--p; goto fallback; }
	St_36:
		if((c= *p++) ==80) {			goto St_44;}
		else {--p; goto fallback; }
	St_44:
		if((c= *p++) ==65) {			goto St_51;}
		else {--p; goto fallback; }
	St_51:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 23;
			goto done;
	St_37:
		if((c= *p++) ==73) {			goto St_45;}
		else {--p; goto fallback; }
	St_45:
		if((c= *p++) ==80) {			goto St_52;}
		else {--p; goto fallback; }
	St_52:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 26;
			goto done;
	St_38:
		if((c= *p++) ==79) {			goto St_46;}
		else {--p; goto fallback; }
	St_46:
		if((c= *p++) ==80) {			goto St_53;}
		else {--p; goto fallback; }
	St_53:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 28;
			goto done;
	St_27:
			TokenEnd=p=auxCComment(TokenStart, p-TokenStart);
			extcode = 15001;
			goto done;
	St_28:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 12;
			goto done;
	St_29:
		if((c= *p++) ==61) {			goto St_39;}
		else {--p; goto fallback; }
	St_39:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 24;
			goto done;
	St_30:
		if((c= *p++) ==83) {			goto St_40;}
		else {--p; goto fallback; }
	St_40:
		if((c= *p++) ==84) {			goto St_47;}
		else {--p; goto fallback; }
	St_47:
		if((c= *p++) ==65) {			goto St_54;}
		else {--p; goto fallback; }
	St_54:
		if((c= *p++) ==82) {			goto St_57;}
		else {--p; goto fallback; }
	St_57:
		if((c= *p++) ==84) {			goto St_60;}
		else {--p; goto fallback; }
	St_60:
		if((c= *p++) ==95) {			goto St_63;}
		else {--p; goto fallback; }
	St_63:
		if((c= *p++) ==83) {			goto St_64;}
		else {--p; goto fallback; }
	St_64:
		if((c= *p++) ==89) {			goto St_65;}
		else {--p; goto fallback; }
	St_65:
		if((c= *p++) ==77) {			goto St_66;}
		else {--p; goto fallback; }
	St_66:
		if((c= *p++) ==66) {			goto St_67;}
		else {--p; goto fallback; }
	St_67:
		if((c= *p++) ==79) {			goto St_68;}
		else {--p; goto fallback; }
	St_68:
		if((c= *p++) ==76) {			goto St_69;}
		else {--p; goto fallback; }
	St_69:
		if((c= *p++) ==62) {			goto St_70;}
		else {--p; goto fallback; }
	St_70:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 27;
			goto done;
	St_32:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 11;
			goto done;
	St_31:
		/*  0-9 A-Z _ a-z*/
		while(scanTbl[(c= *p++)+0] & 1<< 3);--p;
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 15;
			mkidnwod(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
