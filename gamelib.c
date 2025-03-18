#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "gamelib.h"
static void clear_buffer(void);

// variabili per impostare il gioco
bool creagiocatori = false;
int n_giocatori;

// struct creazione giocatore
struct Giocatore *giocatore1;
struct Giocatore *giocatore2;
struct Giocatore *giocatore3;
// variabili creazione giocatore
char nome_giocatore1[50];
char nome_giocatore2[50];
char nome_giocatore3[50];
// variabile globale punti vita
int p_vita_max;

// variabili mappa
bool creazionemappa = false;
bool mappa_valida = false;
int value_mappa;
// int scelta_tipo_stanza;
struct Stanza *nuovastanza;
struct Stanza *temp;          // puntatore che scorre tutta la lista delle stanze
struct Stanza *prec = NULL;   // tiene traccia del penultimo nodo inserito, quindi si attiva solo quando abbiamo più di una stanza in quella posizione
struct Stanza *pFirst = NULL; // puntatore che identifica la prima stanza creata
struct Stanza *pLast = NULL;  // puntatore che identifica l'ultima stanza creata
int scelta_tipo_stanza;
int risultato_tipo_stanza;
int scelta_tesoro;
int risultato_tesoro;
int scelta_trabocchetto;
int risultato_trabocchetto;
int posizione;
int risultato_posizione;
int numero_stanza;

// variabili gioco
int scelta_gioco;
bool vittoria = false;
int random_combatti;
struct Nemico *Nemico;
bool apparso_nemico;
bool trabocchetto;
int turni_avanzati;
bool passa_turno;
static void pulizia_buffer(void)
{
    while (getchar() != '\n')
        ;
}
void termina_gioco()
{
}
void creagiocatore()
{
    int scelta_classe = 0;
    switch (n_giocatori)
    {
    case 1:
        giocatore1 = (struct Giocatore *)malloc(sizeof(struct Giocatore)); // vado a creare la struct di giocatore1 chiamando il malloc e la struct Giocatore
        {
            printf("inserire il nome del giocatore1: ");
            scanf("%50s", nome_giocatore1);                      // imposto il nome
            strcpy(giocatore1->nome_giocatore, nome_giocatore1); // gli passo il nome a giocatore1

            giocatore1->p_vita_max = 3;
            giocatore1->p_vita = giocatore1->p_vita_max;
            printf("\x1b[33m%s\x1b[37m inizia con la vita max:%u\n", giocatore1->nome_giocatore, giocatore1->p_vita_max);
            printf("\x1b[33m%s\x1b[37m inizia con la vita:%u\n", giocatore1->nome_giocatore, giocatore1->p_vita);

            printf("\nla classe di \x1b[33m%s\x1b[37m è Principe perchè è impostato di defualt essendo un unico giocatore\n", giocatore1->nome_giocatore);
            giocatore1->classe = PRINCIPE;

            printf("\x1b[33m%s\x1b[37m puoi scappare solo 1 volta dato che sei un PRINCIPE\n", giocatore1->nome_giocatore);
            giocatore1->scappare = 1;

            giocatore1->dadi_attacco = 2; // inizio predefinito con 2 dadi di attacco
            giocatore1->dadi_difesa = 2;  // inizio predefinito con 2 dadi di difesa
            printf("\x1b[33m%s\x1b[37m inizia con %u dadi in attacco\n", giocatore1->nome_giocatore, giocatore1->dadi_attacco);
            printf("\x1b[33m%s\x1b[37m inizia con %u dadi in difesa\n", giocatore1->nome_giocatore, giocatore1->dadi_difesa);
        }
        creagiocatori = true;
        break;
    case 2:
        giocatore1 = (struct Giocatore *)malloc(sizeof(struct Giocatore)); // vado a creare la struct di giocatore1 chiamando il malloc e la struct Giocatore
        giocatore2 = (struct Giocatore *)malloc(sizeof(struct Giocatore));
        {
            printf("inserire il nome del giocatore1: ");
            scanf("%s", nome_giocatore1);
            strcpy(giocatore1->nome_giocatore, nome_giocatore1);

            printf("inserire il nome del giocatore2: ");
            scanf("%s", nome_giocatore2);
            strcpy(giocatore2->nome_giocatore, nome_giocatore2);

            printf("\ncontinuiamo ora con la creazione del giocatore1:\x1b[33m%s\x1b[37m\n", giocatore1->nome_giocatore);
            giocatore1->p_vita_max = 3;
            giocatore1->p_vita = giocatore1->p_vita_max;
            printf("\x1b[33m%s\x1b[37m inizia con la vita max:%u\n", giocatore1->nome_giocatore, giocatore1->p_vita_max);
            printf("\x1b[33m%s\x1b[37m inizia con la vita:%u\n", giocatore1->nome_giocatore, giocatore1->p_vita);
            do
            {
                printf("selezionare se essere:\n");
                printf("1) PRINCIPE\n");
                printf("2) DOPPLEGANGER\n");
                printf("inserire la scelta della classe:");
                scanf("%d", &scelta_classe);
                pulizia_buffer();
                if (scelta_classe < 1 || scelta_classe > 2)
                {
                    printf("\x1b[31m errore, digitare un numero tra 1 e 2 \x1b[37m\n");
                }
            } while (scelta_classe < 1 || scelta_classe > 2);
            if (scelta_classe == 1)
            {
                giocatore1->classe = PRINCIPE;
                printf("\x1b[33m%s\x1b[37m puoi scappare solo 1 volta dato che sei un PRINCIPE\n", giocatore1->nome_giocatore);
                giocatore1->scappare = 1;

                giocatore1->dadi_attacco = 2; // inizio predefinito con 2 dadi di attacco
                giocatore1->dadi_difesa = 2;  // inizio predefinito con 2 dadi di difesa
                printf("\x1b[33m%s\x1b[37m inizia con %u dadi in attacco\n", giocatore1->nome_giocatore, giocatore1->dadi_attacco);
                printf("\x1b[33m%s\x1b[37m inizia con %u dadi in difesa\n", giocatore1->nome_giocatore, giocatore1->dadi_difesa);
                printf("il giocatore:\x1b[33m%s\x1b[37m ha scelto di essere PRINCIPE\n", giocatore1->nome_giocatore);
            }
            else
            {
                giocatore1->classe = DOPPLEGANGER;
                printf("\x1b[33m%s\x1b[37m puoi scappare 2 volte dato che sei un DOPPLEGANGER\n", giocatore1->nome_giocatore);
                giocatore1->scappare = 2;

                giocatore1->dadi_attacco = 2; // inizio predefinito con 2 dadi di attacco
                giocatore1->dadi_difesa = 2;  // inizio predefinito con 2 dadi di difesa
                printf("\x1b[33m%s\x1b[37m inizia con %u dadi in attacco\n", giocatore1->nome_giocatore, giocatore1->dadi_attacco);
                printf("\x1b[33m%s\x1b[37m inizia con %u dadi in difesa\n", giocatore1->nome_giocatore, giocatore1->dadi_difesa);
                printf("il giocatore:\x1b[33m%s\x1b[37m ha scelto di essere DOPPLEGANGER\n", giocatore1->nome_giocatore);
            }
            scelta_classe = 0;
            printf("\ndopo aver completato la creazione del giocatore1 andiamo a finire quella del giocatore2:\x1b[32m%s\x1b[37m\n", giocatore2->nome_giocatore);
            giocatore2->p_vita_max = 3;
            giocatore2->p_vita = giocatore2->p_vita_max;
            printf("\x1b[32m%s\x1b[37m inizia con la vita max:%u\n", giocatore2->nome_giocatore, giocatore2->p_vita_max);
            printf("\x1b[32m%s\x1b[37m inizia con la vita:%u\n", giocatore2->nome_giocatore, giocatore2->p_vita);
            if (giocatore1->classe == PRINCIPE)
            {
                do
                {
                    printf("selezionare se essere:\n");
                    printf("1) PRINCIPE\n");
                    printf("2) DOPPLEGANGER\n");
                    printf("inserire la scelta della classe:");
                    scanf("%d", &scelta_classe);
                    pulizia_buffer();
                    if (scelta_classe < 1 || scelta_classe > 2)
                    {
                        printf("\x1b[31m errore, digitare un numero tra 1 e 2 \x1b[37m\n");
                    }
                } while (scelta_classe < 1 || scelta_classe > 2);
                if (scelta_classe == 1)
                {
                    giocatore2->classe = PRINCIPE;
                    printf("\x1b[32m%s\x1b[37m puoi scappare solo 1 volta dato che sei un PRINCIPE\n", giocatore2->nome_giocatore);
                    giocatore2->scappare = 1;

                    giocatore2->dadi_attacco = 2; // inizio predefinito con 2 dadi di attacco
                    giocatore2->dadi_difesa = 2;  // inizio predefinito con 2 dadi di difesa
                    printf("\x1b[32m%s\x1b[37m inizia con %u dadi in attacco\n", giocatore2->nome_giocatore, giocatore2->dadi_attacco);
                    printf("\x1b[32m%s\x1b[37m inizia con %u dadi in difesa\n", giocatore2->nome_giocatore, giocatore2->dadi_difesa);
                    printf("il giocatore:\x1b[32m%s\x1b[37m ha scelto di essere PRINCIPE\n", giocatore2->nome_giocatore);
                }
                else
                {
                    giocatore2->classe = DOPPLEGANGER;
                    printf("\x1b[32m%s\x1b[37m puoi scappare 2 volta dato che sei un DOPPLEGANGER\n", giocatore2->nome_giocatore);
                    giocatore2->scappare = 2;

                    giocatore2->dadi_attacco = 2; // inizio predefinito con 2 dadi di attacco
                    giocatore2->dadi_difesa = 2;  // inizio predefinito con 2 dadi di difesa
                    printf("\x1b[32m%s\x1b[37m inizia con %u dadi in attacco\n", giocatore2->nome_giocatore, giocatore2->dadi_attacco);
                    printf("\x1b[32m%s\x1b[37m inizia con %u dadi in difesa\n", giocatore2->nome_giocatore, giocatore2->dadi_difesa);
                    printf("il giocatore:\x1b[32m%s\x1b[37m ha scelto di essere DOPPLEGANGER\n", giocatore2->nome_giocatore);
                }
            }

            else
            {
                printf("\x1b[32m%s\x1b[37m è obbligato a scegliere:PRINCIPE\n", giocatore2->nome_giocatore);
                giocatore2->classe = PRINCIPE;
                printf("\x1b[32m%s\x1b[37m puoi scappare solo 1 volta dato che sei un PRINCIPE\n", giocatore2->nome_giocatore);
                giocatore2->scappare = 1;

                giocatore2->dadi_attacco = 2; // inizio predefinito con 2 dadi di attacco
                giocatore2->dadi_difesa = 2;  // inizio predefinito con 2 dadi di difesa
                printf("\x1b[32m%s\x1b[37m inizia con %u dadi in attacco\n", giocatore2->nome_giocatore, giocatore2->dadi_attacco);
                printf("\x1b[32m%s\x1b[37m inizia con %u dadi in difesa\n", giocatore2->nome_giocatore, giocatore2->dadi_difesa);
            }
        }
        creagiocatori = true;
        break;
    case 3:
        giocatore1 = (struct Giocatore *)malloc(sizeof(struct Giocatore)); // vado a creare la struct di giocatore1 chiamando il malloc e la struct Giocatore
        giocatore2 = (struct Giocatore *)malloc(sizeof(struct Giocatore));
        giocatore3 = (struct Giocatore *)malloc(sizeof(struct Giocatore));
        {
            printf("inserire il nome del giocatore1: ");
            scanf("%s", nome_giocatore1);
            strcpy(giocatore1->nome_giocatore, nome_giocatore1);

            printf("inserire il nome del giocatore2: ");
            scanf("%s", nome_giocatore2);
            strcpy(giocatore2->nome_giocatore, nome_giocatore2);

            printf("inserire il nome del giocatore3: ");
            scanf("%s", nome_giocatore3);
            strcpy(giocatore3->nome_giocatore, nome_giocatore3); // 35 numero colorato

            printf("\ncontinuiamo ora con la creazione del giocatore 1:\x1b[33m%s\x1b[37m\n", giocatore1->nome_giocatore);
            giocatore1->p_vita_max = 3;
            giocatore1->p_vita = giocatore1->p_vita_max;
            printf("\x1b[33m%s\x1b[37m inizia con la vita max:%u\n", giocatore1->nome_giocatore, giocatore1->p_vita_max);
            printf("\x1b[33m%s\x1b[37m inizia con la vita:%u\n", giocatore1->nome_giocatore, giocatore1->p_vita);
            do
            {
                printf("selezionare se essere:\n");
                printf("1) PRINCIPE\n");
                printf("2) DOPPLEGANGER\n");
                printf("inserire la scelta della classe:");
                scanf("%d", &scelta_classe);
                pulizia_buffer();
                if (scelta_classe < 1 || scelta_classe > 2)
                {
                    printf("\x1b[31m errore, digitare un numero tra 1 e 2 \x1b[37m\n");
                }
            } while (scelta_classe < 1 || scelta_classe > 2);
            if (scelta_classe == 1)
            {
                giocatore1->classe = PRINCIPE;
                printf("\x1b[33m%s\x1b[37m puoi scappare solo 1 volta dato che sei un PRINCIPE\n", giocatore1->nome_giocatore);
                giocatore1->scappare = 1;

                giocatore1->dadi_attacco = 2; // inizio predefinito con 2 dadi di attacco
                giocatore1->dadi_difesa = 2;  // inizio predefinito con 2 dadi di difesa
                printf("\x1b[33m%s\x1b[37m inizia con %u dadi in attacco\n", giocatore1->nome_giocatore, giocatore1->dadi_attacco);
                printf("\x1b[33m%s\x1b[37m inizia con %u dadi in difesa\n", giocatore1->nome_giocatore, giocatore1->dadi_difesa);
                printf("il giocatore:\x1b[33m%s\x1b[37m ha scelto di essere PRINCIPE\n", giocatore1->nome_giocatore);
            }
            else
            {
                giocatore1->classe = DOPPLEGANGER;
                printf("\x1b[33m%s\x1b[37m puoi scappare 2 volta dato che sei un DOPPLEGANGER\n", giocatore1->nome_giocatore);
                giocatore1->scappare = 2;

                giocatore1->dadi_attacco = 2; // inizio predefinito con 2 dadi di attacco
                giocatore1->dadi_difesa = 2;  // inizio predefinito con 2 dadi di difesa
                printf("\x1b[33m%s\x1b[37m inizia con %u dadi in attacco\n", giocatore1->nome_giocatore, giocatore1->dadi_attacco);
                printf("\x1b[33m%s\x1b[37m inizia con %u dadi in difesa\n", giocatore1->nome_giocatore, giocatore1->dadi_difesa);
                printf("il giocatore:\x1b[33m%s\x1b[37m ha scelto di essere DOPPLEGANGER\n", giocatore1->nome_giocatore);
            }
            scelta_classe = 0;
            printf("dopo aver completato la creazione del giocatore1 andiamo a finire quella del giocatore2:\x1b[32m%s\x1b[37m\n", giocatore2->nome_giocatore);
            giocatore2->p_vita_max = 3;
            giocatore2->p_vita = giocatore2->p_vita_max;
            printf("\x1b[32m%s\x1b[37m inizia con la vita max:%u\n", giocatore2->nome_giocatore, giocatore2->p_vita_max);
            printf("\x1b[32m%s\x1b[37m inizia con la vita:%u\n", giocatore2->nome_giocatore, giocatore2->p_vita);
            do
            {
                printf("selezionare se essere:\n");
                printf("1) PRINCIPE\n");
                printf("2) DOPPLEGANGER\n");
                printf("inserire la scelta della classe:");
                scanf("%d", &scelta_classe);
                pulizia_buffer();
                if (scelta_classe < 1 || scelta_classe > 2)
                {
                    printf("\x1b[31m errore, digitare un numero tra 1 e 2 \x1b[37m\n");
                }
            } while (scelta_classe < 1 || scelta_classe > 2);
            if (scelta_classe == 1)
            {
                giocatore2->classe = PRINCIPE;
                printf("\x1b[32m%s\x1b[37m puoi scappare solo 1 volta dato che sei un PRINCIPE\n", giocatore2->nome_giocatore);
                giocatore2->scappare = 1;

                giocatore2->dadi_attacco = 2; // inizio predefinito con 2 dadi di attacco
                giocatore2->dadi_difesa = 2;  // inizio predefinito con 2 dadi di difesa
                printf("\x1b[32m%s\x1b[37m inizia con %u dadi in attacco\n", giocatore2->nome_giocatore, giocatore2->dadi_attacco);
                printf("\x1b[32m%s\x1b[37m inizia con %u dadi in difesa\n", giocatore2->nome_giocatore, giocatore2->dadi_difesa);
                printf("il giocatore:\x1b[32m%s\x1b[37m ha scelto di essere PRINCIPE\n", giocatore2->nome_giocatore);
            }
            else
            {
                giocatore2->classe = DOPPLEGANGER;
                printf("\x1b[32m%s\x1b[37m puoi scappare solo 1 volta dato che sei un DOPPLEGANGER\n", giocatore2->nome_giocatore);
                giocatore2->scappare = 2;

                giocatore2->dadi_attacco = 2; // inizio predefinito con 2 dadi di attacco
                giocatore2->dadi_difesa = 2;  // inizio predefinito con 2 dadi di difesa
                printf("\x1b[32m%s\x1b[37m inizia con %u dadi in attacco\n", giocatore2->nome_giocatore, giocatore2->dadi_attacco);
                printf("\x1b[32m%s\x1b[37m inizia con %u dadi in difesa\n", giocatore2->nome_giocatore, giocatore2->dadi_difesa);
                printf("il giocatore:\x1b[32m%s\x1b[37m ha scelto di essere DOPPLEGANGER\n", giocatore2->nome_giocatore);
            }
            scelta_classe = 0;
            printf("dopo aver completato la creazione del giocatore1 e il giocatore2 andiamo a finire quella del giocatore3:\x1b[35m%s\x1b[37m\n", giocatore3->nome_giocatore);
            giocatore3->p_vita_max = 3;
            giocatore3->p_vita = giocatore3->p_vita_max;
            printf("\x1b[35m%s\x1b[37m inizia con la vita max:%u\n", giocatore3->nome_giocatore, giocatore3->p_vita_max);
            printf("\x1b[35m%s\x1b[37m inizia con la vita:%u\n", giocatore3->nome_giocatore, giocatore3->p_vita);
            if (giocatore1->classe == PRINCIPE || giocatore2->classe == PRINCIPE)
            {
                do
                {
                    printf("selezionare se essere:\n");
                    printf("1) PRINCIPE\n");
                    printf("2) DOPPLEGANGER\n");
                    printf("inserire la scelta della classe:");
                    scanf("%d", &scelta_classe);
                    pulizia_buffer();
                    if (scelta_classe < 1 || scelta_classe > 2)
                    {
                        printf("\x1b[31m errore, digitare un numero tra 1 e 2 \x1b[37m\n");
                    }
                } while (scelta_classe < 1 || scelta_classe > 2);
                if (scelta_classe == 1)
                {
                    giocatore3->classe = PRINCIPE;
                    printf("\x1b[35m%s\x1b[37m puoi scappare solo 1 volta dato che sei un PRINCIPE\n", giocatore3->nome_giocatore);
                    giocatore3->scappare = 1;

                    giocatore3->dadi_attacco = 2; // inizio predefinito con 2 dadi di attacco
                    giocatore3->dadi_difesa = 2;  // inizio predefinito con 2 dadi di difesa
                    printf("\x1b[35m%s\x1b[37m inizia con %u dadi in attacco\n", giocatore3->nome_giocatore, giocatore3->dadi_attacco);
                    printf("\x1b[35m%s\x1b[37m inizia con %u dadi in difesa\n", giocatore3->nome_giocatore, giocatore3->dadi_difesa);
                    printf("il giocatore:\x1b[32m%s\x1b[37m ha scelto di essere PRINCIPE\n", giocatore3->nome_giocatore);
                }
                else
                {
                    giocatore3->classe = DOPPLEGANGER;
                    printf("\x1b[35m%s\x1b[37m puoi scappare solo 1 volta dato che sei un DOPPLEGANGER\n", giocatore3->nome_giocatore);
                    giocatore3->scappare = 2;

                    giocatore3->dadi_attacco = 2; // inizio predefinito con 2 dadi di attacco
                    giocatore3->dadi_difesa = 2;  // inizio predefinito con 2 dadi di difesa
                    printf("\x1b[35m%s\x1b[37m inizia con %u dadi in attacco\n", giocatore3->nome_giocatore, giocatore3->dadi_attacco);
                    printf("\x1b[35m%s\x1b[37m inizia con %u dadi in difesa\n", giocatore3->nome_giocatore, giocatore3->dadi_difesa);
                    printf("il giocatore:\x1b[32m%s\x1b[37m ha scelto di essere DOPPLEGANGER\n", giocatore3->nome_giocatore);
                }
            }

            else
            {
                printf("\x1b[32m%s\x1b[37m è obbligato a scegliere:PRINCIPE\n", giocatore3->nome_giocatore);
                giocatore3->classe = PRINCIPE;
                printf("\x1b[35m%s\x1b[37m puoi scappare solo 1 volta dato che sei un PRINCIPE\n", giocatore3->nome_giocatore);

                giocatore3->dadi_attacco = 2; // inizio predefinito con 2 dadi di attacco
                giocatore3->dadi_difesa = 2;  // inizio predefinito con 2 dadi di difesa
                printf("\x1b[35m%s\x1b[37m inizia con %u dadi in attacco\n", giocatore3->nome_giocatore, giocatore3->dadi_attacco);
                printf("\x1b[35m%s\x1b[37m inizia con %u dadi in difesa\n", giocatore3->nome_giocatore, giocatore3->dadi_difesa);
            }
            creagiocatori = true;
            break;
        }
    default:
        creagiocatori = false;
        printf("\x1b[31m errore, digitare un numero tra 0 e 3 \x1b[37m\n");
        break;
    }
    imposta_gioco(); // richiamo metodo imposta_gioco, così da impostare i rimanenti comandi
}
void inserisci_stanza()
{
    struct Stanza *nuovastanza = (struct stanza *)malloc(sizeof(struct Stanza)); // creazione di una nuova stanza nella memoria
    do
    {
        printf("0:Corridoio\n");
        printf("1:Scala\n");
        printf("2:Sala banchetto\n");
        printf("3:Magazzino\n");
        printf("4:Posto guardia\n");
        printf("5:Prigione\n");
        printf("6:Armeria\n");
        printf("7:Moschea\n");
        printf("8:Torre\n");
        printf("9:Bagni\n");
        printf("Scegli la stanza da inserire: ");
        risultato_tipo_stanza = scanf("%d", &scelta_tipo_stanza);
        if (risultato_tipo_stanza != 1) // Se scanf non ha letto un numero valido
        {
            printf("\x1b[31mErrore, inserire un numero tra 0 e 9\x1b[37m\n");
            // Pulisce il buffer dell'input
            pulizia_buffer();
            scelta_tipo_stanza = -1; // Imposta un valore non valido per ripetere il ciclo
        }
        else if (scelta_tipo_stanza < 0 || scelta_tipo_stanza > 9)
        {
            printf("\x1b[31mErrore, digitare un numero tra 0 e 9\x1b[37m\n");
        }
    } while (scelta_tipo_stanza < 0 || scelta_tipo_stanza > 9);
    nuovastanza->tipo_stanza = scelta_tipo_stanza;
    do
    {
        printf("0:Nessuno\n");
        printf("1:Tegola\n");
        printf("2:Lame\n");
        printf("3:Caduta\n");
        printf("4:Burrone\n");
        printf("scegli il trabocchetto da inserire: ");
        risultato_trabocchetto = scanf("%d", &scelta_trabocchetto);
        if (risultato_trabocchetto != 1) // Se scanf non ha letto un numero valido
        {
            printf("\x1b[31mErrore, inserire un numero tra 0 e 4\x1b[37m\n");
            // Pulisce il buffer dell'input
            pulizia_buffer();
            scelta_trabocchetto = -1; // Imposta un valore non valido per ripetere il ciclo
        }
        else if (scelta_trabocchetto < 0 || scelta_trabocchetto > 4)
        {
            printf("\x1b[31m errore, digitare un numero tra 0 e 4 \x1b[37m\n");
        }
    } while (scelta_trabocchetto < 0 || scelta_trabocchetto > 4);
    nuovastanza->tipo_trabocchetto = scelta_trabocchetto;
    do
    {
        printf("0:Nessun tesoro\n");
        printf("1:Verde veleno\n");
        printf("2:Blu guarigione\n");
        printf("3:Rosso aumenta vita\n");
        printf("4:Spada tagliente\n");
        printf("5:Scudo\n");
        printf("scegli il tesoro da inserire: ");
        risultato_tesoro = scanf("%d", &scelta_tesoro);
        if (risultato_tesoro != 1) // Se scanf non ha letto un numero valido
        {
            printf("\x1b[31mErrore, inserire un numero tra 0 e 5\x1b[37m\n");
            // Pulisce il buffer dell'input
            pulizia_buffer();
            scelta_tesoro = -1; // Imposta un valore non valido per ripetere il ciclo
        }
        else if (scelta_tesoro < 0 || scelta_tesoro > 5)
        {
            printf("\x1b[31m errore, digitare un numero tra 0 e 5 \x1b[37m\n");
        }
    } while (scelta_tesoro < 0 || scelta_tesoro > 5);
    nuovastanza->tipo_tesoro = scelta_tesoro;
    do
    {
        printf("\n***********************************\x1b[36m POSIZIONE STANZA \x1b[37m*******************************************\n");
        printf("1-sopra\n");
        printf("2-sotto\n");
        printf("3-destra\n");
        printf("4-sinistra\n");
        printf("******************************************************************************************\n");
        printf("In quale posizione vuoi mettere la stanza? ");
        risultato_posizione = scanf("%d", &posizione);
        if (risultato_posizione != 1) // Se scanf non ha letto un numero valido
        {
            printf("\x1b[31mErrore, inserire un numero tra 1 e 4\x1b[37m\n");
            // Pulisce il buffer dell'input
            pulizia_buffer();
            posizione = -1; // Imposta un valore non valido per ripetere il ciclo
        }
        else if (posizione < 1 || posizione > 4)
        {
            printf("\x1b[31m errore, digitare un numero tra 1 e 4 \x1b[37m\n");
        }
    } while (posizione < 1 || posizione > 4);
    if (pLast == NULL)
    {
        pFirst = nuovastanza;
        pLast = nuovastanza;
        nuovastanza->next = NULL;
    }
    switch (posizione)
    {       // modificare switch renderlo più semplice
    case 1: // Sopra
        if (pLast->stanza_sopra == NULL)
        {
            pLast->stanza_sopra = nuovastanza;
            nuovastanza->stanza_sotto = pLast; // Collega sotto
        }
        break;
    case 2: // Sotto
        if (pLast->stanza_sotto == NULL)
        {
            pLast->stanza_sotto = nuovastanza;
            nuovastanza->stanza_sopra = pLast; // Collega sopra
        }
        break;
    case 3: // Destra
        if (pLast->stanza_destra == NULL)
        {
            pLast->stanza_destra = nuovastanza;
            nuovastanza->stanza_sinistra = pLast; // Collega sinistra
        }
        break;
    case 4: // Sinistra
        if (pLast->stanza_sinistra == NULL)
        {
            pLast->stanza_sinistra = nuovastanza;
            nuovastanza->stanza_destra = pLast; // Collega destra
        }
        break;
    default:
        printf("Posizione non valida.\n");
        free(nuovastanza);
        return;
    }

    // Collega la stanza corrente al "next"
    pLast->next = nuovastanza; // Imposta il puntatore "next" della stanza precedente alla nuova stanza
    pLast = nuovastanza;       // Aggiorna pLast all'ultima stanza inserita
}

void cancella_stanza()
{
    if (pFirst == NULL)
    {
        printf("La mappa è vuota, non ci sono stanze da cancellare.\n");
        return;
    }

    if (pFirst->next == NULL)
    {
        // Se c'è solo una stanza, non possiamo cancellarla
        printf("Non puoi cancellare l'ultima stanza rimasta.\n");
        return;
    }

    temp = pFirst;

    // Iteriamo fino all'ultima stanza
    while (temp->next != NULL)
    {
        prec = temp;
        temp = temp->next;
    }

    // Ora 'temp' è l'ultima stanza, 'prec' è la penultima stanza
    // Se 'prec' è diverso da NULL, significa che abbiamo almeno due stanze nella lista
    if (prec != NULL)
    {
        // dettagli ultima stanza
        printf("Tipo stanza: %d\n", temp->tipo_stanza);
        printf("Tipo tesoro: %d\n", temp->tipo_tesoro);
        printf("Tipo trabocchetto: %d\n", temp->tipo_trabocchetto);
        // Liberiamo la memoria dell'ultima stanza
        free(temp);

        // Impostiamo il puntatore 'next' della penultima stanza a NULL
        prec->next = NULL;

        printf("Ultima stanza cancellata correttamente.\n");
    }
}

// Funzione per stampare la mappa del castello
// Funzione ricorsiva per stampare le stanze senza ripetizioni
void stampa_stanza(struct Stanza *stanza, int *stanza_id)
{ // stampare menno cose
    if (stanza == NULL)
        return;

    printf("\n-------------------------------------\n");
    printf("Stanza #%d\n", (*stanza_id)++);
    printf("Tipo stanza: %d\n", stanza->tipo_stanza);
    printf("Tipo trabocchetto: %d\n", stanza->tipo_trabocchetto);
    printf("Tipo tesoro: %d\n", stanza->tipo_tesoro);

    printf("Puntatori (esadecimale):\n");
    printf("  Indirizzo stanza: %p\n", (void *)stanza);
    printf("  Sopra:   %p\n", (void *)stanza->stanza_sopra);
    printf("  Sotto:   %p\n", (void *)stanza->stanza_sotto);
    printf("  Destra:  %p\n", (void *)stanza->stanza_destra);
    printf("  Sinistra: %p\n", (void *)stanza->stanza_sinistra);

    // Segna la stanza come visitata (modificando un campo facoltativo o un array esterno)
    stanza->tipo_stanza = -1; // Indica che la stanza è già stata stampata

    // Visita le stanze collegate se non già visitate
    if (stanza->stanza_sopra && stanza->stanza_sopra->tipo_stanza != -1)
        stampa_stanza(stanza->stanza_sopra, stanza_id);
    if (stanza->stanza_sotto && stanza->stanza_sotto->tipo_stanza != -1)
        stampa_stanza(stanza->stanza_sotto, stanza_id);
    if (stanza->stanza_destra && stanza->stanza_destra->tipo_stanza != -1)
        stampa_stanza(stanza->stanza_destra, stanza_id);
    if (stanza->stanza_sinistra && stanza->stanza_sinistra->tipo_stanza != -1)
        stampa_stanza(stanza->stanza_sinistra, stanza_id);
}
// Funzione principale per stampare tutta la mappa
void stampa_mappa()
{
    if (pFirst == NULL)
    {
        printf("La mappa è vuota!\n");
        return;
    }

    struct Stanza *temp = pFirst;
    int stanza_id = 1;

    printf("\n===== MAPPA DEL DUNGEON =====\n");

    while (temp != NULL)
    {
        printf("\n-------------------------------------\n");
        printf("Stanza #%d\n", stanza_id++);
        printf("Tipo stanza: %d\n", temp->tipo_stanza);
        printf("Tipo trabocchetto: %d\n", temp->tipo_trabocchetto);
        printf("Tipo tesoro: %d\n", temp->tipo_tesoro);

        // Stampa i puntatori per verificare se sono correttamente impostati
        printf("Puntatori (esadecimale):\n");
        printf("  Indirizzo stanza: %p\n", (void *)temp);
        printf("  Sopra:   %p\n", (void *)temp->stanza_sopra);
        printf("  Sotto:   %p\n", (void *)temp->stanza_sotto);
        printf("  Destra:  %p\n", (void *)temp->stanza_destra);
        printf("  Sinistra:%p\n", (void *)temp->stanza_sinistra);

        // Aggiungi la stampa di next, se è la lista semplice
        printf("  Next:    %p\n", (void *)temp->next);

        temp = temp->next; // Passa alla prossima stanza nella lista
    }
    printf("\n===== FINE MAPPA =====\n");
}

void genera_stanza_random()
{
    int mappa_random;
    if (creazionemappa == true)
    {
        printf("Sei sicuro di voler creare una nuova mappa con 15 stanze? Perderai la mappa attuale.\n");
        printf("1 - Sì\n");
        printf("2 - No\n");
        printf("digita la risposta: ");
        // Controllo dello scanf
        if (scanf("%d", &mappa_random) != 1)
        {
            printf("\x1b[31mErrore: input non valido. Riprova.\x1b[37m\n");
            pulizia_buffer();
            return;
        }

        if (mappa_random == 1)
        {
            numero_stanza = 0;
            // Cancella la mappa attuale
            while (pFirst != NULL)
            {
                temp = pFirst;
                pFirst = pFirst->next;
                free(temp);
            }
            pLast = NULL;
            creazionemappa = false;
            printf("\x1b[32mMappa cancellata con successo!\x1b[37m\n");

            // Creazione di 15 stanze casuali
            for (int i = 0; i < 15; i++)
            {
                numero_stanza++;
                struct Stanza *nuovastanza = (struct Stanza *)malloc(sizeof(struct Stanza));
                if (!nuovastanza)
                {
                    printf("Errore nell'allocazione della memoria\n");
                    return;
                }

                // Inizializza i puntatori a NULL per evitare valori casuali
                nuovastanza->stanza_destra = NULL;
                nuovastanza->stanza_sinistra = NULL;
                nuovastanza->stanza_sopra = NULL;
                nuovastanza->stanza_sotto = NULL;
                nuovastanza->next = NULL;

                // Generazione casuale del tipo di stanza
                int n_random_stanza = rand() % 10; // Numero casuale tra 0 e 9
                nuovastanza->tipo_stanza = n_random_stanza;
                int n_random_trabocchetto = rand() % 100 + 1;
                if (n_random_trabocchetto <= 65)
                {
                    nuovastanza->tipo_trabocchetto = NESSUNO;
                }
                else if (n_random_trabocchetto <= 75)
                {
                    nuovastanza->tipo_trabocchetto = TEGOLA;
                }
                else if (n_random_trabocchetto <= 84)
                {
                    nuovastanza->tipo_trabocchetto = LAME;
                }
                else if (n_random_trabocchetto <= 92)
                {
                    nuovastanza->tipo_trabocchetto = CADUTA;
                }
                else if (n_random_trabocchetto <= 100)
                {
                    nuovastanza->tipo_trabocchetto = BURRONE;
                }
                else
                {
                    printf("\x1b[31m errore nella generazione di trabocchetti\x1b[37m\n");
                }
                int n_random_tesoro = rand() % 100 + 1;
                if (n_random_tesoro <= 20)
                {
                    nuovastanza->tipo_tesoro = NESSUN_TESORO;
                }
                else if (n_random_tesoro <= 40)
                {
                    nuovastanza->tipo_tesoro = VERDE_VELENO;
                }
                else if (n_random_tesoro <= 60)
                {
                    nuovastanza->tipo_tesoro = BLU_GUARIGIONE;
                }
                else if (n_random_tesoro <= 75)
                {
                    nuovastanza->tipo_tesoro = ROSSO_AUMENTA_VITA;
                }
                else if (n_random_tesoro <= 90)
                {
                    nuovastanza->tipo_tesoro = SPADA_TAGLIENTE;
                }
                else if (n_random_tesoro <= 100)
                {
                    nuovastanza->tipo_tesoro = SCUDO;
                }
                else
                {
                    printf("\x1b[31m errore nella generazione dei tesori\x1b[37m\n");
                }

                // Generazione casuale della posizione (1-4)
                int posizione = (rand() % 4) + 1;

                if (pLast == NULL)
                {
                    pFirst = nuovastanza;
                    pLast = nuovastanza;
                }
                else
                {
                    switch (posizione)
                    {
                    case 1: // Sopra
                        if (pLast->stanza_sopra == NULL)
                        {
                            pLast->stanza_sopra = nuovastanza;
                            nuovastanza->stanza_sotto = pLast;
                        }
                        break;
                    case 2: // Sotto
                        if (pLast->stanza_sotto == NULL)
                        {
                            pLast->stanza_sotto = nuovastanza;
                            nuovastanza->stanza_sopra = pLast;
                        }
                        break;
                    case 3: // Destra
                        if (pLast->stanza_destra == NULL)
                        {
                            pLast->stanza_destra = nuovastanza;
                            nuovastanza->stanza_sinistra = pLast;
                        }
                        break;
                    case 4: // Sinistra
                        if (pLast->stanza_sinistra == NULL)
                        {
                            pLast->stanza_sinistra = nuovastanza;
                            nuovastanza->stanza_destra = pLast;
                        }
                        break;
                    }
                    pLast->next = nuovastanza;
                    pLast = nuovastanza;
                }
            }
            creazionemappa = true;
            printf("\x1b[32mMappa generata con successo!\x1b[37m\n");
        }
        else
        {
            printf("Ok, continuiamo con la vecchia mappa creata\n");
        }
    }
}

void menu_imposta_mappa()
{
    do
    {
        time_t t;
        srand((unsigned)time(&t));
        printf("\n***********************************\x1b[36m Crea Mappa \x1b[37m*******************************************\n");
        printf("1: inserisci stanza\n");
        printf("2: cancella stanza\n");
        printf("3: stampa stanze\n");
        printf("4: genera una stanza in maniera randomica\n");
        printf("5: chiudi mappa\n");
        printf("******************************************************************************************\n");
        printf("digitare il codice per impostare la mappa: ");
        scanf("%d", &value_mappa);
        pulizia_buffer();
        if (!(value_mappa == 1 || value_mappa == 2 || value_mappa == 3 || value_mappa == 4 || value_mappa == 5))
        {
            printf("\x1b[31m errore nell'inserimento, ripetere\x1b[37m\n");
        }
        else
        {
            if (numero_stanza <= 0)
            {
                creazionemappa = false;
                inserisci_stanza();
            }
            switch (value_mappa)
            {
            case 1:
                if (numero_stanza >= 15)
                {
                    printf("hai raggiunto il massimo di stanze\n");
                }
                else
                {
                    numero_stanza++;
                    inserisci_stanza();
                    creazionemappa = true;
                }
                break;
            case 2:
                if (creazionemappa == true)
                {
                    if (numero_stanza == 1)
                    {
                        printf("non puoi eliminare la zona, è la prima zona creata\n");
                    }
                    else // cancello le stanze
                    {
                        numero_stanza--;
                        cancella_stanza();
                        printf("zona rimanenti:%d\n", numero_stanza);
                    }
                }
                else
                {
                    printf("prima di eliminare la zona, devi almeno crearla una\n");
                }

                break;
            case 3:
                if (creazionemappa == true)
                {
                    stampa_mappa(pFirst);
                }
                else
                {
                    printf("prima di stampare la mappa devi almeno creare una zona\n");
                }

                break;
            case 4:
                genera_stanza_random();
                creazionemappa = true;
                break;
            case 5: // posso salvare la mappa solo se le stanze create sono 4 o maggiori
                if (numero_stanza >= 4)
                {

                    printf("mappa salvata\n");
                    mappa_valida = true;
                }
                else
                {
                    printf("prima di stampare la mappa devi almeno creare 4 stanze\n");
                }
                break;
            default:
                printf("\x1b[31m errore menu \x1b[37m\n");
                break;
            }
        }
    } while (mappa_valida != true);
    imposta_gioco();
}

void imposta_gioco()
{
    if (creagiocatori == false)
    {
        do
        {
            printf("Inserire il numero di giocatori tra 1 e 3: ");
            scanf("%d", &n_giocatori); // prende da tastiera il numero dei giocatori
            pulizia_buffer();
            creagiocatore();
            if (n_giocatori < 1 || n_giocatori > 3)
            {
                printf("\x1b[31m errore,numero non compreso tra 1 e 3 \x1b[37m\n");
            }
        } while (n_giocatori < 1 || n_giocatori > 3);
    }
    else if (creagiocatori == true && mappa_valida == false)
    {
        do
        {
            menu_imposta_mappa();
            if (creagiocatori == false && mappa_valida == true)
            {
                printf("\x1b[31m errore \x1b[37m\n");
            }
        } while (mappa_valida != true);
    }
    else if (creagiocatori == true && mappa_valida == true)
    {
        printf("tutte le impostazioni di gioco sono state settate in maniera corretta\n");
        printf("se vuoi rimpostare il gioco clicca 1\n");
        printf("Se vuoi giocare clicca 2\n");
        void stampaMenu();
    }
}
void stampa_giocatore(struct Giocatore *g)
{
    if (g->nome_giocatore == giocatore1->nome_giocatore)
    {
        printf("il giocatore \x1b[33m%s\x1b[37m, i suoi punti vita massimi sono %d e i suoi punti vita sono: %d\n", g->nome_giocatore, g->p_vita_max, g->p_vita);
    }
    else if (g->nome_giocatore == giocatore2->nome_giocatore)
    {
        printf("il giocatore \x1b[32m%s\x1b[37m, la sua sanità mentale è %d e i suoi punti vita sono: %d\n", g->nome_giocatore, g->p_vita_max, g->p_vita);
    }
    else if (g->nome_giocatore == giocatore3->nome_giocatore)
    {
        printf("il giocatore \x1b[35m%s\x1b[37m, la sua sanità mentale è %d e i suoi punti vita sono: %d\n", g->nome_giocatore, g->p_vita_max, g->p_vita);
    }
    else
    {
        printf("errore giocatore\n");
    }
    printf("la classe è: ");
    switch (g->classe)
    {
    case 1:
        printf("Principe\n");
        break;
    case 2:
        printf("Doppleberg\n");
        break;
    default:
        printf("\x1b[31m errore \x1b[37m\n");
        break;
    }
}
void stampa_zona(struct Giocatore *g)
{
    switch (g->posizione->tipo_stanza)
    {
    case 0:
        printf("Corridoio\n");
        break;
    case 1:
        printf("Scala\n");
        break;
    case 2:
        printf("Sala Banchetto\n");
        break;
    case 3:
        printf("Magazzino\n");
        break;
    case 4:
        printf("Posto guardia\n");
        break;
    case 5:
        printf("Prigione\n");
        break;
    case 6:
        printf("Armeria\n");
        break;
    case 7:
        printf("Moschea\n");
        break;
    case 8:
        printf("Torre\n");
        break;
    case 9:
        printf("Bagni\n");
        break;
    default:
        printf("\x1b[31m errore,stampa zona \x1b[37m\n");
        break;
    }
    switch (g->posizione->tipo_trabocchetto)
    {
    case 0:
        printf("Nessuno\n");
        break;
    case 1:
        printf("Tegola\n");
        break;
    case 2:
        printf("Lame\n");
        break;
    case 3:
        printf("Caduta\n");
        break;
    case 4:
        printf("Burrone\n");
        break;
    default:
        printf("\x1b[31m errore,stampa trabocchetto \x1b[37m\n");
        break;
    }
    if (g->posizione->tipo_tesoro == NESSUN_TESORO)
    {
        printf("Tesoro presente:NO\n");
    }
    else
    {
        printf("Tesoro presente:SI\n");
    }
}
void apparizone_nemico(struct Giocatore *g)
{
    time_t t;
    srand((unsigned)time(&t));
    int random_nemico = (rand() % 100) + 1;
    apparso_nemico = false;
    if (random_nemico <= 25)
    {
        Nemico = (struct Nemico *)malloc(sizeof(struct Nemico));
        apparso_nemico = true;
        int tipo_nemico = (rand() % 100) + 1;
        if (tipo_nemico <= 60)
        {
            printf("Uno Scheletro è comparso!\n");
            Nemico->classe = SCHELETRO;
            Nemico->dadi_attacco = 1;
            Nemico->dadi_difesa = 1;
            Nemico->p_vita_max = 1;
            Nemico->p_vita = p_vita_max;
        }
        else
        {
            printf("Una guardia è comparsa!\n");
            Nemico->classe = GUARDIA;
            Nemico->dadi_attacco = 2;
            Nemico->dadi_difesa = 2;
            Nemico->p_vita_max = 2;
            Nemico->p_vita = p_vita_max;
        }
    }
    if (g->posizione == pLast)
    {
        printf("sei arrivato all'ultima stanza\n");
        printf("Hai raggiunto JAFFAR!\n");
        Nemico->classe = JAFFAR;
        Nemico->dadi_attacco = 3;
        Nemico->dadi_difesa = 3;
        Nemico->p_vita_max = 3;
        Nemico->p_vita = p_vita_max;
    }
    if (apparso_nemico == true)
    {   
        // Chiedi se vuole combattere o scappare
        int scelta;
        printf("Vuoi combattere? ");
        printf("1-si ");
        printf(" 2-vuoi scappare ");
        scanf(" %s", &scelta); // Legge la scelta del giocatore
        if (scelta == 1)
        {
            combatti(g);
        }
        else if (scelta == 2)
        {
            scappa(g); // Funzione di fuga già definita
        }
    }

}
void attacco_difesa(struct Giocatore *g, struct Nemico *Nemico)
{
    g->dadi_attacco=rand()%6+1;
        g->dadi_difesa=rand()%6+1;
        Nemico->dadi_attacco=rand()%6+1;
        Nemico->dadi_difesa=rand()%6+1;
    if(random_combatti==1)
    {
        if(g->dadi_attacco>Nemico->dadi_difesa)
        {
            if(g->dadi_attacco>=4 && Nemico->dadi_difesa<=3)
            {
                printf("il %s subisce un danno perdendo 1 vite\n", Nemico->classe);
                Nemico->p_vita-=1;
            }else if(g->dadi_attacco<=Nemico->dadi_difesa){
                printf("il %s ha parato i colpi\n", Nemico->classe);
            }else if(g->dadi_attacco==6 && Nemico->dadi_difesa<6)
            {
                printf("il %s subisce un danno perdendo 2 vite\n", Nemico->classe);
                Nemico->p_vita-=2;
            }else
            {
                printf("il %s ha parato tutti i colpi\n", Nemico->classe);
            }
        }

    }else{
        if(Nemico->dadi_attacco>g->dadi_difesa)
        {
            if(Nemico->dadi_attacco>=4 && g->dadi_difesa<=3)
            {
                printf("il %s subisce un danno perdendo 1 vite\n",g->nome_giocatore);
                g->p_vita-=1;
            }else if(Nemico->dadi_attacco<=g->dadi_difesa){
                printf("il %s ha parato i colpi\n", g->nome_giocatore);
            }else if(Nemico->dadi_attacco==6 && g->dadi_difesa<6)
            {
                printf("il %s subisce un danno perdendo 2 vite\n", g->nome_giocatore);
                g->p_vita-=2;
            }else
            {
                printf("il %s ha parato tutti i colpi\n", g->nome_giocatore);
            }
        }
    }
}
void combatti(struct Giocatore *g)
{
    int dado_nemico = 0;
int dado_giocatore = 0;
    printf("Hai deciso di combattere...Buona fortuna\n");
    printf("per sapere chi attachera e chi difenderà, dovrai tirare un dado inseme al nemico\n");
    printf("chi ha il punteggio più alto attacca\n");
    random_combatti = rand() % 2 + 1;
    if (random_combatti == 1)
    {
        printf("il primo a tirare il dado è:%s\n", g->nome_giocatore);
        dado_giocatore = rand() % 6 + 1;
        printf("ora il dado lo deve tirare %s\n", Nemico->classe);
        dado_nemico = rand() % 6 + 1;
        printf("i numeri usciti sono: %d,%d", dado_giocatore, dado_nemico);
        if (dado_giocatore > dado_nemico)
        {
            printf("attacca per primo:%s,quindi %s si difende", g->nome_giocatore, Nemico->classe);
            attacco_difesa(g,Nemico);
        }
        else
        {
            printf("attacca per primo:%s, quindi %s si difende", Nemico->classe, g->nome_giocatore);
            attacco_difesa(g,Nemico);
        }
    }
    else
    {
        printf("il primo a tirare il dado è:%s", Nemico->classe);
        dado_nemico = rand() % 6 + 1;
        printf("ora il dado lo deve tirare %s\n", g->nome_giocatore);
        dado_giocatore= rand() % 6 + 1;
        printf("i numeri usciti sono: %d,%d", dado_nemico, dado_giocatore);
        if (dado_giocatore > dado_nemico)
        {
            printf("attacca per primo:%s", g->nome_giocatore);
            attacco_difesa(g,Nemico);
        }
        else
        {
            printf("attacca per primo:%s", Nemico->classe);
            attacco_difesa(g,Nemico);
        }
    }

    // inizializzare variabile bool vittoria
    //  TIRA I DADI
    //  chi ha il punteggio più alto attacca per primo e l'altro si difende
    //  per ogni commbattimento vinto si ottiene +1 di vita
}
void applica_trabocchetto(struct Giocatore *g)
{
    switch (g->posizione->tipo_trabocchetto)
    {
    case 0:
        printf("NESSUN TRABOCCHETTO");
        trabocchetto = false;
        break;
    case 1:
        g->p_vita--;
        trabocchetto = true;
        break;
    case 2:
        g->p_vita -= 2;
        trabocchetto = true;
        break;
    case 3:
        int danno_caduta = (rand() % 2) + 1;
        if (danno_caduta == 1)
        {
            printf("il giocatore perde un punto vita\n");
            g->p_vita--;
        }
        else
        {
            printf("il giocatore perde due punti vita\n");
            g->p_vita -= 2;
        }
        trabocchetto = true;
        break;
    case 4:
        turni_avanzati = 1;
        int danno_burrone = (rand() % 2) + 1;
        if (danno_burrone == 1)
        {
            printf("il giocatore perde un punto vita\n");
            g->p_vita--;
        }
        else
        {
            printf("il giocatore perde due punti vita\n");
            g->p_vita -= 2;
        }
        trabocchetto = true;
        break;
    default:
        printf("\x1b[31m errore\x1b[37m\n");
        break;
    }
}

void scappa(struct Giocatore *g)
{

    if (apparso_nemico == true)
    {
        if (g->classe == PRINCIPE)
        {
            if (g->scappare == 0)
            {
                printf("\x1b[31m non puoi più scappare, devi combattere per forza!\x1b[37m\n");
                combatti(g);
            }
            else
            {
                g->scappare--; // può scappare solo una volta
                if (g->posizione->tipo_trabocchetto && trabocchetto == true)
                {
                    trabocchetto = false; // principe ignora il primo trabocchetto
                    printf("il primo trabocchetto non viene applicato al PRINCIPE");
                }
                else
                {
                    trabocchetto = true;
                    applica_trabocchetto(g);
                }
            }
        }
        else
        {
            if (g->scappare == 0)
            {
                printf("\x1b[31m non puoi più scappare, devi combattere per forza!\x1b[37m\n");
                combatti(g);
            }
            else
            {
                g->scappare--; // può scappare solo due volte
                if (g->posizione->tipo_trabocchetto && trabocchetto == true)
                {
                    trabocchetto = false; // principe ignora il primo trabocchetto
                }
                else
                {
                    trabocchetto = true;
                    // applico trabocchetto al giocatore
                }
            }
        }
        g->posizione = prec;
    }
}

void avanza(struct Giocatore *g)
{
    time_t t;
    srand((unsigned)time(&t)); // Inizializza il generatore di numeri casuali

    if (turni_avanzati == 0 || n_giocatori == 1) // Se è il primo turno o solo un giocatore
    {
        struct Stanza *nuovastanza = g->posizione;
        printf("I giocatori avanzeranno nell'unica possibile direzione:\nSOPRA, DESTRA, SINISTRA, SOTTO\n");
        g->posizione = nuovastanza->next;
        printf("giocatore avanzato\n");
        switch (g->posizione->tipo_trabocchetto)
        {
        case 0:
            printf("NESSUN TRABOCCHETTO");
            trabocchetto = false;
            break;
        case 1:
            printf("sei caduto in un trabocchetto: ");
            printf("Tegola\n");
            printf("il giocatore perde un punto vita\n");
            applica_trabocchetto(g);
            trabocchetto = true;
            break;
        case 2:
            printf("sei caduto in un trabocchetto: ");
            printf("Lame\n");
            printf("il giocatore perde due punti vita\n");
            applica_trabocchetto(g);
            trabocchetto = true;
            break;
        case 3:
            printf("sei caduto in un trabocchetto: ");
            printf("Caduta\n");
            applica_trabocchetto(g);
            trabocchetto = true;
            break;
        case 4:
            printf("sei caduto in un trabocchetto: ");
            printf("Burrone\n");
            applica_trabocchetto(g);
            trabocchetto = true;
            break;
        default:
            printf("\x1b[31m errore trabocchetto\x1b[37m\n");
            break;
        }
    }
    else
    {
        printf("\x1b[31m non puoi avanzare 2 volte di fila \x1b[37m\n");
    }
    turni_avanzati++;
}
void prendi_tesoro(struct Giocatore *g)
{
    if (g->posizione->tipo_tesoro != NULL)
    {
        printf("in questa stanza c'è un \x1b[33m TESORO \x1b[37m\n");
        printf("il tesoro trovato è: ");
        switch (g->posizione->tipo_stanza)
        {
        case 0:
            printf("Nessun Tesoro\n");
            break;
        case 1:
            printf("Verde Veleno\n");
            g->p_vita--;
            printf("ora hai:%u", g->p_vita);
            break;
        case 2:
            printf("Blu Guarigione\n");
            if (g->p_vita < g->p_vita_max)
            {
                g->p_vita++;
                printf("ora hai:%u", g->p_vita_max);
            }
            else
            {
                printf("non guadagna nessuno punto vita perchè già c'è l'ha al massimo\n");
            }
            break;
        case 3:
            printf("Rosso aumenta vita\n");
            g->p_vita_max++;
            printf("la tua vita massima è aumentata di 1\n");
            break;
        case 4:
            printf("Spada tagliente\n");
            g->dadi_attacco++;
            printf("hai ottenuto un dado attacco in più\n");
            break;
        case 5:
            printf("Scudo\n");
            g->dadi_difesa++;
            printf("hai un dado difesa in più\n");
            break;
        default:
            printf("\x1b[31m errore,stampa tesoro \x1b[37m\n");
            break;
        }
    }
    else
    {
        printf("nessun tesoro presente nella stanza\n");
    }
    g->posizione->tipo_tesoro = 0;
}
void cerca_porta_segreta(struct Giocatore *g)
{
    // per le direzioni in cui non si può procedere è possibile cercare una porta segreta
    // 1° volta che ci cerca, la probabilità di comparire è:33%, la 2° volta:20% e la 3°:15%.
    // se viene trovata una nuova stanza viene aggiunta alla mappa(malloc), valori della stanza generati con genera_mappa_random.
    // non possono apparire nemici
    // se un giocatore avanza in un turno, non può cercare la porta segreta
    // infine il giocatopre ritorna nella stanza dove ha trovato la prota segreta
}
void passa(struct Giocatore *g) // passo il turno al giocatore successivo //non funziona
{
    printf("turno passato\n");
    turni_avanzati = 0;
}
void menu_giocatore1()
{
    do
    {
        do
        {
            if (giocatore1->p_vita == 0)
            {
                printf("\x1b[33m%s\x1b[37m è morto\n", giocatore1->nome_giocatore);
                termina_gioco();
                return;
            }

            printf("\n***********************************\x1b[35m Gioca \x1b[37m*******************************************\n");
            printf("\x1b[36m 1\x1b[37m : stampa giocatore\n");
            printf("\x1b[36m 2\x1b[37m : stampa zona\n");
            printf("\x1b[36m 3\x1b[37m : avanza_giocatori\n");
            printf("\x1b[36m 4\x1b[37m : cerca_porta_segreta\n");
            printf("\x1b[36m 5\x1b[37m : combatti\n");
            printf("\x1b[36m 6\x1b[37m : scappa\n");
            printf("\x1b[36m 7\x1b[37m : prendi tesoro\n");
            printf("\x1b[36m 8\x1b[37m : passa turno\n");
            printf("*************************************************************************************\n");
            printf("digitare un comando tra quelli elencati: ");

            do
            {
                scanf("%d", &scelta_gioco);
                if (scelta_gioco < 1 || scelta_gioco > 8)
                {
                    printf("\x1b[31m Errore, numero non compreso tra 1 e 8 \x1b[37m\n");
                }
            } while (scelta_gioco < 1 || scelta_gioco > 8);

            switch (scelta_gioco)
            {
            case 1:
                stampa_giocatore(giocatore1);
                break;
            case 2:
                stampa_zona(giocatore1);
                break;
            case 3:
                avanza(giocatore1);
                apparizone_nemico(giocatore1);
                break;
            case 4:
                cerca_porta_segreta(giocatore1);
                break;
            case 5:
                combatti(giocatore1);
                break;
            case 6:
                scappa(giocatore1);
                break;
            case 7:
                prendi_tesoro(giocatore1);
                break;
            case 8:
                passa(giocatore1);
                break;
            default:
                printf("\x1b[31m Errore, numero non compreso tra 1 e 8 \x1b[37m\n");
                break;
            }
        } while (passa_turno == false);
        passa_turno = false;

    } while (giocatore1->p_vita > 0 && vittoria == false);
}
void menu_giocatore2()
{
    do
    {
        do
        {
            if (giocatore1->p_vita <= 0)
            {
                printf("\x1b[33m%s\x1b[37m è morto\n", giocatore1->nome_giocatore);
                termina_gioco();
                return;
            }

            printf("\n***********************************\x1b[35m Gioca \x1b[37m*******************************************\n");
            printf("\x1b[36m 1\x1b[37m : stampa giocatore\n");
            printf("\x1b[36m 2\x1b[37m : stampa zona\n");
            printf("\x1b[36m 3\x1b[37m : avanza_giocatori\n");
            printf("\x1b[36m 4\x1b[37m : cerca_porta_segreta\n");
            printf("\x1b[36m 5\x1b[37m : combatti\n");
            printf("\x1b[36m 6\x1b[37m : scappa\n");
            printf("\x1b[36m 7\x1b[37m : prendi tesoro\n");
            printf("\x1b[36m 8\x1b[37m : passa turno\n");
            printf("*************************************************************************************\n");
            printf("digitare un comando tra quelli elencati: ");

            do
            {
                scanf("%d", &scelta_gioco);
                if (scelta_gioco < 1 || scelta_gioco > 8)
                {
                    printf("\x1b[31m Errore, numero non compreso tra 1 e 8 \x1b[37m\n");
                }
            } while (scelta_gioco < 1 || scelta_gioco > 8);

            switch (scelta_gioco)
            {
            case 1:
                stampa_giocatore(giocatore1);
                break;
            case 2:
                stampa_zona(giocatore1);
                break;
            case 3:
                avanza(giocatore1);
                apparizone_nemico(giocatore1);
                break;
            case 4:
                cerca_porta_segreta(giocatore1);
                break;
            case 5:
                combatti(giocatore1);
                break;
            case 6:
                scappa(giocatore1);
                break;
            case 7:
                prendi_tesoro(giocatore1);
                break;
            case 8:
                passa(giocatore1);
                break;
            default:
                printf("\x1b[31m Errore, numero non compreso tra 1 e 8 \x1b[37m\n");
                break;
            }
        } while (passa_turno == false);
        passa_turno = false;
        do
        {
            if (giocatore2->p_vita <= 0)
            {
                printf("\x1b[32m%s\x1b[37m è morto\n", giocatore2->nome_giocatore);
                termina_gioco();
                return;
            }

            printf("\n***********************************\x1b[35m Gioca \x1b[37m*******************************************\n");
            printf("\x1b[36m 1\x1b[37m : stampa giocatore\n");
            printf("\x1b[36m 2\x1b[37m : stampa zona\n");
            printf("\x1b[36m 3\x1b[37m : avanza_giocatori\n");
            printf("\x1b[36m 4\x1b[37m : cerca_porta_segreta\n");
            printf("\x1b[36m 5\x1b[37m : combatti\n");
            printf("\x1b[36m 6\x1b[37m : scappa\n");
            printf("\x1b[36m 7\x1b[37m : prendi tesoro\n");
            printf("\x1b[36m 8\x1b[37m : passa turno\n");
            printf("*************************************************************************************\n");
            printf("digitare un comando tra quelli elencati: ");

            do
            {
                scanf("%d", &scelta_gioco);
                if (scelta_gioco < 1 || scelta_gioco > 8)
                {
                    printf("\x1b[31m Errore, numero non compreso tra 1 e 8 \x1b[37m\n");
                }
            } while (scelta_gioco < 1 || scelta_gioco > 8);

            switch (scelta_gioco)
            {
            case 1:
                stampa_giocatore(giocatore2);
                break;
            case 2:
                stampa_zona(giocatore2);
                break;
            case 3:
                avanza(giocatore2);
                apparizone_nemico(giocatore2);
                break;
            case 4:
                cerca_porta_segreta(giocatore2);
                break;
            case 5:
                combatti(giocatore2);
                break;
            case 6:
                scappa(giocatore2);
                break;
            case 7:
                prendi_tesoro(giocatore2);
                break;
            case 8:
                passa(giocatore2);
                break;
            default:
                printf("\x1b[31m Errore, numero non compreso tra 1 e 8 \x1b[37m\n");
                break;
            }
        } while (passa_turno == false);
        passa_turno = false;
    } while (giocatore1->p_vita > 0 && giocatore2->p_vita > 0 && vittoria == false);
}
void menu_giocatore3()
{
    do
    {
        do
        {
            if (giocatore1->p_vita <= 0)
            {
                printf("\x1b[33m%s\x1b[37m è morto\n", giocatore1->nome_giocatore);
                termina_gioco();
                return;
            }

            printf("\n***********************************\x1b[35m Gioca \x1b[37m*******************************************\n");
            printf("\x1b[36m 1\x1b[37m : stampa giocatore\n");
            printf("\x1b[36m 2\x1b[37m : stampa zona\n");
            printf("\x1b[36m 3\x1b[37m : avanza_giocatori\n");
            printf("\x1b[36m 4\x1b[37m : cerca_porta_segreta\n");
            printf("\x1b[36m 5\x1b[37m : combatti\n");
            printf("\x1b[36m 6\x1b[37m : scappa\n");
            printf("\x1b[36m 7\x1b[37m : prendi tesoro\n");
            printf("\x1b[36m 8\x1b[37m : passa turno\n");
            printf("*************************************************************************************\n");
            printf("digitare un comando tra quelli elencati: ");

            do
            {
                scanf("%d", &scelta_gioco);
                if (scelta_gioco < 1 || scelta_gioco > 8)
                {
                    printf("\x1b[31m Errore, numero non compreso tra 1 e 8 \x1b[37m\n");
                }
            } while (scelta_gioco < 1 || scelta_gioco > 8);

            switch (scelta_gioco)
            {
            case 1:
                stampa_giocatore(giocatore1);
                break;
            case 2:
                stampa_zona(giocatore1);
                break;
            case 3:
                avanza(giocatore1);
                apparizone_nemico(giocatore1);
                break;
            case 4:
                cerca_porta_segreta(giocatore1);
                break;
            case 5:
                combatti(giocatore1);
                break;
            case 6:
                scappa(giocatore1);
                break;
            case 7:
                prendi_tesoro(giocatore1);
                break;
            case 8:
                passa(giocatore1);
                break;
            default:
                printf("\x1b[31m Errore, numero non compreso tra 1 e 8 \x1b[37m\n");
                break;
            }
        } while (passa_turno == false);
        passa_turno = false;
        do
        {
            if (giocatore2->p_vita <= 0)
            {
                printf("\x1b[32m%s\x1b[37m è morto\n", giocatore2->nome_giocatore);
                termina_gioco();
                return;
            }

            printf("\n***********************************\x1b[35m Gioca \x1b[37m*******************************************\n");
            printf("\x1b[36m 1\x1b[37m : stampa giocatore\n");
            printf("\x1b[36m 2\x1b[37m : stampa zona\n");
            printf("\x1b[36m 3\x1b[37m : avanza_giocatori\n");
            printf("\x1b[36m 4\x1b[37m : cerca_porta_segreta\n");
            printf("\x1b[36m 5\x1b[37m : combatti\n");
            printf("\x1b[36m 6\x1b[37m : scappa\n");
            printf("\x1b[36m 7\x1b[37m : prendi tesoro\n");
            printf("\x1b[36m 8\x1b[37m : passa turno\n");
            printf("*************************************************************************************\n");
            printf("digitare un comando tra quelli elencati: ");

            do
            {
                scanf("%d", &scelta_gioco);
                if (scelta_gioco < 1 || scelta_gioco > 8)
                {
                    printf("\x1b[31m Errore, numero non compreso tra 1 e 8 \x1b[37m\n");
                }
            } while (scelta_gioco < 1 || scelta_gioco > 8);

            switch (scelta_gioco)
            {
            case 1:
                stampa_giocatore(giocatore2);
                break;
            case 2:
                stampa_zona(giocatore2);
                break;
            case 3:
                avanza(giocatore2);
                apparizone_nemico(giocatore2);
                break;
            case 4:
                cerca_porta_segreta(giocatore2);
                break;
            case 5:
                combatti(giocatore2);
                break;
            case 6:
                scappa(giocatore2);
                break;
            case 7:
                prendi_tesoro(giocatore2);
                break;
            case 8:
                passa(giocatore2);
                break;
            default:
                printf("\x1b[31m Errore, numero non compreso tra 1 e 8 \x1b[37m\n");
                break;
            }
        } while (passa_turno == false);
        passa_turno = false;
        do
        {
            if (giocatore3->p_vita <= 0)
            {
                printf("\x1b[35m%s\x1b[37m è morto\n", giocatore3->nome_giocatore);
                termina_gioco();
                return;
            }

            printf("\n***********************************\x1b[35m Gioca \x1b[37m*******************************************\n");
            printf("\x1b[36m 1\x1b[37m : stampa giocatore\n");
            printf("\x1b[36m 2\x1b[37m : stampa zona\n");
            printf("\x1b[36m 3\x1b[37m : avanza_giocatori\n");
            printf("\x1b[36m 4\x1b[37m : cerca_porta_segreta\n");
            printf("\x1b[36m 5\x1b[37m : combatti\n");
            printf("\x1b[36m 6\x1b[37m : scappa\n");
            printf("\x1b[36m 7\x1b[37m : prendi tesoro\n");
            printf("\x1b[36m 8\x1b[37m : passa turno\n");
            printf("*************************************************************************************\n");
            printf("digitare un comando tra quelli elencati: ");

            do
            {
                scanf("%d", &scelta_gioco);
                if (scelta_gioco < 1 || scelta_gioco > 8)
                {
                    printf("\x1b[31m Errore, numero non compreso tra 1 e 8 \x1b[37m\n");
                }
            } while (scelta_gioco < 1 || scelta_gioco > 8);

            switch (scelta_gioco)
            {
            case 1:
                stampa_giocatore(giocatore3);
                break;
            case 2:
                stampa_zona(giocatore3);
                break;
            case 3:
                avanza(giocatore3);
                apparizone_nemico(giocatore3);
                break;
            case 4:
                cerca_porta_segreta(giocatore3);
                break;
            case 5:
                combatti(giocatore3);
                break;
            case 6:
                scappa(giocatore3);
                break;
            case 7:
                prendi_tesoro(giocatore3);
                break;
            case 8:
                passa(giocatore3);
                break;
            default:
                printf("\x1b[31m Errore, numero non compreso tra 1 e 8 \x1b[37m\n");
                break;
            }
        } while (passa_turno == false);
        passa_turno = false;
    } while (giocatore1->p_vita > 0 && giocatore2->p_vita > 0 && giocatore3->p_vita > 0 && vittoria == false);
}
void menu_gioca()
{
    switch (n_giocatori)
    {
    case 1:
        menu_giocatore1();
        break;
    case 2:
        menu_giocatore2();
        break;
    case 3:
        menu_giocatore3();
        break;

    default:
        printf("\x1b[31m Errore\x1b[37m\n");
        break;
    }
}
void gioca()
{
    switch (n_giocatori)
    {
    case 1:
        giocatore1->posizione = pFirst;
        break;
    case 2:
        giocatore1->posizione = pFirst;
        giocatore2->posizione = pFirst;
        break;
    case 3:
        giocatore1->posizione = pFirst;
        giocatore2->posizione = pFirst;
        giocatore3->posizione = pFirst;
        break;

    default:
        printf("\x1b[31m Errore: giocatori non inizializzati! \x1b[37m\n");
        break;
    }
    menu_gioca();
}

// Funzione per la visualizzazione dei crediti
void crediti()
{
    printf("Crediti:\n");
    printf("Sviluppato da: Rossi Riccardo \n");
}

// Funzione che stampa il menu di gioco
void stampaMenu()
{
    printf("====== MENU DI GIOCO ======\n");
    printf("1) Imposta gioco\n");
    printf("2) Gioca\n");
    printf("3) Termina gioco\n");
    printf("4) Visualizza i crediti\n");
    printf("===========================\n");
    printf("Scegli un'opzione: ");
}

