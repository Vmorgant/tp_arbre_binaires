#include <noeud.h>

/* Etiquette */

extern 
void * noeud_etiquette_lire( const noeud_t * noeud ) 
{
   return(noeud->etiquette) ;  
}

extern 
err_t noeud_etiquette_ecrire( noeud_t * noeud , 
			      void * etiquette ,
			      err_t (*affecter)( void * e1 , void * e2 ) ) 
{
    return(affecter(noeud->etiquette,etiquette)) ;
}

/* Sous arbre gauche */

extern 
noeud_t * noeud_sag_lire( const noeud_t * noeud ) 
{
   return(noeud->gauche);
}

extern 
err_t noeud_sag_ecrire( noeud_t * noeud ,  noeud_t * sous_arbre_gauche ) 
{
   noeud->gauche=sous_arbre_gauche;
  return(OK) ; 
}

/* Sous arbre droit */

extern 
noeud_t * noeud_sad_lire( const noeud_t * noeud ) 
{
  return(noeud->droit); 
}

extern 
err_t noeud_sad_ecrire( noeud_t * noeud ,  noeud_t * sous_arbre_droit ) 
{
  noeud->droit=sous_arbre_droit;
  return(OK) ; 
}

/*
 * Existance ?
 */

booleen_t
noeud_existe( const noeud_t * noeud )
{
  if( noeud == NULL ) 
    return( FAUX ) ; 
  else
    return(VRAI) ; 
}

/* 
 * Feuille ?
 */
extern 
booleen_t noeud_feuille( const noeud_t * noeud )
{
  if(!noeud_existe(noeud_sag_lire(noeud)) && !noeud_existe(noeud_sad_lire(noeud)))
  	  return(VRAI);
  return(FAUX) ;     
}

/* 
 * Parents ?
 */

extern
booleen_t noeud_est_pere( const noeud_t * noeud_pere , 
			  const noeud_t * noeud_fils ) 
{  
  if( (noeud_pere->gauche==noeud_fils) || (noeud_pere->droit==noeud_fils) )
  	  return(VRAI);
  return(FAUX) ;  
}

/* 
 * Creation
 */

extern 
noeud_t * noeud_creer( void * etiquette , 
		       noeud_t * sous_arbre_gauche ,
		       noeud_t * sous_arbre_droit ,
		       err_t (*affecter)( void * e1 , void * e2 ) )
{
  noeud_t * noeud = NULL ; 
  noeud=malloc(sizeof(noeud_t));
  noeud->etiquette=NULL;
  affecter(&(noeud->etiquette),etiquette);
  noeud->gauche=sous_arbre_gauche;
  noeud->droit=sous_arbre_droit;
  return( noeud ) ;
}

/*
 * Destruction d'un noeud 
 */

extern 
err_t noeud_detruire( noeud_t ** noeud , 
		      err_t (*detruire)( void * e) ) 
{
    if(!(noeud_existe(*noeud)))
  	  return(OK);
  
  detruire(&(*noeud)->etiquette);
  return(OK);
}

/*
 * Affichage 
 */

extern
void noeud_afficher( const noeud_t * noeud ,
		     	 void (*afficher)(const void *),
		     	 int profondeur) 
{
	  int i;

  if(!noeud_existe(noeud))
  	  return;
  
		for(i=0 ; i<profondeur ; i++){
			printf("-----|");
		 
		}
		afficher(noeud->etiquette);
		printf("\n");

}

/*
 * Sauvegarde dans un fichier 
 */

extern 
err_t noeud_fd_sauver( noeud_t * noeud  ,	                  /* Noeud a sauvegarder */
		       FILE * fd , 		                  /* Descripteur fichier  */
		       err_t (*sauver)( void * e, FILE *  desc) ) /* Fonction de sauvegarde d'un element */
{
  err_t noerr = OK ;

  if( ! noeud_existe( noeud ) ) 
    return(OK) ; 

  if( ( noerr = sauver( noeud->etiquette , fd ) ) )
   return(noerr) ; 

 return(OK) ; 
}

/*
 * Recherches d'un noeud dans un arbre 
 */

extern
booleen_t noeud_rechercher( noeud_t ** result , 
			  noeud_t * noeud , 
                          const void * etiquette,
			  int(*comparer)(const void *e1,const void *e2) )
{
	if(noeud==NULL)
		return(FAUX);
	int cmp=comparer(etiquette,noeud->etiquette);
	if (cmp==0){
		*result=noeud;
		return(VRAI);
	}
	if(cmp<0)
		return(noeud_rechercher(result,noeud->gauche,etiquette,comparer));
	return(noeud_rechercher(result,noeud->droit,etiquette,comparer));
}


/*
 * Insertion d'un noeud dans un ABR (aux feuilles)
 * Le noeud doit etre cree avec son etiquette
 */
 
extern err_t noeud_inserer( noeud_t * noeud ,			           /* noeud a inserer */  
			    noeud_t ** racine  ,	                   /* Racine de l'arbre de recherche (peut etre modifiee) */
			    int (*comparer)(const void * n1 , const void * n2) ,       /* Fonction de comparaison des etiquettes */
			    err_t (*affecter)( void * e1 , void * e2 ) )  /* Fonction d'affectation des etiquettes */ 
{
  return(OK)  ;
}


/*
 * Suppression d'un noeud dans un ABR
 * Renvoie VRAI si le noeud existait dans l'arbre 
 *         FAUX sinon 
 */

extern
booleen_t noeud_supprimer( void * etiquette ,			 /* valeur a supprimer de l'arbre */ 
			   noeud_t ** racine  ,	                  /* Racine de l'arbre de recherche */
			   err_t (*affecter)( void * e1 , void * e2 ) , /* Fonction d'affectation des etiquettes */
			   err_t (*detruire)( void * e ) , /* Fonction de destruction des etiquettes */
			   int (*comparer)(const void * n1 , const void * n2) ) 
{
  return(VRAI) ;
}


