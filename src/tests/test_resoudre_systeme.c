#include "automate.h"
#include "rationnel.h"
#include "ensemble.h"
#include "outils.h"
#include "parse.h"
#include "scan.h"

/** @file arden.c */ 

bool meme_langage_rat ( Rationnel *rat1,  Rationnel *rat2)
{
	numeroter_rationnel(rat1);
	numeroter_rationnel(rat2);
   	Automate *aut1 = Glushkov(rat1);
   	Automate *aut2 = Glushkov(rat2);
   	// Minimisation des automates créés
   	aut1 = creer_automate_minimal(aut1);
   	aut2 = creer_automate_minimal(aut2);
   
   	// Comparaison des automates = comparaison de tous leurs ensembles (etats, alphabet,initiaux, finaux et transitions)
   	if(comparer_ensemble(aut1->etats, aut2->etats)!=0 || comparer_ensemble(aut1->alphabet, aut2->alphabet)!=0 ||
	  comparer_ensemble(aut1->initiaux, aut2->initiaux)!=0 || comparer_ensemble(aut1->finaux, aut2->finaux)!=0)
      		return false;
      
   	// Comparaison des transitions
   	Table_iterateur it1 = premier_iterateur_table(aut1->transitions);
   	Table_iterateur it2;
   	// Teste si les elements de la table 1 sont dans la table 2
	while(!iterateur_est_vide(it1)){ 
		it2=trouver_table(aut2->transitions, get_cle(it1));
		if(iterateur_est_vide(it2))
			return false;
		if(comparer_ensemble((Ensemble*)get_valeur(it1),(Ensemble*)get_valeur(it2))!=0)
			return false;
		it1 = iterateur_suivant_table(it1);
    	}
    	it2 = premier_iterateur_table(aut2->transitions);
    	//Teste si les elements de la table 2 sont dans la table 1
   	 while(!iterateur_est_vide(it2)){ 
		it1=trouver_table(aut1->transitions, get_cle(it2));
		if(iterateur_est_vide(it1))
			return false;
		if(comparer_ensemble((Ensemble*)get_valeur(it1),(Ensemble*)get_valeur(it2))!=0)
			return false;
		it2 = iterateur_suivant_table(it2);
    	}
   	return true;
}


int main(int argc, char *argv[]){
	// Création d'une expression rationnelle
	Rationnel* rat1;
	rat1 = expression_to_rationnel("(a.b)*.(c.a*)*");
	
	// Conversion de cette expression rationnelle en automate
	numeroter_rationnel(rat1);
	Automate * automateRat1 = Glushkov(rat1);

	// Reconversion de cet automate en expression rationnelle via Arden
	Rationnel* rat2;
	rat2 = Arden(automateRat1);

	// Test si les deux expressions rationnelles rat1 et rat2 produisent le même langage
	bool ardenReussi = meme_langage_rat(rat1, rat2);

	// Résultat à l'écran	
	return ardenReussi;
}



