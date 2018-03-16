typedef int			tp_NodTyp;
typedef int			tp_AttTyp;

typedef char *			tp_FileName;
typedef char *			tp_Str;

typedef int *			tp_FilDsc;

typedef struct _tps_Nod *	tp_Nod;
typedef struct _tps_Sym *	tp_Sym;

typedef union {
   tp_Nod Nod;
   tp_Sym Sym;
   int    Int; }		tp_Att;
