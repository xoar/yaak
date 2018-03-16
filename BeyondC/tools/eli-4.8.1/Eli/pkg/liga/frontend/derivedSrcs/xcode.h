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

case 5:	/* Entered on:  F-G J-K M-Q V X-Z _ a-z */
	St_26:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 6:	/* Entered on: 1-9 */
	St_16:
		/*  0-9*/
		while(scanTbl[(c= *p++)+0] & 1<< 4);--p;
		if( scanTbl[(c= *p++)+0] & 1<< 5){ /*  E e */
		extcode = 23;/* remember fallback*/
		TokenEnd = p-1;

		scan = NULL;
		proc = c_mkint;
			goto St_43;}
		else if(c ==46) {			goto St_42;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 23;
			c_mkint(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 7:	/* Entered on: W */
	St_34:
		if( scanTbl[(c= *p++)+0] & 1<< 6){ /*  0-9 A-H J-Z _ a-z */
			goto St_47;}
		else if(c ==73) {			goto St_68;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 8:	/* Entered on: U */
	St_33:
		if( scanTbl[(c= *p++)+0] & 1<< 7){ /*  0-9 A-M O-Z _ a-z */
			goto St_47;}
		else if(c ==78) {			goto St_67;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 9:	/* Entered on: T */
	St_32:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 B-D F-G I-Q S-Z _ a-z */
			goto St_47;}
		else if(c ==82) {			goto St_66;}
		else if(c ==72) {			goto St_65;}
		else if(c ==69) {			goto St_64;}
		else if(c ==65) {			goto St_63;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 10:	/* Entered on: S */
	St_31:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-G I-X Z _ a-z */
			goto St_47;}
		else if(c ==89) {			goto St_62;}
		else if(c ==72) {			goto St_61;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 11:	/* Entered on: R */
	St_30:
		if( scanTbl[(c= *p++)+256] & 1<< 2){ /*  0-9 A-G I-T V-Z _ a-z */
			goto St_47;}
		else if(c ==85) {			goto St_60;}
		else if(c ==72) {			goto St_59;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 12:	/* Entered on: L */
	St_29:
		if( scanTbl[(c= *p++)+0] & 1<< 6){ /*  0-9 A-H J-Z _ a-z */
			goto St_47;}
		else if(c ==73) {			goto St_58;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 13:	/* Entered on: I */
	St_28:
		if( scanTbl[(c= *p++)+256] & 1<< 3){ /*  0-9 A-M O-S U-Z _ a-z */
			goto St_47;}
		else if(c ==84) {			goto St_57;}
		else if(c ==78) {			goto St_56;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 14:	/* Entered on: H */
	St_27:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 A-D F-Z _ a-z */
			goto St_47;}
		else if(c ==69) {			goto St_55;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 15:	/* Entered on: E */
	St_25:
		if( scanTbl[(c= *p++)+0] & 1<< 7){ /*  0-9 A-M O-Z _ a-z */
			goto St_47;}
		else if(c ==78) {			goto St_54;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 16:	/* Entered on: D */
	St_24:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 A-D F-Z _ a-z */
			goto St_47;}
		else if(c ==69) {			goto St_53;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 17:	/* Entered on: C */
	St_23:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-G I-K M-N P-Z _ a-z */
			goto St_47;}
		else if(c ==79) {			goto St_52;}
		else if(c ==76) {			goto St_51;}
		else if(c ==72) {			goto St_50;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 18:	/* Entered on: B */
	St_22:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-N P-Z _ a-z */
			goto St_47;}
		else if(c ==79) {			goto St_49;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 19:	/* Entered on: A */
	St_21:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-S U-Z _ a-z */
			goto St_47;}
		else if(c ==84) {			goto St_48;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 20:	/* Entered on: < */
	St_19:
		if((c= *p++) ==45) {			goto St_46;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 21:	/* Entered on: : */
	St_17:
		if((c= *p++) ==58) {		extcode = 7;/* remember fallback*/
		TokenEnd = p-1;

		scan = NULL;
		proc = NULL;
			goto St_45;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 7;
			goto done;
			}

case 22:	/* Entered on: 0 */
	St_15:
		if( scanTbl[(c= *p++)+0] & 1<< 4){ /*  0-9 */
			goto St_16;}
		else if( scanTbl[c+512] & 1<< 0){ /*  X x */
			goto St_44;}
		else if( scanTbl[c+0] & 1<< 5){ /*  E e */
		extcode = 23;/* remember fallback*/
		TokenEnd = p-1;

		scan = NULL;
		proc = c_mkint;
			goto St_43;}
		else if(c ==46) {			goto St_42;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 23;
			c_mkint(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 23:	/* Entered on: / */
	St_14:
		if((c= *p++) ==42) {			goto St_41;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 24:	/* Entered on: . */
	St_13:
		if( scanTbl[(c= *p++)+0] & 1<< 4){ /*  0-9 */
			goto St_40;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 5;
			goto done;
			}

case 25:	/* Entered on: + */
	St_11:
		if((c= *p++) ==61) {			goto St_39;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 26:	/* Entered on: ( */
	St_9:
		if((c= *p++) ==42) {			goto St_38;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 19;
			goto done;
			}

case 27:	/* Entered on: ' */
	St_8:
			TokenEnd=p=aux_p_string_or_c_char(TokenStart, p-TokenStart);
			extcode = 25;
			p_mkstr(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;

case 28:	/* Entered on: % */
	St_7:
			TokenEnd=p=auxEOL(TokenStart, p-TokenStart);
			extcode = 15001;
			goto done;

case 29:	/* Entered on: # */
	St_5:
			TokenEnd=p=auxEOL(TokenStart, p-TokenStart);
			extcode = 15001;
			goto done;

case 30:	/* Entered on: " */
	St_4:
			TokenEnd=p=auxCString(TokenStart, p-TokenStart);
			extcode = 24;
			c_mkstr(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;


default: TokenEnd=p; extcode=ExtCodeTbl[c]; goto done; /*  $ ) , ; = [ ] | */
}
	St_38:
			TokenEnd=p=auxPascalComment(TokenStart, p-TokenStart);
			extcode = 15001;
			goto done;
	St_39:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 4;
			goto done;
	St_40:
		/*  0-9*/
		while(scanTbl[(c= *p++)+0] & 1<< 4);--p;
		if( scanTbl[(c= *p++)+512] & 1<< 1){ /*  F L f l */
			goto St_70;}
		else if( scanTbl[c+0] & 1<< 5){ /*  E e */
		extcode = 22;/* remember fallback*/
		TokenEnd = p-1;

		scan = NULL;
		proc = mkstr;
			goto St_69;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkstr(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_69:
		if( scanTbl[(c= *p++)+0] & 1<< 4){ /*  0-9 */
			goto St_101;}
		else if( scanTbl[c+512] & 1<< 2){ /*  + - */
			goto St_100;}
		else {--p; goto fallback; }
	St_100:
		if( scanTbl[(c= *p++)+0] & 1<< 4){ /*  0-9 */
			goto St_101;}
		else {--p; goto fallback; }
	St_101:
		/*  0-9*/
		while(scanTbl[(c= *p++)+0] & 1<< 4);--p;
		if( scanTbl[(c= *p++)+512] & 1<< 1){ /*  F L f l */
			goto St_70;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkstr(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_70:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 22;
			mkstr(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
	St_41:
			TokenEnd=p=auxCComment(TokenStart, p-TokenStart);
			extcode = 15001;
			goto done;
	St_42:
		if( scanTbl[(c= *p++)+0] & 1<< 4){ /*  0-9 */
			goto St_71;}
		else if( scanTbl[c+512] & 1<< 1){ /*  F L f l */
			goto St_70;}
		else if( scanTbl[c+0] & 1<< 5){ /*  E e */
		extcode = 22;/* remember fallback*/
		TokenEnd = p-1;

		scan = NULL;
		proc = mkstr;
			goto St_69;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkstr(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_71:
		/*  0-9*/
		while(scanTbl[(c= *p++)+0] & 1<< 4);--p;
		if( scanTbl[(c= *p++)+512] & 1<< 1){ /*  F L f l */
			goto St_70;}
		else if( scanTbl[c+0] & 1<< 5){ /*  E e */
		extcode = 22;/* remember fallback*/
		TokenEnd = p-1;

		scan = NULL;
		proc = mkstr;
			goto St_69;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkstr(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_43:
		if( scanTbl[(c= *p++)+0] & 1<< 4){ /*  0-9 */
			goto St_73;}
		else if( scanTbl[c+512] & 1<< 2){ /*  + - */
			goto St_72;}
		else {--p; goto fallback; }
	St_72:
		if( scanTbl[(c= *p++)+0] & 1<< 4){ /*  0-9 */
			goto St_73;}
		else {--p; goto fallback; }
	St_73:
		/*  0-9*/
		while(scanTbl[(c= *p++)+0] & 1<< 4);--p;
		if( scanTbl[(c= *p++)+512] & 1<< 1){ /*  F L f l */
			goto St_70;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkstr(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_44:
		if( scanTbl[(c= *p++)+512] & 1<< 3){ /*  0-9 A-F a-f */
			goto St_74;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 23;
			c_mkint(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_74:
		/*  0-9 A-F a-f*/
		while(scanTbl[(c= *p++)+512] & 1<< 3);--p;
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 23;
			c_mkint(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
	St_45:
		if((c= *p++) ==61) {			goto St_75;}
		else {--p; goto fallback; }
	St_75:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 32;
			goto done;
	St_46:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 17;
			goto done;
	St_48:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-S U-Z _ a-z */
			goto St_47;}
		else if(c ==84) {			goto St_76;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_76:
		if( scanTbl[(c= *p++)+512] & 1<< 4){ /*  0-9 A-Q S-Z _ a-z */
			goto St_47;}
		else if(c ==82) {			goto St_102;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_102:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 10;
			goto done;
			}
	St_47:
		/*  0-9 A-Z _ a-z*/
		while(scanTbl[(c= *p++)+0] & 1<< 3);--p;
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
	St_49:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-S U-Z _ a-z */
			goto St_47;}
		else if(c ==84) {			goto St_77;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_77:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-S U-Z _ a-z */
			goto St_47;}
		else if(c ==84) {			goto St_103;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_103:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-N P-Z _ a-z */
			goto St_47;}
		else if(c ==79) {			goto St_124;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_124:
		if( scanTbl[(c= *p++)+512] & 1<< 5){ /*  0-9 A-L N-Z _ a-z */
			goto St_47;}
		else if(c ==77) {			goto St_137;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_137:
		if( scanTbl[(c= *p++)+512] & 1<< 6){ /*  0-9 A-T V-Z _ a-z */
			goto St_47;}
		else if(c ==85) {			goto St_148;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_148:
		if( scanTbl[(c= *p++)+512] & 1<< 7){ /*  0-9 A-O Q-Z _ a-z */
			goto St_47;}
		else if(c ==80) {			goto St_156;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_156:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 15;
			goto done;
			}
	St_50:
		if( scanTbl[(c= *p++)+768] & 1<< 0){ /*  0-9 B-Z _ a-z */
			goto St_47;}
		else if(c ==65) {			goto St_78;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_78:
		if( scanTbl[(c= *p++)+0] & 1<< 6){ /*  0-9 A-H J-Z _ a-z */
			goto St_47;}
		else if(c ==73) {			goto St_104;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_104:
		if( scanTbl[(c= *p++)+0] & 1<< 7){ /*  0-9 A-M O-Z _ a-z */
			goto St_47;}
		else if(c ==78) {			goto St_125;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_125:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-R T-Z _ a-z */
			goto St_47;}
		else if(c ==83) {			goto St_138;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 11;
			goto done;
			}
	St_138:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-S U-Z _ a-z */
			goto St_47;}
		else if(c ==84) {			goto St_149;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_149:
		if( scanTbl[(c= *p++)+768] & 1<< 0){ /*  0-9 B-Z _ a-z */
			goto St_47;}
		else if(c ==65) {			goto St_157;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_157:
		if( scanTbl[(c= *p++)+512] & 1<< 4){ /*  0-9 A-Q S-Z _ a-z */
			goto St_47;}
		else if(c ==82) {			goto St_162;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_162:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-S U-Z _ a-z */
			goto St_47;}
		else if(c ==84) {			goto St_166;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_166:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			goto done;
			}
	St_51:
		if( scanTbl[(c= *p++)+768] & 1<< 0){ /*  0-9 B-Z _ a-z */
			goto St_47;}
		else if(c ==65) {			goto St_79;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_79:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-R T-Z _ a-z */
			goto St_47;}
		else if(c ==83) {			goto St_105;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_105:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-R T-Z _ a-z */
			goto St_47;}
		else if(c ==83) {			goto St_126;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_126:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 41;
			goto done;
			}
	St_52:
		if( scanTbl[(c= *p++)+768] & 1<< 2){ /*  0-9 A-L O-Z _ a-z */
			goto St_47;}
		else if(c ==78) {			goto St_81;}
		else if(c ==77) {			goto St_80;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_80:
		if( scanTbl[(c= *p++)+512] & 1<< 7){ /*  0-9 A-O Q-Z _ a-z */
			goto St_47;}
		else if(c ==80) {			goto St_106;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_106:
		if( scanTbl[(c= *p++)+512] & 1<< 6){ /*  0-9 A-T V-Z _ a-z */
			goto St_47;}
		else if(c ==85) {			goto St_127;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_127:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-S U-Z _ a-z */
			goto St_47;}
		else if(c ==84) {			goto St_139;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_139:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 A-D F-Z _ a-z */
			goto St_47;}
		else if(c ==69) {			goto St_150;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_150:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 14;
			goto done;
			}
	St_81:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-R T-Z _ a-z */
			goto St_47;}
		else if(c ==83) {			goto St_107;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_107:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-S U-Z _ a-z */
			goto St_47;}
		else if(c ==84) {			goto St_128;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_128:
		if( scanTbl[(c= *p++)+0] & 1<< 6){ /*  0-9 A-H J-Z _ a-z */
			goto St_47;}
		else if(c ==73) {			goto St_140;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_140:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-S U-Z _ a-z */
			goto St_47;}
		else if(c ==84) {			goto St_151;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_151:
		if( scanTbl[(c= *p++)+512] & 1<< 6){ /*  0-9 A-T V-Z _ a-z */
			goto St_47;}
		else if(c ==85) {			goto St_158;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_158:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 A-D F-Z _ a-z */
			goto St_47;}
		else if(c ==69) {			goto St_163;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_163:
		if( scanTbl[(c= *p++)+0] & 1<< 7){ /*  0-9 A-M O-Z _ a-z */
			goto St_47;}
		else if(c ==78) {			goto St_167;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_167:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-S U-Z _ a-z */
			goto St_47;}
		else if(c ==84) {			goto St_169;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_169:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-R T-Z _ a-z */
			goto St_47;}
		else if(c ==83) {			goto St_170;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 34;
			goto done;
			}
	St_170:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 35;
			goto done;
			}
	St_53:
		if( scanTbl[(c= *p++)+512] & 1<< 7){ /*  0-9 A-O Q-Z _ a-z */
			goto St_47;}
		else if(c ==80) {			goto St_82;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_82:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 A-D F-Z _ a-z */
			goto St_47;}
		else if(c ==69) {			goto St_108;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_108:
		if( scanTbl[(c= *p++)+0] & 1<< 7){ /*  0-9 A-M O-Z _ a-z */
			goto St_47;}
		else if(c ==78) {			goto St_129;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_129:
		if( scanTbl[(c= *p++)+768] & 1<< 3){ /*  0-9 A-C E-Z _ a-z */
			goto St_47;}
		else if(c ==68) {			goto St_141;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_141:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-R T-Z _ a-z */
			goto St_47;}
		else if(c ==83) {			goto St_152;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_152:
		if( scanTbl[(c= *p++)+768] & 1<< 4){ /*  0-9 A-Z a-z */
			goto St_47;}
		else if(c ==95) {			goto St_159;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_159:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-N P-Z _ a-z */
			goto St_47;}
		else if(c ==79) {			goto St_164;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_164:
		if( scanTbl[(c= *p++)+0] & 1<< 7){ /*  0-9 A-M O-Z _ a-z */
			goto St_47;}
		else if(c ==78) {			goto St_168;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_168:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 18;
			goto done;
			}
	St_54:
		if( scanTbl[(c= *p++)+768] & 1<< 3){ /*  0-9 A-C E-Z _ a-z */
			goto St_47;}
		else if(c ==68) {			goto St_83;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_83:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 38;
			goto done;
			}
	St_55:
		if( scanTbl[(c= *p++)+768] & 1<< 0){ /*  0-9 B-Z _ a-z */
			goto St_47;}
		else if(c ==65) {			goto St_84;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_84:
		if( scanTbl[(c= *p++)+768] & 1<< 3){ /*  0-9 A-C E-Z _ a-z */
			goto St_47;}
		else if(c ==68) {			goto St_109;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_109:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 44;
			goto done;
			}
	St_56:
		if( scanTbl[(c= *p++)+768] & 1<< 5){ /*  0-9 A-B D-G I-Z _ a-z */
			goto St_47;}
		else if(c ==72) {			goto St_86;}
		else if(c ==67) {			goto St_85;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_85:
		if( scanTbl[(c= *p++)+768] & 1<< 6){ /*  0-9 A-K M-Z _ a-z */
			goto St_47;}
		else if(c ==76) {			goto St_110;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_110:
		if( scanTbl[(c= *p++)+512] & 1<< 6){ /*  0-9 A-T V-Z _ a-z */
			goto St_47;}
		else if(c ==85) {			goto St_130;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_130:
		if( scanTbl[(c= *p++)+768] & 1<< 3){ /*  0-9 A-C E-Z _ a-z */
			goto St_47;}
		else if(c ==68) {			goto St_142;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_142:
		if( scanTbl[(c= *p++)+0] & 1<< 6){ /*  0-9 A-H J-Z _ a-z */
			goto St_47;}
		else if(c ==73) {			goto St_153;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_153:
		if( scanTbl[(c= *p++)+0] & 1<< 7){ /*  0-9 A-M O-Z _ a-z */
			goto St_47;}
		else if(c ==78) {			goto St_160;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_160:
		if( scanTbl[(c= *p++)+768] & 1<< 7){ /*  0-9 A-F H-Z _ a-z */
			goto St_47;}
		else if(c ==71) {			goto St_165;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_165:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 33;
			goto done;
			}
	St_86:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 A-D F-Z _ a-z */
			goto St_47;}
		else if(c ==69) {			goto St_111;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 12;
			goto done;
			}
	St_111:
		if( scanTbl[(c= *p++)+512] & 1<< 4){ /*  0-9 A-Q S-Z _ a-z */
			goto St_47;}
		else if(c ==82) {			goto St_131;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_131:
		if( scanTbl[(c= *p++)+0] & 1<< 6){ /*  0-9 A-H J-Z _ a-z */
			goto St_47;}
		else if(c ==73) {			goto St_143;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_143:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-S U-Z _ a-z */
			goto St_47;}
		else if(c ==84) {			goto St_154;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_154:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-R T-Z _ a-z */
			goto St_47;}
		else if(c ==83) {			goto St_161;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_161:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 28;
			goto done;
			}
	St_57:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 A-D F-Z _ a-z */
			goto St_47;}
		else if(c ==69) {			goto St_87;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_87:
		if( scanTbl[(c= *p++)+512] & 1<< 4){ /*  0-9 A-Q S-Z _ a-z */
			goto St_47;}
		else if(c ==82) {			goto St_112;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_112:
		if( scanTbl[(c= *p++)+768] & 1<< 0){ /*  0-9 B-Z _ a-z */
			goto St_47;}
		else if(c ==65) {			goto St_132;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_132:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-S U-Z _ a-z */
			goto St_47;}
		else if(c ==84) {			goto St_144;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_144:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 A-D F-Z _ a-z */
			goto St_47;}
		else if(c ==69) {			goto St_155;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_155:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 30;
			goto done;
			}
	St_58:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-R T-Z _ a-z */
			goto St_47;}
		else if(c ==83) {			goto St_88;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_88:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-S U-Z _ a-z */
			goto St_47;}
		else if(c ==84) {			goto St_113;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_113:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-N P-Z _ a-z */
			goto St_47;}
		else if(c ==79) {			goto St_133;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_133:
		if( scanTbl[(c= *p++)+1024] & 1<< 0){ /*  0-9 A-E G-Z _ a-z */
			goto St_47;}
		else if(c ==70) {			goto St_145;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_145:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 31;
			goto done;
			}
	St_59:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-R T-Z _ a-z */
			goto St_47;}
		else if(c ==83) {			goto St_89;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_89:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 36;
			goto done;
			}
	St_60:
		if( scanTbl[(c= *p++)+768] & 1<< 6){ /*  0-9 A-K M-Z _ a-z */
			goto St_47;}
		else if(c ==76) {			goto St_90;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_90:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 A-D F-Z _ a-z */
			goto St_47;}
		else if(c ==69) {			goto St_114;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_114:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 37;
			goto done;
			}
	St_61:
		if( scanTbl[(c= *p++)+0] & 1<< 6){ /*  0-9 A-H J-Z _ a-z */
			goto St_47;}
		else if(c ==73) {			goto St_91;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_91:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 A-D F-Z _ a-z */
			goto St_47;}
		else if(c ==69) {			goto St_115;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_115:
		if( scanTbl[(c= *p++)+768] & 1<< 6){ /*  0-9 A-K M-Z _ a-z */
			goto St_47;}
		else if(c ==76) {			goto St_134;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_134:
		if( scanTbl[(c= *p++)+768] & 1<< 3){ /*  0-9 A-C E-Z _ a-z */
			goto St_47;}
		else if(c ==68) {			goto St_146;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_146:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 39;
			goto done;
			}
	St_62:
		if( scanTbl[(c= *p++)+768] & 1<< 2){ /*  0-9 A-L O-Z _ a-z */
			goto St_47;}
		else if(c ==78) {			goto St_93;}
		else if(c ==77) {			goto St_92;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_92:
		if( scanTbl[(c= *p++)+1024] & 1<< 1){ /*  0-9 A C-Z _ a-z */
			goto St_47;}
		else if(c ==66) {			goto St_116;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_116:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-N P-Z _ a-z */
			goto St_47;}
		else if(c ==79) {			goto St_135;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_135:
		if( scanTbl[(c= *p++)+768] & 1<< 6){ /*  0-9 A-K M-Z _ a-z */
			goto St_47;}
		else if(c ==76) {			goto St_147;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_147:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 42;
			goto done;
			}
	St_93:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-S U-Z _ a-z */
			goto St_47;}
		else if(c ==84) {			goto St_117;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_117:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 13;
			goto done;
			}
	St_63:
		if( scanTbl[(c= *p++)+0] & 1<< 6){ /*  0-9 A-H J-Z _ a-z */
			goto St_47;}
		else if(c ==73) {			goto St_94;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_94:
		if( scanTbl[(c= *p++)+768] & 1<< 6){ /*  0-9 A-K M-Z _ a-z */
			goto St_47;}
		else if(c ==76) {			goto St_118;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_118:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 45;
			goto done;
			}
	St_64:
		if( scanTbl[(c= *p++)+512] & 1<< 4){ /*  0-9 A-Q S-Z _ a-z */
			goto St_47;}
		else if(c ==82) {			goto St_95;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_95:
		if( scanTbl[(c= *p++)+512] & 1<< 5){ /*  0-9 A-L N-Z _ a-z */
			goto St_47;}
		else if(c ==77) {			goto St_119;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_119:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 40;
			goto done;
			}
	St_65:
		if( scanTbl[(c= *p++)+0] & 1<< 6){ /*  0-9 A-H J-Z _ a-z */
			goto St_47;}
		else if(c ==73) {			goto St_96;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_96:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-R T-Z _ a-z */
			goto St_47;}
		else if(c ==83) {			goto St_120;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_120:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 46;
			goto done;
			}
	St_66:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 A-D F-Z _ a-z */
			goto St_47;}
		else if(c ==69) {			goto St_97;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_97:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 A-D F-Z _ a-z */
			goto St_47;}
		else if(c ==69) {			goto St_121;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_121:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 43;
			goto done;
			}
	St_67:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-S U-Z _ a-z */
			goto St_47;}
		else if(c ==84) {			goto St_98;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_98:
		if( scanTbl[(c= *p++)+0] & 1<< 6){ /*  0-9 A-H J-Z _ a-z */
			goto St_47;}
		else if(c ==73) {			goto St_122;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_122:
		if( scanTbl[(c= *p++)+768] & 1<< 6){ /*  0-9 A-K M-Z _ a-z */
			goto St_47;}
		else if(c ==76) {			goto St_136;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_136:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 29;
			goto done;
			}
	St_68:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-S U-Z _ a-z */
			goto St_47;}
		else if(c ==84) {			goto St_99;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_99:
		if( scanTbl[(c= *p++)+1024] & 1<< 2){ /*  0-9 A-G I-Z _ a-z */
			goto St_47;}
		else if(c ==72) {			goto St_123;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_123:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 21;
			goto done;
			}
