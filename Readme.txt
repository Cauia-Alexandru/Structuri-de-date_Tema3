Cauia Alexandru 314 CB
T1 *nod nou(void)--------------------
Aloc o variabila de tip T1* si initializez toate componentele din structura cu NULL, inclusiv 
cei 68 de copii care reprezinta caracterele.

void add_book_T1-------------------------
Functia primeste ca parametru radacina de tip T1*, cheia care e titlul cartii, si structura cu 
informatiile cartii.
Cu ajutorul functiei poz_litera aflu indexul si intr-un for verific pe rand fiecare litera din 
titlu daca se afla in arbore. Daca nu este, apelez functia de creare nod. Si la finalul caii
introduc un pointer catre structura cu informatii a cartii.

void add_book_T2--------------
Exact ca si add_book_t2, dar la sfarsit verific daca exista campul T1 din nodul T2. Daca nu
il egalez cu un alt T1 care e parametru functiei. Altfel, in functia de citire fac un aux in care
voi stoca titlurile urmatoarelor cati si pe rand le voi pune in trie cu ajutorul primei
functii de add.


Adr_carte search --------------------------
Functia intoarce structura cu carte pentru a putea afisa toate detaliile.
Caut cu ajutorul aceluiasi for, daca nu gasesc returnez null, daca ajung pana la sfarsit, 
returnez informatiile si le printez in functia de citire.

void afisare_T1----------------------
In aceasta functie afisez recursiv toate cartile autorului. Verific daca e nod terminal si
afisez cartea, daca nu merg mai departe pana ajung la nodul frunza.

void list_author----------------------
In aceasta functie am implementat si "search_by_author". Primii 3 parametri ai functiei sunt
pentru "list author", iar ultimii 2 i-am adaugat pentru "search by author"
In aceeasi maniera ca in functiile anterioare verifica daca este autorul in lista. 
Daca este si int a =1, atunci apelez functia pentru list_author. Daca a = 0, apeles pentru
cealalta functie, unde mai folosesc functia "search". 
