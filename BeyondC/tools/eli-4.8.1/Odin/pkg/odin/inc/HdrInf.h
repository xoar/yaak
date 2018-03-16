#ifndef TPS_HDRINF
#define TPS_HDRINF

/* VerifyDate for SrcFilHdr when Verify is when HFS last checked */
/* TransStatus is the minimum status of all element files */
/* TransModDate is the maximum mod. date of all element files */

typedef struct _tps_HdrInf {
   tp_LocHdr LocHdr;
   tp_LocHdr Father, Brother, Son;

   tp_FKind FKind;
   int IFilTyp;
   tp_LocStr LocIdent;
   tp_LocPrm LocPrm;
   tp_LocInp LocInp;
   int DataNum;

   tp_LocElm LocElm;
   tp_LocElm OldLocElm;
   tp_LocElm TgtValLocElm;

   tp_LocInp InpLink;
   tp_LocElm ElmLink;

   tp_Status Status;
   tp_Status ElmNameStatus;
   tp_Status ElmStatus;
   int ErrStatusWord;

   int SysModTime;
   tp_Date ModDate;
   tp_Date ElmNameModDate;
   tp_Date ElmModDate;
   tp_Date ConfirmDate;
   tp_Date ElmNameConfirmDate;
   tp_Date ElmConfirmDate;
   tp_Date VerifyDate;
   tp_Date ElmNameVerifyDate;
   tp_Date ElmVerifyDate;

   int Size;

   tp_LocHdr OrigLocHdr;
   tp_Date OrigModDate;

   tp_LocHdr AliasLocHdr;
   }				tps_HdrInf;

#endif
