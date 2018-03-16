#define DUMMY_INDEX -2

typedef char tps_EntryStr [20];

#ifdef __STDC__

#define DG_HEAD(x) \
 (void)fprintf(DRVGRF_FILE, "%d ",num_##x##S); \
 (void)fprintf(DG_C_FILE, "#include \"inc/" #x ".h\"\n"); \
 (void)fprintf(DG_C_FILE, "extern tps_" #x " _" #x "S [];\n")

#define DG_FOREACH(x) \
 { boolean first_time = TRUE; \
 (void)fprintf((FILE*)StdOutFD, "%d " #x "'s\n", num_##x##S); \
 (void)fprintf(DG_C_FILE, "int num_" #x "S = %d;\n", num_##x##S); \
 (void)fprintf(DG_C_FILE, "tps_" #x " _" #x "S [%d] = {\n  ", num_##x##S); \
 for(x = x##S; x != NIL; x=x->Link) {

#define DG_ENTRY(x,y,z) \
 i##y = ((x->y == 0) ? -1 : x->y->Index); \
 if (x->y == 0) {(void)strcpy(s##y, "0"); \
 }else{ (void)sprintf(s##y, "&_" #z "S[%d]", x->y->Index); }

#define DG_CONST(x,y) \
 (void)fprintf(DRVGRF_FILE, "%d\n", x->Index); \
 (void)fprintf(DG_C_FILE, "tp_" #y " " #x " = &_" #y "S[%d];\n", x->Index)

#else

#define DG_HEAD(x) \
 (void)fprintf(DRVGRF_FILE, "%d ",num_/**/x/**/S); \
 (void)fprintf(DG_C_FILE, "#include \"inc/x.h\"\n"); \
 (void)fprintf(DG_C_FILE, "extern tps_%s _%sS [];\n", "x", "x")

#define DG_FOREACH(x) \
 { boolean first_time = TRUE; \
 (void)fprintf((FILE*)StdOutFD, "%d x's\n", num_/**/x/**/S); \
 (void)fprintf(DG_C_FILE, "int num_%sS = %d;\n", "x", num_/**/x/**/S); \
 (void)fprintf(DG_C_FILE, "tps_%s _%sS [%d] = {\n  ", "x", "x", num_/**/x/**/S); \
 for(x = x/**/S; x != NIL; x=x->Link) {

#define DG_ENTRY(x,y,z) \
 i/**/y = ((x->y == 0) ? -1 : x->y->Index); \
 if (x->y == 0) {(void)strcpy(s/**/y, "0"); \
 }else{ (void)sprintf(s/**/y, "&_%sS[%d]", "z", x->y->Index); }

#define DG_CONST(x,y) \
 (void)fprintf(DRVGRF_FILE, "%d\n", x->Index); \
 (void)fprintf(DG_C_FILE, "tp_%s x = &_%sS[%d];\n", "y", "y", x->Index)

#endif

#define DG_ENTRY_SEPARATOR() \
 if (!first_time) (void)fprintf(DG_C_FILE, ",\n  ")

#define DG_END_FOREACH(x) \
 first_time = FALSE; }/*for*/; }/*block*/; \
 (void)fprintf(DG_C_FILE, " };\n")

