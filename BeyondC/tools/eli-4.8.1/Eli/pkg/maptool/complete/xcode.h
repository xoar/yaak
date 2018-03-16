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

case 5:	/* Entered on:  A-D F-K N-Q S-Z _ a-z */
	St_16:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 6:	/* Entered on: 0-9 */
	St_10:
		/*  0-9*/
		while(scanTbl[(c= *p++)+0] & 1<< 4);--p;
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 19;
			mkint(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;

case 7:	/* Entered on: R */
	St_20:
		if( scanTbl[(c= *p++)+0] & 1<< 5){ /*  0-9 A-T V-Z _ a-z */
			goto St_25;}
		else if(c ==85) {			goto St_29;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 8:	/* Entered on: M */
	St_19:
		if( scanTbl[(c= *p++)+0] & 1<< 6){ /*  0-9 B-Z _ a-z */
			goto St_25;}
		else if(c ==65) {			goto St_28;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 9:	/* Entered on: L */
	St_18:
		if( scanTbl[(c= *p++)+0] & 1<< 7){ /*  0-9 A-H J-Z _ a-z */
			goto St_25;}
		else if(c ==73) {			goto St_27;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 10:	/* Entered on: E */
	St_17:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-M O-Z _ a-z */
			goto St_25;}
		else if(c ==78) {			goto St_26;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 11:	/* Entered on: : */
	St_11:
		if((c= *p++) ==58) {		extcode = 6;/* remember fallback*/
		TokenEnd = p-1;

		scan = NULL;
		proc = NULL;
			goto St_24;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			goto done;
			}

case 12:	/* Entered on: / */
	St_9:
		if((c= *p++) ==42) {			goto St_23;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 13:	/* Entered on: ' */
	St_7:
			TokenEnd=p=auxPascalString(TokenStart, p-TokenStart);
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;

case 14:	/* Entered on: $ */
	St_5:
		if((c= *p++) ==66) {		extcode = 3;/* remember fallback*/
		TokenEnd = p-1;

		scan = NULL;
		proc = NULL;
			goto St_22;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 3;
			goto done;
			}

case 15:	/* Entered on: # */
	St_4:
			TokenEnd=p=auxEOL(TokenStart, p-TokenStart);
			extcode = 15001;
			goto done;


default: TokenEnd=p; extcode=ExtCodeTbl[c]; goto done; /*  & . ;-< > @ | */
}
	St_22:
		if((c= *p++) ==79) {			goto St_30;}
		else {--p; goto fallback; }
	St_30:
		if((c= *p++) ==84) {			goto St_36;}
		else {--p; goto fallback; }
	St_36:
		if((c= *p++) ==84) {			goto St_42;}
		else {--p; goto fallback; }
	St_42:
		if((c= *p++) ==79) {			goto St_47;}
		else {--p; goto fallback; }
	St_47:
		if((c= *p++) ==77) {			goto St_52;}
		else {--p; goto fallback; }
	St_52:
		if((c= *p++) ==85) {			goto St_55;}
		else {--p; goto fallback; }
	St_55:
		if((c= *p++) ==80) {			goto St_57;}
		else {--p; goto fallback; }
	St_57:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 11;
			goto done;
	St_23:
			TokenEnd=p=auxCComment(TokenStart, p-TokenStart);
			extcode = 15001;
			goto done;
	St_24:
		if((c= *p++) ==61) {			goto St_31;}
		else {--p; goto fallback; }
	St_31:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 9;
			goto done;
	St_26:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-C E-Z _ a-z */
			goto St_25;}
		else if(c ==68) {			goto St_32;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_32:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 7;
			goto done;
			}
	St_25:
		/*  0-9 A-Z _ a-z*/
		while(scanTbl[(c= *p++)+0] & 1<< 3);--p;
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
	St_27:
		if( scanTbl[(c= *p++)+256] & 1<< 2){ /*  0-9 A-R T-Z _ a-z */
			goto St_25;}
		else if(c ==83) {			goto St_33;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_33:
		if( scanTbl[(c= *p++)+256] & 1<< 3){ /*  0-9 A-S U-Z _ a-z */
			goto St_25;}
		else if(c ==84) {			goto St_37;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_37:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 A-N P-Z _ a-z */
			goto St_25;}
		else if(c ==79) {			goto St_43;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_43:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-E G-Z _ a-z */
			goto St_25;}
		else if(c ==70) {			goto St_48;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_48:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 10;
			goto done;
			}
	St_28:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-O Q-Z _ a-z */
			goto St_25;}
		else if(c ==80) {			goto St_34;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_34:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-B D-Q T-Z _ a-z */
			goto St_25;}
		else if(c ==83) {			goto St_40;}
		else if(c ==82) {			goto St_39;}
		else if(c ==67) {			goto St_38;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_38:
		if( scanTbl[(c= *p++)+512] & 1<< 0){ /*  0-9 A-G I-Z _ a-z */
			goto St_25;}
		else if(c ==72) {			goto St_44;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_44:
		if( scanTbl[(c= *p++)+0] & 1<< 6){ /*  0-9 B-Z _ a-z */
			goto St_25;}
		else if(c ==65) {			goto St_49;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_49:
		if( scanTbl[(c= *p++)+0] & 1<< 7){ /*  0-9 A-H J-Z _ a-z */
			goto St_25;}
		else if(c ==73) {			goto St_53;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_53:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-M O-Z _ a-z */
			goto St_25;}
		else if(c ==78) {			goto St_56;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_56:
		if( scanTbl[(c= *p++)+256] & 1<< 2){ /*  0-9 A-R T-Z _ a-z */
			goto St_25;}
		else if(c ==83) {			goto St_58;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_58:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 18;
			goto done;
			}
	St_39:
		if( scanTbl[(c= *p++)+0] & 1<< 5){ /*  0-9 A-T V-Z _ a-z */
			goto St_25;}
		else if(c ==85) {			goto St_45;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_45:
		if( scanTbl[(c= *p++)+512] & 1<< 1){ /*  0-9 A-K M-Z _ a-z */
			goto St_25;}
		else if(c ==76) {			goto St_50;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_50:
		if( scanTbl[(c= *p++)+512] & 1<< 2){ /*  0-9 A-D F-Z _ a-z */
			goto St_25;}
		else if(c ==69) {			goto St_54;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_54:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 16;
			goto done;
			}
	St_40:
		if( scanTbl[(c= *p++)+512] & 1<< 3){ /*  0-9 A-X Z _ a-z */
			goto St_25;}
		else if(c ==89) {			goto St_46;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_46:
		if( scanTbl[(c= *p++)+512] & 1<< 4){ /*  0-9 A-L N-Z _ a-z */
			goto St_25;}
		else if(c ==77) {			goto St_51;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_51:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 17;
			goto done;
			}
	St_29:
		if( scanTbl[(c= *p++)+512] & 1<< 1){ /*  0-9 A-K M-Z _ a-z */
			goto St_25;}
		else if(c ==76) {			goto St_35;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_35:
		if( scanTbl[(c= *p++)+512] & 1<< 2){ /*  0-9 A-D F-Z _ a-z */
			goto St_25;}
		else if(c ==69) {			goto St_41;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_41:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 5;
			goto done;
			}
