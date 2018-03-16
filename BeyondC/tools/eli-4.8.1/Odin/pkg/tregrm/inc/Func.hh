#ifdef __STDC__

/* tg.anal.c */
extern void Analyze(tp_Nod, tp_Nod, tp_Nod);
/* tg.att.c */
extern void Reset_Att(tp_AttTyp);
extern tp_Att Get_Att(tp_AttTyp, tp_Sym);
extern void Set_Att(tp_AttTyp, tp_Sym, tp_Att);
/* tg.dummy.c */
extern boolean Empty_DummyStack(void);
extern void Push_DummyStack(tp_Nod, int);
extern void Pop_DummyStack(tp_Nod *, int *);
/* tg.gen_grm.c */
extern void Gen_Grammar(tp_FilDsc, tp_Nod, tp_Nod, tp_Nod);
extern void Gen_LHS(tp_FilDsc, tp_Sym, int);
extern void Gen_Rule(tp_FilDsc, tp_Nod, tp_Sym, int *, int *);
extern void Gen_Seq(tp_FilDsc, tp_Nod, tp_Sym, boolean, int *, int *);
extern void Gen_Token(tp_FilDsc, tp_Nod, tp_Sym, boolean, int *, int *);
extern void Gen_DummySym(tp_FilDsc, tp_Sym, int);
extern void Gen_Act(tp_FilDsc, tp_Nod, int);
extern void Write_Act(tp_FilDsc, int, int);
/* tg.gen_lex.c */
extern void Gen_LexTypes(tp_FilDsc, tp_Nod);
extern boolean Is_UserLeafDef(tp_Nod);
/* tg.gen_nod.c */
extern void Gen_NodeTypes(tp_FilDsc, tp_Nod);
/* tg.main.c */
extern int main(void);
/* tg.nod_grm.c */
extern void Write_Node_Grammar(tp_FilDsc, tp_Nod);
extern tp_Nod Create_Node_Grammar(tp_Nod);
extern void Write_Node(tp_FilDsc, tp_Nod);
extern tp_Nod Append_Seq(tp_Nod, tp_Nod);
extern tp_Nod Union_Alternative(tp_Nod, tp_Nod);
extern tp_Nod NUnion(tp_Nod, tp_Nod);
extern tp_Nod NConc(tp_Nod, tp_Nod);
extern tp_Nod Create_StarNod(tp_Nod);
extern tp_Nod Create_PlusNod(tp_Nod);
extern tp_Nod Copy_Nod(tp_Nod);
extern tp_Nod Make_Nod(tp_NodTyp, tp_Nod);
extern tp_Nod Make_SymNod(tp_NodTyp, tp_Sym);
/* tg.yylex.c */
extern int GetChar(void);
extern void Init_Lex(void);
extern void EndLex(void);
extern int YY_Lex(void);
extern boolean IsNameChr(int);
extern void ParseError(tp_Str);
/* tregrm.yacc.c */
extern tp_Nod YY_Parse(void);
extern void yyerror(char *);
extern int yylex(void);
extern int yyparse(void);
/* if_err.c */
extern void Init_Err(void);
extern void Set_IPC_Err(boolean);
extern void Set_ErrFile(tp_FileName, boolean, tp_FilDsc);
extern void Save_ErrFile(tp_FileName *, boolean *, tp_FilDsc *);
extern boolean IsErr(void);
extern void Reset_Err(void);
extern void Increment_Errors(void);
extern int Num_Errors(void);
extern void SysCallError(tp_FilDsc, char *);
extern void FatalError(char *, char *, int);
extern void SystemError(void *, ...);
extern void Local_ErrMessage(tp_Str);
extern void fatal_err(char *);
/* if_file.c */
extern void Set_ModeMask(tp_FileName);
/* extern void Get_FileInfo(tp_SKind *, int *, tp_FileName); */
extern void MakePlnFile(boolean *, tp_FileName);
extern void MakeDirFile(boolean *, tp_FileName);
extern void GetWorkingDir(boolean *, tp_FileName);
extern void ChangeDir(boolean *, tp_FileName);
extern boolean IsExecutable(tp_FileName);
extern void MakeExecutable(tp_FileName);
extern void MakeReadOnly(boolean *, tp_FileName);
extern void SymLink(boolean *, tp_FileName, tp_FileName);
extern void FileName_SymLinkFileName(tp_FileName, tp_FileName);
extern boolean IsDirectory_FileName(tp_FileName);
extern boolean Exists(tp_FileName);
extern boolean Empty(tp_FileName);
extern void FileSize(boolean *, int *, tp_FileName);
extern void Remove(tp_FileName);
extern void RemoveDir(tp_FileName);
extern void Rename(boolean *, tp_FileName, tp_FileName);
/* if_io.c */
extern void Init_IO(void);
extern boolean GetIsTTY(void);
extern tp_FilDsc FileName_CFilDsc(tp_FileName);
extern tp_FilDsc FileName_WFilDsc(tp_FileName, boolean);
extern tp_FilDsc FileName_AFilDsc(tp_FileName, boolean);
extern tp_FilDsc FileName_RFilDsc(tp_FileName, boolean);
extern tp_FilDsc FileName_RWFilDsc(tp_FileName, boolean);
extern void Flush(tp_FilDsc);
extern void Rewind(tp_FilDsc);
extern void Unwind(tp_FilDsc);
extern void Close(tp_FilDsc);
extern boolean EndOfFile(tp_FilDsc);
extern void Write(tp_FilDsc, tp_Str);
extern void Writech(tp_FilDsc, int);
extern void WriteInt(tp_FilDsc, int);
extern void Writeln(tp_FilDsc, tp_Str);
extern void WriteLine(tp_FilDsc, tp_Str);
extern int Readch(tp_FilDsc);
extern tp_Str Readln(tp_Str, tp_FilDsc);
extern tp_Str ReadLine(tp_Str, tp_FilDsc);
extern int Equal(tp_FilDsc, tp_FilDsc);
extern void FileCopy(tp_FilDsc, tp_FilDsc);
/* if_nod.c */
extern tp_Nod New_Nod(void);
extern void Ret_Nod(tp_Nod);
extern tp_NodTyp Nod_NodTyp(tp_Nod);
extern void Set_Nod_NodTyp(tp_Nod, tp_NodTyp);
extern tp_Nod Nod_FirstSon(tp_Nod);
extern void Set_Nod_FirstSon(tp_Nod, tp_Nod);
extern tp_Nod Nod_Brother(tp_Nod);
extern void Set_Nod_Brother(tp_Nod, tp_Nod);
extern int Nod_NumSons(tp_Nod);
extern tp_Nod Nod_Son(int, tp_Nod);
extern tp_Sym Nod_Sym(tp_Nod);
extern void Set_Nod_Sym(tp_Nod, tp_Sym);
extern boolean Empty_SymStack(void);
extern void Push_SymStack(tp_Sym);
extern void Pop_SymStack(void);
extern void Push_NodStack(tp_Nod);
extern void Pop_NodStack(void);
extern void Push_SonStack(int);
extern void Pop_SonStack(void);
extern void Init_ConstructTree(void);
extern void MakeLeaf(tp_NodTyp, tp_Sym);
extern void MakeEmptyNod(tp_NodTyp);
extern void MakeNod(int);
extern void CollectSons(int);
extern tp_Nod End_ConstructTree(void);
extern void Action(int, int);
/* if_symbol.c */
extern tp_Str GetEnv(tp_Str);
extern tp_Str Malloc_Str(tp_Str);
extern boolean Is_EmptyStr(tp_Str);
extern int Str_PosInt(tp_Str);
extern tp_Str Tail(tp_Str);
extern void StrShift(tp_Str, int);
extern tp_Sym Str_Sym(tp_Str);
extern tp_Str Sym_Str(tp_Sym);
extern int Sym_Att(tp_Sym);
extern void Set_Sym_Att(tp_Sym, int);
extern void Write_Syms(tp_FilDsc);

#else

/* tg.anal.c */
extern void Analyze();
/* tg.att.c */
extern void Reset_Att();
extern tp_Att Get_Att();
extern void Set_Att();
/* tg.dummy.c */
extern boolean Empty_DummyStack();
extern void Push_DummyStack();
extern void Pop_DummyStack();
/* tg.gen_grm.c */
extern void Gen_Grammar();
extern void Gen_LHS();
extern void Gen_Rule();
extern void Gen_Seq();
extern void Gen_Token();
extern void Gen_DummySym();
extern void Gen_Act();
extern void Write_Act();
/* tg.gen_lex.c */
extern void Gen_LexTypes();
extern boolean Is_UserLeafDef();
/* tg.gen_nod.c */
extern void Gen_NodeTypes();
/* tg.main.c */
extern int main();
/* tg.nod_grm.c */
extern void Write_Node_Grammar();
extern tp_Nod Create_Node_Grammar();
extern void Write_Node();
extern tp_Nod Append_Seq();
extern tp_Nod Union_Alternative();
extern tp_Nod NUnion();
extern tp_Nod NConc();
extern tp_Nod Create_StarNod();
extern tp_Nod Create_PlusNod();
extern tp_Nod Copy_Nod();
extern tp_Nod Make_Nod();
extern tp_Nod Make_SymNod();
/* tg.yylex.c */
extern int GetChar();
extern void Init_Lex();
extern void EndLex();
extern int YY_Lex();
extern boolean IsNameChr();
extern void ParseError();
/* tregrm.yacc.c */
extern tp_Nod YY_Parse();
extern void yyerror();
extern int yylex();
extern int yyparse();
/* if_err.c */
extern void Init_Err();
extern void Set_IPC_Err();
extern void Set_ErrFile();
extern void Save_ErrFile();
extern boolean IsErr();
extern void Reset_Err();
extern void Increment_Errors();
extern int Num_Errors();
extern void SysCallError();
extern void FatalError();
extern void SystemError();
extern void Local_ErrMessage();
extern void fatal_err();
/* if_file.c */
extern void Set_ModeMask();
/* extern void Get_FileInfo(); */
extern void MakePlnFile();
extern void MakeDirFile();
extern void GetWorkingDir();
extern void ChangeDir();
extern boolean IsExecutable();
extern void MakeExecutable();
extern void MakeReadOnly();
extern void SymLink();
extern void FileName_SymLinkFileName();
extern boolean IsDirectory_FileName();
extern boolean Exists();
extern boolean Empty();
extern void FileSize();
extern void Remove();
extern void RemoveDir();
extern void Rename();
/* if_io.c */
extern void Init_IO();
extern boolean GetIsTTY();
extern tp_FilDsc FileName_CFilDsc();
extern tp_FilDsc FileName_WFilDsc();
extern tp_FilDsc FileName_AFilDsc();
extern tp_FilDsc FileName_RFilDsc();
extern tp_FilDsc FileName_RWFilDsc();
extern void Flush();
extern void Rewind();
extern void Unwind();
extern void Close();
extern boolean EndOfFile();
extern void Write();
extern void Writech();
extern void WriteInt();
extern void Writeln();
extern void WriteLine();
extern int Readch();
extern tp_Str Readln();
extern tp_Str ReadLine();
extern int Equal();
extern void FileCopy();
/* if_nod.c */
extern tp_Nod New_Nod();
extern void Ret_Nod();
extern tp_NodTyp Nod_NodTyp();
extern void Set_Nod_NodTyp();
extern tp_Nod Nod_FirstSon();
extern void Set_Nod_FirstSon();
extern tp_Nod Nod_Brother();
extern void Set_Nod_Brother();
extern int Nod_NumSons();
extern tp_Nod Nod_Son();
extern tp_Sym Nod_Sym();
extern void Set_Nod_Sym();
extern boolean Empty_SymStack();
extern void Push_SymStack();
extern void Pop_SymStack();
extern void Push_NodStack();
extern void Pop_NodStack();
extern void Push_SonStack();
extern void Pop_SonStack();
extern void Init_ConstructTree();
extern void MakeLeaf();
extern void MakeEmptyNod();
extern void MakeNod();
extern void CollectSons();
extern tp_Nod End_ConstructTree();
extern void Action();
/* if_symbol.c */
extern tp_Str GetEnv();
extern tp_Str Malloc_Str();
extern boolean Is_EmptyStr();
extern int Str_PosInt();
extern tp_Str Tail();
extern void StrShift();
extern tp_Sym Str_Sym();
extern tp_Str Sym_Str();
extern int Sym_Att();
extern void Set_Sym_Att();
extern void Write_Syms();

#endif
