// ConsoleApplication1.cpp : main project file.

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <clocale>
#include <windows.h>

using namespace std;
using namespace System;
using namespace System::IO;

#define ENTER 13
#define ESC 27
#define UP 72
#define DOWN 80
#define HOME 71
#define END 79

int menu(int);
void maxim(struct z*);
void vkurs(struct z*);
void kolvo(struct z*);
void alfalist(struct z*);
void vstavka(struct z*, char*);
void kl(struct z*);
void diagram(struct z*);

char dan[7][70]={
"Какой из студентов имеет наивысший балл?                             ",
"Какие из студентов учатся на определенном курсе?                     ",
"Сколько студентов учатся в определенном институте?                   ",
"Алфавитный список всех студентов                                     ",
"Есть ли студенты из разных институтов, у которых одинаковый балл?    ",
"Диаграмма. Процентное соотношение студентов и их посещаемости        ",
"Выход                                                                "
};
char BlankLine[ ]="                                                                       ";
int NC;
struct z {
  char name[20];
  int kurs;
  int year;
  char inst[10];
  int ball;
  int propusk;
  char city[13];
};
struct sp{ 
 char name[20];
 int ball;
 struct sp* sled;
 struct sp* pred;
} *spisok;

int main(array<System::String ^> ^args)
{
 int i,n;
 FILE *in;
 struct z *students;
 setlocale(LC_CTYPE,"Russian");
 Console::CursorVisible::set(false);
 Console::BufferHeight=Console::WindowHeight;
 Console::BufferWidth=Console::WindowWidth;
 if((in=fopen("Spisok.txt","r"))==NULL)
{
printf("\nФайл Spisok.txt не открыт !");
getch(); exit(1);
}
  fscanf(in, "%d", &NC);
  students = (struct z*)malloc(NC*sizeof(struct z));
  for(i=0;i<NC;i++)
   {
    fscanf(in ,"%s%d%d%s%d%d%s", students[i].name, &students[i].kurs, &students[i].year, students[i].inst, 
      &students[i].ball, &students[i].propusk, students[i].city);
  }
  printf("\t\t %-15s %-6s %-5s %-10s %-6s %-10s %-7s \n", "ФИО", "Курс", "Год", "Институт", "Баллы", "Пропуски", "Город");
  printf("\t\t|----------------------------------------------------------------------|");
  for(i=0;i<NC;i++)
  {
    printf("\n\t\t|%-15s %-5d %-8d %-10s %-8d %-6d %-12s|", students[i].name, students[i].kurs, students[i].year, students[i].inst, 
      students[i].ball, students[i].propusk, students[i].city);
  }
  getch();
 
  while(1)
  {
  Console::ForegroundColor=ConsoleColor::Gray;
  Console::BackgroundColor=ConsoleColor::Cyan;
  Console::Clear();
  Console::ForegroundColor=ConsoleColor::Magenta;
  Console::BackgroundColor=ConsoleColor::Gray;
  Console::CursorLeft=10;
  Console::CursorTop=4;
  printf(BlankLine);
  for(i=0;i<7;i++)
  {
  Console::CursorLeft=10;
  Console::CursorTop=i+5;
  printf(" %s ",dan[i]);
  }
  Console::CursorLeft=10;
  Console::CursorTop=12;
  printf(BlankLine);
  n = menu(7);
  switch(n) {
    case 1: maxim(students);break;
    case 2: vkurs(students);break;
    case 3: kolvo(students);break;
    case 4: alfalist(students);break;
    case 5: kl(students);break;
    case 6: diagram(students);break;
    case 7: exit(0);
    }
  }
  return 0;
  
}
int menu(int n)
{
int y1=0,y2=n-1;
char c=1;
while (c!=ESC)
{
  switch(c) {
   case DOWN: y2=y1; y1++; break;
   case UP: y2=y1; y1--; break; 
   case ENTER: return y1+1;
   case HOME: y2 = y1; y1 = 0; break;
   case END: y2 = y1; y1 = n - 1; break;

   }
  if(y1>n-1){y2=n-1;y1=0;}
  if(y1<0) {y2=0;y1=n-1;}
  Console::ForegroundColor=ConsoleColor::Black;
  Console::BackgroundColor=ConsoleColor::White;
  Console::CursorLeft=11;
  Console::CursorTop=y1+5;
  printf("%s",dan[y1]);
  Console::ForegroundColor=ConsoleColor::Magenta;
  Console::BackgroundColor=ConsoleColor::Gray;
  Console::CursorLeft=11;
  Console::CursorTop=y2+5;
  printf("%s",dan[y2]);
  c=getch();
  } 
exit(0);
}
void maxim(struct z* students) 
{ 
int i=0; struct z best; 
strcpy(best.name,students[0].name); 
best.ball=students[0].ball; 
for(i=1;i<NC;i++) 
if (students[i].ball>best.ball) 
{ 
strcpy(best.name,students[i].name); 
best.ball=students[i].ball; 
}
Console::ForegroundColor=ConsoleColor::Black; 
Console::BackgroundColor=ConsoleColor::White; 
Console::CursorLeft=10; 
Console::CursorTop=15; 
printf("Максимальное количество баллов %d ",best.ball); 
printf("имеет студент %s",best.name); 
getch(); 
}
void vkurs(struct z* students)
{
	int i,b;
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::White;
	Console::CursorLeft=10;
	Console::CursorTop=15;
	Console::CursorVisible::set(true);
	printf("Введите курс:");
	Console::CursorLeft=10;
	Console::CursorTop=16;
	scanf("%d",&b);
	Console::CursorLeft=10;
	Console::CursorTop=17;
	for(i=1;i<NC;i++){
		if (students[i].kurs==b){
			Console::CursorLeft=10;
			printf("%-20s",students[i].name);
			Console::CursorTop+=1;
			Console::CursorVisible::set(false);
		}
	}
	getch();
}
void kolvo(struct z* students)
{
	int i,k=0;
	char s[80];
	Console::BackgroundColor=ConsoleColor::White;
	Console::ForegroundColor=ConsoleColor::Black;
	Console::CursorLeft=10;
	Console::CursorTop=15;
	Console::CursorVisible::set(true);
	printf("Введите институт:");
	Console::CursorLeft=10;
	Console::CursorTop=16;
	SetConsoleCP(1251);
	gets(s);
	SetConsoleCP(866);
	for(i=0;i<NC;i++){
		if (strcmp(students[i].inst, s)==0){
			k=k+1;
		}
	}
	Console::CursorLeft=10;
	Console::CursorTop=17;
	printf("Количество людей, учащихся в институте: %d \n", k);
getch();
}

void kl(struct z *students)
{
int i,x,n=0;
for(i=0;i<NC;i++){
	for(x=1;x<NC;x++){
		if ((students[i].ball==students[x].ball) && (strcmp(students[i].inst,students[x].inst)!=0)){
			Console::BackgroundColor=ConsoleColor::White;
			Console::ForegroundColor=ConsoleColor::Black;
			Console::CursorLeft=10;
			Console::CursorTop=15;
			printf("Студенты %s и %s имеют одинаковый балл: %ld ",students[i].name,students[x].name,students[x].ball);
			Console::CursorLeft=10;
			Console::CursorTop=16;
			printf("и разные институты: %s и %s",students[i].inst,students[x].inst);
			n=1;
			break;
		}
	}
	if(n==1)
		break;
}
if(n!=1){
	Console::BackgroundColor=ConsoleColor::Blue;
	Console::ForegroundColor=ConsoleColor::Gray;
	Console::CursorLeft=10;
	Console::CursorTop=15;
	printf("Совпадений нет!");
}
getch();
}


void alfalist(struct z* students)
{
 int i,x;
 struct sp* nt,*z;
 x = 3;
 Console::ForegroundColor = ConsoleColor::Black;
 Console::BackgroundColor = ConsoleColor::Cyan;
 Console::Clear();
 printf("\n Алфавитный список студентов");
 printf("\n******************************************************************\n");
 if (!spisok)
 for (i = 0; i < NC; i++)
 vstavka(students, students[i].name);
 for (nt = spisok; nt != 0; nt = nt->sled)
 {
 Console::CursorLeft = 0;
 Console::CursorTop = x + 1;
 printf(" %-20s %ld", nt->name, nt->ball);
 x += 1;
 }
 x = 3;
 Console::CursorLeft = 40;
 Console::CursorTop = 1;
 printf("Обратный алфавитный список");
 for (nt = spisok; nt != 0; z = nt, nt = nt->sled);
 for (nt = z, i = 0; nt != 0; i++, nt = nt->pred)
 {
 Console::CursorLeft = 40;
 Console::CursorTop = x + 1;
 printf(" %-20s %ld", nt->name, nt->ball);
 x += 1;
 }
 getch();
}

void vstavka(struct z* students, char* name)
{
 int i;
 struct sp* nov, * nt, * z = 0;
 for (nt = spisok; nt != 0 && strcmp(nt->name, name) < 0; z = nt, nt = nt->sled);
 if (nt && strcmp(nt->name, name) == 0) return;
 nov = (struct sp*)malloc(sizeof(struct sp));
 strcpy(nov->name, name);
 nov->sled = nt;
 nov->pred = z;
 nov->ball = 0;
 for (i = 0; i < NC; i++)
 if (strcmp(students[i].name, name) == 0)
 nov->ball += students[i].ball;
 if (!z) spisok = nov;
 if (z) z->sled = nov;
 if (nt) nt->pred = nov;
 return;
}


void diagram(struct z* students)
{
 struct sp *nt;
 int len, i, NColor;
 long bal = 0;
 char str1[20];
 char str2[20];
 System::ConsoleColor Color;
 Console::ForegroundColor = ConsoleColor::Black;
 Console::BackgroundColor = ConsoleColor::White;
 Console::Clear();
 for (i = 0; i < NC; i++)
 bal = bal + students[i].ball;
 if (!spisok)
 for (i = 0; i < NC; i++)
 vstavka(students, students[i].name);
 Color=ConsoleColor::Black;
 NColor = 0;
 for (nt = spisok, i = 0; nt != 0; nt = nt->sled, i++)
 {
 sprintf(str1,"%s", nt->name);
 sprintf(str2, "%3.1f%%", (nt->ball * 100./ bal));
 Console::ForegroundColor = ConsoleColor::Black;
 Console::BackgroundColor = ConsoleColor::White;
 Console::CursorLeft = 5;
 Console::CursorTop = i + 1;
 printf(str1);
 Console::CursorLeft = 20;
 printf("%s", str2);
 Console::BackgroundColor = ++Color; NColor++;
 Console::CursorLeft = 30;
 for (len = 0; len < nt->ball * 100 / bal; len++) printf(" ");
 if (NColor == 14)
 {
 Color = ConsoleColor::Black;
 NColor = 0;
 }
 }
 getch();
 return;
 }







