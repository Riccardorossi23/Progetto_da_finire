#ifndef gamelib.h
#define gamelib .h
void imposta_gioco();
void gioca();
void termina_gioco();
void crediti();

// Enum per descrivere la classe del giocatore
typedef enum Classe_giocatore
{
    NESSUNA,
    PRINCIPE,
    DOPPLEGANGER
};

// Enum per descrivere il tipo di stanza
typedef enum Tipo_stanza
{
    CORRIDOIO,
    SCALA,
    SALA_BANCHETTO,
    MAGAZZINO,
    POSTO_GUARDIA,
    PRIGIONE,
    ARMERIA,
    MOSCHEA,
    TORRE,
    BAGNI
};

// Enum per descrivere il tipo di trabocchetto
typedef enum Tipo_trabocchetto
{
    NESSUNO,
    TEGOLA,
    LAME,
    CADUTA,
    BURRONE
};

// Enum per descrivere il tipo di tesoro
typedef enum Tipo_tesoro
{
    NESSUN_TESORO,
    VERDE_VELENO,
    BLU_GUARIGIONE,
    ROSSO_AUMENTA_VITA,
    SPADA_TAGLIENTE,
    SCUDO
};

// Struttura per rappresentare un giocatore
typedef struct Stanza Stanza; // Forward declaration

struct Giocatore
{
    char nome_giocatore[50];
    enum Classe_giocatore classe;
    Stanza *posizione;
    unsigned char p_vita_max;
    unsigned char p_vita;
    unsigned char dadi_attacco;
    unsigned char dadi_difesa;
    unsigned char scappare;
};

// Struttura per rappresentare una stanza
struct Stanza
{
    Stanza *stanza_destra;
    Stanza *stanza_sinistra;
    Stanza *stanza_sopra;
    Stanza *stanza_sotto;
    Stanza *next;
    struct Stanza *next_sopra;    // Permette di collegare più stanze sopra
    struct Stanza *next_sotto;    // Permette di collegare più stanze sotto
    struct Stanza *next_destra;   // Permette di collegare più stanze a destra
    struct Stanza *next_sinistra; // Permette di collegare più stanze a sinistra
    enum Tipo_stanza tipo_stanza;
    enum Tipo_trabocchetto tipo_trabocchetto;
    enum Tipo_tesoro tipo_tesoro;
};

#endif // GAMELIB_H
