# AnomalyDetectionSystem

## Autore 
- Andrea Donelli.

## Corso 
- Corso: Ingegneria del Software 2023/24.
- Facoltà: Ingengeria dell'informazione, informatica e statistica
- Sede: La Sapienza, RM
- Professore: E.T.

## Progetto
- Nome: Anomaly_Detection_System.

## Descrizione e Funzionalità 
Il progetto è un sistema di anomaly detection per uno stream di dati.

Diviso in "Client" e "Server":

1. Client legge dati da un file *.csv, stabilisce l'ampiezza della finestra temporale di azione (W) e attraverso una connessione "Redis",  manda al Server come messaggio Redis il valore di W e i dati presenti nella finestra temporale W. Aspetta la risposta del Server per mandargli la finestra temporale successiva.
    - Supporta solo dati del formato {Timestamp, Sensore, Valore}

2. Server attraverso una connessione "Redis" aspetta il messaggio da parte del Client ed effettua le seguenti azioni per ogni messaggio in arrivo:
    - Salva in locale i dati da analizzare
    - Effettua il calcolo del Valore Medio per ogni sensore 
    - Effettua il calcolo della Covarianza per ogni coppia di sensori 
    - Rileva e Conteggia le anomalie nei sensori per il Valore Medio e per la Covarianza
    - Effettua l'accesso al Database PostgreSQL
    - Per ogni sensore salva nella table "average" i seguenti dati:
        - (PID, Sensore, Average, Timestamp, Stardard_Deviation, Deviation)
    - Per ogni coppia di sensori salva nella table "covariance" i seguenti dati:
        - (PID, Sensore1, Sensore2, Covariance, Timestamp, Stardard_Deviation, Deviation)
    - Per ogni risposta inviata al Client verranno salvati nel DB anche i Log, nella table "logtime" con i seguenti dati:
        - (Time, Execution_Time, PID, Timestamp, Window_Size, Result)
    - Effettua il Monitor per le seguenti proprietà:
        - Valore Medio
        - Covarianza
        - Anomalie di Valore Medio
        - Tempo di Esecuzione
        - Correttezza dei Log

## Makefile
Il Makefile è stato progettato per compilare i programmi "client" e "server" all'interno di "bin".
Gestisce il loro processo di compilazione chiamando altri files Makefile presenti nelle subdir Client, server, Con2db, Con2redis presenti nella directory "software".
Dispone della funzione "clean" per eliminare i file .o, i due eseguibili e la cartella "bin".

## Prerequisiti necessari
Per poter compilare ed eseguire i programmi in UBUNTU, è NECESSARIO installare quanto segue:
1. Compilatore GCC
2. gmake
3. PostgreSQL
4. Libreria libpq-dev
5. Redis

## Inizializzazione DB
- Informazioni DB:
	- hostname: 127.0.0.1
	- port: 5432
	- username: detection
	- password: 1901126
	- dbname: logdb_detection
	
1. Assicurati di avere installato correttamente tutti i prerequisiti necessari.
2. Apri un terminale e posizionati nella directory del progetto.
3. Posizionati nella directory db-scripts.
4. Digita il comando chmod +x create.sh (SE NECESSARIO).
5. Digita il comando ./create.sh
6. Per entrare nel DB digita il comando:
	- sudo -u postgres psql logdb_detection

## Compilazione ed Esecuzione
1. Assicurati di avere installato correttamente tutti i prerequisiti necessari e di avere inizializzato il DB.
2. Apri un terminale e posizionati nella directory del progetto.
3. Esegui il comando "make" per compilare il programma.
    - make genererà una directory "bin" contenente gli eseguibili "client" e "server".
4. Posizionati nella directory "bin".
5. Apri DUE terminali.
6. Terminale1: digita e invia il comando ./server
7. Terminale2: digita e invia il comando ./client

8. Esegui il comando "make clean" per rimuovere i file oggetto e i programmi generati durante il processo di compilazione.

## Test e funzionamento
Nella subdir DATA, presente in Client, sono presenti alcuni files .csv per testare la correttezza dei programmi.
- I files sono del formato {Timestamp, SensorName, Value}.

NB: Alcuni dati sono configurabili per effettuare diversi tipi di test.
- Dati Configurabili:
        - File di input da analizzare (DEFAULT data1.csv)
        - Ampiezza della finestra temporale (W) di analisi (DEFAULT 50)
        - Numero massimo di sensori diversi utilizzati per l'analisi (DEFAULT 250)
        
- Come cambiare configurazione:
1. Recarsi nella directory /Anomaly_Detection_System/software/Client/src.
2. Aprire con un Editor il file "Utils.cpp".
3. Effettuare le modifiche e salvare il file.
4. Compilare il programma come descritto in "Compilazione ed Esecuzione".

