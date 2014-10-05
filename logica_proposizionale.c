/****************************************************************************************/
/*Programma per il calcolo della soddisfacibilità di una formula di Logica Proposizionale*/
/****************************************************************************************/

/**************************************/
/*Programma scritto da Edoardo Spadoni*/
/**************************************/

/***************************/
/*Inclusione delle librerie*/
/***************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


/******************************/
/*Dichiarazione delle funzioni*/
/******************************/

/*Funzione che riduce l'array calcolando via via i valori di verità delle proposizioni*/
void riduzione(char *, int , int , int );	

/*Funzione che calcola i valori di verità del NOT*/
void calcola_not(char *, int );	

/*Funzione che calcola i valori di verità del AND e del NAND*/
void calcola_and_nand(char *, int );		

/*Funzione che calcola i valori di verità dell' OR del NOR e dello XOR*/
void calcola_or_nor_xor(char *, int );

/*Funzione che calcola i valori di verità della IMPLICAZIONE*/
void calcola_implicazione(char *, int );

/*Funzione che calcola i valori di verità della DOPPIA IMPLICAZIONE*/
void calcola_doppia_implicazione(char *, int );

/*Funzione che calcola la soddisfacibilità della formula*/
int calcola_verita(char *, int );

/*Funzione che prova se con detrminati valori della tabella della verità la formula è soddisfacibile*/
int test_verita(char *, int );	

/*Funzione che controlla la correttezza della formula inserita*/
int controllo_formula(char *, int , int , int );	

/*Funzione che permette l'acquisizione della formula*/
int acquisizione(char *);


/****************************/
/*Definizione delle funzioni*/
/****************************/

/*Definizione della funzione main*/
int main(void)
{
	/*Dichiarazione delle variabili locali alla funzione*/
	char *formula = (char *)calloc(10, sizeof(char));	/*Array che contiene la formula*/
		
	int conta_caratteri = 0,				/*Contatore lunghezza della formula*/
            esito_verita = 0;					/*Prende il risultato di "calcola_verita"*/	

	/*Messaggio video che richiede l'inserimento della formula*/
	printf("Calcolo del valore di verita' di una formula di Logica Proposizionale\n\nQuesti sono gli operatori:\n* -  NOT \t(negazione)\n2 -  AND \t(congiunzione)\n3 -  NAND  \t(disgiunzione)\n4 -  OR  \t(congiunzione negata)\n5 -  NOR \t(disgiunzione negata)\n6 -  XOR \t(disgiunzione esclusiva)\n7 -  -> \t(implicazione)\n8 -  <-> \t(doppia implicazione)\n\n- Per le proposizioni usa le lettere minuscole q, w, e, r (NON ALTRE!)\n\n- Non sono ammessi operatori contigui ad eccezione del NOT (IMPORTANTE!)\n\n- E' consentito l'uso di al piu' 4 Proposizioni e al piu' 3 Connettivi logici\n\nEsempio di formula: q3w8*r (q NAND w <-> NOT r)\nEsempio di formula errata: q35a*b\n\n");

	/*Acquisisce la formula e salva la lunghezza di essa in "conta_caratteri"*/
	conta_caratteri = acquisizione(formula);

	/*La variabile "esito_verita" prende il valore della chiamata a funzione "calcola_verita"*/
	esito_verita = calcola_verita(formula, conta_caratteri);
 
	/*Stampa a video del valore di verità della funzione*/
	printf("Il risultato della formula e': %d (%s)\n", esito_verita, (esito_verita == 1)? "SODDISFACIBILE": "CONTRADDIZIONE");

	return(0);
}


/*Acquisizione formula*/
int acquisizione(char a[])
{
	/*Dichiarazione delle variabili locali alla funzione*/
	int i,				/*Variabile contatore per ciclo*/
	    conta_caratteri,		/*Variabile che assume il valore della lunghezza della formula*/
	    esito_controllo,		/*Variabile che prende il risultato di "controllo_formula"*/
	    conta_connettivi,		/*Variabile che conta i connettivi logici*/
	    conta_proposizioni;		/*Variabile che conta le proposizioni*/

	char input_carattere;		/*Carattere che memorizza ogni input dell'utente*/

	/*Ciclo che itera fino a quando non ci sono anomalie nella formula*/
	do
	{
		/*Svuotamento buffer di memoria inizio ciclo*/
		esito_controllo = 0;
		conta_caratteri = 0;
		input_carattere = '\0';
		conta_connettivi = 0;
		conta_proposizioni = 0;

		
		printf("Inserisci la formula: ");

		for(i = 0; 
   		    ((input_carattere = getchar()) != '\n');
   		    i++) 
		{
			if(isdigit(input_carattere))
				conta_connettivi += 1;

			else if(isalpha(input_carattere))
				conta_proposizioni += 1;

			else if(input_carattere == '*')
				conta_connettivi += 1;

			a[i] = input_carattere;
			conta_caratteri += 1;

		}

		a[i] = '\0';

		esito_controllo = controllo_formula(a, conta_caratteri, conta_connettivi, conta_proposizioni);

	}while(esito_controllo != 1);
	
	/*Restituisco il valore "conta_caratteri" che contiene la lunghezza dalla formula*/
	return(conta_caratteri);
}


/*Controllo della correttezza della formula*/
int controllo_formula(char a[], int lunghezza_formula, int numero_connettivi, int numero_proposizioni)
{
	/*Dichiarazione delle variabili locali alla funzione*/
	int i,					/*Contatore di ciclo*/
            correttezza_formula = 0,		/*Assume valore 0 ogni volta che ci sono errori nella formula*/
	    esito_controllo = 0;		/*Variabile che restituisce il tipo int della funzione*/

	/*Se la formula supera i limiti di lunghezza posti, richiede l’inserimento*/
	if(lunghezza_formula > 7 || numero_connettivi > 3 || numero_proposizioni > 4)
		correttezza_formula = 0;

	/*Controlla tutte le altre tipologie di violazione della correttezza della formula*/
	else
	{
		for(i = 0;
    		    i < lunghezza_formula;
    		    i++)
		{
			/*Controlla se le lettere utilizzate corrispondono a quelle stabilite*/
			if(a[i] == 'q' || a[i] == 'w' || a[i] == 'e' || a[i] == 'r')
			{
				/*Controlla se la formula contiene una sola proposizione*/
				if(i == 0)
					correttezza_formula = 1;

				/*Controlla se ci sono due proposizioni contigue*/
				else if(isalpha(a[i - 1]))
				{
					correttezza_formula = 0;
					i = lunghezza_formula;
				}

				else
					correttezza_formula = 1;

			}

			/*Controlla se i numeri utilizzati per i connettivi corrispondono a quelli stabiliti*/
			else if(a[i] == '2' || a[i] == '3' || a[i] == '4' || a[i] == '5' || a[i] == '6' || a[i] == '7' || a[i] == '8')
			{
				/*Verifica se la formula inizia con un numero*/
				if(i == 0)
				{
					if(isdigit(a[i]))
					{
						correttezza_formula = 0;
						i = lunghezza_formula;
					}

				}

				/*Verifica se un numero è seguito da un altro numero*/
				else if(isdigit(a[i - 1]))
				{
					correttezza_formula = 0;
					i = lunghezza_formula;
				}

				/*Verifica se un numero è posto alla fine della formula*/
				else if(a[i + 1] == '\0')
				{
					correttezza_formula = 0;
					i = lunghezza_formula;
				}
				
				else
					correttezza_formula = 1;
			}

			/*Verica i casi in cui l'utilizzo del NOT è errato*/
			else if(a[i] == '*')
			{

				/*Se dopo il NOT c'è un numero la formula è errata*/
				if(isdigit(a[i + 1]))
				{
					correttezza_formula = 0;
					i = lunghezza_formula;
				}

				/*Se il NOT è preceduto da una proposizione la formula è errata*/
				else if(i > 0 && isalpha(a[i - 1]))
				{
					correttezza_formula = 0;
					i = lunghezza_formula;
				}

				/*Caso valido in cui il NOT è seguito da una lettera*/
				else if(isalpha(a[i + 1]))
					correttezza_formula = 1;

				/*Caso valido in cui il NOT è seguito da un altro NOT*/
				else if(a[i + 1] == '*')
					correttezza_formula = 1;
				
				/*Caso errato in cui il not è posizionato alla fine della formula*/
				else if(a[i + 1] == '\0')
				{
					correttezza_formula = 0;
					i = lunghezza_formula;
				}
			}

			/*Se sono presenti caratteri o numeri diversi la formula è errata*/
			else
			{
				correttezza_formula = 0;
				i = lunghezza_formula;
			}
			
		}

	}

	/*Controlla se sono presenti anomalie nella formula tramite la variabile "correttezza_formula*/
	if(correttezza_formula == 0)
	{
		esito_controllo = 0;
		a[1] = '\0';
	}

	else
		esito_controllo = 1;
	
	return(esito_controllo);
}


/*Calcola per tutti i connetivi logici i valori di verità*/
int test_verita(char a[], int lunghezza_formula)
{
	/*Richiama le funzioni per il calcolo dei valori di verità in ordine di precedenza e associatività*/
	calcola_not(a, lunghezza_formula);
	calcola_and_nand(a, lunghezza_formula);
	calcola_or_nor_xor(a, lunghezza_formula);
	calcola_implicazione(a, lunghezza_formula);
	calcola_doppia_implicazione(a, lunghezza_formula);

	if(a[0] == '1')
		return(1);
	else
		return(0);
}


/*Assegna a tutte le proposizioni le possibili combinazioni della tabella di verità*/
int calcola_verita(char a[], int lunghezza_formula)
{
	/*Dichiarazione delle variabili locali alla funzione*/
	int i,				/*Contatore ciclo che copia array "a" in "b"*/
	    j,				/*Contatore ciclo per verificare la presenza delle proposizioni*/
	    h,				/*Contatore di ciclo per copiare array "b" in "a"*/
	    righe_tabella_verita = 0,	/*Indice che indica le righe dell'array "tabella_verita"*/
	    esito_verita = 0,		/*Contiene il risultato della chiamata della funzione "test_verita"*/
	    presenza_q,			/*Verifica se la proposizione Q è presente nella formula*/
	    presenza_w,			/*Verifica se la proposizione W è presente nella formula*/
	    presenza_e,			/*Verifica se la proposizione E è presente nella formula*/
	    presenza_r;			/*Verifica se la proposizione R è presente nella formula*/

	/*Array ausiliario per conservare gli elementi di a prima della riduzione*/
	char *b = (char *)calloc(lunghezza_formula, sizeof(char));

	/*Array che contiene i valori della tabella di verità*/
	char tabella_verita[16][4] =	{{'0', '0', '0', '0'},
					 {'0', '0', '0', '1'},
					 {'0', '0', '1', '0'},
					 {'0', '0', '1', '1'},
					 {'0', '1', '0', '0'},
					 {'0', '1', '0', '1'},
					 {'0', '1', '1', '0'},
					 {'0', '1', '1', '1'},
					 {'1', '0', '0', '0'},
					 {'1', '0', '0', '1'},
					 {'1', '0', '1', '0'},
					 {'1', '0', '1', '1'},
					 {'1', '1', '0', '0'},
					 {'1', '1', '0', '1'},
					 {'1', '1', '1', '0'},
					 {'1', '1', '1', '1'}};

	/*Ciclo che copia elementi di b in a*/
	for(i = 0;
   	    i < lunghezza_formula;
   	    i++)
		b[i] = a[i];

	b[i] = '\0';

	/*Ciclo per verificare la presenza delle proposizioni nell’array e calcolarne il valore di verità*/
	do
	{
		presenza_q = 0;
		presenza_w = 0;
		presenza_e = 0;
		presenza_r = 0;

		for(j = 0;
  		    j < lunghezza_formula;
  		    j++)
		{
			if(a[j] == 'q')
			{
				a[j] = tabella_verita[righe_tabella_verita][3];
				presenza_q = 1;
			}


			else if(a[j] == 'w')
			{
				a[j] = tabella_verita[righe_tabella_verita][2];
				presenza_w = 1;
			}

			else if(a[j] == 'e')
			{
				a[j] = tabella_verita[righe_tabella_verita][1];
				presenza_e = 1;
			}

			else if(a[j] == 'r')
			{
				a[j] = tabella_verita[righe_tabella_verita][0];
				presenza_r = 1;
			}
		}

	/*Incremento dell'indice "righe_tabella_verita" se la combinazione di valori non soddisfa la formula*/
	righe_tabella_verita += 1;	

	/*La variabile prende il risultato della funzione "test_verita"*/
	esito_verita = test_verita(a, lunghezza_formula);

	/*Copio i valori di "b", precedentemente copiati da "a", nuovamente in "a"*/
	for(h = 0;
	    h < lunghezza_formula;
	    h++)
		a[h] = b[h];
	

	}while (esito_verita != 1 && righe_tabella_verita <16);

	/*Controllo se "esito_verita" vale zero e se così è la formula è una contraddizione*/
	if(esito_verita == 0)
	{
		presenza_q = 0;
		presenza_w = 0;
		presenza_e = 0;
		presenza_r = 0;
	}

	/*Stampo a video i valori che assumono le variabili nel caso in cui la formula sia soddisfacibile*/
	if(esito_verita == 1)
	{
		if(presenza_q == 1)
			printf("Se Q vale: %c\n", tabella_verita[righe_tabella_verita - 1][3]);

		if(presenza_w == 1)
			printf("Se W vale: %c\n", tabella_verita[righe_tabella_verita - 1][2]);

		if(presenza_e == 1)
			printf("Se E vale: %c\n", tabella_verita[righe_tabella_verita - 1][1]);

		if(presenza_r == 1)
			printf("Se R vale: %c\n", tabella_verita[righe_tabella_verita - 1][0]);
	}

	/*Restituisco il valore di "esito_verita"*/
	return(esito_verita); 
}


/*NOT*/
void calcola_not(char a[], int lunghezza_formula)
{
	/*Dichiarazione delle variabili locali alla funzione*/
	int i;				/*Contatore del ciclo per eventuali NOT all'interno della formula*/
	
	int conta_not = 0,		/*Variabile per il conteggio dei NOT presenti dentro la formula*/
	    indice_not;			/*Variabile che memorizza l'indice in cui si trova il NOT*/
	
	int conversione_prop_not;	/*Conversione da char a int e calcolo del valore di verità*/

	for (i = 0;
    	     i < lunghezza_formula;
    	     i++)
	{
		indice_not = 0;

		if((a[i] & a[i + 1] & a[i + 2]) == '*')
		{
			/*Converte il char in int*/
			conversione_prop_not = a[i + 3] - '0';

			/*Calcola valore di verità*/
			conversione_prop_not = !(conversione_prop_not);

			/*Riassegna il valore convertito nuovamente in char all'elemento dell'array*/
			a[i + 3] = conversione_prop_not + 48;
			conta_not = 3;		/*Memorizza i NOT*/
			indice_not = i;		/*Memorizza l'indice in cui c'è il NOT*/

			/*Applica la funzione di riduzione dell'array*/
			riduzione(a, conta_not, indice_not, lunghezza_formula);
		}

		else if((a[i] & a[i + 1]) == '*')
		{
			/*Converte il char in int*/
			conversione_prop_not = a[i + 2] - '0';

			/*Riassegna il valore convertito nuovamente in char all'elemento dell'array*/
			a[i + 2] = conversione_prop_not + 48;
			conta_not = 2;		/*Memorizza i NOT*/
			indice_not = i;		/*Memorizza l'indice in cui c'è il NOT*/

			/*Applica la funzione di riduzione dell'array*/
			riduzione(a, conta_not, indice_not, lunghezza_formula);
		}

		else if(a[i] == '*')
		{
			/*Converte il char in int*/
			conversione_prop_not = a[i + 1] - '0';

			/*Calcola valore di verità*/
			conversione_prop_not = !(conversione_prop_not);

			/*Riassegna il valore convertito nuovamente in char all'elemento dell'array*/
			a[i + 1] = conversione_prop_not + 48;
			conta_not = 1;		/*Memorizza i NOT*/
			indice_not = i;		/*Memorizza l'indice in cui c'è il NOT*/

			/*Applica la funzione di riduzione dell'array*/
			riduzione(a, conta_not, indice_not, lunghezza_formula);
		}

	}
}


/*AND*/ /*NAND*/
void calcola_and_nand(char a[], int lunghezza_formula)
{
	/*Dichiarazione delle variabili locali alla funzione*/
	int i;					/*Contatore ciclo per AND, NAND all'interno della formula*/
	
	int conta_and = 0,			/*Variabile per conteggio AND*/
	    indice_and,				/*Variabile che memorizza l'indice in cui si trova l' AND*/
	    conta_nand = 0,			/*Variabile per posti successivi ai NAND*/
	    indice_nand;			/*Variabile che memorizza l'indice in cui si trova il NAND*/
	
	int conversione_prop_and_sx = 0,	/*Conversione proposizione prima dell’ AND*/
	    conversione_prop_and_dx = 0,	/*Conversione proposizione dopo dell’ AND*/
	    calcolo_verita_and = 0;		/*Variabile per calcolo valore di verità*/						
	
	int conversione_prop_nand_sx = 0,	/*Conversione proposizione prima del NAND*/
	    conversione_prop_nand_dx = 0,	/*Conversione proposizione dopo del NAND*/
	    calcolo_verita_nand = 0;		/*Variabile per calcolo valore di verità*/		

	for(i = 0;
   	    i < lunghezza_formula;
   	    i++)
	{
		indice_and = 0;
		indice_nand = 0;

		if(a[i] == '2')
		{
			/*Converte il char in int*/
			conversione_prop_and_sx = a[i - 1] - '0';
			conversione_prop_and_dx = a[i + 1] - '0';

			/*Calcola il valore di verità*/
			calcolo_verita_and = conversione_prop_and_sx & conversione_prop_and_dx;	

			/*Riassegna il valore convertito nuovamente in char all'elemento dell'array*/
			a[i - 1] = calcolo_verita_and + 48;
			conta_and = 2;	
			indice_and = i;

			/*Applica la funzione di riduzione dell'array*/
			riduzione(a, conta_and, indice_and, lunghezza_formula);
			i -= i;
		}

		else if(a[i] == '3')
		{
			/*Converte il char in int*/
			conversione_prop_nand_sx = a[i - 1] - '0';
			conversione_prop_nand_dx = a[i + 1] - '0';

			/*Calcola il valore di verità*/
			calcolo_verita_nand = !(conversione_prop_nand_sx & conversione_prop_nand_dx);
				
			/*Riassegna il valore convertito nuovamente in char all'elemento dell'array*/
			a[i - 1] = calcolo_verita_nand + 48;
			conta_nand = 2;	
			indice_nand = i;

			/*Applica la funzione di riduzione dell'array*/
			riduzione(a, conta_nand, indice_nand, lunghezza_formula);
			i -= i;
		}
	}
}


/*OR*/ /*NOR*/ /*XOR*/
void calcola_or_nor_xor(char a[], int lunghezza_formula)
{
	/*Dichiarazione delle variabili locali alla funzione*/
	int i;				/*Contatore del ciclo per OR, NOR, XOR all'interno della formula*/
	
	int conta_or = 0,		/*Variabile per conteggio OR*/
	    indice_or,			/*Variabile che memorizza l'indice in cui si trova l' OR*/
   	    conta_nor = 0,		/*Variabile per conteggio NOR*/					
	    indice_nor, 		/*Variabile che memorizza l'indice in cui si trova il NOR*/
   	    conta_xor = 0,		/*Variabile per conteggio XOR*/				
	    indice_xor;			/*Variabile che memorizza l'indice in cui si trova lo XOR*/

	int conversione_prop_or_sx,	/*Conversione proposizione prima dell’ OR*/
	    conversione_prop_or_dx,	/*Conversione proposizione dopo dell’ OR*/
	    calcolo_verita_or;		/*Variabile per calcolo valore di verità*/	
						
	int conversione_prop_nor_sx,	/*Conversione proposizione prima del NOR*/
	    conversione_prop_nor_dx,	/*Conversione proposizione dopo del NOR*/
	    calcolo_verita_nor;		/*Variabile per calcolo valore di verità*/		
	
	int conversione_prop_xor_sx,	/*Conversione proposizione prima dello XOR*/
	    conversione_prop_xor_dx,	/*Conversione proposizione dopo dello XOR*/
	    calcolo_verita_xor;		/*Variabile per calcolo valore di verità*/	

	for(i = 0;
    	    i < lunghezza_formula;
    	    i++)
	{
		indice_or = 0;
		indice_nor = 0;
		indice_xor = 0;

		if(a[i] == '4')
		{
			/*Converte il char in int*/
			conversione_prop_or_sx = a[i - 1] - '0';
			conversione_prop_or_dx = a[i + 1] - '0';

			/*Calcola il valore di verità*/
			calcolo_verita_or = conversione_prop_or_sx | conversione_prop_or_dx;
	
			/*Riassegna il valore convertito nuovamente in char all'elemento dell'array*/
			a[i - 1] = calcolo_verita_or + 48;
			conta_or = 2;	
			indice_or = i;

			/*Applica la funzione di riduzione dell'array*/
			riduzione(a, conta_or, indice_or, lunghezza_formula);
			i -= i;
		}

		if(a[i] == '5')
		{
			/*Converte il char in int*/
			conversione_prop_nor_sx = a[i - 1] - '0';
			conversione_prop_nor_dx = a[i + 1] - '0';

			/*Calcola il valore di verità*/
			calcolo_verita_nor = !(conversione_prop_nor_sx | conversione_prop_nor_dx);

			/*Riassegna il valore convertito nuovamente in char all'elemento dell'array*/
			a[i - 1] = calcolo_verita_nor + 48;
			conta_nor = 2;	
			indice_nor = i;

			/*Applica la funzione di riduzione dell'array*/
			riduzione(a, conta_nor, indice_nor, lunghezza_formula);
			i -= i;
		}

		if(a[i] == '6')
		{
			/*Converte il char in int*/
			conversione_prop_xor_sx = a[i - 1] - '0';
			conversione_prop_xor_dx = a[i + 1] - '0';

			/*Calcola il valore di verità*/
			calcolo_verita_xor = conversione_prop_xor_sx ^ conversione_prop_xor_dx;	
			
			/*Riassegna il valore convertito nuovamente in char all'elemento dell'array*/
			a[i - 1] = calcolo_verita_xor + 48;
			conta_xor = 2;	
			indice_xor = i;

			/*Applica la funzione di riduzione dell'array*/
			riduzione(a, conta_xor, indice_xor, lunghezza_formula);
			i -= i;
		}
	}
}


/*IMPLICAZIONE*/
void calcola_implicazione(char a[], int lunghezza_formula)
{
	/*Dichiarazione delle variabili locali alla funzione*/
	int i;					/*Contatore del ciclo per IMPLICAZIONI dentro la formula*/

	int conta_implicazione = 0,		/*Variabile per conteggio IMPLICAZIONI*/
	    indice_implicazione;		/*Variabile che memorizza l'indice dell' IMPLICAZIONE*/
				
	int conversione_prop_implicazione_sx,	/*Conversione proposizione prima dell’ IMPLICAZIONE*/
	    conversione_prop_implicazione_dx,	/*Conversione proposizione dopo dell’ IMPLICAZIONE*/
	    calcolo_verita_implicazione;	/*Variabile per calcolo valore di verità*/

	for(i = 0;
    	    i < lunghezza_formula;
   	    i++)
	{
		indice_implicazione = 0;

		if(a[i] == '7')
		{
			/*Converte il char in int*/
			conversione_prop_implicazione_sx = a[i - 1] - '0';
			conversione_prop_implicazione_dx = a[i + 1] - '0';


			/*Calcola il valore di verità*/
			calcolo_verita_implicazione = ((!(conversione_prop_implicazione_sx)) | (conversione_prop_implicazione_dx));
	
			/*Riassegna il valore convertito nuovamente in char all'elemento dell'array*/
			a[i - 1] = calcolo_verita_implicazione + 48;
			conta_implicazione = 2;	
			indice_implicazione = i;

			/*Applica la funzione di riduzione dell'array*/
			riduzione(a, conta_implicazione, indice_implicazione, lunghezza_formula);
			i -= i;
		}
	}
}


/*DOPPIA IMPLICAZIONE*/
void calcola_doppia_implicazione(char a[], int lunghezza_formula)
{
	/*Dichiarazione delle variabili locali alla funzione*/
	int i;						/*Contatore per DOPPIE IMPLICAZIONI nella formula*/

	int conta_doppia_implicazione = 0,		/*Variabile per conteggio DOPPIE IMPLICAZIONI*/
	    indice_doppia_implicazione;			/*Memorizza l'indice della DOPPIA IMPLICAZIONE*/		
	
	int conversione_prop_doppia_implicazione_sx,	/*Conversione prop. prima della DOPPIA IMPLICAZIONE*/
	    conversione_prop_doppia_implicazione_dx,	/*Conversione prop. dopo della DOPPIA IMPLICAZIONE*/
	    calcolo_verita_doppia_implicazione;		/*Variabile per calcolo valore di verità*/

	for(i = 0;
    	    i < lunghezza_formula;
   	    i++)
	{
		indice_doppia_implicazione = 0;

		if(a[i] == '8')
		{
			/*Converte il char in int e lo assegna a valore*/
			conversione_prop_doppia_implicazione_sx = a[i - 1] - '0';
			conversione_prop_doppia_implicazione_dx = a[i + 1] - '0';

			/*Calcola il valore di verità*/
			calcolo_verita_doppia_implicazione = (conversione_prop_doppia_implicazione_sx & conversione_prop_doppia_implicazione_dx) | ((!(conversione_prop_doppia_implicazione_sx)) & (!(conversione_prop_doppia_implicazione_dx)));

			/*Riassegna il valore convertito nuovamente in char all'elemento dell'array*/
			a[i - 1] = calcolo_verita_doppia_implicazione + 48;
			conta_doppia_implicazione = 2;	
			indice_doppia_implicazione = i;

			/*Applica la funzione di riduzione dell'array*/
			riduzione(a, conta_doppia_implicazione, indice_doppia_implicazione, lunghezza_formula);
			i -= i;
		}
	}
}


/*Riduzione array con criteri di precendeza e associatività*/
void riduzione(char a[], int numero_connettivi, int posizione_indice, int lunghezza_formula)
{
	/*Dichiarazione delle variabili locali alla funzione*/
	char *b;	/*Array di supporto per la riduzione*/
	
	int i,		/*Contatore per lo "scorrimento" delle proposizioni*/
	    j;		/*Contatore per l'assegnamento all'array di supporto "b" i valori di "a"*/
		
	/*Ciclo per far "scalare" gli elementi verso l'inizio dell’ array*/
	for(i = posizione_indice;
    	    i < lunghezza_formula + 1;
   	    i++)
	{
		if(a[i] != '\0')
			a[i] = a[i + numero_connettivi];

		else
			i = lunghezza_formula + 1;
	}

	/*Alloco dinamicamente "b" di un grandezza pari a quella iniziale meno il connettivo trovato*/
	b = (char*)calloc((lunghezza_formula - numero_connettivi), sizeof(char));

	/*Ciclo per copiare in "b" l'array "a"*/
	for(j = 0;
    	    j < (lunghezza_formula - numero_connettivi);
    	    j++)
		b[j] = a[j];

	b[j] = '\0';

	/*Copio "b" in "a" che è stato ridotto con il metodo sopra citato*/
	a = b;

}
