/*
Das Programm hat die 4 Felder, 2 Gegner Felder und 2 Spieler Felder. Jedem Spieler wird das eigene Feld und ein GegnerFeld 
angezeigt. In seinem Feld kann er sehen wo seine Schiffe sind, auf dem Gegner Feld kann er nur sehen was er getroffen hat
und ob das Wasser oder getroffenes Schiff ist, wenn der was trifft, dann wird das mit 'g'gekennzeichnet. Es wird die Anzahl der 
Schiffe festgelegt und wie groß diese Schiffe sind
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
//? ist was unbekanntes
//- ist wasser
//X ist die Stelle des Schiffes
//g ist getroffen, aber nicht versenkt
//V ist versenktes Schiff


void clrscr()
{
	if(system("clear"))
		system("cls");
}
void Anzeige_Gegner_Feld(char **Feld_Gegner,char *Spieler)
{ 
	int i=0;
	int j=0;
	char Gegner=0;
	
	for(i=1;i<11;i++){
	Feld_Gegner[0][i]=i+47;//bei 48 fängt 0 als char in ASCII an
	Feld_Gegner[i][0]=i+64;//bei 65 fängt A in ASCII an!
	}
	if(*Spieler=='A')
		Gegner='B';
	if(*Spieler=='B')
		Gegner='A';
	printf("\n\n\t\t\t%c greift %c an:\nGegnerfeld: \n",*Spieler,Gegner);
	for(i=0;i<12;i++){
		printf("\n\n");
		for(j=0;j<12;j++){
			printf("%c\t",Feld_Gegner[i][j]);	
		}
	}
	getchar();
}
void Anzeige_Spieler_Feld(char **Feld_Spieler,char *Spieler)
{
	int i=0;
	int j=0;
	
	for(i=1;i<11;i++){
		Feld_Spieler[0][i]=i+47;//bei 48 fängt 0 als char in ASCII an
		Feld_Spieler[i][0]=i+64;//bei 65 fängt A in ASCII an!
	}
	printf("\n\t\t\t\tFeld von %c",*Spieler);
	for(i=0;i<12;i++){
		printf("\n\n");
		for(j=0;j<12;j++)
			printf("%c\t",Feld_Spieler[i][j]);		
	}
	getchar();
}
int Angriff(char **Feld_Spieler,char **Feld_Gegner,char **Feld_Schiff,char **Treffer,char *Spieler)
{
	Oben1:1;
	int a=0;
	int b=0;
	int i=0;
	int j=0;
	int x=0;
	int y=0;
	
	printf("\t\t\t\tSpieler %c",*Spieler);
	printf("\nWelche Position willst du angreifen (z.B. A3)? ");
	scanf("%c%c",&x,&y);
	fflush(stdin);
	x-=64;// gleich wie x=x-64
	y-=47;
	if(x<0||x>10||y<0||y>10){
		printf("\t\t\t\t\t++++++++++++falsche Eingabe++++++++++++\n\t\t\t\t\t\t  \\/________________        \n\t\t\t\t\t\t /     _____________)\n\t\t\t\t\t\t/     /     /   \\ |         \n\t\t\t\t\t\t\\/\\/\\/     (O) (O)|           \n\t\t\t\t\t\t  |           ------, \n\t\t\t\t\t\t  |  _       ______/ \n\t\t\t\t\t\t  | (_      /   \\  \\\n\t\t\t\t\t\t  |        /  ___\\_ \\       \n\t\t\t\t\t\t  |        \\      / / \n\t\t\t\t\t\t__|_________\\______/\n\t\t\t\t\t\t\\______________\\./__\\   \n\t\t\t\t\t\t /     .       | \\  |\n\t\t\t\t\t\t \\    /_\\   .  |  \\ |\\     \n\t\t\t\t\t\t |`\\       /_\\ |   \\| \\\n\n");
		goto Oben1;
	}
	
	clrscr();
	printf("Die Stelle: (%d,%d) bzw. (%c,%c)",x,y,x+64,y+47);
	if(Feld_Spieler[x][y]=='X'){//Es wird geschaut, ob an den Koordinaten xundy ein X in dem Feld des Gegenspieler Steht
		Feld_Gegner[x][y]='g';//wenn ja dann ist das ein Treffer
		for(i=0;i<10;i++){
			for(j=0;j<8;j++){
				if(Feld_Schiff[i][j]==x&&Feld_Schiff[i][j+1]==y){
					Treffer[i][j]=Feld_Schiff[i][j];
					Treffer[i][j+1]=Feld_Schiff[i][j+1];
				}
				j++;//damit j immer 2 Stellenmäßig funktioniert			
			}
			if(Treffer[i][0]==Feld_Schiff[i][0]&&Treffer[i][1]==Feld_Schiff[i][1]&&Treffer[i][2]==Feld_Schiff[i][2]&&Treffer[i][3]==Feld_Schiff[i][3]&&Treffer[i][4]==Feld_Schiff[i][4]&&Treffer[i][5]==Feld_Schiff[i][5]&&Treffer[i][6]==Feld_Schiff[i][6]&&Treffer[i][7]==Feld_Schiff[i][7]){//&&Treffer[i][j+1]==Feld_Schiff_B[i][j+1]
				for(j=0;j<8;j++){
					a=Treffer[i][j];
					b=Treffer[i][j+1];
					Feld_Gegner[a][b]='V';
					j++;
				}		
			}
		}
		a=0;
		for(i=0;i<10;i++){
			for(j=0;j<8;j++){
				if(Feld_Schiff[i][j]==Treffer[i][j])
					a=1;
				if(Feld_Schiff[i][j]!=Treffer[i][j]){
					a=0;
					break;
				}
			}
			if(a==0)
				break;
		}
		if(a==1){
			clrscr();
			return 0;
		}
			
		Anzeige_Gegner_Feld(Feld_Gegner,Spieler);	
		goto Oben1;
	}	
	if(Feld_Spieler[x][y]=='~'){
		Feld_Gegner[x][y]='~';
		printf("\nDu (%c) hast verkackt, der andere ist dran!",*Spieler);
	}
		
	Anzeige_Gegner_Feld(Feld_Gegner,Spieler);
	
	return 0;

}
void check()
{
	
}
void Eingabe(char **Feld_Spieler,char **Feld_Schiff,char *Spieler)//Feld Spieler und schiff eingener Spieler
{
	int i=0;
	int j=0;
	int x=0;
	int y=0;
	int s=0;
	int t=0;
	int Richtung='s';
	int Array[10]={4,3,3,2,2,2,1,1,1,1};
	
	for(i=0;i<10;i++){//SchiffFeld auf 0 gesetzt 
		for(j=0;j<8;j++)
			Feld_Schiff[i][j]=0;
	}
	i=10;//Anzahl der Schiffe
	while(i>0){
		
		clrscr();
		oben:1;
		if(x<0||x>10||y<0||y>10||(Richtung!='s'&&Richtung!='w'))
		{
			printf("\t\t\t\t\t++++++++++++++falsche Eingabe++++++++++++++");
		}//printf("\n\t\t\t                                                                      .uuu\n\t\t\t    z@#´%%c                      .uuzm**´´´´´*%%mu..             z*´` .e@#N\n\t\t\t   @!!!R.  #c              .z*´                    ^*c       z    dT!!!!!>\n\t\t\t  ´!!!!!!N   ´i         u*´                            #s  :´   @?!!!!!!!R\n\t\t\t  t!!!!!!!#u   ´i    .@                                  ^$   :R!!!!!!!!!X\n\t\t\t  ´!!!!!!!!!#c   ´i:#                                      ?> R!!!!!!!!!!X\n\t\t\t  ´!!!!!!!!!!!N   @                                         4W!!!!!!!!!!!>\n\t\t\t  ´!!!!!!!!!!!!Ru´                                           ?!!!!!!!!!!X\n\t\t\t  ´X!!!!!!!!!!!9~                                      .  .  ´X!!!!!!!!!6\n\t\t\t   R!!!!!!!!!!tF                                     z$#`   h &!!UR!!!!!F\n\t\t\t   ?!!!!!$X!!!$                                    .@       X $WTR!!!!!X\n\t\t\t    M!!!!!i#U!E  .                                @F        ! FdR!!!!!!f\n\t\t\t    ´X!!!!!#c´?u@#´*$N.                         :$          F´9!!!!!!!@\n\t\t\t     9!!!!!!!?NM      ^*c                      dF          ´ @!!!!!!!X>\n\t\t\t      R!!!!!!!!&         ´e                   d            K<!!!!!!!XF\n\t\t\t      ´X!!!!!!!M>          ^N                f            < E!!!!!!X´\n\t\t\t        t!!!!!!!#            ^N            :´      .e$´^  Fn!!!!!XP\n\t\t\t         #X!!!!!!ML             *c       z´    .e$$$$$   M´!!!!W*\n\t\t\t           ´*UX!!X@t  ^%%u.         ´´**#).zd$$#$$$$$$$  <\\*@**´\n\t\t\t                    ´N    4$$$$$@$$$)$$#$$k4$$$$$$$$$E :$\n\t\t\t                       ?>  ´$$$$$$´:$$$W$$$ ´$$$$$$$$   %%\n\t\t\t                      :´           ? ^#*´  S  ´$$$$$     ?\n\t\t\t                      F            L      d$L            X\n\t\t\t                      &           t$i    @$$$           f\n\t\t\t                       *          $$$$$$$$$$\\&        @\n\t\t\t                        ´*.      W'$$$$$$$$FM h    u#\n\t\t\t                           ^*muz* %% $$$$$$´:    `´\n\t\t\t                                   # ^**´ d\n\t\t\t                                     ´***´");
		
		//printf("\t\t\t\t\t++++++++++++falsche Eingabe++++++++++++\n\t\t\t\t\t\t  \\/________________        \n\t\t\t\t\t\t /     _____________)\n\t\t\t\t\t\t/     /     /   \\ |         \n\t\t\t\t\t\t\\/\\/\\/     (O) (O)|           \n\t\t\t\t\t\t  |           ------, \n\t\t\t\t\t\t  |  _       ______/ \n\t\t\t\t\t\t  | (_      /   \\  \\\n\t\t\t\t\t\t  |        /  ___\\_ \\       \n\t\t\t\t\t\t  |        \\      / / \n\t\t\t\t\t\t__|_________\\______/\n\t\t\t\t\t\t\\______________\\./__\\   \n\t\t\t\t\t\t /     .       | \\  |\n\t\t\t\t\t\t \\    /_\\   .  |  \\ |\\     \n\t\t\t\t\t\t |`\\       /_\\ |   \\| \\\n\n");		
		s=0;
		x=0;
		y=0;
		Richtung=0;
		printf("\n\n\t\t\t\t\t\tSpieler %c ",*Spieler);
		printf("\nDas % der Schiff ist dran:\n",Array[10-i]);
		printf("Geben Sie an wo das Schiff anfangen soll (z.B. %c%d): ",*Spieler+(10-i),(10-i));
		scanf("%c%c",&x,&y);
		fflush(stdin);
		x=x-64;
		y=y-47;
		if(x<0||x>10||y<0||y>10 ||Feld_Spieler[x][y]=='X')
			{
			if(Feld_Spieler[x][y]=='X')
			printf("\n Die Stelle ist belegt, platziere dein Schiff woanders!\n");
			goto oben;	
			}
		if(Feld_Spieler[x-1][y]=='X'||Feld_Spieler[x+1][y]=='X'||Feld_Spieler[x][y-1]=='X'||Feld_Spieler[x][y+1]=='X')
		{
			printf("so wird es nix, da ein Schiff in der Nähe steht, platziere das Schiff woanders!");
			goto oben;
		}
		if(Array[10-i]!=1){
		t=x-Array[10-i]+1;
		printf("Schiff senkrecht(s) oder waagerecht(w) setzen: ");
		scanf("%c",&Richtung);
		fflush(stdin);
		if(Richtung!='s'&&Richtung!='w')
		goto oben;
	//	clrscr();
		printf("Position:%c%c\n",x+64,y+47);
		printf("Richtung:%c",Richtung);
		if(Richtung=='s'){//muss k erhöht werden als x
			s=0;
			if((11-x)<Array[10-i]){
				for(j=0;j<2*Array[10-i];j++){
				
					printf("t+s: %d",t+s);
					Feld_Spieler[t+s][y]='X';
					Feld_Schiff[10-i][j]=t+s;
					j++;//für den ungeraden Wert
					Feld_Schiff[10-i][j]=y;
					s++;//damit die Stelle beim Spieler Feld sich um 1 erhöht
					if(Feld_Spieler[(t+s)-1][y]=='X'||Feld_Spieler[(t+s)+1][y]=='X'||Feld_Spieler[t+s][y-1]=='X'||Feld_Spieler[t+s][y+1]=='X')
					{	
						printf("so wird es nix, da ein Schiff in der Nähe steht, platziere das Schiff woanders!");
						goto oben;
					}
				}
				
			}
			if(11-x >= Array[10-i]){
				for(j=0;j<2*Array[10-i];j++){
				Feld_Spieler[x+s][y]='X';
			//	printf("x+s: %d",x+s);
				Feld_Schiff[10-i][j]=x+s;
				j++;//für den ungeraden Wert
				Feld_Schiff[10-i][j]=y;
				s++;//damit die Stelle beim Spieler Feld sich um 1 erhöht
					if(Feld_Spieler[(t+s)-1][y]=='X'||Feld_Spieler[(t+s)+1][y]=='X'||Feld_Spieler[t+s][y-1]=='X'||Feld_Spieler[t+s][y+1]=='X')
					{	
						printf("so wird es nix, da ein Schiff in der Nähe steht, platziere das Schiff woanders!");
						goto oben;
					}
			}	
			}
			
		}
		printf("\nSchritt 2");
		if(Richtung=='w'){//muss l erhöht werden als y
			for(j=0;j<2*Array[10-i];j++){
				Feld_Spieler[x][y+s]='X';
				Feld_Schiff[10-i][j]=x;
				j++;//für den ungeraden Wert
				Feld_Schiff[10-i][j]=y+s;
				s++;//damit die Stelle beim Spieler Feld sich um 1 erhöht
			}
		}	
		
		if(Array[10-i]==1){
			Feld_Spieler[x][y]='X';
			Feld_Schiff[10-i][0]=x;
			Feld_Schiff[10-i][1]=y;
			Richtung='s';//Fehler zu vermeiden, da bei der Ausgabe vom Spielerfeld sonst mit falsche Eingabe angezeigt wird, da man hier kein Richtung benutzt
		}
	
		Anzeige_Spieler_Feld(Feld_Spieler,Spieler);
		i--;
	}
}
}
int main()
{
	int i=0;
	int j=0;
	int a=1;
	int b=1;
	int x=11;
	int y=11;
	char Spieler=0;
	char Richtung=0;
	
	char *Feld_Spieler_A[x];//mit - aufgefüllt, das ist der Feld des Spielers A, was dem Spieler A angezeigt wird
	char *Feld_Gegner_von_A[x];//Feld des Spieler B, wird dem Gegner A angezeigt, ob er was getroffen hat oder nicht 
	char *Feld_Spieler_B[x];//Feld des Spieler B, wird Spieler B nur Angezeigt
	char *Feld_Gegner_von_B[x];//mit ? aufgefüllt, das ist der Feld des Spielers A, was für B angezeigt wird
	char *Feld_Schiff_A[10];
	char *Feld_Schiff_B[10];
	char *Treffer_A[10];
	char *Treffer_B[10];

	for(i=0;i<12;i++){
		Feld_Spieler_A[i]=(char *)calloc(y,sizeof(char));
		Feld_Gegner_von_A[i]=(char *)calloc(y,sizeof(char));
		Feld_Spieler_B[i]=(char *)calloc(y,sizeof(char));
		Feld_Gegner_von_B[i]=(char *)calloc(y,sizeof(char));
	}
	
	for(i=0;i<10;i++){
		Feld_Schiff_A[i]=(char *)calloc(8,sizeof(char));
		Feld_Schiff_B[i]=(char *)calloc(8,sizeof(char));
		Treffer_A[i]=(char *)calloc(8,sizeof(char));
		Treffer_B[i]=(char *)calloc(8,sizeof(char));
	}
	for(i=1;i<11;i++){		
		for(j=1;j<11;j++){
			Feld_Spieler_A[i][j]='~';
			Feld_Gegner_von_A[i][j]='?';
			Feld_Spieler_B[i][j]='~';
			Feld_Gegner_von_B[i][j]='?';
		}
	}
	system("color 61");/*61*/

	Spieler='A';
	printf("Spieler (A)\nSpieler (B)\nSpieler (A) beginnt: \n");
	printf("\n\n\n\t\t\t    _/_/_/_/              _/                          \n\t\t\t   _/        _/_/_/    _/_/_/_/    _/_/    _/  _/_/   \n\t\t\t  _/_/_/    _/    _/    _/      _/_/_/_/  _/_/        \n\t\t\t _/        _/    _/    _/      _/        _/           \n\t\t\t_/_/_/_/  _/    _/      _/_/    _/_/_/  _/ ");
	getchar();
	Eingabe(Feld_Spieler_A,Feld_Schiff_A,&Spieler);
	
	Spieler='B';
	Eingabe(Feld_Spieler_B,Feld_Schiff_B,&Spieler);

	while(a==0||b==0){
		printf("\nSpieler A ist dran");
		getchar();
		clrscr();
		Spieler='A';
		Angriff(Feld_Spieler_B,Feld_Gegner_von_A,Feld_Schiff_B,Treffer_A,&Spieler);
		for(i=0;i<10;i++){
			for(j=0;j<8;j++){
				if(Feld_Schiff_B[i][j]==Treffer_A[i][j])
					a=1;
				if(Feld_Schiff_B[i][j]!=Treffer_A[i][j])
					a=0;
				if(a==0)
					break;
			}
			if(a==0)
				break;
		}
		if(a==1)
			break;
		
		printf("Spieler B ist dran:\n");
		getchar();
		clrscr();
		Spieler='B';
		Angriff(Feld_Spieler_A,Feld_Gegner_von_B,Feld_Schiff_A,Treffer_B,&Spieler);
		for(i=0;i<10;i++){
			for(j=0;j<8;j++){
				if(Feld_Schiff_A[i][j]==Treffer_B[i][j])
					b=1;
				if(Feld_Schiff_A[i][j]!=Treffer_B[i][j])
					b=0;
				if(b==0)
					break;
			}
			if(b==0)
				break;
		}
		if(b==1)
			break;
	}
	clrscr();                                           
	if(a==1){	//Wenn A gewinnt, dann wird das ausgeführt
		printf("\t\t	      .--..--..--..--..--..--.\n\t\t	    .' \\  (`._   (_)     _   \\\n\t\t	  .'    |  '._)         (_)  |\n\t\t	  \\ _.')\\      .----..---.   /\n\t\t	  |(_.'  |    /    .-\\-.  \\  |\n\t\t	  \\     0|    |   ( O| O) | o|\n\t\t	   |  _  |  .--.____.'._.-.  |\n\t\t	   \\ (_) | o         -` .-`  |\n\t\t	    |    \\   |`-._ _ _ _ _\\ /\n\t\t	    \\    |   |  `. |_||_|   |\n\t\t	    | o  |    \\_      \\     |     -.   .-.\n\t\t	    |.-.  \\     `--..-'   O |     `.`-' .'\n\t\t	  _.'  .' |     `-.-'      /-.__   ' .-'\n\t\t	.' `-.` '.|='=.='=.='=.='=|._/_ `-'.'\n\t\t	`-._  `.  |________/\\_____|    `-.'\n\t\t	   .'   ).| '=' '='\\/ '=' |\n\t\t	   `._.`  '---------------'\n\t\t	           //___\\   //___\\\n\t\t	             ||       ||\n\t\t	             ||_.-.   ||_.-.\n\t\t	            (_.--__) (_.--__)");
		printf("\n\t\t\t\tSpieler A hat gewonnen!\n");
	}
	if(b==1){
		printf("\n\t\t\t\t        mmmmm,\n\t\t\t            mmMMMMMMMMMMM,\n\t\t\t       .mmMMMMMMMMMMMMMMM|                             .MMMMMm,\n\t\t\t     mMMMMMMMMMMMMMMMMMMM|                           mMMMMMMMMMMm\n\t\t\t    /MMMMMMMMMMMMMMMMMMMM|      ...::::::::::\\..     \\MMMMMMMMMMM\\\n\t\t\t    \\MMMMMMM/´        \\MM/::::::::::::::::::::::::.   `MMMMMMMMMMM\\\n\t\t\t     ´´´´´´         .:::::::::::::::::::::::::::::::,  `MMMMMMMMMMM)\n\n\t\t\t                .:::::::::::::::::::::::::::::::::::::,  mMMMMMMMMMM)\n\t\t\t             .:::::::::::::::::::::::::::::::::::::::::\\,, \\MMMMMMMM/\n\t\t\t           /:::::::::::::::::::::::::::::::::::::::::::::::)MMMMMMM´ \n\t\t\t        ,/:::::::::::::::::::::::::::::::::::::::::::::::::)MMMMM/\n\t\t\t       /::::::::::::::::::::::::::::::::::::::::::::::(MmmMMMMM,´\n\t\t\t      /:::::::::::::´´´´´´´´´´´´´´´,::::::::::::::::(MMMMMM´::::\n\t\t\t     (::::::::::mmmmmmmmMMMMMMMMMmmmmmm´:::::::::::::\\MMMM)::::::\n\t\t\t     :::::::´´´MMMMMM´´´          Mmmmm´          ´`\\:::::::::::::\n\t\t\t     :::´´mMMMMMMM,´               m´                 \\Mmm::::::::\n\t\t\t     ´(:  MMMMMMM/                                     \\MMMMm:::::\n\t\t\t       ´(,mMMMMM/                                       )MMMMMm\\:::\n\t\t\t         (MMMMMM(                                       |MMMMMM^^^\\::\n\t\t\t         mMMMMMM\\                                      /MMMMMMM|^^^^\\\n\t\t\t         MMMMMMM|                                     /mMMMMMMMM^^^^^^\\.\n\t\t\t         (MMMMMM(             .oo,   .o,             ,´MMMMMMMM^^^^^^^^^\\.\n\t\t\t         `MMMMMMM\\           oOOO´   OOOo           ,´MMM´´´´´M^^^^^^^^^^^^\\.\n\t\t\t          \\MMMMMMMm.        oOOO´    OOOO         ,/´´´        `.^^^^^^^^^^^^,\n\t\t\t           \\MMMMMMMMm,      `OO´......OO´        ´     __       )^^^^^^^^^^^^)\n\t\t\t    <mmmmm,´          ´´   .**        **.           ./  /\\,     )^^^^^^^^^^^^,\n\t\t\t     \\´MM/         ___      ****.....*****          `  /  )    /^^^^^^^^^^^^^)\n\t\t\t   `MMMMM       ./ \\  ´      ´**********´             /        /^^^^^^^^^^^^^)\n\t\t\t     `\\MMm      `   \\            ´´´´´              ,´        /´ ^^^^^^^^^^^/\n\t\t\t          \\.         ´.                          cCCCCc,    ,´´       ´´´´´´\n\t\t\t            `.         `-.___             ,ccCCCCCCCCCCCc´´´\n\t\t\t              `\\._           `´´´´´´´´´´´´  ´\\CCCCCCCCCCCC\n\t\t\t                  ´-.__                        CCCCCCCCCCC\n\t\t\t                       ´´´´´´´´´´´\\.          ,´CCCCCCCCCC)\n\t\t\t                                    ´\\.___,-´   CCCCCCCC´´\n\t\t\t                                                  CCCCC´\n");
		printf("\n\t\t\t\t\t\tSpieler B hat gewonnen!\n");
	}
	return 0;
}
