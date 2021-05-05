Nume: Vasilescu Alexandru Madalin
Grupa: 331CB

# Tema 2
### Inmultire de matrici 
Implementarea calculului C = A × B × B^t + A^t × A

Organizare
-
Am lucrat in cele 3 fisiere puse la dispozitie din schelet(solver_blas.c, solver_neopt.c, solver_opt.c).

***BLAS***
* In cadrul acestei metode am folosit functii din biblioteca cblas.h
* Am folosit functiile cblas_trmm si cblas_dgemm.
* Am folosit cblas_dtrmm pentru a realiza inmultirea cu matricile triunghiulare(A × B si A^t × A). In cadrul celei de-a doua operatii am considerat doar A^t ca fiind matricea triunghiulara si A transmisa ca o matrice oarecare. 
* Am transmis parametrii necesari gasiti online pentru functie.
* Am folosit functia cblas_dgemm atat pentru inmultirea rezultatului A × B cu B^t cat si pentru adunarea cu A^t × A. 
* Am alocat 2 matrici suplimentare in care am copiat A si B pentru a putea pastra rezultatele partiale si a le da ca parametrii functiilor.
* O matrice am dezalocat-o pentru ca nu mai era nevoie de ea la final si pe cealalta am returnat-o.

***NEOPT***
* Am creat o functie care aduna 2 matrici. Elementele din prima matrice sunt adunate la elementele celei de-a doua(data ca parametru).
* Prima data am realizat inmultirea dintre A si B. Inmultirea se face cu o matrice superior triunghiulara asa ca se folosesc doar elementele de deasupra matricei A(k porneste de la i).
* Apoi am realizat inmultirea A×B cu B^t. Nu am recalculat matricea B transpus. Am preferat sa fac inmultirea linie cu linie in loc de linie cu coloana.
* Ultima inmultire este intre A^t si A. Inmultirea se face cu o matrice inferior triunghiulara(A transpus) deci am folosit doar elementele de sub diagonala principala(k merge de la 0 la i). Nu am trasnpus matricea A. Am facut inmultirea coloana cu coloana.
* Dupe efectuarea tuturor inmultirilor matricile finale se aduna si matricile auxiliare se elibereaza.

***OPT***   
* Am inceput prin a calcula transpusa matricei A pentru ultima inmultire.
* Prima data am realizat inmultirea B × B^t pentru ca rezultatul este o matrice simetrica. Inmultirea cu B transpus am facut-o linie cu linie ca la varianta neoptimizata.
* Apoi am realizat inmultirea rezultatului anterior cu A. Datorita faptului ca matricea anterioara (B × B^t) este simetrica am putut face din nou inmultire linie cu linie(liniile si coloanele fiind egale). 
* Ca in cazul neopt k-ul porneste de la i si merge pana la n pentru a folosi doar ce e deasupra diagonalei principale
* Ultima inmultire este intre A^t si A. Am folosit pentru ambi operanzi matricea At(A transpus calculata anterior) pentru a face inmultirea linie cu linie. 
* Ca in cazul neopt k-ul porneste de la 0 si merge pana la minimul dintre i si j pentru a folosi doar ce e deasupra diagonalei celei de-a doua matrice sau sub diagonala primei. Rezultatul l-am adunat direct la matricea obtinuta la inmultirea A × B × B^t
* Am facut doar inmultiri linie cu linie pentru a reduce timpul de acces la memorie(inmultirile linie cu coloana ingreuneaza timpul prin aces al elementelor pe coloane). Prin rearanjarea operatiilor acest lucru mi-a fost foarte usor de realizat.
* Ca metoda de optimizare am ales metoda de eliminare a constantelor si optimizarea accesului la vectori predat la laboratorul 5.
* Am ales sa folosesc pointerii la matrici, suma in care se retin elementele si variabila k ca registri deoarece sunt accesati foarte des si sunt schimbati foarte des.
* Am adaptat algoritmul de la laborator sa faca inmultiri doar pe linii.

***CACHEGRIND***
* Am folosit utilitarul valgrind cu parametri oferiti in enunt. Am salvat in fisiere analizele cache asa cum se cere.
* Am observat diferente foarte mari intre cele 3 metode.

**Din punct de vedere al intructiunilor realizate:**
* Neopt are cele mai multe instructiuni(apx 5 miliarde), opt are mai putine (apx 1 Miliard) si blas are cele mai putine(250 de milioane).
* Astfel varianta optimizata are un sfert din intructiunile variantei neoptimizate datorita accesarii memoriei cu pointeri si lucrului cu registri si varianta blas de 20 de ori mai putine.
* Toate 3 metodele au aproximativ acelasi numar de miss-uri si 0% miss rate pe instructiuni(nivelul 1 de cache).

**Din punct de vedere al accesarilor memoriei:**
* Varianta neoptimizate din nou are cele mai multe accesari ale memoriei cache (apx. 3 miliarde) si cele mai multe missuri.
* Varianta optimzata are doar o zecime din accesarile variantei optimizate(doar 300 de milioane) si mai putine missuri.
* Varianta blas are cele mai putine accesari si missuri.
* Varianta neoptimizata are miss rateul mai mic decat varianta optimizata datorita faptului ca sunt foarte multe accesari ale aceleiasi date de mai multe ori(matricea rezultat). Varianta blas are cel mai mic miss rate deci este cea mai cache efficient
* Din LL refs se pot observa si numarul de accesari la memoria principala. Din nou neopt are cele mai multe urmata de opt si blas.

**Din punct de vedere a branchurilor executate:**
* Varianta optimizata si neoptimizata au un numar aproximativ egal de branchuri si mispredicts(acesta fiind foarte mare) datorat conditiilor din foruri.
* Varianta blas are foarte putine branchuri fata de celelalte variante.

***ANALIZA COMPARATIVA***
* Am realizat analiza in functie de timpul de rulare a fiecarei metode pe dimensiuni ale matricilor diferite
* Am folosit dimensiunile oferite cu scheletul (400,800,1200). Am adaugat eu 1000 si 1600 pentru a vedea cum decurge programul pe dimensiuni mai mari.
* Timpii la varianta blas sunt cei mai mici (la 1600 calculul se realizeaza in doar 2 secunde). Au o creste lenta timpii.
* Pentru varianta optimizata timpii cresc mai repede intre dimeniuni diferite dar la dimensiunea maxima (1600) operatiile se realizeaza in doar 11 secunde.
* Pentru varianta neoptimzata timpii au o creste rapida (la matricea de 1600x1600 operatiile se realizeaza in 80 de secunde) 
* Variantele optimzata si neoptimizata au ambele o crestere polinomiala insa cea neoptimizata are o creste mult mai rapida decat cea optimizata.
* Am inclus si un grafic in care cele 3 metode sunt scalate logaritmic. Au cam aceelasi tip de crestere dar in timpi diferiti.

Implementare
-

* Am implementat intreg enuntul
* Toate fisierele comparatiile intre rezolvarea mea si fisierele de referinta sunt ok. 
* Timpul la varianta optimizata la 1200 de elemente pe coada este de 4.4 secunde.

Resurse utilizate
-

* Am folosit resursele puse la dispozitie de echipa.
* Documentatia de la Blas ATLAS, laboaratorul 5 si 6.
* Documentatii suplimentare pentru functiile blas
* cblas_dgemm -> http://www.netlib.org/lapack/explore-html/dc/d18/cblas__dgemm_8c_abae9e96e4ce9231245ea09a3f46bdba5.html
* cblas_dtrmm -> http://www.netlib.org/lapack/explore-html/d5/db0/cblas__dtrmm_8c_acbf40f4eac3fa3e2cdcafa5a1f1cf6da.html

Github
-
https://github.com/alexandru-vasilescu/Matrix-multiplication/tree/main
