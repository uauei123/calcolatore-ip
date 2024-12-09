# Calcolatore IP

Il **Calcolatrice IP** è uno strumento progettato per calcolare subnet, incluse quelle con maschere di sottorete fisse e variabili (VLSM). Lo strumento supporta sia un'interfaccia a riga di comando (CLI) sia un'interfaccia grafica (GUI). L'applicazione è pensata per effettuare calcoli di subnet in modo efficiente, fornendo agli utenti vari dettagli relativi alla rete, ID di rete, maschere di sottorete e altro.

## Indice

1. [Compilazione](#compilazione)
   1. [Dipendenze](#dipendenze)
   2. [Configurazione di FLTK](#configurazione-di-fltk)
   3. [Clonazione del Repository](#clonazione-del-repository)
   4. [Compilazione del Progetto](#compilazione-del-progetto)
2. [Licenza](#licenza)

## Introduzione

Il progetto offre due modalità di interazione:
1. **Interfaccia a Riga di Comando (CLI)**: gli utenti possono interagire tramite terminale, utile per automazione.
2. **Interfaccia Grafica (GUI)**: un'interfaccia costruita con la libreria FLTK.

Il processo di compilazione utilizza **CMake** come sistema di build.
Supporto per Windows e sperimentale per Linux.

## Compilazione

### Dipendenze

Prima di compilare il progetto, assicurati che le seguenti dipendenze siano installate nel tuo sistema:

- **CMake**: Necessario per il sistema di build. [Guida all'installazione di CMake](https://cmake.org/install/)
- **FLTK (Fast Light Toolkit)**: Libreria necessaria per costruire l'interfaccia grafica. Assicurati che FLTK sia installato e disponibile nel `PATH` del tuo ambiente. [Guida all'installazione di FLTK](https://www.fltk.org/)

### Configurazione di FLTK

Assicurati che FLTK sia installato e configurato correttamente nel tuo ambiente. Il sistema di build CMake rileverà automaticamente FLTK tramite il percorso dell'ambiente.

- Per **Windows**: Scarica e compila FLTK da [FLTK Downloads](https://www.fltk.org/download.php).
- Per **Linux**: Installa FLTK tramite il gestore di pacchetti (ad esempio, `apt-get install libfltk1.3-dev` su Ubuntu).

### Clonazione del Repository

Clona il repository sulla tua macchina locale usando `git`:

```bash
git clone https://github.com/uauei123/calcolatore-ip.git
cd calcolatore-ip
```

### Compilazione del Progetto

Dopo aver configurato FLTK e clonato il repository, segui questi passaggi per compilare il progetto:

1. Vai nella directory del progetto ed entra nella cartella build `build`:
    ```bash
    cd build
    ```

2. Esegui `cmake` per configurare il progetto:
    ```bash
    cmake ..
    ```

3. Compila il progetto:
    ```bash
    cmake --build .
    ```

4. Dopo il completamento della compilazione, l'eseguibile sarà disponibile nella directory `build`.

## Licenza

Questo progetto è distribuito sotto licenza MIT - consulta il file [LICENSE](LICENSE) per ulteriori dettagli.
