# Haladó algoritmusok

### Legkisebb Egybefoglaló Poligon Hegymászó módszerrel megvalósítva
#### Probléma / Megoldás tér:
- Pontok halmaza amelyek koordinátái a megadott 0.0 és 100.0 közötti intervallumban találhatóak.
- Egy egybefoglaló _poligon_, amely négy ponttal rendelkezik. Pontjai a megadott intervallumban találhatóak.
- Cél a legkisebb területű poligon megtalálása, amely minden probléma térben található pontot tartalmaz.
#### Függvények ismertetése:
```cpp
void initAndSolve();
```
Kezdő függvény, amelynek feladata a kezdő értékek beállítása, azaz a probléma tér intervallumának meghatározása és annak feltöltése véletlen koordinátákkal generált pontokkal.
Ebben a függvényben van leírva a _távolság függvény_ is, amely egy meglévő poligonból létrehoz egy új poligont úgy, hogy pontjait véletlenszerűen generálja egy epsilon értéken és a problématéren belül.
Szintén itt van meghatározva a _fitnesz függvény_ is, amely a poligon térfogatát adja vissza.
A _leállási feltétel_ egy egyszerű ciklus számláló.
A fent leírtak meghatározása után meghívja a hegymászó algoritmus általános megoldó függvényét a _solveSBP()_ függvényt, majd ennek eredményét kiírja a _printSolution()_ függvény segítségével.

```cpp
Solution solveSBP(ProblemSpaceSize aS, DistSFn, float aEpsilon, FitnessFn, size_t aStopCond);
```
A hegymászó algoritmus általános megoldó algoritmusát tartalmazza.
Első lépésként létrehozza a kezdő poligont, amely a probléma tér négy sarkából indul. A megoldás indoklása, hogy így biztosabban ad vissza eredményt, mint ha véletlenszerű pozíciókból hoznánk létre poligont.
Ciklus fut, amíg a leállási feltétel nem teljesül. Új poligonok generálása a távolság függvény segítségével.
A megoldás arra is választ ad, hogy sikerült e jó megoldást találni. Ha nem akkor, csak azt a választ adja vissza, hogy nem sikerült, ha sikerült a megoldást is visszaadja.

```cpp
void fillWithRandomPoints(Polygon&, ProblemSpaceSize&, size_t aPointCount);
```
A jelenlegi megoldásban nem használt függvény. Kezdő véletlenszerű poligon létrehozására készült, de ezzel a megoldással sokszor nem kaptunk használható megoldás, így sokkal jobbnak bizonyult a probléma tér négy sarkából indulni.

```cpp
void printSolution(Solution&);
```
Kiírja a megoldást, ha talált.
#### Megjegyzések:
A véletlenszerűen számolt élek az egybefoglaló poligonhoz nagyon sokszor nem tudtak érvényes megoldást adni, a kiinduló helyzet lesz választva, hogy a keresési tér négy sarkából indulva közelít a módszer. Így mindig van jó megoldás, csak a véletlennek köszönhető jóságukban térnek el.

### Ütazó-ügynök probléma megoldása Genetikus programozással
#### Reprezentáció:
Tíz darab város(Town) osztály. A városok x és y pozíciót tartalmaznak, amelyek véletlenszerűen generáltak. 
#### Probléma tér:
Utak halmaza. Egy _út(Route)_ tíz várost jár be. Az egyes utak a városok sorrendjének permutációit tartalmazzák.
Az utak halmazát _populációnak(Population)_ tekintjük. Egy utat a hozzá tartozó fitnesz értékkel _egyednek(Individual)_ hívjuk.
Cél: a legrövidebb utat megtalálni a városok között.
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
A paraméterben megadott mennyiségben (100) legenerálja a populáció egyedeit. Az első számsorrendben megadott út permutációit hozza létre és adja hozzá a megoldástérhez. Az egyedek fitnesz értékeit nem tölti ki, csak beállítja maximális értékre.

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
Kiválaszt k - kettő - random szülőt a megadott populációból.

```cpp
FitnessVal calcFitness(Route&);
```  
Kiszámolja a megadott út fitnesz értékét. Abban az egyedben eltárolja, amelyikben az út is található.

```cpp
void printSolution(Individual&);
```  
Kiírja a végeredményt.

### Függvény közelítés megoldása Raj alapú módszerrel
#### Reprezentáció:
A lehetséges megoldások halmaza: populáció, mely véletlenszerűen generált egyedeket tartalmaz.
Egy egyednek pozíciója, sebessége és lokális optimuma van. Ezekre az értékekre ötdimenziós vektorokként tekintünk, ami megfeleltethető a köbös polinomnak, amelyet a feladathoz mellékelt fitnesz számítási függvény is használ.
#### Probléma / Megoldás tér:
A keresési tér a lehetséges megoldás polinom koefficienst értékei. Ezeket változtatjuk a sebesség, pozíció, lokális optimum és globális optimum értékeinek figyelembevételével.
#### Megoldás ismertetése:
A megoldás teljes mértékben a könyv által ismertetett algoritmusokat használja.
Fix kezdő adathalmazzal dolgozik, a könnyebb eredmény összehasonlítás végett. Az adathalmaz azt mutatja, hogy 1 óra tanulással 50 pontot lehet a vizsgán elérni, 2 óra tanulással 60 pontot, stb..
Ennek az adathalmaznak keressük a közelítő függvényét.
Megállási feltétel iterációszám vagy elfogadható hibahatár esetén valósul meg.
A végén kiírja a legjobb talált eredményt a globális optimumot és összehasonlítja az eredeti adathalmazzal, a hibát százalékos formában megjeleníti.
#### Értékelés:
A megoldás sok paramétert használt ezek változtatásával a következő észrevételek születtek:
- a legjobb eredményeket 1-3%-os hibákat, a véletlen egyedszámok nagyságrenddel növelése hozta
- fontosnak bizonyult a keresési tér megfelelő beállítása is, ez problémafüggő, túl kicsi és túl nagy keresési tér sem volt optimális
- léptetés számának növelése nem hozta meg a várt eredményt, itt sejtés, hogy lehet rossz a sebességszámítás, vagy lépés nagysága, gond lehet, hogy a globális optimumot a teljes polinomra nézzük, az egyes koefficiens számításokhoz, nem egyedileg
- a léptetéshez használt súlyok beállítása nehézkes
- a lépés nagyság megállapítása nehézkes 
- sikerült elég jó megközelítéseket találni, 1-3%-os hibahatáron belül
- az algoritmus nagyon be tud lassulni már 1000< egyedszám, vagy 1000< iteráció fölött
