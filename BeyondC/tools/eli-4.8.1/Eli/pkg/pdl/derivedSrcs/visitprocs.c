
#include "HEAD.h"
#include "err.h"
#include "node.h"
#include "visitprocs.h"
#include "attrpredef.h"

#include "visitmap.h"

#ifdef MONITOR
#include "attr_mon_dapto.h"
#include "liga_dapto.h"
#endif

#ifndef _VisitVarDecl
#define _VisitVarDecl()
#endif

#ifndef _VisitEntry
#define _VisitEntry()
#endif

#ifndef _VisitExit
#define _VisitExit()
#endif


#if defined(__STDC__) || defined(__cplusplus)
#define _CALL_VS_(args) (void (*)args)
#else
#define _CALL_VS_(args) 
#endif
PTGNode* _IG_incl14;
PTGNode* _IG_incl15;
DefTableKey* _IG_incl12;
funclist* _IG_incl13;
Environment* _IG_incl11;
Environment* _IG_incl8;
Environment* _IG_incl7;
DefTableKey* _IG_incl1;
Environment* _IG_incl3;
Environment* _IG_incl0;
PTGNode _AVG2__const19;
int _AVG1ElementNum_pre;
PTGNode _AVG1__const8;
PTGNode _AVG1__const9;
PTGNode _AVG1__const10;
PTGNode _AVG1__const11;
PTGNode _AVG1__const12;
PTGNode _AVG1__const13;
PTGNode _AVG1__const14;
PTGNode _AVG1__const15;
PTGNode _AVG1__const18;
PTGNode _AVG1__const19;
int _AVG1KeyIndex_post;
PTGNode _AVG1fileout_post;
PTGNode _AVPropertyValueList__const19;
int _AVPropertyValueElementNum_pre;
Binding _AVPropertyValue_KnownKeyBind;
PTGNode _AVPropertyValue_Element;
int _AVPropertyValue_Sym;
DefTableKey _AVPropertyValue_Key;
PTGNode _AVKnownKey__const19;
Binding _AVKnownKey_KnownKeyBind;
int _AVKnownKey_IsKnownKeyFirstOcc;
PTGNode _AVKnownKey_Array;
PTGNode _AVKnownKey_Define;
int _AVKnownKey_Sym;
PTGNode _AVPropertyValues__const19;
PTGNode _AVFileDecl__const15;
PTGNode _AVFileDecl__const18;
PTGNode _AVFileDecl__const19;
PTGNode _AVParameterTypeDecl_out;
PTGNode _AVModifier_out;
PTGNode _AVParameterDecl_extout;
PTGNode _AVParameterDecl_formallist;
PTGNode _AVParameterDecl_arglist;
PTGNode _AVParameterDecl_declout;
PTGNode _AVParameterDecl_out;
funclist _AVOperationNameDeclfunc_post;
DefTableKey _AVType__const1;
PTGNode _AVType__const2;
PTGNode _AVType__const3;
PTGNode _AVType_extout;
funclist _AVType_functions;
PTGNode _AVType_funcout;
PTGNode _AVPropertyNameList__const9;
PTGNode _AVPropertyNameList__const10;
PTGNode _AVPropertyNameList__const11;
PTGNode _AVPropertyNameList__const13;
PTGNode _AVPropertyNameList__const14;
PTGNode _AVPropertyDecl__const8;
PTGNode _AVPropertyDecl__const9;
PTGNode _AVPropertyDecl__const10;
PTGNode _AVPropertyDecl__const11;
PTGNode _AVPropertyDecl__const12;
PTGNode _AVPropertyDecl__const13;
PTGNode _AVPropertyDecl__const14;
DefTableKey _AVOperationNameDecl_key;
PTGNode _AVParameterList_extout;
PTGNode _AVParameterList_formallist;
PTGNode _AVParameterList_arglist;
PTGNode _AVParameterList_declout;
PTGNode _AVParameterList_out;
PTGNode _AVTypeSpecifier_type;
PTGNode _AVTypeSpecifier_typeid;
DefTableKey _AVTypeSpecifier_TypeKey;
ExtOutput _AVOperationDecl_extstruct;
PTGNode _AVOperationDecl_formallist;
PTGNode _AVOperationDecl_arglist;
OpOutput _AVOperationDecl_opout;
int _AVPropertyNameDecl_first_RuleAttr_87;
PTGNode _AVPropertyNameDecl_CloneCase;
PTGNode _AVPropertyNameDecl_macroout;
PTGNode _AVPropertyNameDecl_switch;
PTGNode _AVPropertyNameDecl_type;
PTGNode _AVPropertyNameDecl_name;
PTGNode _AVRange__const8;
PTGNode _AVRange__const9;
PTGNode _AVRange__const10;
PTGNode _AVRange__const11;
PTGNode _AVRange__const12;
PTGNode _AVRange__const13;
PTGNode _AVRange__const14;
PTGNode _AVRange__const15;
PTGNode _AVRange__const18;
PTGNode _AVRange__const19;
PTGNode _AVSource_ArrayElts;
PTGNode _AVSource_Define;
PTGNode _AVSource_macroout;
PTGNode _AVSource_extout;
PTGNode _AVSource_CloneKey;
PTGNode _AVSource_Array;
PTGNode _AVSource_Element;
PTGNode _AVSource_mon;
PTGNode _AVSource_funcout;

#if defined(__STDC__) || defined(__cplusplus)
void LIGA_ATTREVAL (NODEPTR _currn)
#else
void LIGA_ATTREVAL (_currn) NODEPTR _currn;
#endif
{(*(VS1MAP[_currn->_prod])) ((NODEPTR)_currn);}
/*SPC(0)*/

#if defined(__STDC__) || defined(__cplusplus)
void _VS0Empty(NODEPTR _currn)
#else
void _VS0Empty(_currn) NODEPTR _currn;
#endif
{ _VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_1(_TPPrule_1 _currn)
#else
void _VS1rule_1(_currn )
_TPPrule_1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVG1ElementNum_pre=ADD(_AVPropertyValueElementNum_pre, 1);
/*SPC(544)*/
_AVPropertyValue_Sym=_currn->_ATTERM_1;
/*SPC(513)*/
_AVPropertyValue_Key=KeyInEnv((* _IG_incl0), _currn->_ATTERM_1);
/*SPC(514)*/
_AVPropertyValue_KnownKeyBind=BindIdn((* _IG_incl3), _AVPropertyValue_Sym);
/*SPC(677)*/
_currn->_ATKnownKeyKey=KeyOf(_AVPropertyValue_KnownKeyBind);
/*SPC(679)*/
ListInsertValueList((* _IG_incl1), CreateElement(GetSelector(_AVPropertyValue_Key, 0), PTGElementName(PTGNum(_AVPropertyValueElementNum_pre)), GetTypeName(GetType(_AVPropertyValue_Key, NoKey), PTGNULL), _currn->_ATTERM_2));
/*SPC(546)*/
IsText(_currn->_ATKnownKeyKey, _currn->_ATTERM_2, 0);
/*SPC(537)*/

if (NE(GetKind(_AVPropertyValue_Key, Undefined), PropertyClass)) {
message(ERROR, "Undefined property", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(490)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_1(_TPPrule_1 _currn)
#else
void _VS2rule_1(_currn )
_TPPrule_1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (AND(HasText(_currn->_ATKnownKeyKey), NOT(GetText(_currn->_ATKnownKeyKey, 0)))) {
message(ERROR, "More than one initializer for the same property", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(542)*/
_AVPropertyValue_Element=
((GetElementDone((* _IG_incl1), 0)
) ? (PTGNULL
) : (
(ResetElementDone((* _IG_incl1), 1), GenElements(GetValueList((* _IG_incl1), NULLElementList)))
))
;
/*SPC(555)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_2(_TPPrule_2 _currn)
#else
void _VS1rule_2(_currn )
_TPPrule_2 _currn;

#endif
{
DefTableKey* _IL_incl1;

_VisitVarDecl()
_VisitEntry();
_IL_incl1=_IG_incl1;_IG_incl1= &(_currn->_ATKnownKeyKey);
_AVKnownKey_Sym=_currn->_ATTERM_1;
/*SPC(498)*/
_AVKnownKey_KnownKeyBind=BindIdn((* _IG_incl3), _AVKnownKey_Sym);
/*SPC(677)*/
_currn->_ATKnownKeyKey=KeyOf(_AVKnownKey_KnownKeyBind);
/*SPC(679)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl1=_IL_incl1;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_2(_TPPrule_2 _currn)
#else
void _VS2rule_2(_currn )
_TPPrule_2 _currn;

#endif
{
DefTableKey* _IL_incl1;

_VisitVarDecl()
_VisitEntry();
_IL_incl1=_IG_incl1;_IG_incl1= &(_currn->_ATKnownKeyKey);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVKnownKey__const19=_AVPropertyValueList__const19;
/*SPC(496)*/
_IG_incl1=_IL_incl1;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_2(_TPPrule_2 _currn)
#else
void _VS3rule_2(_currn )
_TPPrule_2 _currn;

#endif
{
DefTableKey* _IL_incl1;

_VisitVarDecl()
_VisitEntry();
_IL_incl1=_IG_incl1;_IG_incl1= &(_currn->_ATKnownKeyKey);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVKnownKey_IsKnownKeyFirstOcc=SetGetKnownKeyFirstOcc(_currn->_ATKnownKeyKey, 1, 0);
/*SPC(746)*/
_AVKnownKey_Array=
((_AVKnownKey_IsKnownKeyFirstOcc
) ? (PTGArrayElt(FirstValueList(_currn->_ATKnownKeyKey))
) : (PTGNULL))
;
/*SPC(598)*/
_AVKnownKey_Define=
((_AVKnownKey_IsKnownKeyFirstOcc
) ? (PTGDefine(PTGIdentifier(_currn->_ATTERM_1), PTGNum(_AVG1KeyIndex_post))
) : (PTGNULL))
;
/*SPC(590)*/
_AVG1KeyIndex_post=
((_AVKnownKey_IsKnownKeyFirstOcc
) ? (ADD(_AVG1KeyIndex_post, 1)
) : (_AVG1KeyIndex_post))
;
/*SPC(594)*/
_IG_incl1=_IL_incl1;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_016(_TPPrule_016 _currn)
#else
void _VS1rule_016(_currn )
_TPPrule_016 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_016(_TPPrule_016 _currn)
#else
void _VS2rule_016(_currn )
_TPPrule_016 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_016(_TPPrule_016 _currn)
#else
void _VS3rule_016(_currn )
_TPPrule_016 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRange__const8=_AVG1__const8;
/*SPC(816)*/
_AVRange__const13=_AVG1__const13;
/*SPC(816)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_016(_TPPrule_016 _currn)
#else
void _VS4rule_016(_currn )
_TPPrule_016 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_016(_TPPrule_016 _currn)
#else
void _VS5rule_016(_currn )
_TPPrule_016 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRange__const19=_AVG1__const19;
/*SPC(816)*/
_AVG1ElementNum_pre=_currn->_desc1->_ATElementNum_post;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6rule_016(_TPPrule_016 _currn)
#else
void _VS6rule_016(_currn )
_TPPrule_016 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS6MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRange__const9=_AVG1__const9;
/*SPC(816)*/
_AVRange__const10=_AVG1__const10;
/*SPC(816)*/
_AVRange__const11=_AVG1__const11;
/*SPC(816)*/
_AVRange__const12=_AVG1__const12;
/*SPC(816)*/
_AVRange__const14=_AVG1__const14;
/*SPC(816)*/
_AVRange__const15=_AVG1__const15;
/*SPC(816)*/
_AVRange__const18=_AVG1__const18;
/*SPC(816)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_015(_TPPrule_015 _currn)
#else
void _VS1rule_015(_currn )
_TPPrule_015 _currn;

#endif
{
Environment* _IL_incl3;

_VisitVarDecl()
_VisitEntry();
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATKnownKeyEnv);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl3=_IL_incl3;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_015(_TPPrule_015 _currn)
#else
void _VS2rule_015(_currn )
_TPPrule_015 _currn;

#endif
{
Environment* _IL_incl3;

_VisitVarDecl()
_VisitEntry();
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATKnownKeyEnv);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVPropertyValues__const19=_AVG2__const19;
/*SPC(812)*/
_IG_incl3=_IL_incl3;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_015(_TPPrule_015 _currn)
#else
void _VS3rule_015(_currn )
_TPPrule_015 _currn;

#endif
{
Environment* _IL_incl3;

_VisitVarDecl()
_VisitEntry();
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATKnownKeyEnv);
_IG_incl3=_IL_incl3;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_014(_TPPrule_014 _currn)
#else
void _VS1rule_014(_currn )
_TPPrule_014 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATKnownKeyEnv=
(
((EQ(GetEnv((* _IG_incl1), NoEnv), NoEnv)
) ? ((ResetEnv((* _IG_incl1), NewScope((* _IG_incl7))), 0)
) : ((0)))
, GetEnv((* _IG_incl1), NoEnv))
;
/*SPC(502)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_014(_TPPrule_014 _currn)
#else
void _VS2rule_014(_currn )
_TPPrule_014 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVPropertyValueList__const19=_AVPropertyValues__const19;
/*SPC(808)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_014(_TPPrule_014 _currn)
#else
void _VS3rule_014(_currn )
_TPPrule_014 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_013(_TPPrule_013 _currn)
#else
void _VS2rule_013(_currn )
_TPPrule_013 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVPropertyValueList__const19=PTGNull();
/*SPC(804)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_012(_TPPrule_012 _currn)
#else
void _VS1rule_012(_currn )
_TPPrule_012 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_012(_TPPrule_012 _currn)
#else
void _VS2rule_012(_currn )
_TPPrule_012 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVPropertyNameList__const13=concatptgnode(_AVPropertyNameList__const13, creatptgnode(_AVPropertyNameDecl_macroout));
/*SPC(800)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_012(_TPPrule_012 _currn)
#else
void _VS3rule_012(_currn )
_TPPrule_012 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVPropertyNameList__const9=concatptgnode(_AVPropertyNameList__const9, creatptgnode(_AVPropertyNameDecl_name));
/*SPC(800)*/
_AVPropertyNameList__const10=concatptgnode(_AVPropertyNameList__const10, creatptgnode(_AVPropertyNameDecl_type));
/*SPC(800)*/
_AVPropertyNameList__const11=concatptgnode(_AVPropertyNameList__const11, creatptgnode(_AVPropertyNameDecl_switch));
/*SPC(800)*/
_AVPropertyNameList__const14=PTGSeq(_AVPropertyNameList__const14, IDENTICAL(_AVPropertyNameDecl_CloneCase));
/*SPC(800)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_011(_TPPrule_011 _currn)
#else
void _VS2rule_011(_currn )
_TPPrule_011 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVPropertyNameList__const13=creatptgnode(_AVPropertyNameDecl_macroout);
/*SPC(796)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_011(_TPPrule_011 _currn)
#else
void _VS3rule_011(_currn )
_TPPrule_011 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVPropertyNameList__const9=creatptgnode(_AVPropertyNameDecl_name);
/*SPC(796)*/
_AVPropertyNameList__const10=creatptgnode(_AVPropertyNameDecl_type);
/*SPC(796)*/
_AVPropertyNameList__const11=creatptgnode(_AVPropertyNameDecl_switch);
/*SPC(796)*/
_AVPropertyNameList__const14=IDENTICAL(_AVPropertyNameDecl_CloneCase);
/*SPC(796)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_008(_TPPrule_008 _currn)
#else
void _VS1rule_008(_currn )
_TPPrule_008 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_008(_TPPrule_008 _currn)
#else
void _VS2rule_008(_currn )
_TPPrule_008 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_007(_TPPrule_007 _currn)
#else
void _VS1rule_007(_currn )
_TPPrule_007 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_006(_TPPrule_006 _currn)
#else
void _VS1rule_006(_currn )
_TPPrule_006 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVPropertyValueElementNum_pre=_AVG1ElementNum_pre;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_006(_TPPrule_006 _currn)
#else
void _VS2rule_006(_currn )
_TPPrule_006 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVG2__const19=IDENTICAL(_AVPropertyValue_Element);
/*SPC(776)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_005(_TPPrule_005 _currn)
#else
void _VS1rule_005(_currn )
_TPPrule_005 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVPropertyValueElementNum_pre=_AVG1ElementNum_pre;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_005(_TPPrule_005 _currn)
#else
void _VS2rule_005(_currn )
_TPPrule_005 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVG2__const19=PTGSeq(_AVG2__const19, IDENTICAL(_AVPropertyValue_Element));
/*SPC(772)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_004(_TPPrule_004 _currn)
#else
void _VS1rule_004(_currn )
_TPPrule_004 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_004(_TPPrule_004 _currn)
#else
void _VS2rule_004(_currn )
_TPPrule_004 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_004(_TPPrule_004 _currn)
#else
void _VS3rule_004(_currn )
_TPPrule_004 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVG1__const8=concatptgnode(_AVG1__const8, _AVPropertyDecl__const8);
/*SPC(768)*/
_AVG1__const13=concatptgnode(_AVG1__const13, _AVPropertyDecl__const13);
/*SPC(768)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_004(_TPPrule_004 _currn)
#else
void _VS4rule_004(_currn )
_TPPrule_004 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATElementNum_post=_currn->_desc1->_ATElementNum_post;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_004(_TPPrule_004 _currn)
#else
void _VS5rule_004(_currn )
_TPPrule_004 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVG1__const19=_AVG1__const19;
/*SPC(768)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6rule_004(_TPPrule_004 _currn)
#else
void _VS6rule_004(_currn )
_TPPrule_004 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS6MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVG1__const9=concatptgnode(_AVG1__const9, _AVPropertyDecl__const9);
/*SPC(768)*/
_AVG1__const10=concatptgnode(_AVG1__const10, _AVPropertyDecl__const10);
/*SPC(768)*/
_AVG1__const11=concatptgnode(_AVG1__const11, _AVPropertyDecl__const11);
/*SPC(768)*/
_AVG1__const12=concatptgnode(_AVG1__const12, _AVPropertyDecl__const12);
/*SPC(768)*/
_AVG1__const14=PTGSeq(_AVG1__const14, _AVPropertyDecl__const14);
/*SPC(768)*/
_AVG1__const15=_AVG1__const15;
/*SPC(768)*/
_AVG1__const18=_AVG1__const18;
/*SPC(768)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_003(_TPPrule_003 _currn)
#else
void _VS1rule_003(_currn )
_TPPrule_003 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_003(_TPPrule_003 _currn)
#else
void _VS2rule_003(_currn )
_TPPrule_003 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_003(_TPPrule_003 _currn)
#else
void _VS3rule_003(_currn )
_TPPrule_003 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVG1__const8=_AVG1__const8;
/*SPC(764)*/
_AVG1__const13=_AVG1__const13;
/*SPC(764)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_003(_TPPrule_003 _currn)
#else
void _VS4rule_003(_currn )
_TPPrule_003 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATElementNum_post=_currn->_desc1->_ATElementNum_post;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_003(_TPPrule_003 _currn)
#else
void _VS5rule_003(_currn )
_TPPrule_003 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVG1__const19=_AVG1__const19;
/*SPC(764)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6rule_003(_TPPrule_003 _currn)
#else
void _VS6rule_003(_currn )
_TPPrule_003 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS6MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVG1__const9=_AVG1__const9;
/*SPC(764)*/
_AVG1__const10=_AVG1__const10;
/*SPC(764)*/
_AVG1__const11=_AVG1__const11;
/*SPC(764)*/
_AVG1__const12=_AVG1__const12;
/*SPC(764)*/
_AVG1__const14=_AVG1__const14;
/*SPC(764)*/
_AVG1__const15=_AVG1__const15;
/*SPC(764)*/
_AVG1__const18=_AVG1__const18;
/*SPC(764)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_002(_TPPrule_002 _currn)
#else
void _VS1rule_002(_currn )
_TPPrule_002 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_002(_TPPrule_002 _currn)
#else
void _VS2rule_002(_currn )
_TPPrule_002 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_002(_TPPrule_002 _currn)
#else
void _VS3rule_002(_currn )
_TPPrule_002 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVG1__const8=_AVG1__const8;
/*SPC(760)*/
_AVG1__const13=_AVG1__const13;
/*SPC(760)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_002(_TPPrule_002 _currn)
#else
void _VS4rule_002(_currn )
_TPPrule_002 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVG1ElementNum_pre=_currn->_desc1->_ATElementNum_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_ATElementNum_post=_AVG1ElementNum_pre;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_002(_TPPrule_002 _currn)
#else
void _VS5rule_002(_currn )
_TPPrule_002 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVG1__const19=PTGSeq(_AVG1__const19, _AVFileDecl__const19);
/*SPC(760)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6rule_002(_TPPrule_002 _currn)
#else
void _VS6rule_002(_currn )
_TPPrule_002 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS6MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVG1__const9=_AVG1__const9;
/*SPC(760)*/
_AVG1__const10=_AVG1__const10;
/*SPC(760)*/
_AVG1__const11=_AVG1__const11;
/*SPC(760)*/
_AVG1__const12=_AVG1__const12;
/*SPC(760)*/
_AVG1__const14=_AVG1__const14;
/*SPC(760)*/
_AVG1__const15=PTGARRAYSEQ(_AVG1__const15, _AVFileDecl__const15);
/*SPC(760)*/
_AVG1__const18=PTGSeq(_AVG1__const18, _AVFileDecl__const18);
/*SPC(760)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_001(_TPPrule_001 _currn)
#else
void _VS3rule_001(_currn )
_TPPrule_001 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVG1__const8=nullptgnode();
/*SPC(756)*/
_AVG1__const13=nullptgnode();
/*SPC(756)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_001(_TPPrule_001 _currn)
#else
void _VS4rule_001(_currn )
_TPPrule_001 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATElementNum_post=_AVG1ElementNum_pre;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_001(_TPPrule_001 _currn)
#else
void _VS5rule_001(_currn )
_TPPrule_001 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVG1__const19=PTGNull();
/*SPC(756)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6rule_001(_TPPrule_001 _currn)
#else
void _VS6rule_001(_currn )
_TPPrule_001 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVG1__const9=nullptgnode();
/*SPC(756)*/
_AVG1__const10=nullptgnode();
/*SPC(756)*/
_AVG1__const11=nullptgnode();
/*SPC(756)*/
_AVG1__const12=nullptgnode();
/*SPC(756)*/
_AVG1__const14=PTGNull();
/*SPC(756)*/
_AVG1__const15=PTGNull();
/*SPC(756)*/
_AVG1__const18=PTGNull();
/*SPC(756)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_000(_TPPrule_000 _currn)
#else
void _VS1rule_000(_currn )
_TPPrule_000 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_000(_TPPrule_000 _currn)
#else
void _VS2rule_000(_currn )
_TPPrule_000 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVFileDecl__const19=_AVKnownKey__const19;
/*SPC(752)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_000(_TPPrule_000 _currn)
#else
void _VS3rule_000(_currn )
_TPPrule_000 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVFileDecl__const15=IDENTICAL(_AVKnownKey_Array);
/*SPC(752)*/
_AVFileDecl__const18=IDENTICAL(_AVKnownKey_Define);
/*SPC(752)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1FileSpec(_TPPFileSpec _currn)
#else
void _VS1FileSpec(_currn )
_TPPFileSpec _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2FileSpec(_TPPFileSpec _currn)
#else
void _VS2FileSpec(_currn )
_TPPFileSpec _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVFileDecl__const19=PTGNull();
/*SPC(418)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3FileSpec(_TPPFileSpec _currn)
#else
void _VS3FileSpec(_currn )
_TPPFileSpec _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVFileDecl__const15=PTGNull();
/*SPC(418)*/
_AVFileDecl__const18=PTGNull();
/*SPC(418)*/
_AVG1fileout_post=PTGSeq(_AVG1fileout_post, PTGInclude(PTGIdentifier(_currn->_ATTERM_1)));
/*SPC(421)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1IdentParameterTS(_TPPIdentParameterTS _currn)
#else
void _VS1IdentParameterTS(_currn )
_TPPIdentParameterTS _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVParameterTypeDecl_out=PTGIPTypeSpec(_AS1out, PTGIdentifier(_currn->_ATTERM_1), _AVModifier_out);
/*SPC(384)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2IdentParameterTS(_TPPIdentParameterTS _currn)
#else
void _VS2IdentParameterTS(_currn )
_TPPIdentParameterTS _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3IdentParameterTS(_TPPIdentParameterTS _currn)
#else
void _VS3IdentParameterTS(_currn )
_TPPIdentParameterTS _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1ParameterTypeSpec(_TPPParameterTypeSpec _currn)
#else
void _VS1ParameterTypeSpec(_currn )
_TPPParameterTypeSpec _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVParameterTypeDecl_out=PTGPTypeSpec(_AS1out, _AVModifier_out);
/*SPC(379)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2ParameterTypeSpec(_TPPParameterTypeSpec _currn)
#else
void _VS2ParameterTypeSpec(_currn )
_TPPParameterTypeSpec _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3ParameterTypeSpec(_TPPParameterTypeSpec _currn)
#else
void _VS3ParameterTypeSpec(_currn )
_TPPParameterTypeSpec _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1SingleParameterType(_TPPSingleParameterType _currn,PTGNode* _AS0out)
#else
void _VS1SingleParameterType(_currn ,_AS0out)
_TPPSingleParameterType _currn;
PTGNode* _AS0out;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(* _AS0out)=_AVParameterTypeDecl_out;
/*SPC(374)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2SingleParameterType(_TPPSingleParameterType _currn,PTGNode* _AS0out)
#else
void _VS2SingleParameterType(_currn ,_AS0out)
_TPPSingleParameterType _currn;
PTGNode* _AS0out;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3SingleParameterType(_TPPSingleParameterType _currn,PTGNode* _AS0out)
#else
void _VS3SingleParameterType(_currn ,_AS0out)
_TPPSingleParameterType _currn;
PTGNode* _AS0out;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1MultipleParameterTypes(_TPPMultipleParameterTypes _currn,PTGNode* _AS0out)
#else
void _VS1MultipleParameterTypes(_currn ,_AS0out)
_TPPMultipleParameterTypes _currn;
PTGNode* _AS0out;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(* _AS0out)=PTGCommaSeq(_AS1out, _AVParameterTypeDecl_out);
/*SPC(368)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2MultipleParameterTypes(_TPPMultipleParameterTypes _currn,PTGNode* _AS0out)
#else
void _VS2MultipleParameterTypes(_currn ,_AS0out)
_TPPMultipleParameterTypes _currn;
PTGNode* _AS0out;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3MultipleParameterTypes(_TPPMultipleParameterTypes _currn,PTGNode* _AS0out)
#else
void _VS3MultipleParameterTypes(_currn ,_AS0out)
_TPPMultipleParameterTypes _currn;
PTGNode* _AS0out;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1ExtendedModifier(_TPPExtendedModifier _currn)
#else
void _VS1ExtendedModifier(_currn )
_TPPExtendedModifier _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));
_AVModifier_out=PTGEModifier(_AS1out);
/*SPC(362)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2ExtendedModifier(_TPPExtendedModifier _currn)
#else
void _VS2ExtendedModifier(_currn )
_TPPExtendedModifier _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3ExtendedModifier(_TPPExtendedModifier _currn)
#else
void _VS3ExtendedModifier(_currn )
_TPPExtendedModifier _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1SimpleModifier(_TPPSimpleModifier _currn)
#else
void _VS1SimpleModifier(_currn )
_TPPSimpleModifier _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));
_AVModifier_out=PTGSModifier(_AS1out);
/*SPC(357)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2SimpleModifier(_TPPSimpleModifier _currn)
#else
void _VS2SimpleModifier(_currn )
_TPPSimpleModifier _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3SimpleModifier(_TPPSimpleModifier _currn)
#else
void _VS3SimpleModifier(_currn )
_TPPSimpleModifier _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1VoidModifier(_TPPVoidModifier _currn)
#else
void _VS1VoidModifier(_currn )
_TPPVoidModifier _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVModifier_out=PTGString("()");
/*SPC(352)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1EmptyModifier(_TPPEmptyModifier _currn)
#else
void _VS1EmptyModifier(_currn )
_TPPEmptyModifier _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVModifier_out=PTGNULL;
/*SPC(347)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1ParameterSpec(_TPPParameterSpec _currn)
#else
void _VS1ParameterSpec(_currn )
_TPPParameterSpec _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVParameterDecl_extout=PTGExtParamDecl(_AS1out, PTGIdentifier(_currn->_ATTERM_1), _AVModifier_out);
/*SPC(477)*/
_AVParameterDecl_formallist=PTGParen(PTGIdentifier(_currn->_ATTERM_1));
/*SPC(342)*/
_AVParameterDecl_arglist=PTGIdentifier(_currn->_ATTERM_1);
/*SPC(341)*/
_AVParameterDecl_declout=
((EQ(_AVModifier_out, PTGNULL)
) ? (PTGParamDecl(_AS1out, PTGIdentifier(_currn->_ATTERM_1), PTGNULL)
) : (PTGParamDecl(_AS1out, PTGFuncName(PTGIdentifier(_currn->_ATTERM_1)), _AVModifier_out)))
;
/*SPC(334)*/
_AVParameterDecl_out=PTGIdentifier(_currn->_ATTERM_1);
/*SPC(333)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2ParameterSpec(_TPPParameterSpec _currn)
#else
void _VS2ParameterSpec(_currn )
_TPPParameterSpec _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3ParameterSpec(_TPPParameterSpec _currn)
#else
void _VS3ParameterSpec(_currn )
_TPPParameterSpec _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1SingleParameter(_TPPSingleParameter _currn)
#else
void _VS1SingleParameter(_currn )
_TPPSingleParameter _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVParameterList_extout=_AVParameterDecl_extout;
/*SPC(471)*/
_AVParameterList_formallist=_AVParameterDecl_formallist;
/*SPC(328)*/
_AVParameterList_arglist=_AVParameterDecl_arglist;
/*SPC(327)*/
_AVParameterList_declout=_AVParameterDecl_declout;
/*SPC(326)*/
_AVParameterList_out=_AVParameterDecl_out;
/*SPC(325)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1MultipleParameters(_TPPMultipleParameters _currn)
#else
void _VS1MultipleParameters(_currn )
_TPPMultipleParameters _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVParameterList_extout=PTGCommaSeq(_AVParameterList_extout, _AVParameterDecl_extout);
/*SPC(465)*/
_AVParameterList_formallist=PTGCommaSeq(_AVParameterList_formallist, _AVParameterDecl_formallist);
/*SPC(319)*/
_AVParameterList_arglist=PTGCommaSeq(_AVParameterList_arglist, _AVParameterDecl_arglist);
/*SPC(317)*/
_AVParameterList_declout=PTGSeq(_AVParameterList_declout, _AVParameterDecl_declout);
/*SPC(315)*/
_AVParameterList_out=PTGCommaSeq(_AVParameterList_out, _AVParameterDecl_out);
/*SPC(314)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2MultipleParameters(_TPPMultipleParameters _currn)
#else
void _VS2MultipleParameters(_currn )
_TPPMultipleParameters _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3MultipleParameters(_TPPMultipleParameters _currn)
#else
void _VS3MultipleParameters(_currn )
_TPPMultipleParameters _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1TypeWithOp(_TPPTypeWithOp _currn)
#else
void _VS1TypeWithOp(_currn )
_TPPTypeWithOp _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));
_AVOperationNameDeclfunc_post=nullfunclist();
/*SPC(242)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVType__const1=_AVTypeSpecifier_TypeKey;
/*SPC(226)*/
_AVType_functions=_AVOperationNameDeclfunc_post;
/*SPC(233)*/
addfunclist(_currn->_desc1->_ATkey, _AVType_functions);
/*SPC(230)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2TypeWithOp(_TPPTypeWithOp _currn)
#else
void _VS2TypeWithOp(_currn )
_TPPTypeWithOp _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
_AVType_funcout=GenFunctions(_currn->_desc1->_ATkey, _currn->_desc1->_ATsym, (* _IG_incl8), GetFuncList(_currn->_desc1->_ATkey, dummyfunclist));
/*SPC(236)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3TypeWithOp(_TPPTypeWithOp _currn)
#else
void _VS3TypeWithOp(_currn )
_TPPTypeWithOp _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));
_AVType__const2=_AVTypeSpecifier_typeid;
/*SPC(226)*/
_AVType__const3=_AVTypeSpecifier_type;
/*SPC(226)*/
_AVType_extout=GenExterns(_currn->_desc1->_ATkey, _currn->_desc1->_ATsym, (* _IG_incl8), GetFuncList(_currn->_desc1->_ATkey, dummyfunclist));
/*SPC(448)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1TypeNoOp(_TPPTypeNoOp _currn)
#else
void _VS1TypeNoOp(_currn )
_TPPTypeNoOp _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));
_AVType__const1=_AVTypeSpecifier_TypeKey;
/*SPC(213)*/
_AVType_functions=dummyfunclist;
/*SPC(216)*/
VOIDEN(0);
/*SPC(217)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2TypeNoOp(_TPPTypeNoOp _currn)
#else
void _VS2TypeNoOp(_currn )
_TPPTypeNoOp _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
_AVType_funcout=GenFunctions(_currn->_desc1->_ATkey, _currn->_desc1->_ATsym, (* _IG_incl8), GetFuncList(_currn->_desc1->_ATkey, dummyfunclist));
/*SPC(220)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3TypeNoOp(_TPPTypeNoOp _currn)
#else
void _VS3TypeNoOp(_currn )
_TPPTypeNoOp _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));
_AVType__const2=_AVTypeSpecifier_typeid;
/*SPC(213)*/
_AVType__const3=_AVTypeSpecifier_type;
/*SPC(213)*/
_AVType_extout=GenExterns(_currn->_desc1->_ATkey, _currn->_desc1->_ATsym, (* _IG_incl8), GetFuncList(_currn->_desc1->_ATkey, dummyfunclist));
/*SPC(439)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1PropertySpec(_TPPPropertySpec _currn)
#else
void _VS1PropertySpec(_currn )
_TPPPropertySpec _currn;

#endif
{
DefTableKey* _IL_incl12;
funclist* _IL_incl13;

_VisitVarDecl()
_VisitEntry();
_IL_incl12=_IG_incl12;_IG_incl12= &(_currn->_ATTypeKey);
_IL_incl13=_IG_incl13;_IG_incl13= &(_currn->_ATfunctions);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_ATfunctions=_AVType_functions;
/*SPC(183)*/
_currn->_ATTypeKey=_AVType__const1;
/*SPC(111)*/

if (EQ(_currn->_ATTypeKey, NoKey)) {
message(FATAL, "TYPE is not a valid type specification for a property", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(116)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl12=_IL_incl12;
_IG_incl13=_IL_incl13;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2PropertySpec(_TPPPropertySpec _currn)
#else
void _VS2PropertySpec(_currn )
_TPPPropertySpec _currn;

#endif
{
DefTableKey* _IL_incl12;
funclist* _IL_incl13;

_VisitVarDecl()
_VisitEntry();
_IL_incl12=_IG_incl12;_IG_incl12= &(_currn->_ATTypeKey);
_IL_incl13=_IG_incl13;_IG_incl13= &(_currn->_ATfunctions);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVPropertyDecl__const8=creatptgnode(_AVType_funcout);
/*SPC(109)*/
_AVPropertyDecl__const13=_AVPropertyNameList__const13;
/*SPC(109)*/
_IG_incl12=_IL_incl12;
_IG_incl13=_IL_incl13;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3PropertySpec(_TPPPropertySpec _currn)
#else
void _VS3PropertySpec(_currn )
_TPPPropertySpec _currn;

#endif
{
PTGNode* _IL_incl14;
PTGNode* _IL_incl15;
DefTableKey* _IL_incl12;
funclist* _IL_incl13;

_VisitVarDecl()
_VisitEntry();
_IL_incl14=_IG_incl14;_IG_incl14= &(_currn->_ATtype);
_IL_incl15=_IG_incl15;_IG_incl15= &(_currn->_ATtypeid);
_IL_incl12=_IG_incl12;_IG_incl12= &(_currn->_ATTypeKey);
_IL_incl13=_IG_incl13;_IG_incl13= &(_currn->_ATfunctions);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_ATtype=_AVType__const3;
/*SPC(187)*/
_currn->_ATtypeid=_AVType__const2;
/*SPC(186)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVPropertyDecl__const9=_AVPropertyNameList__const9;
/*SPC(109)*/
_AVPropertyDecl__const10=_AVPropertyNameList__const10;
/*SPC(109)*/
_AVPropertyDecl__const11=_AVPropertyNameList__const11;
/*SPC(109)*/
_AVPropertyDecl__const12=creatptgnode(_AVType_extout);
/*SPC(109)*/
_AVPropertyDecl__const14=_AVPropertyNameList__const14;
/*SPC(109)*/
_IG_incl14=_IL_incl14;
_IG_incl15=_IL_incl15;
_IG_incl12=_IL_incl12;
_IG_incl13=_IL_incl13;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1DefinedType(_TPPDefinedType _currn,PTGNode* _AS0out)
#else
void _VS1DefinedType(_currn ,_AS0out)
_TPPDefinedType _currn;
PTGNode* _AS0out;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(* _AS0out)=PTGIdentifier(_currn->_desc1->_ATsym);
/*SPC(309)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2DefinedType(_TPPDefinedType _currn,PTGNode* _AS0out)
#else
void _VS2DefinedType(_currn ,_AS0out)
_TPPDefinedType _currn;
PTGNode* _AS0out;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATsym=_currn->_desc1->_ATsym;
/*SPC(260)*/
_currn->_ATkey=_currn->_desc1->_ATkey;
/*SPC(261)*/
_AVTypeSpecifier_TypeKey=_currn->_desc1->_ATkey;
/*SPC(106)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3DefinedType(_TPPDefinedType _currn,PTGNode* _AS0out)
#else
void _VS3DefinedType(_currn ,_AS0out)
_TPPDefinedType _currn;
PTGNode* _AS0out;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVTypeSpecifier_typeid=PTGIdentifier(_currn->_desc1->_ATsym);
/*SPC(264)*/
_AVTypeSpecifier_type=PTGArrayEntry(_AVTypeSpecifier_typeid);
/*SPC(265)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1GenericType(_TPPGenericType _currn,PTGNode* _AS0out)
#else
void _VS1GenericType(_currn ,_AS0out)
_TPPGenericType _currn;
PTGNode* _AS0out;

#endif
{

_VisitVarDecl()
_VisitEntry();
(* _AS0out)=PTGString("TYPE");
/*SPC(304)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2GenericType(_TPPGenericType _currn,PTGNode* _AS0out)
#else
void _VS2GenericType(_currn ,_AS0out)
_TPPGenericType _currn;
PTGNode* _AS0out;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATsym=0;
/*SPC(248)*/
_currn->_ATkey=NoKey;
/*SPC(249)*/
_AVTypeSpecifier_TypeKey=NoKey;
/*SPC(101)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3GenericType(_TPPGenericType _currn,PTGNode* _AS0out)
#else
void _VS3GenericType(_currn ,_AS0out)
_TPPGenericType _currn;
PTGNode* _AS0out;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVTypeSpecifier_typeid=PTGString("TYPE");
/*SPC(253)*/
_AVTypeSpecifier_type=PTGArrayEntry(_AVTypeSpecifier_typeid);
/*SPC(254)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1OperationName(_TPPOperationName _currn)
#else
void _VS1OperationName(_currn )
_TPPOperationName _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVOperationNameDecl_key=FindOpKey((* _IG_incl8), _currn->_ATTERM_1);
/*SPC(276)*/
_AVOperationNameDeclfunc_post=concatfunclist(_AVOperationNameDecl_key, _AVOperationNameDeclfunc_post);
/*SPC(280)*/

if (EQ(KeyInEnv((* _IG_incl8), _currn->_ATTERM_1), NoKey)) {
message(FATAL, "Operation not defined", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(81)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1OperationSpec(_TPPOperationSpec _currn)
#else
void _VS1OperationSpec(_currn )
_TPPOperationSpec _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVOperationDecl_extstruct=BuildExternSpec(_AS1out, PTGIdentifier(_currn->_ATTERM_1), _AVParameterList_extout);
/*SPC(458)*/
_AVOperationDecl_formallist=_AVParameterList_formallist;
/*SPC(296)*/
_AVOperationDecl_arglist=PTGParen(_AVParameterList_arglist);
/*SPC(295)*/
_AVOperationDecl_opout=BuildOperationSpec(_AS1out, PTGIdentifier(_currn->_ATTERM_1), _AVParameterList_out, _AVParameterList_declout, PTGIdentifier(_currn->_ATTERM_2));
/*SPC(288)*/
_currn->_ATkey=DefineIdn((* _IG_incl11), _currn->_ATTERM_1);
/*SPC(67)*/
OpDefine(_currn->_ATkey, _AVOperationDecl_opout, _AVOperationDecl_arglist, _AVOperationDecl_formallist, _AVOperationDecl_extstruct, _currn->_ATTERM_1);
/*SPC(63)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2OperationSpec(_TPPOperationSpec _currn)
#else
void _VS2OperationSpec(_currn )
_TPPOperationSpec _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3OperationSpec(_TPPOperationSpec _currn)
#else
void _VS3OperationSpec(_currn )
_TPPOperationSpec _currn;

#endif
{
PTGNode _AS1out;

_VisitVarDecl()
_VisitEntry();

if (EQ(GetDefine(_currn->_ATkey, Undefined), MultDefined)) {
message(FATAL, "Operation is multiply defined", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(73)*/
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1out)));
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1PropertyName(_TPPPropertyName _currn)
#else
void _VS1PropertyName(_currn )
_TPPPropertyName _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATkey=DefineIdn((* _IG_incl0), _currn->_ATTERM_1);
/*SPC(48)*/
addfunclist(_currn->_ATkey, (* _IG_incl13));
/*SPC(194)*/
TypeIs(_currn->_ATkey, (* _IG_incl12));
/*SPC(122)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2PropertyName(_TPPPropertyName _currn)
#else
void _VS2PropertyName(_currn )
_TPPPropertyName _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (EQ(GetDefine(_currn->_ATkey, Unknown), MultDefined)) {
message(FATAL, "Redeclaration of Property with different type", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(129)*/
_AVPropertyNameDecl_macroout=GenMacros(_currn->_ATkey, _currn->_ATTERM_1, (* _IG_incl8), GetFuncList(_currn->_ATkey, dummyfunclist));
/*SPC(428)*/
KindIs(_currn->_ATkey, PropertyClass);
/*SPC(51)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3PropertyName(_TPPPropertyName _currn)
#else
void _VS3PropertyName(_currn )
_TPPPropertyName _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (EQ(GetKind(_currn->_ATkey, Undefined), NameClash)) {
message(FATAL, "Property and Type names must be different", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(56)*/
_AVPropertyNameDecl_first_RuleAttr_87=GetFirst(_currn->_ATkey, 1);
/*SPC(199)*/
_AVPropertyNameDecl_CloneCase=
((GetGenCloneCases(_currn->_ATkey, 0)
) ? (PTGNULL
) : (
(ResetGenCloneCases(_currn->_ATkey, 1), PTGCloneCase(GetSelector(_currn->_ATkey, 0), PTGIdentifier(_currn->_ATTERM_1), PTGIdentifier(GetSym(GetType(_currn->_ATkey, NoKey), 0))))
))
;
/*SPC(620)*/
_AVPropertyNameDecl_switch=
((_AVPropertyNameDecl_first_RuleAttr_87
) ? (PTGSwitchEntry(GetSelector(_currn->_ATkey, 0), (* _IG_incl15))
) : (PTGNULL))
;
/*SPC(206)*/
_AVPropertyNameDecl_type=
((_AVPropertyNameDecl_first_RuleAttr_87
) ? ((* _IG_incl14)
) : (PTGNULL))
;
/*SPC(204)*/
_AVPropertyNameDecl_name=
((_AVPropertyNameDecl_first_RuleAttr_87
) ? (PTGArrayEntry(PTGIdentifier(_currn->_ATTERM_1))
) : (PTGNULL))
;
/*SPC(202)*/
ResetFirst(_currn->_ATkey, 0);
/*SPC(200)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1TypeName(_TPPTypeName _currn)
#else
void _VS1TypeName(_currn )
_TPPTypeName _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2TypeName(_TPPTypeName _currn)
#else
void _VS2TypeName(_currn )
_TPPTypeName _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATkey=DefineIdn((* _IG_incl0), _currn->_ATTERM_1);
/*SPC(33)*/
ResetSym(_currn->_ATkey, _currn->_ATTERM_1);
KindIs(_currn->_ATkey, TypeClass);
;
/*SPC(36)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3TypeName(_TPPTypeName _currn)
#else
void _VS3TypeName(_currn )
_TPPTypeName _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (EQ(GetKind(_currn->_ATkey, Undefined), NameClash)) {
message(FATAL, "Property and Type names must be different", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(43)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1LibrarySpec(_TPPLibrarySpec _currn)
#else
void _VS1LibrarySpec(_currn )
_TPPLibrarySpec _currn;

#endif
{
Environment* _IL_incl11;

_VisitVarDecl()
_VisitEntry();
_IL_incl11=_IG_incl11;_IG_incl11= &(_currn->_ATopenv);
_currn->_ATopenv=InitOpEnv();
/*SPC(28)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl11=_IL_incl11;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2LibrarySpec(_TPPLibrarySpec _currn)
#else
void _VS2LibrarySpec(_currn )
_TPPLibrarySpec _currn;

#endif
{
Environment* _IL_incl11;

_VisitVarDecl()
_VisitEntry();
_IL_incl11=_IG_incl11;_IG_incl11= &(_currn->_ATopenv);
_IG_incl11=_IL_incl11;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3LibrarySpec(_TPPLibrarySpec _currn)
#else
void _VS3LibrarySpec(_currn )
_TPPLibrarySpec _currn;

#endif
{
Environment* _IL_incl11;

_VisitVarDecl()
_VisitEntry();
_IL_incl11=_IG_incl11;_IG_incl11= &(_currn->_ATopenv);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl11=_IL_incl11;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1Axiom(_TPPAxiom _currn)
#else
void _VS1Axiom(_currn )
_TPPAxiom _currn;

#endif
{
Environment* _IL_incl11;
Environment* _IL_incl8;
Environment* _IL_incl7;
Environment* _IL_incl3;
Environment* _IL_incl0;

_VisitVarDecl()
_VisitEntry();
_IL_incl11=_IG_incl11;_IG_incl11= &(_currn->_ATopenv);
_IL_incl8=_IG_incl8;_IG_incl8= &(_currn->_ATopenv);
_IL_incl7=_IG_incl7;_IG_incl7= &(_currn->_ATKnownKeyEnv);
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATKnownKeyEnv);
_IL_incl0=_IG_incl0;_IG_incl0= &(_currn->_ATenv);
_currn->_ATenv=InitEnv();
/*SPC(14)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_ATopenv=NewScope(_currn->_desc2->_ATopenv);
/*SPC(17)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATKnownKeyEnv=KnownKeyRootEnv;
/*SPC(642)*/
_AVSource_macroout=_AVRange__const13;
/*SPC(407)*/
_AVSource_funcout=_AVRange__const8;
/*SPC(162)*/
_AVG1ElementNum_pre=1;
/*SPC(523)*/
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVSource_Element=PTGElements(_AVRange__const19);
/*SPC(529)*/
_AVG1KeyIndex_post=0;
/*SPC(570)*/
_AVG1fileout_post=PTGNULL;
/*SPC(402)*/
(*(_CALL_VS_((NODEPTR )) (VS6MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVSource_ArrayElts=_AVRange__const15;
/*SPC(575)*/
_AVSource_Define=PTGDefines(_AVRange__const18);
/*SPC(571)*/
_AVSource_extout=_AVRange__const12;
/*SPC(405)*/
_AVSource_CloneKey=PTGCloneKey(_AVRange__const14);
/*SPC(611)*/
_AVSource_Array=
((NE(_AVSource_ArrayElts, PTGNULL)
) ? (PTGArray(_AVRange__const15)
) : (PTGNULL))
;
/*SPC(578)*/
_AVSource_mon=PTGMon(_AVRange__const9, _AVRange__const10, _AVRange__const11);
/*SPC(167)*/
PTGOutFile("pdl_gen.h", PTGHGen(_AVG1fileout_post, _AVSource_extout, _AVSource_macroout, _AVSource_Define));
/*SPC(415)*/
PTGOutFile("pdl_gen.c", PTGCGen(_AVSource_funcout, _AVSource_Element, _AVSource_Array, _AVSource_CloneKey, _AVSource_mon));
/*SPC(177)*/
_IG_incl11=_IL_incl11;
_IG_incl8=_IL_incl8;
_IG_incl7=_IL_incl7;
_IG_incl3=_IL_incl3;
_IG_incl0=_IL_incl0;

_VisitExit();
}

