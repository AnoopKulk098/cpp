#include<iostream.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
      void pos(int);
      void con(int);
      void arith(char,int,int);
      void bracket();
      int ntod(int);
      void nton(int,int);
      void dton(int);

      char ex[30];
      int loc[30];
      float c[30];
      char d[30];
      int e,num ;

 void main( )
 {
 clrscr();
 cout<<"welcome to our calculator,press enter to continue";
  int n;
  cout<<"\nenter option no.";
  cout<<"\n1.arithematic calculator"<<"\n"<<"2.different base to decimal convertor"<<"\n"<<"3.decimal to different base"<<"\n4.nth to nth base converter";
 int x;
 cin>>x;
 switch(x)
{ case 1:
 {cout<<"please enter your expression : ";
 cin>>ex;
   pos(strlen(ex));
   con(num);
   bracket();
   arith('^',0,num);
   cout<<c[0];
   }break;

   case 2:
   {int n,dec1;
   cout<<"enter the base:";
   cin>>n;
   dec1=ntod(n);
   cout<<"the no. in decimal is:"<<dec1;
   }break;

   case 3:
   {
   int m;
   cout<<"enter the base to convert to:";
   cin>>m;
   dton(m);
   }break;

   case 4:
   {int n,n1;int dec;
   cout<<"enter the base you are converting from:";
   cin>>n;
   cout<<"enter the base you are converting to :";
   cin>>n1;
   dec=ntod(n);
   nton(dec,n1);
   }
   }
  getch();
  }


  void pos(int n )
  {loc[0]=-1;
   for(int k=1 ,i=0;i<=n;i++)
   {if( ex[i]=='/'||ex[i]=='*'||ex[i]=='+'||ex[i]=='-'||ex[i]=='='||ex[i]=='('||ex[i]==')'||ex[i]=='s'||ex[i]=='i'||ex[i]=='n'||ex[i]=='c'||ex[i]=='o'||ex[i]=='t'||ex[i]=='a'||ex[i]=='e'||ex[i]=='l'||ex[i]=='m'||ex[i]=='g'||ex[i]=='d'||ex[i]=='^')
    { loc[k]=i;
       k++ ;
       num=k ;
    }

 }
 }
 void con(int n)
  {
      for(int x=1;x<n;x++)
      { c[x-1]=0;
	if(loc[x-1]!=loc[x]-1)
	  {
	    for (int p=loc[x-1]+1,k=0;p<loc[x];k++,p++)
	      {
		d[k]=ex[p];
		e =  loc[x]-loc[x-1]-2;
	       c[x-1]=c[x-1]+(d[k]-48)*pow(10,e-k);
	       if(ex[loc[x-1]]=='-')
	       {
	       c[x-1]=-c[x-1];
	       ex[loc[x-1]]='+';
	       }
	      }

	  }
      }

  }




 void arith( char x ,int s, int l)
  {int k,j;
  int y=l;
     switch(x)
	{ case '^':
	  {
	   for(int i=s;i<y;i++)
	    { k=i,j=i-1;
	      if(ex[loc[i]]=='^')
	      {
		   lb9: if(c[k]=='\0'&& k<num-1)
		      { k++;
			goto lb9;
		      }
		   lb10:if(c[j]=='\0'&&j>=s)
		      {j--;
			goto lb10;
		      }
		  c[j]=pow(c[j],c[k]);
		  c[k]='\0';
		  loc[i]='\0';

	      }
	    }
	  }
	  case '/':
	  { for(int i=s;i<y;i++)
	    { k=i,j=i-1;
	      if(ex[loc[i]]=='/')
	      {
		   lb1: if(c[k]=='\0'&& k<num-1)
		      { k++;
			goto lb1;
		      }
		   lb2:if(c[j]=='\0'&&j>=s)
		      {j--;
			goto lb2;
		      }
		  c[j]=c[j]/c[k];
		  c[k]='\0';
		  loc[i]='\0';

	      }
	    }
	  }
	  case '*':
	  { for(int i=s;i<y;i++)
	    { k=i,j=i-1;
	      if(ex[loc[i]]=='*')
	      {
		   lb3: if(c[k]=='\0'&& k<num-1)
		      { k++;
			goto lb3;
		      }
		   lb4:if(c[j]=='\0'&&j>=s)
		      {j--;
			goto lb4;
		      }
		  c[j]=c[j]*c[k];
		  c[k]='\0';
		  loc[i]='\0';

	      }
	    }
	  }
	  case '+':
	  { for(int i=s;i<y;i++)
	    { k=i,j=i-1;
	      if(ex[loc[i]]=='+')
	      {
		   lb5: if(c[k]=='\0'&& k<num-1)
		      { k++;
			goto lb5;
		      }
		   lb6:if(c[j]=='\0'&&j>=s)
		      {j--;
			goto lb6;
		      }
		  c[j]=c[j]+c[k];
		  c[k]='\0';
		  loc[i]='\0';

	      }
	    }
	  }
	  case '-':

	  { for(int i=s;i<y;i++)
	    { k=i,j=i-1;
	      if(ex[loc[i]]=='-')
	      {
		   lb7: if(c[k]=='\0'&& k<num-1)
		      { k++;
			goto lb7;
		      }
		   lb8:if(c[j]=='\0'&&j>=s)
		      {j--;
			goto lb8;
		      }
		  c[j]=c[j]-c[k];
		  c[k]='\0';
		  loc[i]='\0';

	      }
	    }

	  }

	}

  }




 void bracket()
  {int x=0,y=0,count=0,max=0,l=0;
   for(int i=0;i<=num;i++)
     {if(ex[loc[i]]=='(')
       {x++;
       }
     }
   for(int j=0;j<x;j++)
     {for(i=0;i<=num;i++)
      {
       if(ex[loc[i]]=='(')
	 {count++;}
       if(max<count)
	 {max=count;
	  x=i;
	 }
       if(ex[loc[i]]==')')
	 {
	  count--;
	  if(max==count+1&&l==0)
	     { y=i;
	     l++;}
	 }
       }
      }
  arith('^',loc[x],loc[y]);
  ex[loc[x]]='\0';
  ex[loc[y]]='\0';
  }



void dton(int n)
{
int d,j=0;
cout<<"enter the no. in decimal";
cin>>d;
char no[30];
for(int i=0;d!=0;i++)
{
if(d%n>9)
{
no[i]=d%n+55;
}
else
{
no[i]=d%n+48;
}
d=d/n;
j++;
}
cout<<"\nThe no. in base "<<n<<" is ";
for(i=j-1;i>=0;i--)
{
cout<<no[i];
}

}


int ntod(int n)
{  char no[30];
  int d=0;
  cout<<"enter the no. in base:";
  cin>>no;
  for(int i=0;i<strlen(no);i++)
   { if(no[i]>=65)
      {no[i]=no[i]-55;}
      else
      no[i]=(no[i]-48);
     d=d+no[i]*pow(n,strlen(no)-i-1);
   }

    return d;


}
void nton(int d,int n)
{
int j=0;
cout<<"enter the no. in decimal";
char no[30];
for(int i=0;d!=0;i++)
{
if(d%n>9)
{
no[i]=d%n+55;
}
else
{
no[i]=d%n+48;
}
d=d/n;
j++;
}
cout<<"\nThe no. in base "<<n<<" is ";
for(i=j-1;i>=0;i--)
{
cout<<no[i];
}
}