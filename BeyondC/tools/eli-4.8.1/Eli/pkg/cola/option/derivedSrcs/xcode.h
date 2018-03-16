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

case 5:	/* Entered on: 0-9 */
	St_6:
		/*  0-9*/
		while(scanTbl[(c= *p++)+0] & 1<< 3);--p;
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 13;
			mkint(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;

case 6:	/* Entered on: T */
	St_22:
		if((c= *p++) ==84) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_55;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 7:	/* Entered on: S */
	St_21:
		if((c= *p++) ==87) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_54;}
		else if(c ==85) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_53;}
		else if(c ==84) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_52;}
		else if(c ==73) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_51;}
		else if(c ==68) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_50;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 8:	/* Entered on: R */
	St_20:
		if((c= *p++) ==79) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_49;}
		else if(c ==69) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_48;}
		else if(c ==68) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_47;}
		else if(c ==67) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_46;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 9:	/* Entered on: P */
	St_19:
		if((c= *p++) ==85) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_45;}
		else if(c ==79) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_44;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 10:	/* Entered on: O */
	St_18:
		if((c= *p++) ==86) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_43;}
		else if(c ==80) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_42;}
		else if(c ==78) {			goto St_41;}
		else if(c ==70) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_40;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 11:	/* Entered on: N */
	St_17:
		if((c= *p++) ==84) {			goto St_39;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 12:	/* Entered on: M */
	St_16:
		if((c= *p++) ==73) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_38;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 13:	/* Entered on: L */
	St_15:
		if((c= *p++) ==69) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_37;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 14:	/* Entered on: I */
	St_14:
		if((c= *p++) ==78) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_36;}
		else if(c ==70) {			goto St_35;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 15:	/* Entered on: G */
	St_13:
		if((c= *p++) ==79) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_34;}
		else if(c ==67) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_33;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 16:	/* Entered on: F */
	St_12:
		if((c= *p++) ==82) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_32;}
		else if(c ==73) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_31;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 17:	/* Entered on: E */
	St_11:
		if((c= *p++) ==82) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_30;}
		else if(c ==81) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_29;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 18:	/* Entered on: D */
	St_10:
		if((c= *p++) ==69) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_28;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 19:	/* Entered on: C */
	St_9:
		if((c= *p++) ==79) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_27;}
		else if(c ==72) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_26;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 20:	/* Entered on: B */
	St_8:
		if((c= *p++) ==73) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_25;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 21:	/* Entered on: A */
	St_7:
		if((c= *p++) ==85) {
		TokenEnd = TokenStart; /* prepare for error fallback */
			goto St_24;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 22:	/* Entered on: / */
	St_5:
		if((c= *p++) ==42) {			goto St_23;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 23:	/* Entered on: # */
	St_4:
			TokenEnd=p=auxEOL(TokenStart, p-TokenStart);
			extcode = 15001;
			goto done;


default: TokenEnd=p; extcode=ExtCodeTbl[c]; goto done; /*  */
}
	St_23:
			TokenEnd=p=auxCComment(TokenStart, p-TokenStart);
			extcode = 15001;
			goto done;
	St_24:
		if((c= *p++) ==84) {			goto St_56;}
		else {--p; goto fallback; }
	St_56:
		if((c= *p++) ==79) {			goto St_89;}
		else {--p; goto fallback; }
	St_89:
		if((c= *p++) ==77) {			goto St_117;}
		else {--p; goto fallback; }
	St_117:
		if((c= *p++) ==65) {			goto St_130;}
		else {--p; goto fallback; }
	St_130:
		if((c= *p++) ==84) {			goto St_138;}
		else {--p; goto fallback; }
	St_138:
		if((c= *p++) ==73) {			goto St_144;}
		else {--p; goto fallback; }
	St_144:
		if((c= *p++) ==67) {			goto St_148;}
		else {--p; goto fallback; }
	St_148:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 20;
			goto done;
	St_25:
		if((c= *p++) ==78) {			goto St_57;}
		else {--p; goto fallback; }
	St_57:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 2;
			goto done;
	St_26:
		if((c= *p++) ==65) {			goto St_58;}
		else {--p; goto fallback; }
	St_58:
		if((c= *p++) ==73) {			goto St_90;}
		else {--p; goto fallback; }
	St_90:
		if((c= *p++) ==78) {			goto St_118;}
		else {--p; goto fallback; }
	St_118:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 34;
			goto done;
	St_27:
		if((c= *p++) ==78) {			goto St_60;}
		else if(c ==68) {			goto St_59;}
		else {--p; goto fallback; }
	St_59:
		if((c= *p++) ==69) {			goto St_91;}
		else {--p; goto fallback; }
	St_91:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 16;
			goto done;
	St_60:
		if((c= *p++) ==78) {			goto St_92;}
		else {--p; goto fallback; }
	St_92:
		if((c= *p++) ==69) {			goto St_119;}
		else {--p; goto fallback; }
	St_119:
		if((c= *p++) ==67) {			goto St_131;}
		else {--p; goto fallback; }
	St_131:
		if((c= *p++) ==84) {			goto St_139;}
		else {--p; goto fallback; }
	St_139:
		if((c= *p++) ==73) {			goto St_145;}
		else {--p; goto fallback; }
	St_145:
		if((c= *p++) ==79) {			goto St_149;}
		else {--p; goto fallback; }
	St_149:
		if((c= *p++) ==78) {			goto St_151;}
		else {--p; goto fallback; }
	St_151:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 4;
			goto done;
	St_28:
		if((c= *p++) ==70) {			goto St_61;}
		else {--p; goto fallback; }
	St_61:
		if((c= *p++) ==65) {			goto St_93;}
		else {--p; goto fallback; }
	St_93:
		if((c= *p++) ==85) {			goto St_120;}
		else {--p; goto fallback; }
	St_120:
		if((c= *p++) ==76) {			goto St_132;}
		else {--p; goto fallback; }
	St_132:
		if((c= *p++) ==84) {			goto St_140;}
		else {--p; goto fallback; }
	St_140:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 5;
			goto done;
	St_29:
		if((c= *p++) ==85) {			goto St_62;}
		else {--p; goto fallback; }
	St_62:
		if((c= *p++) ==65) {			goto St_94;}
		else {--p; goto fallback; }
	St_94:
		if((c= *p++) ==76) {			goto St_121;}
		else {--p; goto fallback; }
	St_121:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 6;
			goto done;
	St_30:
		if((c= *p++) ==82) {			goto St_63;}
		else {--p; goto fallback; }
	St_63:
		if((c= *p++) ==79) {			goto St_95;}
		else {--p; goto fallback; }
	St_95:
		if((c= *p++) ==82) {			goto St_122;}
		else {--p; goto fallback; }
	St_122:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 17;
			goto done;
	St_31:
		if((c= *p++) ==82) {			goto St_64;}
		else {--p; goto fallback; }
	St_64:
		if((c= *p++) ==83) {			goto St_96;}
		else {--p; goto fallback; }
	St_96:
		if((c= *p++) ==84) {			goto St_123;}
		else {--p; goto fallback; }
	St_123:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 35;
			goto done;
	St_32:
		if((c= *p++) ==69) {			goto St_65;}
		else {--p; goto fallback; }
	St_65:
		if((c= *p++) ==69) {			goto St_97;}
		else {--p; goto fallback; }
	St_97:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 21;
			goto done;
	St_33:
		if((c= *p++) ==83) {			goto St_66;}
		else {--p; goto fallback; }
	St_66:
		if((c= *p++) ==66) {			goto St_99;}
		else if(c ==65) {			goto St_98;}
		else {--p; goto fallback; }
	St_98:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 24;
			goto done;
	St_99:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 25;
			goto done;
	St_34:
		if((c= *p++) ==84) {			goto St_67;}
		else {--p; goto fallback; }
	St_67:
		if((c= *p++) ==79) {			goto St_100;}
		else {--p; goto fallback; }
	St_100:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 9;
			goto done;
	St_35:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 3;
			goto done;
	St_36:
		if((c= *p++) ==70) {			goto St_69;}
		else if(c ==68) {			goto St_68;}
		else {--p; goto fallback; }
	St_68:
		if((c= *p++) ==73) {			goto St_101;}
		else {--p; goto fallback; }
	St_101:
		if((c= *p++) ==86) {			goto St_124;}
		else {--p; goto fallback; }
	St_124:
		if((c= *p++) ==73) {			goto St_133;}
		else {--p; goto fallback; }
	St_133:
		if((c= *p++) ==68) {			goto St_141;}
		else {--p; goto fallback; }
	St_141:
		if((c= *p++) ==85) {			goto St_146;}
		else {--p; goto fallback; }
	St_146:
		if((c= *p++) ==65) {			goto St_150;}
		else {--p; goto fallback; }
	St_150:
		if((c= *p++) ==76) {			goto St_152;}
		else {--p; goto fallback; }
	St_152:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 10;
			goto done;
	St_69:
		if((c= *p++) ==79) {			goto St_102;}
		else {--p; goto fallback; }
	St_102:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 23;
			goto done;
	St_37:
		if((c= *p++) ==83) {			goto St_70;}
		else {--p; goto fallback; }
	St_70:
		if((c= *p++) ==66) {			goto St_104;}
		else if(c ==65) {			goto St_103;}
		else {--p; goto fallback; }
	St_103:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 26;
			goto done;
	St_104:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 27;
			goto done;
	St_38:
		if((c= *p++) ==78) {			goto St_71;}
		else {--p; goto fallback; }
	St_71:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 36;
			goto done;
	St_39:
		if((c= *p++) ==65) {		extcode = 7;/* remember fallback*/
		TokenEnd = p-1;

		scan = NULL;
		proc = NULL;
			goto St_72;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 7;
			goto done;
			}
	St_72:
		if((c= *p++) ==66) {			goto St_105;}
		else {--p; goto fallback; }
	St_105:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 39;
			goto done;
	St_40:
		if((c= *p++) ==70) {			goto St_73;}
		else {--p; goto fallback; }
	St_73:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 32;
			goto done;
	St_41:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 33;
			goto done;
	St_42:
		if((c= *p++) ==84) {			goto St_74;}
		else {--p; goto fallback; }
	St_74:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 40;
			goto done;
	St_43:
		if((c= *p++) ==69) {			goto St_75;}
		else {--p; goto fallback; }
	St_75:
		if((c= *p++) ==82) {			goto St_106;}
		else {--p; goto fallback; }
	St_106:
		if((c= *p++) ==70) {			goto St_125;}
		else {--p; goto fallback; }
	St_125:
		if((c= *p++) ==76) {			goto St_134;}
		else {--p; goto fallback; }
	St_134:
		if((c= *p++) ==79) {			goto St_142;}
		else {--p; goto fallback; }
	St_142:
		if((c= *p++) ==87) {			goto St_147;}
		else {--p; goto fallback; }
	St_147:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 38;
			goto done;
	St_44:
		if((c= *p++) ==83) {			goto St_76;}
		else {--p; goto fallback; }
	St_76:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 22;
			goto done;
	St_45:
		if((c= *p++) ==83) {			goto St_77;}
		else {--p; goto fallback; }
	St_77:
		if((c= *p++) ==72) {			goto St_107;}
		else {--p; goto fallback; }
	St_107:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 37;
			goto done;
	St_46:
		if((c= *p++) ==83) {			goto St_78;}
		else {--p; goto fallback; }
	St_78:
		if((c= *p++) ==66) {			goto St_109;}
		else if(c ==65) {			goto St_108;}
		else {--p; goto fallback; }
	St_108:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 28;
			goto done;
	St_109:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 29;
			goto done;
	St_47:
		if((c= *p++) ==83) {			goto St_79;}
		else {--p; goto fallback; }
	St_79:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 30;
			goto done;
	St_48:
		if((c= *p++) ==68) {			goto St_80;}
		else {--p; goto fallback; }
	St_80:
		if((c= *p++) ==85) {			goto St_110;}
		else {--p; goto fallback; }
	St_110:
		if((c= *p++) ==67) {			goto St_126;}
		else {--p; goto fallback; }
	St_126:
		if((c= *p++) ==69) {			goto St_135;}
		else {--p; goto fallback; }
	St_135:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 11;
			goto done;
	St_49:
		if((c= *p++) ==87) {			goto St_81;}
		else {--p; goto fallback; }
	St_81:
		if((c= *p++) ==83) {			goto St_111;}
		else {--p; goto fallback; }
	St_111:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 8;
			goto done;
	St_50:
		if((c= *p++) ==83) {			goto St_82;}
		else {--p; goto fallback; }
	St_82:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 31;
			goto done;
	St_51:
		if((c= *p++) ==90) {			goto St_84;}
		else if(c ==77) {			goto St_83;}
		else {--p; goto fallback; }
	St_83:
		if((c= *p++) ==73) {			goto St_112;}
		else {--p; goto fallback; }
	St_112:
		if((c= *p++) ==76) {			goto St_127;}
		else {--p; goto fallback; }
	St_127:
		if((c= *p++) ==65) {			goto St_136;}
		else {--p; goto fallback; }
	St_136:
		if((c= *p++) ==82) {			goto St_143;}
		else {--p; goto fallback; }
	St_143:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 12;
			goto done;
	St_84:
		if((c= *p++) ==69) {			goto St_113;}
		else {--p; goto fallback; }
	St_113:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 19;
			goto done;
	St_52:
		if((c= *p++) ==65) {			goto St_85;}
		else {--p; goto fallback; }
	St_85:
		if((c= *p++) ==67) {			goto St_114;}
		else {--p; goto fallback; }
	St_114:
		if((c= *p++) ==75) {			goto St_128;}
		else {--p; goto fallback; }
	St_128:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 18;
			goto done;
	St_53:
		if((c= *p++) ==66) {			goto St_86;}
		else {--p; goto fallback; }
	St_86:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 14;
			goto done;
	St_54:
		if((c= *p++) ==73) {			goto St_87;}
		else {--p; goto fallback; }
	St_87:
		if((c= *p++) ==84) {			goto St_115;}
		else {--p; goto fallback; }
	St_115:
		if((c= *p++) ==67) {			goto St_129;}
		else {--p; goto fallback; }
	St_129:
		if((c= *p++) ==72) {			goto St_137;}
		else {--p; goto fallback; }
	St_137:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 15;
			goto done;
	St_55:
		if((c= *p++) ==65) {			goto St_88;}
		else {--p; goto fallback; }
	St_88:
		if((c= *p++) ==66) {			goto St_116;}
		else {--p; goto fallback; }
	St_116:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 41;
			goto done;
