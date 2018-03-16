#include <stdio.h>
#include <stdlib.h>

#include "ptg_gen.h"
#include "obstack.h"

/* -------------------------------------------------------- */
/*                      Memory Management                   */
/* -------------------------------------------------------- */

static Obstack _PTGObstack;
static void *_PTGFirstObj = NULL;

static void _PTGInit()
{
       if (_PTGFirstObj)
               return;
       obstack_init(&_PTGObstack);
       _PTGFirstObj = obstack_alloc(&_PTGObstack, 0);
}

void PTGFree()
{
       obstack_free(&_PTGObstack, _PTGFirstObj);
       _PTGFirstObj = obstack_alloc(&_PTGObstack, 0);
}


#if defined(__STDC__) || defined(__cplusplus)
static void *MALLOC(int size)
#else
static void *MALLOC(size) int size;
#endif
{
       if (! _PTGFirstObj)
               _PTGInit();
       return (obstack_alloc(&_PTGObstack, size));
}

/* -------------------------------------------------------- */
/*                       Output-functions                   */
/* -------------------------------------------------------- */

static PTG_OUTPUT_FILE f;
static char buffer[40];

#if PTG_OUTPUT_DEFAULT
#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGOut (PTGNode r)
#else
PTGNode PTGOut (r)
       PTGNode r;
#endif
{
       f = stdout;
       if (r) {
               (* (r->_print)) (r);
       }
       return (r);
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGOutFile (const char *fn, PTGNode r)
#else
PTGNode PTGOutFile (fn, r)
       char * fn; PTGNode r;
#endif
{
       if ((f = fopen(fn, "w"))  == (FILE *)NULL)
       {
               fprintf(stderr, "ERROR: PTGOutFile: output file '%s' can't be opened.\n",fn);
               exit(1);
       }
       if (r)
               (* (r->_print)) (r);
       fclose(f);
       return (r);
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGOutFPtr(FILE *fptr, PTGNode r)
#else
PTGNode PTGOutFPtr(fptr, r)
       FILE *fptr; PTGNode r;
#endif
{
       if ((f = fptr) == (FILE *)NULL)
       {
               fprintf(stderr, "ERROR: PTGOutFPtr: output file not open.\n");
               exit(1);
       }
       if (r)
               (* (r->_print)) (r);
       return (r);
}

#endif

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGProcess(PTG_OUTPUT_FILE file, PTGNode r)
#else
PTGNode PTGProcess(file, r)
       PTG_OUTPUT_FILE file; PTGNode r;
#endif
{
       f = file;
       if (r)
               (* (r->_print)) (r);
       return (r);
}
/* -------------------------------------------------------- */
/*                            PTGNULL                       */
/* -------------------------------------------------------- */

/* Define PTGNULL as a PTGNode that prints nothing. */

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGNULL(_PPTG0 n)
#else
static void _PrPTGNULL(n)
_PPTG0 n;
#endif
{(void)n; /* function printing nothing */}

struct _SPTG0   _PTGNULL = { (_PTGProc) _PrPTGNULL };

/* -------------------------------------------------------- */
/*          Node-Construction and Print-functions           */
/* -------------------------------------------------------- */

/* ============================ */

/* Implementation of Pattern hbl */

typedef struct _SPTGhbl{
	_PTGProc _print;
} * _PPTGhbl;

#ifdef PROTO_OK
static void _PrPTGhbl(_PPTGhbl n)
#else
static void _PrPTGhbl(n)
	_PPTGhbl n;
#endif
{
	PTG_OUTPUT_STRING(f, "-hbl");
}

static struct _SPTGhbl _sptghbl = { (_PTGProc) _PrPTGhbl };

#ifdef PROTO_OK
PTGNode PTGhbl(void)
#else
PTGNode PTGhbl()
#endif
{
	return (PTGNode)(&_sptghbl);
}


/* Implementation of Pattern dgd */

typedef struct _SPTGdgd{
	_PTGProc _print;
} * _PPTGdgd;

#ifdef PROTO_OK
static void _PrPTGdgd(_PPTGdgd n)
#else
static void _PrPTGdgd(n)
	_PPTGdgd n;
#endif
{
	PTG_OUTPUT_STRING(f, "-dgd");
}

static struct _SPTGdgd _sptgdgd = { (_PTGProc) _PrPTGdgd };

#ifdef PROTO_OK
PTGNode PTGdgd(void)
#else
PTGNode PTGdgd()
#endif
{
	return (PTGNode)(&_sptgdgd);
}


/* Implementation of Pattern mp */

typedef struct _SPTGmp{
	_PTGProc _print;
} * _PPTGmp;

#ifdef PROTO_OK
static void _PrPTGmp(_PPTGmp n)
#else
static void _PrPTGmp(n)
	_PPTGmp n;
#endif
{
	PTG_OUTPUT_STRING(f, "-mp");
}

static struct _SPTGmp _sptgmp = { (_PTGProc) _PrPTGmp };

#ifdef PROTO_OK
PTGNode PTGmp(void)
#else
PTGNode PTGmp()
#endif
{
	return (PTGNode)(&_sptgmp);
}


/* Implementation of Pattern cre */

typedef struct _SPTGcre{
	_PTGProc _print;
} * _PPTGcre;

#ifdef PROTO_OK
static void _PrPTGcre(_PPTGcre n)
#else
static void _PrPTGcre(n)
	_PPTGcre n;
#endif
{
	PTG_OUTPUT_STRING(f, "-cre");
}

static struct _SPTGcre _sptgcre = { (_PTGProc) _PrPTGcre };

#ifdef PROTO_OK
PTGNode PTGcre(void)
#else
PTGNode PTGcre()
#endif
{
	return (PTGNode)(&_sptgcre);
}


/* Implementation of Pattern lp */

typedef struct _SPTGlp{
	_PTGProc _print;
} * _PPTGlp;

#ifdef PROTO_OK
static void _PrPTGlp(_PPTGlp n)
#else
static void _PrPTGlp(n)
	_PPTGlp n;
#endif
{
	PTG_OUTPUT_STRING(f, "-lp");
}

static struct _SPTGlp _sptglp = { (_PTGProc) _PrPTGlp };

#ifdef PROTO_OK
PTGNode PTGlp(void)
#else
PTGNode PTGlp()
#endif
{
	return (PTGNode)(&_sptglp);
}


/* Implementation of Pattern noc */

typedef struct _SPTGnoc{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGnoc;

#ifdef PROTO_OK
static void _PrPTGnoc(_PPTGnoc n)
#else
static void _PrPTGnoc(n)
	_PPTGnoc n;
#endif
{
	PTG_OUTPUT_STRING(f, "-noc ");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGnoc(PTGNode p1)
#else
PTGNode PTGnoc(p1)

PTGNode p1;
#endif
{
	_PPTGnoc n;
	n = (_PPTGnoc)MALLOC(sizeof(struct _SPTGnoc));
	n->_print = (_PTGProc)_PrPTGnoc;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern nosa */

typedef struct _SPTGnosa{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGnosa;

#ifdef PROTO_OK
static void _PrPTGnosa(_PPTGnosa n)
#else
static void _PrPTGnosa(n)
	_PPTGnosa n;
#endif
{
	PTG_OUTPUT_STRING(f, "-nosa ");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGnosa(PTGNode p1)
#else
PTGNode PTGnosa(p1)

PTGNode p1;
#endif
{
	_PPTGnosa n;
	n = (_PPTGnosa)MALLOC(sizeof(struct _SPTGnosa));
	n->_print = (_PTGProc)_PrPTGnosa;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern dfs */

typedef struct _SPTGdfs{
	_PTGProc _print;
} * _PPTGdfs;

#ifdef PROTO_OK
static void _PrPTGdfs(_PPTGdfs n)
#else
static void _PrPTGdfs(n)
	_PPTGdfs n;
#endif
{
	PTG_OUTPUT_STRING(f, "-dfs");
}

static struct _SPTGdfs _sptgdfs = { (_PTGProc) _PrPTGdfs };

#ifdef PROTO_OK
PTGNode PTGdfs(void)
#else
PTGNode PTGdfs()
#endif
{
	return (PTGNode)(&_sptgdfs);
}


/* Implementation of Pattern scc */

typedef struct _SPTGscc{
	_PTGProc _print;
} * _PPTGscc;

#ifdef PROTO_OK
static void _PrPTGscc(_PPTGscc n)
#else
static void _PrPTGscc(n)
	_PPTGscc n;
#endif
{
	PTG_OUTPUT_STRING(f, "-scc");
}

static struct _SPTGscc _sptgscc = { (_PTGProc) _PrPTGscc };

#ifdef PROTO_OK
PTGNode PTGscc(void)
#else
PTGNode PTGscc()
#endif
{
	return (PTGNode)(&_sptgscc);
}


/* Implementation of Pattern cc */

typedef struct _SPTGcc{
	_PTGProc _print;
} * _PPTGcc;

#ifdef PROTO_OK
static void _PrPTGcc(_PPTGcc n)
#else
static void _PrPTGcc(n)
	_PPTGcc n;
#endif
{
	PTG_OUTPUT_STRING(f, "-cc");
}

static struct _SPTGcc _sptgcc = { (_PTGProc) _PrPTGcc };

#ifdef PROTO_OK
PTGNode PTGcc(void)
#else
PTGNode PTGcc()
#endif
{
	return (PTGNode)(&_sptgcc);
}


/* Implementation of Pattern dum */

typedef struct _SPTGdum{
	_PTGProc _print;
} * _PPTGdum;

#ifdef PROTO_OK
static void _PrPTGdum(_PPTGdum n)
#else
static void _PrPTGdum(n)
	_PPTGdum n;
#endif
{
	PTG_OUTPUT_STRING(f, "-dum");
}

static struct _SPTGdum _sptgdum = { (_PTGProc) _PrPTGdum };

#ifdef PROTO_OK
PTGNode PTGdum(void)
#else
PTGNode PTGdum()
#endif
{
	return (PTGNode)(&_sptgdum);
}


/* Implementation of Pattern src */

typedef struct _SPTGsrc{
	_PTGProc _print;
} * _PPTGsrc;

#ifdef PROTO_OK
static void _PrPTGsrc(_PPTGsrc n)
#else
static void _PrPTGsrc(n)
	_PPTGsrc n;
#endif
{
	PTG_OUTPUT_STRING(f, "-src");
}

static struct _SPTGsrc _sptgsrc = { (_PTGProc) _PrPTGsrc };

#ifdef PROTO_OK
PTGNode PTGsrc(void)
#else
PTGNode PTGsrc()
#endif
{
	return (PTGNode)(&_sptgsrc);
}


/* Implementation of Pattern irc */

typedef struct _SPTGirc{
	_PTGProc _print;
} * _PPTGirc;

#ifdef PROTO_OK
static void _PrPTGirc(_PPTGirc n)
#else
static void _PrPTGirc(n)
	_PPTGirc n;
#endif
{
	PTG_OUTPUT_STRING(f, "-irc");
}

static struct _SPTGirc _sptgirc = { (_PTGProc) _PrPTGirc };

#ifdef PROTO_OK
PTGNode PTGirc(void)
#else
PTGNode PTGirc()
#endif
{
	return (PTGNode)(&_sptgirc);
}


/* Implementation of Pattern dsc */

typedef struct _SPTGdsc{
	_PTGProc _print;
} * _PPTGdsc;

#ifdef PROTO_OK
static void _PrPTGdsc(_PPTGdsc n)
#else
static void _PrPTGdsc(n)
	_PPTGdsc n;
#endif
{
	PTG_OUTPUT_STRING(f, "-dsc");
}

static struct _SPTGdsc _sptgdsc = { (_PTGProc) _PrPTGdsc };

#ifdef PROTO_OK
PTGNode PTGdsc(void)
#else
PTGNode PTGdsc()
#endif
{
	return (PTGNode)(&_sptgdsc);
}


/* Implementation of Pattern lo */

typedef struct _SPTGlo{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGlo;

#ifdef PROTO_OK
static void _PrPTGlo(_PPTGlo n)
#else
static void _PrPTGlo(n)
	_PPTGlo n;
#endif
{
	PTG_OUTPUT_STRING(f, "-lo ");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGlo(PTGNode p1)
#else
PTGNode PTGlo(p1)

PTGNode p1;
#endif
{
	_PPTGlo n;
	n = (_PPTGlo)MALLOC(sizeof(struct _SPTGlo));
	n->_print = (_PTGProc)_PrPTGlo;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern aec */

typedef struct _SPTGaec{
	_PTGProc _print;
} * _PPTGaec;

#ifdef PROTO_OK
static void _PrPTGaec(_PPTGaec n)
#else
static void _PrPTGaec(n)
	_PPTGaec n;
#endif
{
	PTG_OUTPUT_STRING(f, "-aec");
}

static struct _SPTGaec _sptgaec = { (_PTGProc) _PrPTGaec };

#ifdef PROTO_OK
PTGNode PTGaec(void)
#else
PTGNode PTGaec()
#endif
{
	return (PTGNode)(&_sptgaec);
}


/* Implementation of Pattern cl */

typedef struct _SPTGcl{
	_PTGProc _print;
} * _PPTGcl;

#ifdef PROTO_OK
static void _PrPTGcl(_PPTGcl n)
#else
static void _PrPTGcl(n)
	_PPTGcl n;
#endif
{
	PTG_OUTPUT_STRING(f, "-cl");
}

static struct _SPTGcl _sptgcl = { (_PTGProc) _PrPTGcl };

#ifdef PROTO_OK
PTGNode PTGcl(void)
#else
PTGNode PTGcl()
#endif
{
	return (PTGNode)(&_sptgcl);
}


/* Implementation of Pattern qz */

typedef struct _SPTGqz{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGqz;

#ifdef PROTO_OK
static void _PrPTGqz(_PPTGqz n)
#else
static void _PrPTGqz(n)
	_PPTGqz n;
#endif
{
	PTG_OUTPUT_STRING(f, "-qz ");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGqz(PTGNode p1)
#else
PTGNode PTGqz(p1)

PTGNode p1;
#endif
{
	_PPTGqz n;
	n = (_PPTGqz)MALLOC(sizeof(struct _SPTGqz));
	n->_print = (_PTGProc)_PrPTGqz;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern sz */

typedef struct _SPTGsz{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGsz;

#ifdef PROTO_OK
static void _PrPTGsz(_PPTGsz n)
#else
static void _PrPTGsz(n)
	_PPTGsz n;
#endif
{
	PTG_OUTPUT_STRING(f, "-sz ");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGsz(PTGNode p1)
#else
PTGNode PTGsz(p1)

PTGNode p1;
#endif
{
	_PPTGsz n;
	n = (_PPTGsz)MALLOC(sizeof(struct _SPTGsz));
	n->_print = (_PTGProc)_PrPTGsz;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern zahl */

typedef struct _SPTGzahl{
	_PTGProc _print;
	int p1;
} * _PPTGzahl;

#ifdef PROTO_OK
static void _PrPTGzahl(_PPTGzahl n)
#else
static void _PrPTGzahl(n)
	_PPTGzahl n;
#endif
{
	PTG_OUTPUT_INT(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGzahl(int p1)
#else
PTGNode PTGzahl(p1)

int p1;
#endif
{
	_PPTGzahl n;
	n = (_PPTGzahl)MALLOC(sizeof(struct _SPTGzahl));
	n->_print = (_PTGProc)_PrPTGzahl;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern seq */

typedef struct _SPTGseq{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGseq;

#ifdef PROTO_OK
static void _PrPTGseq(_PPTGseq n)
#else
static void _PrPTGseq(n)
	_PPTGseq n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ");
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGseq(PTGNode p1, PTGNode p2)
#else
PTGNode PTGseq(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGseq n;
	n = (_PPTGseq)MALLOC(sizeof(struct _SPTGseq));
	n->_print = (_PTGProc)_PrPTGseq;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern optinfo */

typedef struct _SPTGoptinfo{
	_PTGProc _print;
} * _PPTGoptinfo;

#ifdef PROTO_OK
static void _PrPTGoptinfo(_PPTGoptinfo n)
#else
static void _PrPTGoptinfo(n)
	_PPTGoptinfo n;
#endif
{
	PTG_OUTPUT_STRING(f, "OPT_INFO");
}

static struct _SPTGoptinfo _sptgoptinfo = { (_PTGProc) _PrPTGoptinfo };

#ifdef PROTO_OK
PTGNode PTGoptinfo(void)
#else
PTGNode PTGoptinfo()
#endif
{
	return (PTGNode)(&_sptgoptinfo);
}


/* Implementation of Pattern ttab */

typedef struct _SPTGttab{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGttab;

#ifdef PROTO_OK
static void _PrPTGttab(_PPTGttab n)
#else
static void _PrPTGttab(n)
	_PPTGttab n;
#endif
{
	PTG_OUTPUT_STRING(f, "T_TAB ");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGttab(PTGNode p1)
#else
PTGNode PTGttab(p1)

PTGNode p1;
#endif
{
	_PPTGttab n;
	n = (_PPTGttab)MALLOC(sizeof(struct _SPTGttab));
	n->_print = (_PTGProc)_PrPTGttab;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern ntab */

typedef struct _SPTGntab{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGntab;

#ifdef PROTO_OK
static void _PrPTGntab(_PPTGntab n)
#else
static void _PrPTGntab(n)
	_PPTGntab n;
#endif
{
	PTG_OUTPUT_STRING(f, "N_TAB ");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGntab(PTGNode p1)
#else
PTGNode PTGntab(p1)

PTGNode p1;
#endif
{
	_PPTGntab n;
	n = (_PPTGntab)MALLOC(sizeof(struct _SPTGntab));
	n->_print = (_PTGProc)_PrPTGntab;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern mode_gcsa */

typedef struct _SPTGmode_gcsa{
	_PTGProc _print;
} * _PPTGmode_gcsa;

#ifdef PROTO_OK
static void _PrPTGmode_gcsa(_PPTGmode_gcsa n)
#else
static void _PrPTGmode_gcsa(n)
	_PPTGmode_gcsa n;
#endif
{
	PTG_OUTPUT_STRING(f, "GCSA");
}

static struct _SPTGmode_gcsa _sptgmode_gcsa = { (_PTGProc) _PrPTGmode_gcsa };

#ifdef PROTO_OK
PTGNode PTGmode_gcsa(void)
#else
PTGNode PTGmode_gcsa()
#endif
{
	return (PTGNode)(&_sptgmode_gcsa);
}


/* Implementation of Pattern mode_gcsb */

typedef struct _SPTGmode_gcsb{
	_PTGProc _print;
} * _PPTGmode_gcsb;

#ifdef PROTO_OK
static void _PrPTGmode_gcsb(_PPTGmode_gcsb n)
#else
static void _PrPTGmode_gcsb(n)
	_PPTGmode_gcsb n;
#endif
{
	PTG_OUTPUT_STRING(f, "GCSB");
}

static struct _SPTGmode_gcsb _sptgmode_gcsb = { (_PTGProc) _PrPTGmode_gcsb };

#ifdef PROTO_OK
PTGNode PTGmode_gcsb(void)
#else
PTGNode PTGmode_gcsb()
#endif
{
	return (PTGNode)(&_sptgmode_gcsb);
}


/* Implementation of Pattern mode_lesa */

typedef struct _SPTGmode_lesa{
	_PTGProc _print;
} * _PPTGmode_lesa;

#ifdef PROTO_OK
static void _PrPTGmode_lesa(_PPTGmode_lesa n)
#else
static void _PrPTGmode_lesa(n)
	_PPTGmode_lesa n;
#endif
{
	PTG_OUTPUT_STRING(f, "LESA");
}

static struct _SPTGmode_lesa _sptgmode_lesa = { (_PTGProc) _PrPTGmode_lesa };

#ifdef PROTO_OK
PTGNode PTGmode_lesa(void)
#else
PTGNode PTGmode_lesa()
#endif
{
	return (PTGNode)(&_sptgmode_lesa);
}


/* Implementation of Pattern mode_lesb */

typedef struct _SPTGmode_lesb{
	_PTGProc _print;
} * _PPTGmode_lesb;

#ifdef PROTO_OK
static void _PrPTGmode_lesb(_PPTGmode_lesb n)
#else
static void _PrPTGmode_lesb(n)
	_PPTGmode_lesb n;
#endif
{
	PTG_OUTPUT_STRING(f, "LESB");
}

static struct _SPTGmode_lesb _sptgmode_lesb = { (_PTGProc) _PrPTGmode_lesb };

#ifdef PROTO_OK
PTGNode PTGmode_lesb(void)
#else
PTGNode PTGmode_lesb()
#endif
{
	return (PTGNode)(&_sptgmode_lesb);
}


/* Implementation of Pattern mode_rcsa */

typedef struct _SPTGmode_rcsa{
	_PTGProc _print;
} * _PPTGmode_rcsa;

#ifdef PROTO_OK
static void _PrPTGmode_rcsa(_PPTGmode_rcsa n)
#else
static void _PrPTGmode_rcsa(n)
	_PPTGmode_rcsa n;
#endif
{
	PTG_OUTPUT_STRING(f, "RCSA");
}

static struct _SPTGmode_rcsa _sptgmode_rcsa = { (_PTGProc) _PrPTGmode_rcsa };

#ifdef PROTO_OK
PTGNode PTGmode_rcsa(void)
#else
PTGNode PTGmode_rcsa()
#endif
{
	return (PTGNode)(&_sptgmode_rcsa);
}


/* Implementation of Pattern mode_rcsb */

typedef struct _SPTGmode_rcsb{
	_PTGProc _print;
} * _PPTGmode_rcsb;

#ifdef PROTO_OK
static void _PrPTGmode_rcsb(_PPTGmode_rcsb n)
#else
static void _PrPTGmode_rcsb(n)
	_PPTGmode_rcsb n;
#endif
{
	PTG_OUTPUT_STRING(f, "RCSB");
}

static struct _SPTGmode_rcsb _sptgmode_rcsb = { (_PTGProc) _PrPTGmode_rcsb };

#ifdef PROTO_OK
PTGNode PTGmode_rcsb(void)
#else
PTGNode PTGmode_rcsb()
#endif
{
	return (PTGNode)(&_sptgmode_rcsb);
}


/* Implementation of Pattern mode_sds */

typedef struct _SPTGmode_sds{
	_PTGProc _print;
} * _PPTGmode_sds;

#ifdef PROTO_OK
static void _PrPTGmode_sds(_PPTGmode_sds n)
#else
static void _PrPTGmode_sds(n)
	_PPTGmode_sds n;
#endif
{
	PTG_OUTPUT_STRING(f, "SDS");
}

static struct _SPTGmode_sds _sptgmode_sds = { (_PTGProc) _PrPTGmode_sds };

#ifdef PROTO_OK
PTGNode PTGmode_sds(void)
#else
PTGNode PTGmode_sds()
#endif
{
	return (PTGNode)(&_sptgmode_sds);
}


/* Implementation of Pattern mode_rds */

typedef struct _SPTGmode_rds{
	_PTGProc _print;
} * _PPTGmode_rds;

#ifdef PROTO_OK
static void _PrPTGmode_rds(_PPTGmode_rds n)
#else
static void _PrPTGmode_rds(n)
	_PPTGmode_rds n;
#endif
{
	PTG_OUTPUT_STRING(f, "RDS");
}

static struct _SPTGmode_rds _sptgmode_rds = { (_PTGProc) _PrPTGmode_rds };

#ifdef PROTO_OK
PTGNode PTGmode_rds(void)
#else
PTGNode PTGmode_rds()
#endif
{
	return (PTGNode)(&_sptgmode_rds);
}


/* Implementation of Pattern line */

typedef struct _SPTGline{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGline;

#ifdef PROTO_OK
static void _PrPTGline(_PPTGline n)
#else
static void _PrPTGline(n)
	_PPTGline n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n");
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGline(PTGNode p1, PTGNode p2)
#else
PTGNode PTGline(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGline n;
	n = (_PPTGline)MALLOC(sizeof(struct _SPTGline));
	n->_print = (_PTGProc)_PrPTGline;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern info */

typedef struct _SPTGinfo{
	_PTGProc _print;
} * _PPTGinfo;

#ifdef PROTO_OK
static void _PrPTGinfo(_PPTGinfo n)
#else
static void _PrPTGinfo(n)
	_PPTGinfo n;
#endif
{
	PTG_OUTPUT_STRING(f, "ALL_STATES");
}

static struct _SPTGinfo _sptginfo = { (_PTGProc) _PrPTGinfo };

#ifdef PROTO_OK
PTGNode PTGinfo(void)
#else
PTGNode PTGinfo()
#endif
{
	return (PTGNode)(&_sptginfo);
}


/* Implementation of Pattern freepos */

typedef struct _SPTGfreepos{
	_PTGProc _print;
} * _PPTGfreepos;

#ifdef PROTO_OK
static void _PrPTGfreepos(_PPTGfreepos n)
#else
static void _PrPTGfreepos(n)
	_PPTGfreepos n;
#endif
{
	PTG_OUTPUT_STRING(f, "FREE_POS");
}

static struct _SPTGfreepos _sptgfreepos = { (_PTGProc) _PrPTGfreepos };

#ifdef PROTO_OK
PTGNode PTGfreepos(void)
#else
PTGNode PTGfreepos()
#endif
{
	return (PTGNode)(&_sptgfreepos);
}


/* Implementation of Pattern aecfile */

typedef struct _SPTGaecfile{
	_PTGProc _print;
} * _PPTGaecfile;

#ifdef PROTO_OK
static void _PrPTGaecfile(_PPTGaecfile n)
#else
static void _PrPTGaecfile(n)
	_PPTGaecfile n;
#endif
{
	PTG_OUTPUT_STRING(f, "#ifndef _ERROR_OFF\n");
	PTG_OUTPUT_STRING(f, "#define _ERROR_OFF\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
}

static struct _SPTGaecfile _sptgaecfile = { (_PTGProc) _PrPTGaecfile };

#ifdef PROTO_OK
PTGNode PTGaecfile(void)
#else
PTGNode PTGaecfile()
#endif
{
	return (PTGNode)(&_sptgaecfile);
}

/* ============================ */

/* -------------------------------------------------------- */
/*                  Default Output Functions                */
/* -------------------------------------------------------- */


#ifdef PROTO_OK
void _PTGPrintInt(PTG_OUTPUT_FILE file, int param)
#else
void _PTGPrintInt(file, param)
       PTG_OUTPUT_FILE file; int param;
#endif
{    /* used for short and int */
       sprintf(buffer,"%d",param);
       PTG_OUTPUT_STRING(file,buffer);
}

#ifdef PROTO_OK
void _PTGPrintLong(PTG_OUTPUT_FILE file, long param)
#else
void _PTGPrintLong(file, param)
       PTG_OUTPUT_FILE file; long param;
#endif
{
       sprintf(buffer,"%ld",param);
       PTG_OUTPUT_STRING(file,buffer);
}

#ifdef PROTO_OK
void _PTGPrintDouble(PTG_OUTPUT_FILE file, double param)
#else
void _PTGPrintDouble(file, param)
       PTG_OUTPUT_FILE file; double param;
#endif
{    /* used for float and double */
       sprintf(buffer,"%g",param);
       PTG_OUTPUT_STRING(file,buffer);
}

#ifdef PROTO_OK
void _PTGPrintChar(PTG_OUTPUT_FILE file, char param)
#else
void _PTGPrintChar(file, param)
       PTG_OUTPUT_FILE file; char param;
#endif
{
       buffer[0] = param;
       buffer[1] = 0;
       PTG_OUTPUT_STRING(file,buffer);
}

