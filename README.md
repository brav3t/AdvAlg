# Haladó algoritmusok

### Smallest Bounding Polygon with Hill Climbing
#### Reprezentáció:

#### Probléma tér:
#### Megoldás tér:
#### Függvények ismertetése:
#### Megjegyzések:

### Ütazó-ügynök probléma megoldása Genetikus programozással
#### Reprezentáció:
Tíz darab város(Town) osztály. A városok x és y pozíciót tartalmaznak, amelyek véletlenszerűen generáltak. 

#### Probléma tér:
Utak halmaza. Egy _út(Route)_ tíz várost jár be. Az egyes utak a városok sorrendjének permutációit tartalmazzák.
Az utak halmazát _populációnak(Population)_ tekintjük. Egy utat a hozzá tartozó fitness értékkel _egyednek(Individual)_ hívjuk.

#### Megoldás tér:
Egy tömb, amiben tíz szám 0..9-ig egyedi sorrendben, megfeleltethető egy útnak.

#### Függvények ismertetése:

```cpp
void initAndSolve();
```

Fő függvény, amely az általános genetikus algoritmus megoldását tartalmazza. A végén a megoldást kiírja a konzolra.
_Stop Condition:_ a megállási feltétel egy egyszerű ciklushoz kötött.

```cpp
void createTowns(size_t numOfTowns);
```

A paraméterben megadott mennyiségben generál Town osztályokat véletlen x és y pozíciókkal.

```cpp
Population initializePopulation(size_t numOfPopulation);
```

A paraméterben megadott mennyiségben (100) legenerálja a populáció egyedeit. Az első számsorrendben megadott út permutációit hozza létre és adja hozzá a megoldástérhez.

```cpp
void evaluation(Population&);
```

A populáció minden egyedének kiszámítja a fitnesz értékét. A populáció egy egyede tartalmazza a hozzá tartozó utat és fitness értéket.

```cpp
Population selection(Population&);
```

A populáció egyedeit sorrendbe rendezi fitnesz érték alapján és a jobbik felét kiválasztja szülőnek. A maradék másik fél elemeit eldobja a populációból - csonkoló kiválasztás - így lefelezve a populációt.

```cpp
Individual crossOver(Population& parents);
```

Paraméterként a szülőket megkapva - két szülő - sorrend alapú keresztezést hajt végre oly módon hogy a gyermek az első szülő tulajdonságainak első felét teljesen átveszi, majd a második szülőtől megkapja a tulajdonságainak második felét sorrendben úgy, hogy ismétlődő tulajdonságot nem örököl. Így őrizve meg a tulajdonságok elemeinek egyediségét.

```cpp
void mutate(Individual&, size_t occurence);
```

A megkapott egyedet lehet hogy mutálja úgy hogy két elemet felcserél. A cserék lehetséges számát az _occurence_ paraméter határozza meg, amely véletlenszerű értéke 0 és 2 között lehetséges.

```cpp
void reinsertion(Population&, Population&);
```

Két populáció unióját teszi lehetővé. Az eredeti populáció első feléhez adja az új keresztezett és mutált egyedek halmazát.

```cpp
Individual getBestIndividual(Population&); // argmin f(x)
```

Fitness érték szerint kiszedi a legjobb(legalacsonyabb) értékkel rendelkező egyedet a populációból.

```cpp
// (p1, p2,.., pk) <--random-- M
Population getKRandomParents(Population&, size_t numOfRandomIndividuals);
```

Kiválaszt két random szülőt a megadott populációból.

```cpp
FitnessVal calcFitness(Route&);
```

Kiszámolja a megadott út fitness értékét. Abban az egyedben eltárolja, amelyikben az út is található.

```cpp
void printSolution(Individual&);
```

Kiírja a végeredményt.
#### Megjegyzések:
nincs
### Harmadik probléma valamivel megoldva
#### Reprezentáció:

#### Probléma tér:
#### Megoldás tér:
#### Függvények ismertetése:
#### Megjegyzések: