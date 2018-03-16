#ifndef TPS_NOD
#define TPS_NOD


typedef struct _tps_Nod {
   tp_NodTyp NodTyp;
   tp_Sym Sym;
   tp_Nod Brother;
   tp_Nod Son;
   }				tps_Nod;

#endif
