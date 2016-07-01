#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>
float mini_ratio,min_cj_zj,min_ratio[10],max_cj_zj;
float pre_res,key_row,key_element,dv[10],res[10],cb[10];
int slack[10],art[5],k,flag,i,j,key_col,tot_dv,tot_cons,var_num;
char cas[5],sym[10],ch[5],var[10][3],number[5],bv[10][3];
float cons[10][10],zj[10],cj_zj[10],sum,key_rows[10],fixed_element;
void main()
{

flag=0; // for -ve resource purpose
 // graphics driver intialzing
 int driver=DETECT,mode;
 initgraph(&driver,&mode,"f:\\tc\\bgi");
 void erase_screen();
void end();
void display();
void iteration_fun();
void display_final_result();
clrscr();
cleardevice();
 int x,y;
     int col=0;
     for(int i=0;i<200;i++)
     {
      putpixel(random(640),random(480),col);
      col++;
      if(col==15){col=0;}
      }
gotoxy(110,60);
settextstyle(7, HORIZ_DIR, 12);
outtext("SIMPLEX");
moveto(80,160);
settextstyle(7, 0, 12);
outtext("METHOD");
moveto(140,380);
settextstyle(5, 0, 4);
outtext("Developed by : Parminder Singh");
getch();
clrscr();
cleardevice();
  col=0;
     for(i=0;i<200;i++)
     {
      putpixel(random(640),random(480),col);
      col++;
      if(col==15){col=0;}
      }
printf("Enter Case (MAX/MIN)");
fflush(stdin);
gets(cas);
strupr(cas);
printf("\n\nEnter total number of decision variables");
scanf("%d",&tot_dv);
printf("Enter the Coefficient of Objective function (Z =)");
for(j=0;j<tot_dv;j++)
	scanf("%f",&dv[j]);

printf("Enter total number of Constraints");
scanf("%d",&tot_cons);

	for(i=0;i<tot_cons;i++)
	{
		for(j=0;j<tot_dv;j++)
		{
			printf("Enter %d constraint",i+1);
			printf(" (For Skip Enter zero)");
			scanf("%f",&cons[i][j]);
		}
		printf("Enter Symbol ( >,=,< )");
		fflush(stdin);
		scanf("%c",&sym[i]);
		printf("Enter the Resource of %d Constraint",i+1);
		scanf("%f",&res[i]);
		printf("\n\n");
	}
clrscr();
cleardevice();
//For Assigning X
for(i=0;i<tot_dv;i++)
{
	strcpy(var[i],"x");
	itoa(i+1,number,10);
	strcat(var[i],number);
}

//Display L.P Problem

printf("\n\nThe L.P Problem is \n\n");
display();

//If the resource is -ve then multiply whole of the constraint by -1
//And change the Symbol
for(i=0;i<tot_cons;i++)
{
	if(res[i]<0)
	{
		flag=1;
		res[i]*=-1;
		if(sym[i]=='>')
			sym[i]='<';
		else
			sym[i]='>';
		for(j=0;j<tot_dv;j++)
		{
			cons[i][j]*=-1;
		}

	}
}
//if resources were -ve then print again otherwise no need to print again
if(flag==1)
{
//Display L.P Problem
printf("\n\nNow The L.P Problem is \n\n");
display();
}

//Change the < & > to =
k=tot_dv;
var_num=1;
for(i=0;i<tot_cons;i++)
{
	if(sym[i]=='>')
	{
		cons[i][k]=-1;
		dv[k]=0;
		strcpy(var[k],"s");
		itoa(i+1,number,10);
		strcat(var[k],number);

		k++;
		cons[i][k]=1;
		if(strcmp(cas,"MAX")==0)
			cb[i]=dv[k]=-100000;
		else
			cb[i]=dv[k]=100000;
		sym[i]='=';

		strcpy(var[k],"A");
		itoa(var_num,number,10);
		strcat(var[k],number);
		strcpy(bv[i],var[k]);
		var_num++;
	}
	else if(sym[i]=='<')
	{
		cons[i][k]=1;
		cb[i]=dv[k]=0;
		sym[i]='=';
		strcpy(var[k],"s");
		itoa(i+1,number,10);
		strcat(var[k],number);
		strcpy(bv[i],var[k]);
	}
	else
	{
		cons[i][k]=1;
		if(strcmp(cas,"MAX")==0)
			cb[i]=dv[k]=-100000;
		else
			cb[i]=dv[k]=100000;
		strcpy(var[k],"A");
		itoa(var_num,number,10);
		strcat(var[k],number);
		strcpy(bv[i],var[k]);
		var_num++;
	}
	k++;
}

printf("\n\nStandard Form is: \n\n");
printf("%s Z= ",cas);
for(i=0;i<k;i++)
{
	if(i!=0)
		printf("+ %.1f%s ",dv[i],var[i]);
	else
		printf("%.1f%s ",dv[i],var[i]);
}

printf("\n\nSub to :\n");

for(i=0;i<tot_cons;i++)
{
		printf("\n\t");
	for(j=0;j<k;j++)
	{
		if(cons[i][j]!=0)
		{
			if(j!=0)
				printf("+ %.1f%s ",cons[i][j],var[j]);
			else
				printf("%.1f%s ",cons[i][j],var[j]);
		}

	}
	printf("%c",sym[i]);
	printf(" %.1f",res[i]);

}
//Display Non-Negativity Resrtiction
printf("\n");
for(j=0;j<k;j++)
{
	printf("%s ",var[j]);
}
printf("> 0");

printf("\n\n\nPress any key to continue...");
getch();
clrscr();
cleardevice();
label:

printf("\n\n\n");
printf("\n----------------------------------------------------------------------------\n");
printf("\t\tCj\t");
for(i=0;i<k;i++)
	printf("%.1f\t",dv[i]);
//printf("\n----------------------------------------------------------------------------\n");

printf("\nCb\tBv\tSv");
for(i=0;i<k;i++)
printf("\t%s ",var[i]);

printf("\n----------------------------------------------------------------------------\n");
for(i=0;i<tot_cons;i++)
{
	printf("%.1f\t",cb[i]);
	printf("%s\t",bv[i]);
	printf("%.1f\t",res[i]);
	for(j=0;j<k;j++)
	{
		printf("%.1f\t",cons[i][j]);
	}

	printf("\n");
}

//print & Calculate the value of Zj & Zj - Cj
printf("\n----------------------------------------------------------------------------\n");
printf("    Zj = \t\t");

for(j=0;j<k;j++)
{
	sum=0;
	for(i=0;i<tot_cons;i++)
	{
		sum=sum+(cb[i]*cons[i][j]);
	}
	zj[j]=sum;
	printf("%.1f\t",zj[j]);
	cj_zj[j]=dv[j]-zj[j];
}

printf("\n----------------------------------------------------------------------------\n");
printf(" Cj - Zj = \t\t");

key_col=0;
if(strcmp(cas,"MAX")==0)
{
	max_cj_zj=cj_zj[0];
	for(i=0;i<k;i++)
	{
		printf("%.1f\t",cj_zj[i]);
		if(max_cj_zj<=cj_zj[i+1])
		{
			max_cj_zj=cj_zj[i+1];
			key_col=i+1;
		}
	}
	if(max_cj_zj>0)
	{
		iteration_fun();
		goto label;
	}
	else
	{
	   display_final_result();
	}
}
else
{
	min_cj_zj=cj_zj[0];
	for(i=0;i<k;i++)
	{
		printf("%.1f\t",cj_zj[i]);
		if(min_cj_zj>=cj_zj[i+1])
		{
			min_cj_zj=cj_zj[i+1];
			key_col=i+1;
		}
	}
	if(min_cj_zj<0)
	{
		iteration_fun();
		goto label;
	}
	else
	{
		display_final_result();
	}
}
clrscr();
end();
erase_screen();
//getch();
}
void display_final_result()
{
	printf("\n\nSolution is over");
	printf("\nPress any key to see the final Result\n");
	getch();
	printf("\n\t\t----------------------------\n");
	printf("\n\t\tCb\tBv\tSv\n");
	printf("\n\t\t----------------------------\n\t\t");
	for(i=0;i<tot_cons;i++)
	{
		printf("%.1f\t",cb[i]);
		printf("%s\t",bv[i]);
		printf("%.1f\t",res[i]);
		printf("\n\t\t");
	}
	printf("\n\t\t----------------------------\n");
//Calculate & print the value of Zj
	printf("\t\t    Z = \t");
	sum=0;
	for(i=0;i<tot_cons;i++)
		sum+=(cb[i]*res[i]);
	printf("%.1f\t",sum);
	getch();
}



void display()
{
printf("%s Z= ",cas);
for(i=0;i<tot_dv;i++)
{
	if(i!=0)
	printf("+ %.1f%s ",dv[i],var[i]);
	else
	printf("%.1f%s ",dv[i],var[i]);
}
printf("\n\nSub to :\n");
for(i=0;i<tot_cons;i++)
{
		printf("\n\t");
	for(j=0;j<tot_dv;j++)
	{
		if(cons[i][j]!=0)
		{
			if(j!=0)     // For Printing +
			printf("+ %.1f%s ",cons[i][j],var[j]);
			else
			printf("%.1f%s ",cons[i][j],var[j]);
		}

	}
	printf("%c",sym[i]);
	printf(" %.1f",res[i]);

}
printf("\n");

//Display Non-Negativity Resrtiction
for(j=0;j<tot_dv;j++)
{
	printf("%s ",var[j]);
}
printf("> 0");
}


void iteration_fun()
{
	printf("\n\nSolution is not optimise. We have to optimise");
	printf("\nPress any key to continue");
	getch();

//For Minimum Ratio & Key Row
	mini_ratio = 40000; //assumed minimum ratio
	printf("\n\n-------------------");
	printf("\n\nMinimum Ratio");
	printf("\n\n-------------------\n");
	for(i=0;i<tot_cons;i++)
	{
		if(cons[i][key_col]<=0)
		{
			min_ratio[i]=40000;
			printf("\nCan't Divide by 0 or -ve So assume ratio is ");
		}
		else
		{
			min_ratio[i]=res[i]/cons[i][key_col];
		}
		printf("%.1f\n",min_ratio[i]);
		if(mini_ratio>min_ratio[i])
		{
			mini_ratio=min_ratio[i];
			key_row=i;
		 }
	}


//Display Key Column, Key Row & Key Element
	printf("\n\n-------------------\n\n");
	printf("Key Column is %s",var[key_col]);
	printf("\nKey Row is %s",bv[key_row]);
	key_element=cons[key_row][key_col];
	printf("\nKey Element is %.1f",key_element);

	printf("\nEntering Variable is %s",var[key_col]);
	printf("\nDeparting Variable is %s",bv[key_row]);
	strcpy(bv[key_row],var[key_col]);

//Store the key row element in key_rows array
	pre_res=res[key_row]; //for resources
	for(i=0;i<k;i++)
		key_rows[i]=cons[key_row][i];

//Change Key Row & Generate new rows
	cb[key_row]=dv[key_col]; //Entering variable
	res[key_row]/=key_element;
	for(i=0;i<k;i++)
	{
		if(cons[key_row][i]!=0)
		cons[key_row][i]/=key_element;
	}

	for(i=0;i<tot_cons;i++)
	{

		if(i!=key_row)
		{

			fixed_element=cons[i][key_col]/key_element;
			res[i]-=(pre_res * fixed_element);
			for(j=0;j<k;j++)
			{
				cons[i][j]=cons[i][j]-(key_rows[j]*fixed_element);
			}
		}
	}
printf("\n\nPress any key to continue...");
getch();
}

void end()
   {
     cleardevice();
     int x,y;
     int col=0;
     for(int i=0;i<200;i++)
     {
      putpixel(random(640),random(480),col);
      col++;
      if(col==15){col=0;}
      }
      printf("\n\n\n\n Programmer : Parminder Singh MCA IV Sem");
      printf("\n\nMail in Your Suggestions And Queries At :");
      printf("\n  < inder_923 @ yahoo.co.uk > ");
      printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n ^ Press Any Key To Exit ^" );
      getch();
   }
void erase_screen()
{
 int x1=0,y1=0,x2=639,y2=479;
 setcolor(0);
  for(;x1<x2;)
  {
  delay(10);
  rectangle(x1,y1,x2,y2);
  x1++;y1++;x2--;y2--;
  }
  cleardevice();
}
