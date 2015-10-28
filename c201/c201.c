
/* c201.c *********************************************************************}
{* Téma: Jednosmìrný lineární seznam
**
**                     Návrh a referenèní implementace: Petr Pøikryl, øíjen 1994
**                                          Úpravy: Andrea Nìmcová listopad 1996
**                                                   Petr Pøikryl, listopad 1997
**                                Pøepracované zadání: Petr Pøikryl, bøezen 1998
**                                  Pøepis do jazyka C: Martin Tuèek, øíjen 2004
**	                                      Úpravy: Bohuslav Køena, øíjen 2015
**
** Implementujte abstraktní datový typ jednosmìrný lineární seznam.
** U¾iteèným obsahem prvku seznamu je celé èíslo typu int.
** Seznam bude jako datová abstrakce reprezentován promìnnou typu tList.
** Definici konstant a typù naleznete v hlavièkovém souboru c201.h.
** 
** Va¹ím úkolem je implementovat následující operace, které spolu s vý¹e
** uvedenou datovou èástí abstrakce tvoøí abstraktní datový typ tList:
**
**      InitList ...... inicializace seznamu pøed prvním pou¾itím,
**      DisposeList ... zru¹ení v¹ech prvkù seznamu,
**      InsertFirst ... vlo¾ení prvku na zaèátek seznamu,
**      First ......... nastavení aktivity na první prvek,
**      CopyFirst ..... vrací hodnotu prvního prvku,
**      DeleteFirst ... zru¹í první prvek seznamu,
**      PostDelete .... ru¹í prvek za aktivním prvkem,
**      PostInsert .... vlo¾í nový prvek za aktivní prvek seznamu,
**      Copy .......... vrací hodnotu aktivního prvku,
**      Actualize ..... pøepí¹e obsah aktivního prvku novou hodnotou,
**      Succ .......... posune aktivitu na dal¹í prvek seznamu,
**      Active ........ zji¹»uje aktivitu seznamu.
**
** Pøi implementaci funkcí nevolejte ¾ádnou z funkcí implementovaných v rámci
** tohoto pøíkladu, není-li u dané funkce explicitnì uvedeno nìco jiného.
**
** Nemusíte o¹etøovat situaci, kdy místo legálního ukazatele na seznam 
** pøedá nìkdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodnì komentujte!
**
** Terminologická poznámka: Jazyk C nepou¾ívá pojem procedura.
** Proto zde pou¾íváme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c201.h"

int solved;
int errflg;

void Error() {
/*
** Vytiskne upozornìní na to, ¾e do¹lo k chybì.
** Tato funkce bude volána z nìkterých dále implementovaných operací.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;                      /* globální promìnná -- pøíznak chyby */
}

void InitList (tList *L) {
/*
** Provede inicializaci seznamu L pøed jeho prvním pou¾itím (tzn. ¾ádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádìt nad ji¾ inicializovaným
** seznamem, a proto tuto mo¾nost neo¹etøujte. V¾dy pøedpokládejte,
** ¾e neinicializované promìnné mají nedefinovanou hodnotu.
**/
	L->Act = NULL;
	L->First = NULL;
}

void DisposeList (tList *L) {
/*
** Zru¹í v¹echny prvky seznamu L a uvede seznam L do stavu, v jakém se nacházel
** po inicializaci. Ve¹kerá pamì» pou¾ívaná prvky seznamu L bude korektnì
** uvolnìna voláním operace free.
***/

	while (L->First != NULL) { // iteruje kym nepride na prvy prvok

		tElemPtr tpom = L->First;

		if (L->First == L->Act){ 
			L->Act = NULL;
		}

		L->First = L->First->ptr; // prepise prvy nasedujucim 
		free (tpom); 
	}

	L->First = NULL;
	L->Act = NULL;
}

void InsertFirst (tList *L, int val) {
/*
** Vlo¾í prvek s hodnotou val na zaèátek seznamu L.
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci Error().
**/
	tElemPtr tpom = malloc(sizeof(struct tElem)); 

	if(tpom == NULL) {
		Error();
		return;	 
	}
	else{
		tpom->data = val;
		tpom->ptr = L->First; //prvy prvok sa zaradi ako druhy
		L->First = tpom; //priradim novy prvok na zaciatok seznamu
	}
}

void First (tList *L) {
/*
** Nastaví aktivitu seznamu L na jeho první prvek.
** Funkci implementujte jako jediný pøíkaz, ani¾ byste testovali,
** zda je seznam L prázdný.
**/
	L->Act = L->First; // nastav aktivitu seznamu na prvy prvok
}

void CopyFirst (tList *L, int *val) {
/*
** Prostøednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci Error().
**/
	if ( L->First == NULL) {
	  	Error();
	  	return;
  	} else  // vracia hodnotu prveho prvku seznamu v ktora je v data
  		*val = L->First->data;
}

void DeleteFirst (tList *L) {
/*
** Zru¹í první prvek seznamu L a uvolní jím pou¾ívanou pamì».
** Pokud byl ru¹ený prvek aktivní, aktivita seznamu se ztrácí.
** Pokud byl seznam L prázdný, nic se nedìje.
**/
	tElemPtr tpom ;

	if ( L->First == NULL) { 
		return;
	}

	if ( L->First == L->Act) { 
	 	L->Act = NULL;
	}

	if (L->First != NULL) { 
	 	tpom = L->First; // ulozim si do pomocnej prvy
	 	L->First = L->First->ptr; // ziskam cestu k nasledujucemu
 		free(tpom);
	}
}	

void PostDelete (tList *L) {
/* 
** Zru¹í prvek seznamu L za aktivním prvkem a uvolní jím pou¾ívanou pamì».
** Pokud není seznam L aktivní nebo pokud je aktivní poslední prvek seznamu L,
** nic se nedìje.
**/
	if(L->Act==NULL || L->Act->ptr == NULL) { 
		return;
	}

	if(L->Act->ptr->ptr != NULL) { // pokial saa aktivny  nachadza v strede zoznamu
		tElemPtr tpom = L->Act->ptr->ptr;
		free(L->Act->ptr);
		L->Act->ptr = tpom;
	}
	else{
		free(L->Act->ptr); // pokial je aktivny predopsledny 
		L->Act->ptr = NULL;
	}
}

void PostInsert (tList *L, int val) {
/*
** Vlo¾í prvek s hodnotou val za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se nedìje!
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** zavolá funkci Error().
**/
	if (L->Act != NULL) { 

		tElemPtr tpom = malloc(sizeof(struct tElem)); 

		if(tpom == NULL) {
			Error();
			return;
		}
		else{
			tpom->data = val; //vlozim hodnotu val do noveho prvku
    		tpom->ptr = L->Act->ptr; //novemu prvku pripadim ukazatel z act ukazatela
    		L->Act->ptr = tpom; //predosli ukazatel nahradim novym	
    	}
	}	
}

void Copy (tList *L, int *val) {
/*
** Prostøednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam není aktivní, zavolá funkci Error().
**/
	if (L->Act == NULL) {
	 	Error();
	 	return;
 	} 
 	else {
 		*val = L->Act->data; // inak priradi hodnotu z data aktualneho prvku do *val
 	}
}

void Actualize (tList *L, int val) {
/*
** Pøepí¹e data aktivního prvku seznamu L hodnotou val.
** Pokud seznam L není aktivní, nedìlá nic!
**/
	if (L->Act != NULL){
	 	L->Act->data = val; // priradi do premennej data aktualneho prvku ,hodnotu z *val
	}
	else {
	 	return;
	}
}

void Succ (tList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** V¹imnìte si, ¾e touto operací se mù¾e aktivní seznam stát neaktivním.
** Pokud není pøedaný seznam L aktivní, nedìlá funkce nic.
**/
	if (L->Act != NULL){

		if(L->Act->ptr != NULL) { // ak prvok za aktuualnym ,tak posunie aktivitu na neho
			L->Act = L->Act->ptr;
		}
		else {
			L->Act = NULL;
		}
	}
	else {
    	return;
	}
}

int Active (tList *L) {		
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Tuto funkci je vhodné implementovat jedním pøíkazem return. 
**/
	return ((L->Act == NULL) ? 0 : 1); // ak je zoznam aktivny vracia 1 ak nie tak 0
}

/* Konec c201.c */
