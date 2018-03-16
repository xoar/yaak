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

case 5:	/* Entered on:  C-D H J-N P-Q U-Z _ a-z */
	St_13:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 6:	/* Entered on: 0-9 */
	St_8:
		/*  0-9*/
		while(scanTbl[(c= *p++)+0] & 1<< 4);--p;
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 13;
			mkint(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;

case 7:	/* Entered on: T */
	St_21:
		if( scanTbl[(c= *p++)+0] & 1<< 5){ /*  0-9 A-Q S-Z _ a-z */
			goto St_25;}
		else if(c ==82) {			goto St_41;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 8:	/* Entered on: S */
	St_20:
		if( scanTbl[(c= *p++)+0] & 1<< 6){ /*  0-9 A-X Z _ a-z */
			goto St_25;}
		else if(c ==89) {			goto St_40;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 9:	/* Entered on: R */
	St_19:
		if( scanTbl[(c= *p++)+0] & 1<< 7){ /*  0-9 A-T V-Z _ a-z */
			goto St_25;}
		else if(c ==85) {			goto St_39;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 10:	/* Entered on: O */
	St_18:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-O Q S-Z _ a-z */
			goto St_25;}
		else if(c ==82) {			goto St_38;}
		else if(c ==80) {			goto St_37;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 11:	/* Entered on: I */
	St_17:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-M O-Z _ a-z */
			goto St_25;}
		else if(c ==78) {			goto St_36;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 12:	/* Entered on: G */
	St_16:
		if( scanTbl[(c= *p++)+0] & 1<< 5){ /*  0-9 A-Q S-Z _ a-z */
			goto St_25;}
		else if(c ==82) {			goto St_35;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 13:	/* Entered on: F */
	St_15:
		if( scanTbl[(c= *p++)+256] & 1<< 2){ /*  0-9 B-N P-Z _ a-z */
			goto St_25;}
		else if(c ==79) {			goto St_34;}
		else if(c ==65) {			goto St_33;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 14:	/* Entered on: E */
	St_14:
		if( scanTbl[(c= *p++)+256] & 1<< 3){ /*  0-9 A-U W Y-Z _ a-z */
			goto St_25;}
		else if(c ==88) {			goto St_32;}
		else if(c ==86) {			goto St_31;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 15:	/* Entered on: B */
	St_12:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 B-D F-Z _ a-z */
			goto St_25;}
		else if(c ==69) {			goto St_30;}
		else if(c ==65) {			goto St_29;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 16:	/* Entered on: A */
	St_11:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Q S V-Z _ a-z */
			goto St_25;}
		else if(c ==85) {			goto St_28;}
		else if(c ==84) {			goto St_27;}
		else if(c ==82) {			goto St_26;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 17:	/* Entered on: / */
	St_7:
		if((c= *p++) ==42) {			goto St_24;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 18:	/* Entered on: # */
	St_4:
			TokenEnd=p=auxEOL(TokenStart, p-TokenStart);
			extcode = 15001;
			goto done;


default: TokenEnd=p; extcode=ExtCodeTbl[c]; goto done; /*  , . :-; [ ] */
}
	St_24:
			TokenEnd=p=auxCComment(TokenStart, p-TokenStart);
			extcode = 15001;
			goto done;
	St_26:
		if( scanTbl[(c= *p++)+0] & 1<< 5){ /*  0-9 A-Q S-Z _ a-z */
			goto St_25;}
		else if(c ==82) {			goto St_42;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_42:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 B-Z _ a-z */
			goto St_25;}
		else if(c ==65) {			goto St_59;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_59:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-M O-Z _ a-z */
			goto St_25;}
		else if(c ==78) {			goto St_75;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_75:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-F H-Z _ a-z */
			goto St_25;}
		else if(c ==71) {			goto St_87;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_87:
		if( scanTbl[(c= *p++)+512] & 1<< 0){ /*  0-9 A-D F-Z _ a-z */
			goto St_25;}
		else if(c ==69) {			goto St_96;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_96:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 26;
			goto done;
			}
	St_25:
		/*  0-9 A-Z _ a-z*/
		while(scanTbl[(c= *p++)+0] & 1<< 3);--p;
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
	St_27:
		if( scanTbl[(c= *p++)+512] & 1<< 1){ /*  0-9 A-S U-Z _ a-z */
			goto St_25;}
		else if(c ==84) {			goto St_43;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_43:
		if( scanTbl[(c= *p++)+0] & 1<< 5){ /*  0-9 A-Q S-Z _ a-z */
			goto St_25;}
		else if(c ==82) {			goto St_60;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_60:
		if( scanTbl[(c= *p++)+512] & 1<< 2){ /*  0-9 A-R T-Z _ a-z */
			goto St_25;}
		else if(c ==83) {			goto St_76;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_76:
		if( scanTbl[(c= *p++)+512] & 1<< 3){ /*  0-9 A-O Q-Z _ a-z */
			goto St_25;}
		else if(c ==80) {			goto St_88;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_88:
		if( scanTbl[(c= *p++)+512] & 1<< 0){ /*  0-9 A-D F-Z _ a-z */
			goto St_25;}
		else if(c ==69) {			goto St_97;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_97:
		if( scanTbl[(c= *p++)+512] & 1<< 4){ /*  0-9 A-Y _ a-z */
			goto St_25;}
		else if(c ==90) {			goto St_103;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_103:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 18;
			goto done;
			}
	St_28:
		if( scanTbl[(c= *p++)+512] & 1<< 1){ /*  0-9 A-S U-Z _ a-z */
			goto St_25;}
		else if(c ==84) {			goto St_44;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_44:
		if( scanTbl[(c= *p++)+512] & 1<< 5){ /*  0-9 A-N P-Z _ a-z */
			goto St_25;}
		else if(c ==79) {			goto St_61;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_61:
		if( scanTbl[(c= *p++)+512] & 1<< 6){ /*  0-9 A-L N-Z _ a-z */
			goto St_25;}
		else if(c ==77) {			goto St_77;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_77:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 B-Z _ a-z */
			goto St_25;}
		else if(c ==65) {			goto St_89;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_89:
		if( scanTbl[(c= *p++)+512] & 1<< 1){ /*  0-9 A-S U-Z _ a-z */
			goto St_25;}
		else if(c ==84) {			goto St_98;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_98:
		if( scanTbl[(c= *p++)+512] & 1<< 7){ /*  0-9 A-H J-Z _ a-z */
			goto St_25;}
		else if(c ==73) {			goto St_104;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_104:
		if( scanTbl[(c= *p++)+768] & 1<< 0){ /*  0-9 A-B D-Z _ a-z */
			goto St_25;}
		else if(c ==67) {			goto St_108;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_108:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 B-Z _ a-z */
			goto St_25;}
		else if(c ==65) {			goto St_111;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_111:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-K M-Z _ a-z */
			goto St_25;}
		else if(c ==76) {			goto St_112;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_112:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-K M-Z _ a-z */
			goto St_25;}
		else if(c ==76) {			goto St_113;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_113:
		if( scanTbl[(c= *p++)+0] & 1<< 6){ /*  0-9 A-X Z _ a-z */
			goto St_25;}
		else if(c ==89) {			goto St_114;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_114:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			goto done;
			}
	St_29:
		if( scanTbl[(c= *p++)+768] & 1<< 0){ /*  0-9 A-B D-Z _ a-z */
			goto St_25;}
		else if(c ==67) {			goto St_45;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_45:
		if( scanTbl[(c= *p++)+768] & 1<< 2){ /*  0-9 A-J L-Z _ a-z */
			goto St_25;}
		else if(c ==75) {			goto St_62;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_62:
		if( scanTbl[(c= *p++)+512] & 1<< 0){ /*  0-9 A-D F-Z _ a-z */
			goto St_25;}
		else if(c ==69) {			goto St_78;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_78:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-M O-Z _ a-z */
			goto St_25;}
		else if(c ==78) {			goto St_90;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_90:
		if( scanTbl[(c= *p++)+768] & 1<< 3){ /*  0-9 A-C E-Z _ a-z */
			goto St_25;}
		else if(c ==68) {			goto St_99;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_99:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 20;
			goto done;
			}
	St_30:
		if( scanTbl[(c= *p++)+768] & 1<< 4){ /*  0-9 A-E G-Z _ a-z */
			goto St_25;}
		else if(c ==70) {			goto St_46;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_46:
		if( scanTbl[(c= *p++)+512] & 1<< 5){ /*  0-9 A-N P-Z _ a-z */
			goto St_25;}
		else if(c ==79) {			goto St_63;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_63:
		if( scanTbl[(c= *p++)+0] & 1<< 5){ /*  0-9 A-Q S-Z _ a-z */
			goto St_25;}
		else if(c ==82) {			goto St_79;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_79:
		if( scanTbl[(c= *p++)+512] & 1<< 0){ /*  0-9 A-D F-Z _ a-z */
			goto St_25;}
		else if(c ==69) {			goto St_91;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_91:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			goto done;
			}
	St_31:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 B-Z _ a-z */
			goto St_25;}
		else if(c ==65) {			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_47:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-K M-Z _ a-z */
			goto St_25;}
		else if(c ==76) {			goto St_64;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_64:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 7;
			goto done;
			}
	St_32:
		if( scanTbl[(c= *p++)+512] & 1<< 3){ /*  0-9 A-O Q-Z _ a-z */
			goto St_25;}
		else if(c ==80) {			goto St_48;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_48:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 B-Z _ a-z */
			goto St_25;}
		else if(c ==65) {			goto St_65;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_65:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-M O-Z _ a-z */
			goto St_25;}
		else if(c ==78) {			goto St_80;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_80:
		if( scanTbl[(c= *p++)+768] & 1<< 3){ /*  0-9 A-C E-Z _ a-z */
			goto St_25;}
		else if(c ==68) {			goto St_92;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_92:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			goto done;
			}
	St_33:
		if( scanTbl[(c= *p++)+512] & 1<< 2){ /*  0-9 A-R T-Z _ a-z */
			goto St_25;}
		else if(c ==83) {			goto St_49;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_49:
		if( scanTbl[(c= *p++)+512] & 1<< 1){ /*  0-9 A-S U-Z _ a-z */
			goto St_25;}
		else if(c ==84) {			goto St_66;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_66:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 3;
			goto done;
			}
	St_34:
		if( scanTbl[(c= *p++)+0] & 1<< 5){ /*  0-9 A-Q S-Z _ a-z */
			goto St_25;}
		else if(c ==82) {			goto St_50;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_50:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 4;
			goto done;
			}
	St_35:
		if( scanTbl[(c= *p++)+256] & 1<< 2){ /*  0-9 B-N P-Z _ a-z */
			goto St_25;}
		else if(c ==79) {			goto St_52;}
		else if(c ==65) {			goto St_51;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_51:
		if( scanTbl[(c= *p++)+512] & 1<< 3){ /*  0-9 A-O Q-Z _ a-z */
			goto St_25;}
		else if(c ==80) {			goto St_67;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_67:
		if( scanTbl[(c= *p++)+768] & 1<< 5){ /*  0-9 A-G I-Z _ a-z */
			goto St_25;}
		else if(c ==72) {			goto St_81;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_81:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 27;
			goto done;
			}
	St_52:
		if( scanTbl[(c= *p++)+0] & 1<< 7){ /*  0-9 A-T V-Z _ a-z */
			goto St_25;}
		else if(c ==85) {			goto St_68;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_68:
		if( scanTbl[(c= *p++)+512] & 1<< 3){ /*  0-9 A-O Q-Z _ a-z */
			goto St_25;}
		else if(c ==80) {			goto St_82;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_82:
		if( scanTbl[(c= *p++)+512] & 1<< 7){ /*  0-9 A-H J-Z _ a-z */
			goto St_25;}
		else if(c ==73) {			goto St_93;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_93:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-M O-Z _ a-z */
			goto St_25;}
		else if(c ==78) {			goto St_100;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_100:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-F H-Z _ a-z */
			goto St_25;}
		else if(c ==71) {			goto St_105;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_105:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 19;
			goto done;
			}
	St_36:
		if( scanTbl[(c= *p++)+768] & 1<< 0){ /*  0-9 A-B D-Z _ a-z */
			goto St_25;}
		else if(c ==67) {			goto St_53;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 9;
			goto done;
			}
	St_53:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-K M-Z _ a-z */
			goto St_25;}
		else if(c ==76) {			goto St_69;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_69:
		if( scanTbl[(c= *p++)+0] & 1<< 7){ /*  0-9 A-T V-Z _ a-z */
			goto St_25;}
		else if(c ==85) {			goto St_83;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_83:
		if( scanTbl[(c= *p++)+768] & 1<< 3){ /*  0-9 A-C E-Z _ a-z */
			goto St_25;}
		else if(c ==68) {			goto St_94;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_94:
		if( scanTbl[(c= *p++)+512] & 1<< 7){ /*  0-9 A-H J-Z _ a-z */
			goto St_25;}
		else if(c ==73) {			goto St_101;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_101:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-M O-Z _ a-z */
			goto St_25;}
		else if(c ==78) {			goto St_106;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_106:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-F H-Z _ a-z */
			goto St_25;}
		else if(c ==71) {			goto St_109;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_109:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 17;
			goto done;
			}
	St_37:
		if( scanTbl[(c= *p++)+512] & 1<< 1){ /*  0-9 A-S U-Z _ a-z */
			goto St_25;}
		else if(c ==84) {			goto St_54;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_54:
		if( scanTbl[(c= *p++)+512] & 1<< 7){ /*  0-9 A-H J-Z _ a-z */
			goto St_25;}
		else if(c ==73) {			goto St_70;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_70:
		if( scanTbl[(c= *p++)+512] & 1<< 6){ /*  0-9 A-L N-Z _ a-z */
			goto St_25;}
		else if(c ==77) {			goto St_84;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_84:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 23;
			goto done;
			}
	St_38:
		if( scanTbl[(c= *p++)+768] & 1<< 3){ /*  0-9 A-C E-Z _ a-z */
			goto St_25;}
		else if(c ==68) {			goto St_55;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_55:
		if( scanTbl[(c= *p++)+512] & 1<< 0){ /*  0-9 A-D F-Z _ a-z */
			goto St_25;}
		else if(c ==69) {			goto St_71;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_71:
		if( scanTbl[(c= *p++)+0] & 1<< 5){ /*  0-9 A-Q S-Z _ a-z */
			goto St_25;}
		else if(c ==82) {			goto St_85;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_85:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 24;
			goto done;
			}
	St_39:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-K M-Z _ a-z */
			goto St_25;}
		else if(c ==76) {			goto St_56;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_56:
		if( scanTbl[(c= *p++)+512] & 1<< 0){ /*  0-9 A-D F-Z _ a-z */
			goto St_25;}
		else if(c ==69) {			goto St_72;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_72:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 10;
			goto done;
			}
	St_40:
		if( scanTbl[(c= *p++)+512] & 1<< 6){ /*  0-9 A-L N-Z _ a-z */
			goto St_25;}
		else if(c ==77) {			goto St_57;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_57:
		if( scanTbl[(c= *p++)+768] & 1<< 6){ /*  0-9 A C-Z _ a-z */
			goto St_25;}
		else if(c ==66) {			goto St_73;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_73:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 5;
			goto done;
			}
	St_41:
		if( scanTbl[(c= *p++)+512] & 1<< 0){ /*  0-9 A-D F-Z _ a-z */
			goto St_25;}
		else if(c ==69) {			goto St_58;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_58:
		if( scanTbl[(c= *p++)+512] & 1<< 0){ /*  0-9 A-D F-Z _ a-z */
			goto St_25;}
		else if(c ==69) {			goto St_74;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_74:
		if( scanTbl[(c= *p++)+768] & 1<< 7){ /*  0-9 A-Z a-z */
			goto St_25;}
		else if(c ==95) {			goto St_86;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 28;
			goto done;
			}
	St_86:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-M O-Z _ a-z */
			goto St_25;}
		else if(c ==78) {			goto St_95;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_95:
		if( scanTbl[(c= *p++)+512] & 1<< 5){ /*  0-9 A-N P-Z _ a-z */
			goto St_25;}
		else if(c ==79) {			goto St_102;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_102:
		if( scanTbl[(c= *p++)+768] & 1<< 3){ /*  0-9 A-C E-Z _ a-z */
			goto St_25;}
		else if(c ==68) {			goto St_107;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_107:
		if( scanTbl[(c= *p++)+512] & 1<< 0){ /*  0-9 A-D F-Z _ a-z */
			goto St_25;}
		else if(c ==69) {			goto St_110;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_110:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_25;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 15;
			goto done;
			}
