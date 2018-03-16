/* This file is part of the Eli translator construction system.

Eli is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2, or (at your option) any later
version.

Eli is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with Eli; see the file COPYING.  If not, write to the Free Software
Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */
/* Class Attribute accessing macros */

#define birthOfAction(AAction) AAction.IDLclassCommon->birth
#define obituaryOfAction(AAction) AAction.IDLclassCommon->obituary

/* Node Attribute  accessing macros */

#define symbnoOfAttributes(AAttributes) AAttributes->symbno
#define genOfAttributes(AAttributes) AAttributes->gen
#define typeidOfAttributes(AAttributes) AAttributes->typeid
#define partOfAttributes(AAttributes) AAttributes->part
#define classOfAttributes(AAttributes) AAttributes->class
#define symbidOfAttributes(AAttributes) AAttributes->symbid
#define attridOfAttributes(AAttributes) AAttributes->attrid
#define snameOfAttributes(AAttributes) AAttributes->sname
#define anameOfAttributes(AAttributes) AAttributes->aname
#define deathOfAttributes(AAttributes) AAttributes->death
#define birthOfAttributes(AAttributes) AAttributes->birth
#define not_usedOfAttributes(AAttributes) AAttributes->not_used
#define BnNFOfAttributes(AAttributes) AAttributes->BnNF
#define termattrOfAttributes(AAttributes) AAttributes->termattr
#define marksOfCan_Eval(ACan_Eval) ACan_Eval->marks
#define actionsOfCan_Eval(ACan_Eval) ACan_Eval->actions
#define ordOfCan_Eval(ACan_Eval) ACan_Eval->ord
#define symbidOfCan_Eval(ACan_Eval) ACan_Eval->symbid
#define birthOfEval(AEval) AEval->birth
#define obituaryOfEval(AEval) AEval->obituary
#define paramsOfEval(AEval) AEval->params
#define colOfEval(AEval) AEval->col
#define rowOfEval(AEval) AEval->row
#define symbnoOfEval(AEval) AEval->symbno
#define attridOfEval(AEval) AEval->attrid
#define startsymbOfGrammar(AGrammar) AGrammar->startsymb
#define rulesOfGrammar(AGrammar) AGrammar->rules
#define termsOfGrammar(AGrammar) AGrammar->terms
#define nontermsOfGrammar(AGrammar) AGrammar->nonterms
#define membersOfGroup(AGroup) AGroup->members
#define classOfGroup(AGroup) AGroup->class
#define nameOfGroup(AGroup) AGroup->name
#define typeidOfGroup(AGroup) AGroup->typeid
#define groupidOfGroup(AGroup) AGroup->groupid
#define ordOfMarked(AMarked) AMarked->ord
#define symbidOfMarked(AMarked) AMarked->symbid
#define flagOfMarked(AMarked) AMarked->flag
#define followOfNonterminal(ANonterminal) ANonterminal->follow
#define firstOfNonterminal(ANonterminal) ANonterminal->first
#define indexOfNonterminal(ANonterminal) ANonterminal->index
#define symbidOfNonterminal(ANonterminal) ANonterminal->symbid
#define rhsOfRule(ARule) ARule->rhs
#define lhsOfRule(ARule) ARule->lhs
#define prodidOfRule(ARule) ARule->prodid
#define symbnoOfSymbols(ASymbols) ASymbols->symbno
#define partsOfSymbols(ASymbols) ASymbols->parts
#define symbidOfSymbols(ASymbols) ASymbols->symbid
#define nameOfSymbols(ASymbols) ASymbols->name
#define followOfTerminal(ATerminal) ATerminal->follow
#define firstOfTerminal(ATerminal) ATerminal->first
#define occOfTerminal(ATerminal) ATerminal->occ
#define attridOfTerminal(ATerminal) ATerminal->attrid
#define def_attrsOfVSL(AVSL) AVSL->def_attrs
#define app_attrsOfVSL(AVSL) AVSL->app_attrs
#define actionsOfVSL(AVSL) AVSL->actions
#define prodidOfVSL(AVSL) AVSL->prodid
#define actionsOfVisit_Seq(AVisit_Seq) AVisit_Seq->actions
#define attrsOfVisit_Seq(AVisit_Seq) AVisit_Seq->attrs
#define symbsOfVisit_Seq(AVisit_Seq) AVisit_Seq->symbs
#define prodidOfVisit_Seq(AVisit_Seq) AVisit_Seq->prodid
#define lt_grammarOfVisit_Sequences(AVisit_Sequences) AVisit_Sequences->lt_grammar
#define vslOfVisit_Sequences(AVisit_Sequences) AVisit_Sequences->vsl
#define groupsOfVisit_Sequences(AVisit_Sequences) AVisit_Sequences->groups
#define attrsOfVisit_Sequences(AVisit_Sequences) AVisit_Sequences->attrs
#define symbsOfVisit_Sequences(AVisit_Sequences) AVisit_Sequences->symbs
#define tree_attrsOfVisit_Sequences(AVisit_Sequences) AVisit_Sequences->tree_attrs
#define glob_varOfVisit_Sequences(AVisit_Sequences) AVisit_Sequences->glob_var
#define single_visitOfVisit_Sequences(AVisit_Sequences) AVisit_Sequences->single_visit
#define canevalOfVisit_Sequences(AVisit_Sequences) AVisit_Sequences->caneval
#define vi_seqOfVisit_Sequences(AVisit_Sequences) AVisit_Sequences->vi_seq
#define birthOfVisits(AVisits) AVisits->birth
#define obituaryOfVisits(AVisits) AVisits->obituary
#define symbidOfVisits(AVisits) AVisits->symbid
#define ordOfVisits(AVisits) AVisits->ord
#define symbnoOfVisits(AVisits) AVisits->symbno

/* Widening Conversion macros */

extern Action IDLtempAction;
#define VisitsToAction(AVisits) \
	(IDLtempAction.VVisits = AVisits, IDLtempAction)
#define EvalToAction(AEval) \
	(IDLtempAction.VEval = AEval, IDLtempAction)

extern Vocabulary IDLtempVocabulary;
#define TerminalToVocabulary(ATerminal) \
	(IDLtempVocabulary.VTerminal = ATerminal, IDLtempVocabulary)
#define NonterminalToVocabulary(ANonterminal) \
	(IDLtempVocabulary.VNonterminal = ANonterminal, IDLtempVocabulary)


/* Narrowing Conversion macros */

#define ActionToVisits(AAction) \
	((typeof(AAction)==KVisits) ? AAction.VVisits :\
	(ConversionError("Action","Visits"), AAction.VVisits))
#define ActionToEval(AAction) \
	((typeof(AAction)==KEval) ? AAction.VEval :\
	(ConversionError("Action","Eval"), AAction.VEval))
#define VocabularyToTerminal(AVocabulary) \
	((typeof(AVocabulary)==KTerminal) ? AVocabulary.VTerminal :\
	(ConversionError("Vocabulary","Terminal"), AVocabulary.VTerminal))
#define VocabularyToNonterminal(AVocabulary) \
	((typeof(AVocabulary)==KNonterminal) ? AVocabulary.VNonterminal :\
	(ConversionError("Vocabulary","Nonterminal"), AVocabulary.VNonterminal))
