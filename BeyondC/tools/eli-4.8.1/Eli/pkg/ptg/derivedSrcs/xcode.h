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

case 5:	/* Entered on:  A-Z _ a-b e g-h j-k m-o q-r t-z */
	St_10:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_23;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 6:	/* Entered on: 0-9 */
	St_8:
		/*  0-9*/
		while(scanTbl[(c= *p++)+0] & 1<< 4);--p;
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 5;
			mkint(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;

case 7:	/* Entered on: s */
	St_19:
		if( scanTbl[(c= *p++)+0] & 1<< 5){ /*  0-9 A-Z _ a-g i-s u-z */
			goto St_23;}
		else if(c ==116) {			goto St_31;}
		else if(c ==104) {			goto St_30;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 8:	/* Entered on: p */
	St_18:
		if( scanTbl[(c= *p++)+0] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_23;}
		else if(c ==111) {			goto St_29;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 9:	/* Entered on: l */
	St_17:
		if( scanTbl[(c= *p++)+0] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_23;}
		else if(c ==111) {			goto St_28;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 10:	/* Entered on: i */
	St_16:
		if( scanTbl[(c= *p++)+0] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_23;}
		else if(c ==110) {			goto St_27;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 11:	/* Entered on: f */
	St_15:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ a-k m-z */
			goto St_23;}
		else if(c ==108) {			goto St_26;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 12:	/* Entered on: d */
	St_14:
		if( scanTbl[(c= *p++)+0] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_23;}
		else if(c ==111) {			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 13:	/* Entered on: c */
	St_13:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-Z _ a-g i-z */
			goto St_23;}
		else if(c ==104) {			goto St_24;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 14:	/* Entered on: / */
	St_7:
		if((c= *p++) ==42) {			goto St_22;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 15:	/* Entered on: # */
	St_5:
			TokenEnd=p=auxEOL(TokenStart, p-TokenStart);
			extcode = 15001;
			goto done;

case 16:	/* Entered on: " */
	St_4:
			TokenEnd=p=auxCString(TokenStart, p-TokenStart);
			extcode = 7;
			mkstr(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;


default: TokenEnd=p; extcode=ExtCodeTbl[c]; goto done; /*  $ : [ ] { } */
}
	St_22:
			TokenEnd=p=auxCComment(TokenStart, p-TokenStart);
			extcode = 15001;
			goto done;
	St_24:
		if( scanTbl[(c= *p++)+256] & 1<< 2){ /*  0-9 A-Z _ b-z */
			goto St_23;}
		else if(c ==97) {			goto St_32;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_32:
		if( scanTbl[(c= *p++)+256] & 1<< 3){ /*  0-9 A-Z _ a-q s-z */
			goto St_23;}
		else if(c ==114) {			goto St_40;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_40:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_23;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 11;
			goto done;
			}
	St_23:
		/*  0-9 A-Z _ a-z*/
		while(scanTbl[(c= *p++)+0] & 1<< 3);--p;
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
	St_25:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 A-Z _ a-t v-z */
			goto St_23;}
		else if(c ==117) {			goto St_33;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_33:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a c-z */
			goto St_23;}
		else if(c ==98) {			goto St_41;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_41:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ a-k m-z */
			goto St_23;}
		else if(c ==108) {			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_47:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_23;}
		else if(c ==101) {			goto St_52;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_52:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_23;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 12;
			goto done;
			}
	St_26:
		if( scanTbl[(c= *p++)+0] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_23;}
		else if(c ==111) {			goto St_34;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_34:
		if( scanTbl[(c= *p++)+256] & 1<< 2){ /*  0-9 A-Z _ b-z */
			goto St_23;}
		else if(c ==97) {			goto St_42;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_42:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-Z _ a-s u-z */
			goto St_23;}
		else if(c ==116) {			goto St_48;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_48:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_23;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 13;
			goto done;
			}
	St_27:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-Z _ a-s u-z */
			goto St_23;}
		else if(c ==116) {			goto St_35;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_35:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_23;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 14;
			goto done;
			}
	St_28:
		if( scanTbl[(c= *p++)+0] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_23;}
		else if(c ==110) {			goto St_36;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_36:
		if( scanTbl[(c= *p++)+512] & 1<< 0){ /*  0-9 A-Z _ a-f h-z */
			goto St_23;}
		else if(c ==103) {			goto St_43;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_43:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_23;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 15;
			goto done;
			}
	St_29:
		if( scanTbl[(c= *p++)+512] & 1<< 1){ /*  0-9 A-Z _ a-h j-z */
			goto St_23;}
		else if(c ==105) {			goto St_37;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_37:
		if( scanTbl[(c= *p++)+0] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_23;}
		else if(c ==110) {			goto St_44;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_44:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-Z _ a-s u-z */
			goto St_23;}
		else if(c ==116) {			goto St_49;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_49:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_23;}
		else if(c ==101) {			goto St_53;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_53:
		if( scanTbl[(c= *p++)+256] & 1<< 3){ /*  0-9 A-Z _ a-q s-z */
			goto St_23;}
		else if(c ==114) {			goto St_55;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_55:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_23;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 16;
			goto done;
			}
	St_30:
		if( scanTbl[(c= *p++)+0] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_23;}
		else if(c ==111) {			goto St_38;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_38:
		if( scanTbl[(c= *p++)+256] & 1<< 3){ /*  0-9 A-Z _ a-q s-z */
			goto St_23;}
		else if(c ==114) {			goto St_45;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_45:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-Z _ a-s u-z */
			goto St_23;}
		else if(c ==116) {			goto St_50;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_50:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_23;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 17;
			goto done;
			}
	St_31:
		if( scanTbl[(c= *p++)+256] & 1<< 3){ /*  0-9 A-Z _ a-q s-z */
			goto St_23;}
		else if(c ==114) {			goto St_39;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_39:
		if( scanTbl[(c= *p++)+512] & 1<< 1){ /*  0-9 A-Z _ a-h j-z */
			goto St_23;}
		else if(c ==105) {			goto St_46;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_46:
		if( scanTbl[(c= *p++)+0] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_23;}
		else if(c ==110) {			goto St_51;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_51:
		if( scanTbl[(c= *p++)+512] & 1<< 0){ /*  0-9 A-Z _ a-f h-z */
			goto St_23;}
		else if(c ==103) {			goto St_54;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_54:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_23;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 18;
			goto done;
			}
