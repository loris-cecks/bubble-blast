#include <stdio.h>          // libreria per scanf(), print()
#include <stdlib.h>         // libreria per rand() e exit(EXIT_SUCCESS)
#include <stdbool.h>        // libreria per il tipo di dato e i valori booleani
#include <time.h>           // libreria per srand()
#include <string.h>         // libreria per memcpy()

enum DimensioneMatrice { RIGHE = 5, COLONNE = 6 }; // matrice 5x6

enum NumeroBolle {
    NUMERO_BOLLE_MINIMO = 5,    // limite minimo del numero di bolle inserite nel campo di gioco
    NUMERO_BOLLE_BASE = 5       // limite massimo di bolle generate dalla funzione rand(), a cui viene aggiunto NUMERO_BOLLE_MINIMO
};

enum StatoPartita { PARTITA_IN_CORSO = 0, PARTITA_CONCLUSA = 1 };

// stampa le regole di gioco
void stampaIntroduzione();

// crea un campo di gioco senza bolle
void creaMatrice(int matrice[RIGHE][COLONNE]); 

// popola il campo di gioco con un numero casuale di bolle in stati casuali
void popolaMatrice(int matrice[RIGHE][COLONNE]); 

// copia il campo di gioco per la modifica da parte dell'algoritmo
void copiaMatrice(int matrice_algoritmo[RIGHE][COLONNE], int matrice[RIGHE][COLONNE]); 

// calcola e restituisce il numero minimo di mosse per vincere la partita
int algoritmo (int matrice_algoritmo[RIGHE][COLONNE]);

// se viene selezionata una bolla, viene gonfiata, esplode se era in procinto di esplodere
void cambiaStato(int riga_scelta, int colonna_scelta, int matrice[RIGHE][COLONNE]); 

    // fa esplodere la bolla in procinto di esplodere selezionata
    void esplosione(int matrice[RIGHE][COLONNE], int riga, int colonna);

        // l'esplosione viene propagata lungo due direzioni e quattro versi, colpendo eventualmente altre bolle
        void propagazioneSu (int matrice[RIGHE][COLONNE], int riga, int colonna);
        void propagazioneGiu (int matrice[RIGHE][COLONNE], int riga, int colonna);
        void propagazioneDx (int matrice[RIGHE][COLONNE], int riga, int colonna);
        void propagazioneSx (int matrice[RIGHE][COLONNE], int riga, int colonna);

// stampa la matrice di gioco generata
void stampaMatrice (int matrice[RIGHE][COLONNE]); 

// controlla se il campo di gioco è vuoto
int controllaMatrice(int matrice[RIGHE][COLONNE]); 

// stampa l'esito della partita
void esitoPartita (int stato_partita);

int main(){
    int matrice[RIGHE][COLONNE];            // campo di gioco
    int matrice_algoritmo[RIGHE][COLONNE];  // campo di gioco copiato e modificato dall'algoritmo di risoluzione
    int mosse_effettuate = 0, mosse_algoritmo = 0, mosse_disponibili;
    int riga_scelta, colonna_scelta;    // riga e colonna scelta dal giocatore ad ogni turno
    int stato_partita = PARTITA_IN_CORSO;

    stampaIntroduzione();
    creaMatrice(matrice);
    popolaMatrice(matrice);
    copiaMatrice(matrice_algoritmo, matrice);
    mosse_algoritmo = algoritmo(matrice_algoritmo);
    stampaMatrice(matrice);
    printf("\n Buona partita!\n");
    while (mosse_disponibili > 0 && stato_partita == PARTITA_IN_CORSO){
        // la partita finisce se il giocatore esaurisce le mosse o svuota il campo di gioco
        printf("\n Inserisci riga: ");  scanf("%d", &riga_scelta);
        printf(" Inserisci colonna: "); scanf("%d", &colonna_scelta);
        mosse_effettuate++;
        mosse_disponibili = mosse_algoritmo - mosse_effettuate;
        cambiaStato(riga_scelta, colonna_scelta, matrice);
        stampaMatrice(matrice);
        if (mosse_disponibili != 0)
            printf("\n Mosse disponibili: %d\n", mosse_disponibili);
        stato_partita = controllaMatrice(matrice);
    };
    esitoPartita(stato_partita);
    exit(EXIT_SUCCESS);
}

void stampaIntroduzione() {
    printf ("\n Il gioco Bubble Blast consiste nel far esplodere tutte le bolle nella griglia.\n");
    printf ("\n Le bolle si presentano in tre stati, rappresentati da tre numeri: \n");
    printf (" - 1 corrisponde ad una bolla in procinto di esplodere; - 2 ad una bolla gonfia a meta'; - 3 ad una bolla sgonfia.\n");
    printf ("\n Ogni mossa dell'utente gonfia la bolla selezionata, portandola allo stato successivo.\n");
    printf ("\n Se si seleziona una bolla in procinto di esplodere questa esplodera',\n l'esplosione si propaga in verticale e orizzontale.\n");
    printf ("\n Quando una propagazione raggiunge una bolla,\n questa si comporta come se fosse stata selezionata.\n");
    printf ("\n N.B.: la prima riga e' la numero 0 e la prima colonna e' la numero 0\n");
}

void creaMatrice (int matrice[RIGHE][COLONNE]){
    int riga, colonna;
    for (riga=0; riga<RIGHE; riga++){
        for (colonna=0; colonna<COLONNE; colonna++){
            matrice[riga][colonna] = 0;
        }
    }
}

void popolaMatrice (int matrice[RIGHE][COLONNE]){
    int numero_bolle; // numero bolle da inserire
    int riga_casuale, colonna_casuale;  // riga e colonna in cui verrà inserita una bolla

    srand((unsigned)time(0)); // inizializzazione del seme utilizzato da rand()
    numero_bolle = rand() % NUMERO_BOLLE_BASE + NUMERO_BOLLE_MINIMO;
    printf("\n Numero delle bolle inserite: %d\n", numero_bolle);
    do{
        riga_casuale = rand() % RIGHE; colonna_casuale = rand() % COLONNE; 
        if (matrice[riga_casuale][colonna_casuale] == 0){   // evita che vengano inserite bolle dove ci sono già
            matrice[riga_casuale][colonna_casuale] = rand() % 3 + 1; // inserimento di una bolla in uno stato casuale
            numero_bolle--; // decrementa il contatore delle bolle
        }
    } while (numero_bolle != 0); // all'esaurimento del numero di bolle prefissato si torna nella main()
}

void copiaMatrice (int matrice_algoritmo[RIGHE][COLONNE], int matrice[RIGHE][COLONNE]) {
    // viene creata una copia del campo di gioco per la modifica da parte dell'algoritmo
    memcpy(matrice_algoritmo, matrice, RIGHE*COLONNE*sizeof(int));
}

/**
 * input: matrice_algoritmo
 * output: mosse_algoritmo
**/
int algoritmo (int matrice_algoritmo[RIGHE][COLONNE]) {
    int riga_algoritmo, colonna_algoritmo;
    int mosse_algoritmo = 0; // contatore delle mosse effettuate dall'algoritmo
    bool continua;
    do{
        continua = true;
        for (riga_algoritmo = 0; riga_algoritmo < RIGHE; riga_algoritmo++) { // controlla il campo di gioco in cerca di una bolla
            for (colonna_algoritmo = 0; colonna_algoritmo < COLONNE; colonna_algoritmo++) {    
                if(matrice_algoritmo[riga_algoritmo][colonna_algoritmo] != 0){
                    cambiaStato(riga_algoritmo, colonna_algoritmo, matrice_algoritmo);
                    mosse_algoritmo++;
                    continua = false;
                };
            }
        }
    } while (continua == false); // continua finché non ci sono più bolle
    printf("\n Numero delle mosse calcolato dall'algoritmo di risoluzione: %d\n", mosse_algoritmo);
    return mosse_algoritmo; // restituisce il numero di mosse effettuate dall'algoritmo
}

void cambiaStato(int riga_scelta, int colonna_scelta, int matrice[RIGHE][COLONNE]){
    if (matrice[riga_scelta][colonna_scelta] != 0){ // se nella posizione scelta è presente una bolla
        matrice[riga_scelta][colonna_scelta]--;     // la bolla passa allo stato successivo
        if (matrice[riga_scelta][colonna_scelta] == 0)          // se la bolla gonfiata era in procinto di esplodere
            esplosione (matrice, riga_scelta, colonna_scelta);  // la bolla esplode
    }
}

void stampaMatrice (int matrice[RIGHE][COLONNE]) {
    int riga, colonna;
    printf("\n");
    for (riga = 0; riga < RIGHE; riga++){
        for (colonna = 0; colonna < COLONNE; colonna++){
            printf("\t%d", matrice[riga][colonna]);
        }
        printf("\n\n\n");
    }
}

/**
 * input: matrice
 * output: 1 se il campo di gioco contiene bolle
 * output: 0 se il campo di gioco è vuoto
**/
int controllaMatrice (int matrice[RIGHE][COLONNE]){
    int riga, colonna;
    int matrice_nulla = 1;
    for (riga=0; riga<RIGHE; riga++){
        for(colonna=0; colonna<COLONNE; colonna++){
            if (matrice[riga][colonna] != 0){       // se nel campo di gioco è presente almeno una bolla
                matrice_nulla = PARTITA_IN_CORSO;   // la partita è ancora in corso
            }
        }
    }
    return matrice_nulla; 
}

/**
 * input: 1 se il campo di gioco contiene bolle
 * input: 0 se il campo di gioco è vuoto
**/
void esitoPartita (int stato_partita){
    if (stato_partita == PARTITA_CONCLUSA){ //
        printf(" Vittoria!\n");
    } else {
        printf(" Sconfitta!\n");
    }
}

void esplosione (int matrice[RIGHE][COLONNE], int riga, int colonna) {
    propagazioneSu (matrice, riga, colonna);
    propagazioneGiu (matrice, riga, colonna);
    propagazioneDx (matrice, riga, colonna);
    propagazioneSx (matrice, riga, colonna);
}
void propagazioneSu (int matrice[RIGHE][COLONNE], int riga, int colonna) {
    bool bordo_superiore = false; 
    if (riga > 0){
        // se la bolla gonfiata non è sulla prima riga, allora passa alla riga sovrastante
        riga--;
        do{
            if (matrice[riga][colonna] != 0) { // se è stata gonfiata una bolla
                bordo_superiore = true;
                cambiaStato(riga,colonna,matrice);
            }else riga--;  // continua verso l'alto
            if (riga < 0) bordo_superiore = true;
        } while (bordo_superiore != true);
    }
}
void propagazioneGiu (int matrice[RIGHE][COLONNE], int riga, int colonna){
    bool bordo_inferiore = false;
    if (riga < RIGHE-1){
        // se la bolla gonfiata non è sull'ultima riga, allora passa alla riga sottostante
        riga++;
        do{
            if (matrice[riga][colonna] != 0){ // se è stata gonfiata una bolla
                bordo_inferiore = true;
                cambiaStato(riga,colonna,matrice);
            } else riga++; // continua verso il basso
            if (riga == RIGHE) bordo_inferiore = true;
        } while (bordo_inferiore != true);
    }
}
void propagazioneDx (int matrice[RIGHE][COLONNE], int riga, int colonna){
    bool bordo_dx = false;
    if (colonna < COLONNE-1){
        // se la bolla gonfiata non è sull'ultima colonna, allora passa alla colonna alla sua destra
        colonna++;
        do {
            if (matrice[riga][colonna] != 0) { // se è stata gonfiata una bolla
                bordo_dx = true;
                cambiaStato(riga,colonna,matrice);
            }else colonna++; // continua verso destra
            if (colonna == COLONNE) bordo_dx = true;
        } while (bordo_dx != true);
    }
}
void propagazioneSx (int matrice[RIGHE][COLONNE], int riga, int colonna){
    // se la bolla gonfiata non è sull'ultima colonna, allora passa alla colonna alla sua sinistra
    bool bordo_sx = false;
    if (colonna > 0){
        colonna--;
        do{
            if (matrice[riga][colonna] != 0) { // se è stata gonfiata una bolla
                bordo_sx = true;
                cambiaStato(riga,colonna,matrice);
            } else colonna--; // continua verso destra
            if (colonna < 0) bordo_sx = true;
        } while (bordo_sx != true);
    }
}