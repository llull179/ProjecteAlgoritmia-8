# ProjecteAlgoritmia-8

---

**Projecte de l'assignatura d'Algoritmia, Q2 2022/23**

Integrants del grup:

- Lluis Llull  `lluis.llull.riera@estudiantat.upc.edu`

- Miquel Muñoz `miquel.munoz.garcia-ramos@estudiantat.upc.edu`

- Marti Recalde `marti.recalde@estudiantat.upc.edu`

- Iván Serrano `ivan.serrano.hernandez@estudiantat.upc.edu`

---

### Usage

Per compilar tots els fitxers.

```bash 
make
```

Per netejar d'executables i outputs.

```bash
make clean
```

*Usage* del programa per executar els algorismes voraços.

```bash
./program_Greedy                    # for manual input
./program_Greedy graph_name         # input graph from file
./program_Greedy graph_name test    # test propagation
```

*Usage* del programa per executar l'algorisme de cerca local.

```bash
./program_localSearch                    # for manual input
./program_localSearch graph_name         # input graph from file
./program_localSearch graph_name test    # test propagation
```

*Usage* del programa per executar l'algorisme de *simulated annealing*.

```bash
./program_SA                    # for manual input
./program_SA graph_name         # input graph from file
./program_SA graph_name test    # test propagation
```

Totes les sortides dels algorismes es redirigeixen a un fitxer de text pla, on es mostren els resultats i les mètriques de l'execució (temps i nombre d'iteracions).
