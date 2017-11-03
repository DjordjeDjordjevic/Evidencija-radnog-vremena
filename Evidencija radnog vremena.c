#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Struktura za predstavljanje vremena
typedef struct vreme
{
	int sat;
	int minut;
	int sekund;
}Vreme;

//Struktura koja predstavlja radnika
typedef struct radnik
{
	int id;
	char imeRadnika[20];
	char prezimeRadnika[20];
	int test;
	
	Vreme radnoVreme, 
          dolazakNaPosao, 
          odlazakSaPosla,
          ukupnoVremeNedelja, 
          ukupnoVremeMesec;
}Radnik;

Radnik radnik;

void dodavanjeRadnika();                    //Funkcija za dodavanje radnika
void ispisivanjeRadnika();                  //Funkcija za ispis imena radnika
void ispisivanjeRadnikaMesec();             //Funkcija za ispis radnog vremena radnika na mesecnom nivou
void posao();                               //Funkcija za unosenje dolaska i odlaska sa posla
void dodavanjeVremena();                    //Funkcija za unosenje vremena
void dolazakOblazak();                      //Funkcija za unos vremena dolaska i vremena odlaska
void racunanjeRadnogVremena();              //Funkcija za izracunavanje radnog vremena na dnevnom nivou
void formatiranjeVremena();                 //Funkcija za formatiranje vremena
int izmeniRadnika();
void izmenaFajlaRadnik();
int brisanjeRadnika();
int brisanjeRadnikaFajl();
void stvaranjePutanje();


int opcija,                                 //Promenljiva za cuvanje odabrane opcije u meniju
    id = 0,                                 //ID Radnika
	izmenaRadnika;
	
FILE *radnikFajl;
FILE *spisakRadnikaFajl;
FILE *noviSpisak;

char idC[3],
	 ime[20],
	 prezime[20],
	 imeFajla[100],
	 novoImeFajla[100],
	 imeFoldera[10],
	 extenzija[5],
	 imeSpiska[50],
	 imeNovogSpiska[50];
main()
{
	strcpy(imeFoldera, "Radnici\\");
	strcpy(extenzija,".txt");
	strcpy(imeSpiska, "Spisak radnika.txt");
	strcpy(imeNovogSpiska, "Novi spisak radnika.txt");
	
    while(1)
	{
		printf("-------------------------------------------------\n");
		printf("|Program za evidenciju radnog vremena zaposlenih|\n");
		printf("-------------------------------------------------\n");
		printf("|1.|\tRadnici:\t\t\t\t|\n");
		printf("|2.|\tRadno vremena:\t\t\t\t|\n");
		printf("|3.|\tUnos vremena:\t\t\t\t|\n");
		printf("|4.|\tIzlaz iz programa:\t\t\t|\n");
		printf("-------------------------------------------------\n");
		
		//Korisnik bira opciju iz menija
		printf("Izberite opciju: ");
		scanf("%d",&opcija);
		getchar();
		printf("\n");
		
		switch(opcija)
		{
			case 1:
                 //Opcija 1 poziva funkciju za dodavanje radnika
				dodavanjeRadnika();
				break;
			case 2:
                 //Opcija 2 poziva funkciju za ispis imena radnika
                 //A zatim pita korisnika za ID radika
                 //Ako radnik sa datim ID-jem postoji 
                 //Poziva se funkcija za ispisivanje radnog vremena radnika na mesecnom nivou
				ispisivanjeRadnika();
				printf("Unesite ID radnika: ");
				scanf("%d", &id);
				getchar();
				printf("\n");
				
				ispisivanjeRadnikaMesec(id);
				
				break;
			case 3:
                 //Opcija 3 poziva funkciju za ispis radnika
                 //A zatim pita korisnika za ID radnika
                 //Ako radnik sa datim ID-jem postoji 
                 //Poziva se funkcija za unosenje dolaska i odlaska sa posla
				ispisivanjeRadnika();
				
				printf("Unesite ID radnika: ");
				scanf("%d", &id);
				getchar();
				printf("\n");
										
				posao(id);
				
				break;
			case 4:
                 //Opcija 4 gasi program
				exit(0);
				break;
		}
	}
	
}

/*
  FUNKCIJA: Dodavanje radnika
  Kada se pozove funkcija prvo se pozove funkcija ispisivanjeRadnika()
  koja ce ispisati spisak svih radnika.
  Nakon toga korisnik bira da li ce da doda ili izmeni radnika
  Ako korisnik izabere da doda radnike 
      pojavljuje mu se unos u kome unosi imena radnika
  Ako korisnik izabere da izmeni radnika
      korinik prvo unosi ID radnika kojeg zeli da izmeni
      nakon toga mu se pojavljuje staro ime radnika i unos za novo ime radnika
*/
void dodavanjeRadnika()
{	
	int index, pom, opcija;
	
	printf("---------------------------------\n");
	printf("|  |\tRadnici\t\t\t|\n");
	printf("---------------------------------\n");
	printf("|1.|\tDodaj novog radnika\t|\n");
	printf("|2.|\tIzmena radnika\t\t|\n");	
	printf("|3.|\tBrisanje radnika\t|\n");
	printf("|4.|\tSpisak radnika\t\t|\n");
	printf("|5.|\tPovratak\t\t|\n");
	printf("---------------------------------\n");
	printf("Izaberite opciju: ");
	
	scanf("%d", &opcija);
	getchar();
	printf("\n");
	
	switch(opcija)
	{
		//Dodaj radnike
		case 1:	
		
			//Otvaranje fajla spisak radnika
			//radi nalazenja posledenjeg id-a
			spisakRadnikaFajl = fopen(imeSpiska, "r");
			if(spisakRadnikaFajl == NULL)
			{
				printf("Greska prilikom otvaranja fajla %s", imeSpiska);
				return;
			}
			
			while(1)
			{
				fscanf(spisakRadnikaFajl, "%d%s%s", &id, ime, prezime);
				
				if(feof(spisakRadnikaFajl))
				{
					/* TODO (#1#): Algoritam za proveru prvog slobodnog ID 
					               broja */
					id++;
					fclose(spisakRadnikaFajl);
					break;
				}
			}
			
			//Otvaramo fajl spisak radnika u rezimu append
			//za dodavanje novog radnika
			spisakRadnikaFajl = fopen(imeSpiska, "a+");
			if(spisakRadnikaFajl == NULL)
			{
				printf("Greska prilikom otvaranja fajla %s", imeSpiska);
				return;
			}
			
			//Korisnik unosi ime i prezime novog radnika
			printf("---------------------------------\n");
			printf("|Ime i prezime radnika:\t\t|\n");
			printf("---------------------------------\n");
			scanf("%s", ime);
			scanf("%s", prezime);		
			
			//Upisivanje novog radnika u fajl spisak radnika
			fprintf(spisakRadnikaFajl, "%d %s %s\n", id, ime, prezime);
			
			//Pretvaranje int-a u char
			sprintf(idC, "%d", id);
			
			//Stvaranje putanje do fajla novog radnika
			stvaranjePutanje(imeFajla, id, ime, prezime);

			//Otvaranje fajla sa imenom radnika u folderu Radnici
			radnikFajl = fopen(imeFajla, "w");
			if(radnikFajl == NULL)
			{
				printf("Greska prilikom otvaranja fajla %s", imeFajla);
				fclose(spisakRadnikaFajl);
				return;
			}
			
			fclose(radnikFajl);
			fclose(spisakRadnikaFajl);
			
			dodavanjeRadnika();
			break;
		//Izmeni radnike
		case 2:
			//Broj izmena
			izmenaRadnika = 0;
							
			//Prikaz svih radnika
			ispisivanjeRadnika();
			
			//Otvaranje fajla "Spisak radnika"
			spisakRadnikaFajl = fopen(imeSpiska, "r");
			if(spisakRadnikaFajl == NULL)
			{
				printf("Greska prilikom otvaranja fajla %s\n", imeSpiska);
				return;		
			}
			
			//Novi fajl "Novi spisak radnika"
			noviSpisak = fopen(imeNovogSpiska, "a");	
			if(noviSpisak == NULL)
			{
				printf("Greska prilikom otvaranja fajla %s\n", imeNovogSpiska);
				fclose(spisakRadnikaFajl);
				return;		
			}
						
			printf("Unesite id radnika za izmenu:\n");			
			scanf("%d",&pom);
			
			while(izmeniRadnika(spisakRadnikaFajl, noviSpisak, &radnik, pom))
			{
				printf("");
			}		
			
			fclose(noviSpisak);	
			fclose(spisakRadnikaFajl);
			
			//Ako je bilo izmena u fajlu
			if(izmenaRadnika > 0)
			{
				//Brisemo fajl "Spisak radnika"
				if(remove(imeSpiska) == 0)
					printf("Stari fajl obrisan\n");					
				else
					printf("Stari fajl nije obrisan %d");
					
				
				//Preimenujemo "Novi spisak radnika" u "Spisak radnika"
				if(rename(imeNovogSpiska, imeSpiska) == 0)
					printf("Stari fajl preimenovan\n");					
				else
					printf("Stari fajl nije preimenovan\n");
			}
			//Ako nije bilo izmena u fajlu
			else
			{
				//Brisemo fajl "Novi spisak radnika"
				if(remove(imeNovogSpiska) == 0)
					printf("Stari fajl obrisan %s\n", imeNovogSpiska);					
				else
					printf("Stari fajl nije obrisan %s\n", imeNovogSpiska);
			}
			break;
		
		//Brisanje radnika
		case 3:
			//Prikaz svih radnika
			ispisivanjeRadnika();
			
			//Otvaramo fajl "Spisak radnika"
			spisakRadnikaFajl = fopen(imeSpiska, "r");
			if(spisakRadnikaFajl == NULL)
			{
				printf("Greska prilikom otvaranja fajla %s\n", imeSpiska);
				return;		
			}
			
			//Novi fajl "Novi spisak radnika"
			noviSpisak = fopen(imeNovogSpiska, "a");	
			if(noviSpisak == NULL)
			{
				printf("Greska prilikom otvaranja fajla %s\n", imeNovogSpiska);
				fclose(spisakRadnikaFajl);
				return;		
			}			
			
			printf("Unesite id radnika za brisanje:\n");			
			scanf("%d",&pom);
			
			while(brisanjeRadnika(spisakRadnikaFajl, noviSpisak, &radnik, pom))
			{
				printf("");
			}
			fclose(noviSpisak);	
			fclose(spisakRadnikaFajl);
			
			//Brisanje starog fajla "Spisak radnika"
			if(remove(imeSpiska) == 0)
					printf("Stari fajl obrisan %s\n", imeSpiska);
					
			else
				printf("Stari fajl nije obrisan %s\n", imeSpiska);
			
			//Preimenovanje fajla "Novi spisak radnika" u "Spisak radnika"		
			if(rename(imeNovogSpiska, imeSpiska) == 0)
				printf("Stari fajl preimenovan %s\n", imeNovogSpiska);
					
			else
				printf("Stari fajl nije preimenovan %s\n", imeNovogSpiska);
			
			break;
		
		//Spisak radnika
		case 4:
			ispisivanjeRadnika();
			getchar();
            break;
		
		//Povratak
		case 5:
		defalt:
            //Opcija 4 i default opcija vracaju korisnika  na predhodni meni
            break;
	}
	
}

/*
	FUNKCIJA: Ispisivanje imena radnika
	Kada se pozove ova funkcija program prolazi kroz spisak radnika
	i ispisiuje id i ime i prezime svih radnika
*/
void ispisivanjeRadnika()
{
	int i, test;
	
	//Otvaranje fajla "Spisak radnika"
	spisakRadnikaFajl = fopen(imeSpiska, "r");
	if(spisakRadnikaFajl == NULL)
	{
		printf("Greska prilikom otvaranja fajla %s", imeSpiska);
		return;		
	}
	
	printf("----------------------------\n");
	printf("||\t    Radnici\t  ||\n");
	printf("----------------------------\n");
	printf("|id|     Ime i prezime    ||\n");
	printf("----------------------------\n");
	
	//Prolazak kroz fajl "Spisak radnika" i ispisivanje podataka
	while(1)
	{		
		fscanf(spisakRadnikaFajl, "%d%s%s",&i, ime, prezime);
		if(feof(spisakRadnikaFajl))
		{
			printf("----------------------------\n");
			fclose(spisakRadnikaFajl);
			return;
		}
		printf("|%2d|%11s %10s||\n", i, ime, prezime);
	}
}

/*
	FUNKCIJA: Izmena radnika
	Prosledjuju se dva fajla, orginalni fajl sa spiskom radnika i novi fajl za dodavanje nakon izmene, 
	struktura Radnik i id radnika za brisanje
	Citamo podatke iz fajla 'in' i cuvamo ih u strukturi
	Ako nadjemo radnika sa prosledjenim id-jem 
		Ispisujemo ime i prezime radnika za izmenu
		Korisnik unosi novo ime i prezime radnika i 
		upisujemo ih u fajl 'out' i vracamo se iz funkcije
		Ako je novo ime i prezime isto kao i staro 
			samo vracamo iz funkcije
	U suprotnom u fajl 'out' upisujemo ucitane podatke iz fajla 'in'
	i vracamo se iz funkcije
*/
int izmeniRadnika(FILE *in, FILE *out, Radnik *r, int id)
{
	char novoIme[20],
		 novoPrezime[20];
		 
	//Citanje svakog radnika iz spiska radnika
	fscanf(in,"%d%s%s", &r->id, r->imeRadnika, r->prezimeRadnika);
	
	//Ako smo dosli do kraja fajla i nismo napravili nikakvu izmenu radnik ne postoji
	if(feof(in))
	{
		if(izmenaRadnika==0)
			printf("Radnik ne postoji\n");
		return 0;
	}
	
	//Da li ucitani ranik ima isiti ID kao sto je prosledjen funkciji
	if(r->id == id)
	{
		printf("---------------------------------\n");
		printf("|Staro ime i prezime:\t\t|\n");
		printf("---------------------------------\n");
		printf("%s %s\n",r->imeRadnika, r->prezimeRadnika);
		printf("---------------------------------\n");
		printf("|Unesite novo ime i prezime:\t|\n");
		printf("---------------------------------\n");
		scanf("%s", &novoIme);
		scanf("%s", &novoPrezime);
		printf("\n");
		
		//Da li je novo ime i prezime isto kao i staro ime i prezime
		if(strcmp(novoIme, r->imeRadnika) == 0 && strcmp(novoPrezime, r->prezimeRadnika) == 0)
			return 0;
		
		//Upisivanje novog imena i prezimena u fajl 'out'
		fprintf(out, "%d %s %s\n", r->id, novoIme, novoPrezime);
		
		//Izmene u folderu Radnik
		izmenaFajlaRadnik(r, novoIme, novoPrezime);
		
		izmenaRadnika++;
		return;
	}
			
	fprintf(out, "%d %s %s\n", r->id, r->imeRadnika, r->prezimeRadnika);
	return 1;
}

/*
	FUNKCIJA: Izmeni fajl radnika
	Prosledjujemo strukturu Radnik, dva String-a sa novim imenom i prezimenom
	String 'imeFajla' je putanje do fajla koji menjamo 
	a string 'novoImeFajla' je putanja do novog fajla
	Ucitavamo podatke iz starog fajla i upisujemo ih u novi fajl
	Na kraju brisemo stari fajl
*/
void izmenaFajlaRadnik(Radnik *r, char imeIzmena[], char prezimeIzmena[])
{
	char novoImeFajla[100];
	
	FILE *noviFajlRadnik,
		 *stariFajlRadnik;
	
	//Stvaranje putanje do fajla koji se menja
	stvaranjePutanje(imeFajla, r->id,r->imeRadnika, r->prezimeRadnika);
	
	//Stvaranje putanje do fajla sa izmenama
	stvaranjePutanje(novoImeFajla, r->id, imeIzmena, prezimeIzmena);
	
	//Otvaramo novi fajl sa imenom i prezimenom radnika
	stariFajlRadnik = fopen(imeFajla, "r");
	if(stariFajlRadnik == NULL)
	{
		printf("Greska prilikom otvaranja fajla %s\n", imeFajla);
		return;
	}
	
	//Otvaramo novi fajl sa imenom i prezimenom radnika
	noviFajlRadnik = fopen(novoImeFajla, "a");
	if(noviFajlRadnik == NULL)
	{
		printf("Greska prilikom otvaranja fajla %s\n", novoImeFajla);
		return;
	}
	
	while(1)
	{
		//Ucitavamo podatke iz starog fajla sa imenom radnika
		fscanf(stariFajlRadnik, "%d%d%d%d%d%d", &r->dolazakNaPosao.sat,
									  			&r->dolazakNaPosao.minut,
												&r->dolazakNaPosao.sekund,
												&r->odlazakSaPosla.sat,
												&r->odlazakSaPosla.minut,
												&r->odlazakSaPosla.sekund);
		
		//Ako smo dosli do kraja starog fajla radnika
		//Zatvaramo stari i novi fajl
		//izlazimo iz petlje
		if(feof(stariFajlRadnik))
		{
			fclose(noviFajlRadnik);
			fclose(stariFajlRadnik);
			break;
		}
		//Upisujemo podatke u novi fajl sa imenom i prezimenom radnika
		fprintf(noviFajlRadnik, "%d %d %d %d %d %d\n",  r->dolazakNaPosao.sat,
														r->dolazakNaPosao.minut,
														r->dolazakNaPosao.sekund,
														r->odlazakSaPosla.sat,
														r->odlazakSaPosla.minut,
														r->odlazakSaPosla.sekund);
		
	}
	//Brisemo stari fajl
	if(remove(imeFajla) == 0)
		printf("Stari fajl obrisan %s\n", imeFajla);		
	else
		printf("Stari fajl nije obrisan %s\n", imeFajla);
}

/*
	FUNKCIJA: Brisanje radnika
	Prosledjuju se dva fajla, struktura Radnik i id radnika za brisanje
	Citamo podatke iz fajla 'in' i cuvamo ih u strukturi
	Ako nadjemo radnika sa prosledjenim id-jem 
		pozivamo funkciju brisanjeRadnikaFalj() i prosledjujemo strukturu Radnik
		vracamo se iz ove funkcije
	U suprotnom u fajl 'out' upisujemo ucitane podatke iz fajla 'in'
*/
int brisanjeRadnika(FILE *in, FILE *out, Radnik *r, int id)
{
	//Citanje svakog radnika iz spiska radnika
	fscanf(in,"%d%s%s", &r->id, r->imeRadnika, r->prezimeRadnika);
	
	//Izlazimo iz funkcije ako je kraj fajla
	if(feof(in))
	{
		return 0;
	}
	
	//Da li ucitani radnik ima isti ID kao sto je prosledjen funkciji
	if(r->id == id)
	{
		if(brisanjeRadnikaFajl(r) == 0) {}
		else
		return 1;
	}
	
	//Upisivanje u fajl "Novi spisak radnika"	
	fprintf(out, "%d %s %s\n", r->id, r->imeRadnika, r->prezimeRadnika);
	return 1;
}

/*
	FUNKCIJA: Brisanje fajla radnika
	Prosledjuje se struktura Radnik
	String "fajl" je putanja do fajla koji brisemo
	Pozivamo funkciju remove() koja brise fajl
*/
int brisanjeRadnikaFajl(Radnik *r)
{
/* DONE (#1#): Ako se ne obrise fajl radnika u folderu da se ne 
               brise ni u fajlu "Spisak radnika" */
	char fajl[100];	
	
	//Stvaranje putanje do fajla radnika za brisanje		
	stvaranjePutanje(imeFajla, r->id, r->imeRadnika, r->prezimeRadnika);
	
	//Brisanje fajla
	if(remove(imeFajla) == 0)
		printf("Stari fajl obrisan %s\n", imeFajla);		
	else
	{
		printf("Stari fajl nije obrisan %s\n", imeFajla);
		return 0;
	}
		
	return 1;	
}
/*
	FUNKCIJA: Ispisivanje radnog vreme radnika na mesecnom nivou
	Kada se pozove ova funkcija 
    program tabelarno prikazuje radno vreme (za odabranog radnika) za svaki dan u mesecu, 
    ukupno radno vreme za svaku nedelju i za ceo mesec
*/
void ispisivanjeRadnikaMesec(int id)
{
	int i,j;
			
	radnik.ukupnoVremeMesec.sat = 0;
	radnik.ukupnoVremeMesec.minut = 0;
	radnik.ukupnoVremeMesec.sekund = 0;
	
	//Otvaramo fajl "Spisak radnika"
	spisakRadnikaFajl  = fopen(imeSpiska, "r");
	if(spisakRadnikaFajl == NULL)
	{
		printf("Greska prilikom otvaranja fajla %s\n", imeSpiska);
	 	return;
	}
	
	while(1)
	{
		//Ucitavanje podataka iz fajla "Spisak radnika"
		fscanf(spisakRadnikaFajl, "%d%s%s", &radnik.id, radnik.imeRadnika, radnik.prezimeRadnika);
		
		//Ako smo dosli do kraja fajla 
		//Radnik sa datim ID-ijem ne postoji
		//Zatvaramo fajl
		if(feof(spisakRadnikaFajl))
		{
			printf("Radnik ne postoji\n");
			fclose(spisakRadnikaFajl);
			
			return;
		}
	
		//Ako smo nasli radnika sa prosledjenim ID-jem
		if(radnik.id == id)
		{		
			fclose(spisakRadnikaFajl);
			
			//Stvaranje putanje do fajla radnika
			stvaranjePutanje(imeFajla ,radnik.id, radnik.imeRadnika, radnik.prezimeRadnika);
			
			//Otvaramo fajl sa imenom i prezimenom radnika
			radnikFajl = fopen(imeFajla, "r");
			if(radnikFajl == NULL)
			{
				 printf("Greska prilikom otvaranja fajla %s\n", imeFajla);
				 return;
			}
			
			//Ispisujemo ime i prezime radnika
			printf("||===========================================================================||\n");
			printf("||Radno vreme                                    Radnik%11s%11s||\n",radnik.imeRadnika, radnik.prezimeRadnika);
			printf("||---------------------------------------------------------------------------||\n");
			printf("||Ponedeljak|Utorak  |Sreda   |Cetvrtak|Petak   |Subota  |Nedelja ||Ukupno   ||\n");
			printf("||---------------------------------------------------------------------------||\n||  ");
			
			//Prolazak fajl radnika
			//Ispis sata, minuta, i sekundi, radnog vremena za svaki dan
			
			//Pet nedelja u mesecu
			for(i=0;i<5;i++)
			{
				radnik.ukupnoVremeNedelja.sat = 0;
				radnik.ukupnoVremeNedelja.minut = 0;
				radnik.ukupnoVremeNedelja.sekund = 0;
				
		        //Sedam dana u nedelji
				for(j=0;j<7;j++)
				{	
					//Ucitavanje podataka iz fajla radnika
					fscanf(radnikFajl, "%d%d%d%d%d%d",  &radnik.dolazakNaPosao.sat,
												 		&radnik.dolazakNaPosao.minut,
												 		&radnik.dolazakNaPosao.sekund,
														&radnik.odlazakSaPosla.sat,
												 		&radnik.odlazakSaPosla.minut,
												 		&radnik.odlazakSaPosla.sekund);
					
					//Ako nema podataka u fajlu ispisujemo nule
					if(feof(radnikFajl))
						printf("%2d/%2d/%2d|", 0, 0, 0);
					
					//U suprotnom racunamo radno vreme za dan
					//I ispisujemo u tabeli
					else
					{
						racunanjeRadnogVremena(&radnik);
						
						printf("%2d/%2d/%2d|",	radnik.radnoVreme.sat,
												radnik.radnoVreme.minut,
												radnik.radnoVreme.sekund);
					}			
				}
				
				//Dodavanje ukupnog radnog vremena nedelje na ukupno radno vreme meseca
				radnik.ukupnoVremeMesec.sat += radnik.ukupnoVremeNedelja.sat;
				radnik.ukupnoVremeMesec.minut += radnik.ukupnoVremeNedelja.minut;
				radnik.ukupnoVremeMesec.sekund += radnik.ukupnoVremeNedelja.sekund;
				
				
				//Pretvaranje celobrojnih vrednosti radnog vremena u format vremena (sat/minut/sekund)
				formatiranjeVremena(&radnik.ukupnoVremeNedelja.sat,
									&radnik.ukupnoVremeNedelja.minut,
									&radnik.ukupnoVremeNedelja.sekund);
				
				//Ispisivanje ukunog radnog vremena za nedelju
				if(i!=4)
					printf("|%3d/%2d/%2d||\n||  ",
					radnik.ukupnoVremeNedelja.sat,
					radnik.ukupnoVremeNedelja.minut,
					radnik.ukupnoVremeNedelja.sekund);
				else
				{
					printf("|%3d/%2d/%2d||\n",
					radnik.ukupnoVremeNedelja.sat,
					radnik.ukupnoVremeNedelja.minut,
					radnik.ukupnoVremeNedelja.sekund);
				}
			}
			
			//Pretvaranje celobrojnih vrednosti ukupnog radnog vremena 
			//u format vremena (sat/minut/sekund)
			formatiranjeVremena(&radnik.ukupnoVremeMesec.sat, 
								&radnik.ukupnoVremeMesec.minut,
								&radnik.ukupnoVremeMesec.sekund);
			
			printf("||---------------------------------------------------------------------------||\n");
			printf("||                                                          Ukupno||%3d/%2d/%2d||\n",
			//Ispisujemo ukpupno radno vreme za mesec
			radnik.ukupnoVremeMesec.sat, radnik.ukupnoVremeMesec.minut, radnik.ukupnoVremeMesec.sekund);
			printf("||===========================================================================||\n");
			printf("\nPritisnite Enter za povratak ");
			getchar();
			printf("\n");
			
			fclose(radnikFajl);
			
			return;
		}	
	}
}
/*
	FUNKCIJA: Unosenje vremena dolaska i odlaska sa posla
  	Otvaramo fajl sa spiskom radnika i trazimo da li postoji radnik sa prosledjenim ID-jem
  	Ako postoji ispisujemo ime i prezime radnika i pozivamo funkciju za dodavanje vremena
*/
void posao(int id)
{
	
	//Otvaranje fajla "Spisak radnika"
	spisakRadnikaFajl = fopen(imeSpiska, "r");
	if(spisakRadnikaFajl == NULL)
	{
		 printf("Greska prilikom otvaranja fajla %s\n", imeSpiska);
		 return;
	}
	
	while(1)
	{
		//Ucitavanje podataka iz fajla "Spisak radnika"
		fscanf(spisakRadnikaFajl, "%d%s%s", &radnik.id, &radnik.imeRadnika, &radnik.prezimeRadnika);
	
		//Ako smo dosli do kraja spisaka
		//ispisujemo poruku da nema radnika
		//zatvaramo fajl
		if(feof(spisakRadnikaFajl))
		{
			printf("Radnik ne postoji\n");
			fclose(spisakRadnikaFajl);
			return;
		}
	
		//Ako postoji radnik sa prosledjenim ID-jem
		//Zatvaramo fajl "Spisak radnika"
		//i pozivamo funkciju
		if(radnik.id == id)
		{
			fclose(spisakRadnikaFajl);
			dodavanjeVremena(radnik);
			return;
		}
	}
}
/*
  	FUNKCIJA: Unosenje vremena
  	Nakoon pozivanja ove funkcije korisnik unosi vreme dolaska/odlaska u formatu sat/minut/sekund
  	Funkcija odvaja elemente (sat, minut, sekunt) od celog stringa
  	Sat je predstavljen bojevima do prve kose crte, minut do druge kose crte a sekund od druge do kraja stringa
  	Nakon odvajanja, vredosti se dodeljuju adresama prosljedjenih argumenata
*/
void dodavanjeVremena(Radnik *r)
{
	Vreme v;
		
	v.sat = 0;
	v.minut = 0;
	v.sekund = 0;
	
	printf("-----------------------------------------\n");
	printf("|\tIme i prezime radnika    \t|\n");
	printf("-----------------------------------------\n");
	printf("|\t%11s %11s\t\t|\n",r->imeRadnika, r->prezimeRadnika);
	printf("-----------------------------------------\n");
	
	//Stvaranje putanje do fajla radnika		
	stvaranjePutanje(imeFajla, r->id, r->imeRadnika, r->prezimeRadnika);
		
	//Otvaramo fajl radika (citanje)
	radnikFajl = fopen(imeFajla, "r");
	if(radnikFajl == NULL)
	{
	 printf("Greska prilikom otvaranja fajla %s\n", imeFajla);
	 return;
	}

	while(1)
	{
		//Ucitavamo poslednji podatak
		fscanf(radnikFajl, "%d%d%d", &v.sat, &v.minut, &v.sekund);
		
		//Kad dodjemo do kraja fajla zatvaramo fajl
		if(feof(radnikFajl))
		{
			fclose(radnikFajl);
			break;
		}
		
	}
	
	//Ponovo otvaramo fajl radnika (dodavanje)
	radnikFajl = fopen(imeFajla, "a");
	if(radnikFajl == NULL)
	{
		 printf("Greska prilikom otvaranja fajla %s\n", imeFajla);
		 return;
	}
	
	char vremeString[6];                      //Deklarisemo niz karaktera (vremeString[6]) koji ce da cuva uneseno vreme
	
    char satiC[2], minutiC[2], sekundiC[2];   //Deklarisemo nizove karaktera za sat, minut i sekund
	
    int i,
        temp,                                 //pozicija slobodnog elementa u nizovima sat i minut
        pPrveCrte = 0,                        //pozicija prve crte (sat) u nizu vremeString[]
        pDrugeCrte=0,                         //pozicija druge crte (minut) u nizu vremeString[]
        brojac=0;                             //trenutni broj crta
	
	printf("Unesite vreme u sledecem formatu\n");
	printf("ss/mm/ss\n");
	printf("--------------------------------\n");
	
	//Ucitavamo vreme
	gets(vremeString);
	
	//Prolazimo kroz string "vremeString"
	for(i=0;i<strlen(vremeString);i++)
	{
		switch (brojac)
		{
			//Sati
			case 0:
				//Ako ucitani karakter nije '/'
				//cuvamo taj karakter u satiC na i-toj poziciji
				if(vremeString[i]!='/')
				{
					satiC[i] = vremeString[i];
				}
				//Ako jeste '/'
				//povecavamo brojac i pamtimo poziciju prve crte
				else
				{
					brojac++;				
					pPrveCrte = i;
				}
			
				break;
			//Minuti
			case 1:
				//Ako ucitani karakter nije '/'
				//cuvamo taj karakter u minutiC na temp poziciji
				if(vremeString[i]!='/')
				{
					//temp cuva poziciju u nizu karaktera (minutiC)
					temp = i-pPrveCrte-brojac;
					minutiC[temp] = vremeString[i];
				}
				//Ako jeste '/'
				//povecavamo brojac i pamtimo poziciju prve crte
				else
				{
					brojac++;				
					pDrugeCrte = i+1;
					
				}	
				break;
			//Sekundi
			case 2:
				//temp cuva poziciju u nizu karaktera (minutiC)
				temp = i-pDrugeCrte;
				sekundiC[temp] = vremeString[i];
				break;
		}
		
	}
	printf("\n");
	
	//Ako je vrednos poslednjeg podatka u fajlu radnika manja od unesene vrednosti i veca od 0
	//nakon unosa podatka prelazimo u novi red
	if((v.sat * 3600)+(v.minut * 60) + v.sekund < 
	  ((atoi(satiC) * 3600)+(atoi(minutiC)*60)+ atoi(sekundiC)) && 
	   (v.sat * 3600)+(v.minut * 60) + v.sekund > 0)
		fprintf(radnikFajl, "%d %d %d\n", atoi(satiC), atoi(minutiC), atoi(sekundiC));
	//u suprotnom nakon unosa ostajemo u istom redu
	else
		fprintf(radnikFajl, "%d %d %d ", atoi(satiC), atoi(minutiC), atoi(sekundiC));
	
	fclose(radnikFajl);
}
/*
	  FUNKCIJA: Izracunavanje radnog vremena na dnevnom nivou
	  Ova funkcija racuna radno vreme za zadatog radnika
	  Nakon izracunatg radnog vreme izracunati ukuno radno vreme nedelja i meseca
*/
void racunanjeRadnogVremena(Radnik *r)
{
	int i, j, prenos = 0;
	
	//Ako su sekunde dolaska vece od sekundi odlaska
	//radno vreme je jednako 60 (60s=1m) dodamo razliku odlaska i dolaska i prenosimo jedan minut
	if(r->dolazakNaPosao.sekund > r->odlazakSaPosla.sekund)
	{
		r->radnoVreme.sekund = 60 - (r->dolazakNaPosao.sekund) + (r->odlazakSaPosla.sekund);
		prenos = 1;		
	}
	//u suprotnom radno vreme je razlika izmedju odlaska i dolaska
	else
		r->radnoVreme.sekund = r->odlazakSaPosla.sekund - r->dolazakNaPosao.sekund;

    //Ako su minuti dolaska veci od sekundi odlaska
	//radno vreme je jednako 60 (60m=1s) dodamo razliku odlaska i dolaska i prenos i prenosimo jedan sat
	if(r->dolazakNaPosao.minut > r->odlazakSaPosla.minut)
	{
		r->radnoVreme.minut = 60 - (r->dolazakNaPosao.minut) + (r->odlazakSaPosla.minut) - prenos;
		prenos = 1;		
	}
	//u suprotnom radno vreme je razlika izmedju odlaska i dolaska
	else
	{
		r->radnoVreme.minut = r->odlazakSaPosla.minut - r->dolazakNaPosao.minut - prenos;
		prenos = 0;
	}
		
	//Ako je broj sati dolaska veci od broja sati odlaska	
	//radno vreme je jednako 24 (24s=1d) dodamo razliku odlaska i dolaska i prenos i prenosimo jedan sat
	if(r->dolazakNaPosao.sat > r->odlazakSaPosla.sat)
		r->radnoVreme.sat = 24 - (r->odlazakSaPosla.sat ) + (r->dolazakNaPosao.sat) - prenos;
	//u suprotnom radno vreme je razlika izmedju odlaska i dolaska
	else
		r->radnoVreme.sat = r->odlazakSaPosla.sat - r->dolazakNaPosao.sat - prenos;

	//dodamo dnevno radno vreme na ukupno radno vreme nedelje
	r->ukupnoVremeNedelja.sekund += r->radnoVreme.sekund;
	r->ukupnoVremeNedelja.minut += r->radnoVreme.minut;
	r->ukupnoVremeNedelja.sat += r->radnoVreme.sat;

}
/*
    FUNKCIJA: Formatiranje vremena
    Ova funkcija pretvara celobrojne vrednosti u sate, minute i sekunde
  	Prosledjuju se tri int pokazivaca za sat, minut i sekund
*/
void formatiranjeVremena(int *sat, int *min, int *sec)
{
	int prenos = 0;
	if(*sec>60)
	{
		prenos = *sec/60;
		*sec = *sec%60;
	}
	
	*min += prenos;
	
	if(*min>60)
	{
		prenos = *min/60;
		*min = *min%60;
	}
	
	*sat += prenos;	
}
/*
	FUNKCIJA: Stvaranje putanje
	Posledjuju se ime fajla, id, ime i prezime radnika
	Dodajemo putanju do folder, id, ime i prezime u pokazivac file
*/
void stvaranjePutanje(char file[100], int id, char imeP[20], char prezimeP[20])
{
	//Pretvaranje int-a u char
	sprintf(idC, "%d", id);
	
	//Stvaranje putanje do fajla
	//"Radnici\\<ID>_<NovoIme>_<NovoPrezime>.txt"
	strcpy(file, imeFoldera);
	strcat(file, idC);
	strcat(file, " ");
	strcat(file, imeP);
	strcat(file, " ");
	strcat(file, prezimeP);
	strcat(file, extenzija);
}
