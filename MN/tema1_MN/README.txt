Task 1: am incercat initial o altfel de citire a matricei point, pe care am lasat-o acolo(doar ca am comentat-o). 
Am folosit functia load deoarece functiona pe matlab. Aparent nu a functionat pe vmchecker asa ca am folosit dlmread.
Task 2: Am ales NC puncte random din matricea points, dar pentru a nu exista probabilitatea ca randi() sa ia doua puncte la fel, 
am creat un vector de indexi corespondenti tuturor liniilor cu puncte. randi va alege un index din vectorul respectiv, 
iar punctul va fi luat drept corespondentul indexului in matricea points. La final, indexul ales de randi() va fi eliminat din vector.
	Am recreat vectorul index cu nr de linii ale matricei points, avand astfel din nou cate un element corespondent la elementele 
matricei. Apoi am calculat cu norm() distanta de la fiecare punct la fiecare cluster si printr-un algoritm de minim am distrbuit fiecare 
punct la clasterul sau. Am creat o matrice cu 2 coloane: prima coloana este pentru indexii corespondenti fiecarui punct din points, 
iar a doua este pentru indexii corespondenti fiecarui punct din clasters, astfel incat fiecarui punct i se atribuie indexul clasterului 
sau.
	Am recalculat pozitiile centroizilor ca fiind centrele de masa ale punctelor atribuite fiecarui grup in parte.
	Am repetat acest proces pana cand distanta dintre centroizii vechi si cei noi e mai mica decat o toleranta de 10^16.
Task 3: Am recreat matricea 'p_claster' de la punctul 2. Apoi pentru fiecare claster am cautat punctele atribuite lui si le am 
dat aceeasi cloare. 
Task 4: Am recreat matricea 'p_claster' de la punctul 2. Apoi am luat fiecare cluster cu fiecare punct din acesta si am calculat normele
de la centroidul clasterului respectiv si fiecare punct din claster si le am adunat pe toate intr-o variabila 'cost'. Apoi trecand la
urmatoru claster voi repeta acelasi proces, pastrand astef suma tuturor normelor.
Task 5: Folosind functia taskului 4 de aflare a costului, am luat nr. de NC-uri printr-un for de {1, ..., 10}. Astfel pentru fiecare NC 
am realizat o coordonata pt grafic, dar le am salvat in 2 vectori: unul pt axa x si cealalta pentru y. Apoi am folosit comada plot pt. 
afisarea graficului.
	