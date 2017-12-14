#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<string.h>
#include<process.h>
#include<ctype.h>
class book
{
int id;
char author[20];
char publication[20];
int status,issue;
public:
char name[50];
book()
{
status=0;
issue=-1;
}
void input()
{
 cout<<"Enter ID:";cin>>id;
 cout<<"Enter Book name:";gets(name);
 cout<<"Enter Author name:";gets(author);
 cout<<"Enter Publication:";gets(publication);
}
void display()
{
 cout<<"\nBook ID:"<<id;
 cout<<"\nName:";puts(name);
 cout<<"Author:";puts(author);
 cout<<"Publication:";puts(publication);
if(status==0)
 cout<<"Availiable\n";
else
 cout<<"Not available\n";
}
void statuschange(int mid)
{
 issue=mid;
if(status==0)
 status=1;
else
 status=0;
}
int getid()
{return id;}
int getissue()
{return issue;}
int getstatus()
{return status;}
};

struct history
{
 int x;
 history* next;
};
struct date
{int dd,mm,yy;};

class member
{
int id,issue;
date dob,dor,dov;
int flag;
public:
history *start;
member()
{
 dob.dd=dob.mm=dob.yy=0;
 dor.dd=dor.mm=dor.yy=0;
 dov.dd=dov.mm=dov.yy=0;
 issue=-1;
 start=NULL;
 flag=0;
}
void push(int p)
{
 history* h;
 h=new history;
 h->x=p;
 h->next=NULL;
 if(start==NULL)
 {
 start=h;
 }
 else
 {
 history* temp;
 temp=start;
 start=h;
 start->next=temp;
 }
}
char name[50];
void input()
{
 cout<<"Enter Member ID:";cin>>id;
 cout<<"\nEnter the name of member:";gets(name);
}
void bookhist(history* np);
void viewadd();
void display()
{ cout<<"\nID:"<<id;
  cout<<"\nName:";puts(name);
}
void valid()
{
 cout<<"Enter Date of validity:";cin>>dov.dd;
 cout<<"Enter Month of validity";cin>>dov.mm;
 cout<<"Enter Year of validity";cin>>dov.yy;
}
void add_date()
{
 if(flag==0)
 {
  cout<<"Enter Date of birth:";cin>>dob.dd;
  cout<<"Enter Month of birth";cin>>dob.mm;
  cout<<"Enter Year of birth";cin>>dob.yy;
  cout<<"Enter Date of registration:";cin>>dor.dd;
  cout<<"Enter Month of registration";cin>>dor.mm;
  cout<<"Enter Year of registration"; cin>>dor.yy;
  flag=1;
  valid();
 }
else
 cout<<"Cannot edit!";
}
int getissue()
{return issue;}
int getid()
{return id;}
void modifyissue(int a)
{issue=a;}
};

void member::viewadd()
{
 cout<<"\nID:"<<id;
 cout<<"\nName:";puts(name);
 cout<<"\nBook History:";
 bookhist(start);
 cout<<"\nCurrent book:" ;
 fstream f("book.dat",ios::in|ios::binary);
 int c=0;
 book k;
 f.read((char*)&k,sizeof(k));
 while(f)
 {if(issue==k.getid())
  { puts(k.name);
    c=1;
  }
 f.read((char*)&k,sizeof(k));
 }
if(c==0)
 cout<<"None" ;
if((dob.dd==0)&&(dob.mm==0)&&(dob.yy==0))
 cout<<"\nDate of Birth:Not Specified";
else
 cout<<"\nDate of Birth:"<<dob.dd<<"/"<<dob.mm <<"/"<<dob.yy;
if((dor.dd==0)&&(dor.mm==0)&&(dor.yy==0))
 cout<<"\nDate of Registration:Not Specified";
else
 cout<<"\nDate of Registration:"<<dor.dd<<"/"<<dor.mm <<"/"<<dor.yy;
if((dov.dd==0)&&(dov.mm==0)&&(dov.yy==0))
 cout<<"\nValid Upto:Not Specified";
else
 cout<<"\nValid Upto:"<<dov.dd<<"/"<<dov.mm <<"/"<<dov.yy;
}
void member::bookhist(history *np)
{
if(np==NULL)
 {cout<<"---";
  return;}
else
 while(np!=NULL)
 {
 fstream f("book.dat",ios::in|ios::binary);
 book b;
 f.read((char*)&b,sizeof(b));
 while(f)
  {
  if(b.getid()==np->x)
   {
   cout<<"\nID:"<<np->x<<"\nName:";
   puts(b.name);
   }
  f.read((char*)&b,sizeof(b));
  }
 np=np->next;
 }
}
void add()
{
 clrscr();
 fstream f("member.dat",ios::binary|ios::app);
 member x;
 x.input();
 member p;
 fstream z("member.dat",ios::binary|ios::in);
 z.read((char*)&p,sizeof(member));
 while(z)
 {
  if(x.getid()==p.getid())
  {
   cout<<"This ID already exists..Re-enter the information!";
   getch();
   z.close();
   f.close();
   add();
  }
  z.read((char*)&p,sizeof(member));
 }
 f.write((char*)&x,sizeof(member));
}
void viewmem(int x)
{
 fstream f("member.dat",ios::in|ios::binary);
 member l;
 int found=0;
 f.read((char*)&l,sizeof(l));
 while(f)
 {
  if(x==l.getid())
  {
   l.viewadd();
   found=1;
  }
  f.read((char*)&l,sizeof(l));
 }
 if(found==0)
 cout<<"Not Found!";
}
void edit(int x)
{
 fstream f("member.dat",ios::in|ios::out|ios::binary);
 fstream g("temp.dat",ios::in|ios::out|ios::binary);
 member l;
 f.read((char*)&l,sizeof(l));
 while(f)
 {
  if(x==l.getid())
  l.add_date();
 g.write((char*)&l,sizeof(l));
 f.read((char*)&l,sizeof(l));
 }
 g.close();
 f.close();
 remove("member.dat");
 rename("temp.dat","member.dat");
}
void view()
{
 clrscr();
 fstream f("member.dat",ios::in|ios::binary);
 if(!f)
 {cout<<"There are no members on this library.";
  cout<<"\Press any key to return";
  getch();
  return;}
 cout<<"Displaying the information:";
 member x;
 f.read((char*)&x,sizeof(x));
 while(!f.eof())
 {
  x.display();
  f.read((char*)&x,sizeof(member));
 }
 f.close();
 cout<<"\n1.View details of a specific member";
 cout<<"\n2.Add additional details of a member";
 cout<<"\n3.Extend validity of a member";
 cout<<"\n4.Back";
 int choice;
 cin>>choice;
 switch(choice)
 {
  case 1:
  {
   clrscr();
   cout<<"\nEnter ID of member:";
   int mid;
   cin>>mid;
   viewmem(mid);
   break;
  }
  case 2:
  {clrscr();
   cout<<"Enter ID of member:";
   int mid;
   cin>>mid;
   edit(mid);
   break;
  }
  case 3:
  {
  int x;
  cout<<"Enter the ID of member:";
  cin>>x;
  clrscr();
  fstream f("member.dat",ios::in|ios::out|ios::binary);
  fstream g("temp.dat",ios::in|ios::out|ios::binary);
  member l;
  f.read((char*)&l,sizeof(l));
  while(f)
   {
    if(x==l.getid())
    l.valid();
    g.write((char*)&l,sizeof(l));
    f.read((char*)&l,sizeof(l));
   }
  g.close();
  f.close();
  remove("member.dat");
  rename("temp.dat","member.dat");
 }
 case 4:
 {
 return;
 }
 }
}
void addbook()
{
 clrscr();
 fstream f("book.dat",ios::app|ios::binary);
 book x,p;
 fstream z("book.dat",ios::in|ios::binary);
 x.input();
 z.read((char*)&p,sizeof(book));
 while(z)
 {
  if(x.getid()==p.getid())
  {
   cout<<"This ID already exists..Re-enter the information!";
   getch();
   z.close();
   f.close();
   addbook();
  }
  z.read((char*)&p,sizeof(book));
 }
 f.write((char*)&x,sizeof(book));
 f.close();
}
void viewbook()
{clrscr();
 fstream f("book.dat",ios::in|ios::binary);
 if(!f)
 {cout<<"There are no books in this library";
  cout<<"\nPress any key to return";
  getch();
  return;
 }
 book x;
 f.read((char*)&x,sizeof(book));
 while(!f.eof())
 {
 x.display();
 f.read((char*)&x,sizeof(book));
 }
}
int charmatch(char a,char b)
{
 if(isupper(a))
 {
  if(a==toupper(b))
  return 2;
  else if(a==b)
  return 2;
  else
  return 0;
 }
 else if(islower(a))
 {
  if(a==tolower(b))
  return 2;
  else if(a==b)
  return 2;
  else
  return 0;
 }
 else if(a==b)
 return 2;
 else
 return 0;
}
void search()
{
 start:
 char sname[50];
 cout<<"\nEnter the name or part of the name of the book:";
 gets(sname);
 book x;
 fstream f("book.dat",ios::in|ios::binary);
 f.read((char*)&x,sizeof(book));
 while(f)
 {
  int c=strlen(x.name);
  int d=strlen(sname);
  int count=0;
  for(int i=0;i<c;i++)
  {if(charmatch(sname[0],x.name[i])==2)
   {
    count=0;
    for(int j=0;j<d;j++)
    {if(charmatch(sname[j],x.name[j+i])==2)
     count++;
    }
    if(count==d)
    {cout<<"\n";
     x.display();
    }
   }
  }
  f.read((char*)&x,sizeof(book));
 }
}
void modify(int bid,int mid)
{
 fstream bk("book.dat",ios::in|ios::out|ios::binary);
 fstream mem("member.dat",ios::out|ios::in|ios::binary);
 book b;
 member m;
 long pos;
 while(!bk.eof())
 {
  pos=bk.tellg();
  bk.read((char*)&b,sizeof(b));
  if(b.getid()==bid)
  {
   b.statuschange(mid);
   bk.seekg(pos);
   bk.write((char*)&b,sizeof(b));
  }
 }
 bk.close();
 while(!mem.eof())
 {
  pos=mem.tellg();
  mem.read((char*)&m,sizeof(m));
  if(m.getid()==mid)
  {
   m.modifyissue(bid);
   mem.seekg(pos);
   mem.write((char*)&m,sizeof(m));
  }
 }
 mem.close();
}
void btake()
{
 clrscr();
 fstream b("book.dat",ios::in|ios::binary);
 book x;
 member y;
 int count=0;
 b.read((char*)&x,sizeof(x));
 while(!b.eof())
 {
 fstream m("member.dat",ios::in|ios::binary);
 if(x.getstatus()!=0)
  {
  count++;
  cout<<"Book:";
  puts(x.name);
  m.seekg(0);
  m.read((char*)&y,sizeof(y));
  while(!m.eof())
  {
  if(y.getissue()==x.getid())
   {cout<<"Member:";
    puts(y.name);
    cout<<"\n"; }
    m.read((char*)&y,sizeof(y));
   }
   m.close();
  }
  b.read((char*)&x,sizeof(x));
 }
 b.close();
 if(!count)
 cout<<"No books are issued currently";
}
void issue()
{
   int num=0;
   int the=0;
   int bid,mid;
   book k;
   member m;
   cout<<"\nEnter the ID of book you want to issue:";
   cin>>bid;
   fstream f("book.dat",ios::in|ios::out|ios::binary);
   fstream mem("member.dat",ios::in|ios::out|ios::binary);
   while(!f.eof())
   {
    f.read((char*)&k,sizeof(book));
    if(bid==k.getid()&&k.getstatus()==0&&num==0)
    {
     num=1;
     cout<<"\nBOOK AVAILABLE";
     cout<<"\nEnter the ID of member who wants to issue it:";
     cin>>mid;
     mem.read((char*)&m,sizeof(member));
     while(!mem.eof())
     {
      if(m.getid()==mid&&m.getissue()==-1)
      {
       the=1;
       goto lb;
      }
      mem.read((char*)&m,sizeof(member));
     }
    }
   }
   f.close();mem.close();
   if(the==1)
   lb:modify(bid,mid);
   if(the!=1)
   cout<<"Not allowed!";
}
void lend()
{
 clrscr();
 cout<<"\n1.Search a Book before issuing\n2.Issue a Book" ;
 int choice;
 cin>>choice;
 switch(choice)
 {
  case 1:
  {
  clrscr();
  search();
  issue();
  break;
  }
  case 2:
  {
  clrscr();
  issue();
  }
 }
}
void returnbook()
{clrscr();
 int mid;
 cout<<"Enter the Member";
 cin>>mid;
 book k;
 member m;
 int p=0;
 fstream f("book.dat",ios::in|ios::out|ios::binary);
 fstream g("member.dat",ios::in|ios::out|ios::binary);
 fstream temp("temp.dat",ios::in|ios::out|ios::binary);
 fstream temp1("temp1.dat",ios::in|ios::out|ios::binary);
 f.read((char*)&k,sizeof(book));
 while(!f.eof())
 {
  if(k.getissue()==mid)
  {cout<<"The member has the following book:";
   k.display();
   p=1;
  }
  f.read((char*)&k,sizeof(book));
 }
 f.close();
 f.open("book.dat",ios::in|ios::out|ios::binary);
 if(p==0)
 {cout<<"Not Allowed";
  getch();
  return;
 }
 char ch;
 cout<<"\nAre you sure you want to return this book?(y/n)";
 cin>>ch;
 if(ch=='n')
 {
  f.close();
  g.close();
  temp.close();
  temp1.close();
  return;
 }
 else
 {
  g.read((char*)&m,sizeof(member));
  while(!g.eof())
 {
  if(m.getid()==mid)
  {
   m.push(m.getissue());
   m.modifyissue(-1);
  }
  temp.write((char*)&m,sizeof(member));
  g.read((char*)&m,sizeof(member));
 }
 temp.close();
 g.close();
 remove("member.dat");
 rename("temp.dat","member.dat");
 f.read((char*)&k,sizeof(book));
 while(!f.eof())
 {
  if(k.getissue()==mid)
  {
   k.statuschange(-1);
  }
  temp1.write((char*)&k,sizeof(book));
  f.read((char*)&k,sizeof(book));
 }
 f.close();
 temp1.close();
 remove("book.dat");
 rename("temp1.dat","book.dat");
 }
}
void del()
{clrscr();
 int choice,mid,bid;
 member m;
 book k;
 int s=0;int i=0;
 fstream f("member.dat",ios::in|ios::out|ios::binary);
 fstream g("book.dat",ios::in|ios::out|ios::binary);
 fstream temp("temp.dat",ios::out|ios::binary);
 fstream temp1("temp1.dat",ios::out|ios::binary);
 cout<<"What do you want to delete?";
 cout<<"\n1.Member\n2.Book";
 cin>>choice;
 if(choice==1)
 {cout<<"Enter the ID of the member:";
  cin>>mid;
  while(!f.eof())
  {f.read((char*)&m,sizeof(m));}
  if(sizeof(member)==f.tellg())
  {g.read((char*)&k,sizeof(k));
   while(!g.eof())
   {
   if(k.getissue()==mid)
   {k.statuschange(-1);}
   temp1.write((char*)&k,sizeof(book));
   g.read((char*)&k,sizeof(book));
   }
   temp1.close();
   g.close();
   remove("book.dat");
   rename("temp1.dat","book.dat");
   f.close();
   temp.close();
   remove("member.dat");
   return;
  }
  f.close();
  f.open("member.dat",ios::in|ios::out|ios::binary);
  f.read((char*)&m,sizeof(member));
  while(!f.eof())
  {
  if(mid==m.getid())
   {i++;s=1;}
   if(i==2)
   break;
   if(s==0)
   temp.write((char*)&m,sizeof(member));
   s=0;
   f.read((char*)&m,sizeof(member));
  }
  g.read((char*)&k,sizeof(k));
   while(!g.eof())
   {
   if(k.getissue()==mid)
   {k.statuschange(-1);}
   temp1.write((char*)&k,sizeof(book));
   g.read((char*)&k,sizeof(book));
   }
   temp1.close();
   g.close();
   remove("book.dat");
   rename("temp1.dat","book.dat");
  f.close();
  temp.close();
  remove("member.dat");
  rename("temp.dat","member.dat");
 }
 else
 {
  cout<<"Enter the ID of the book:";
  cin>>bid;
  while(!g.eof())
  g.read((char*)&k,sizeof(k));
  if(sizeof(book)==g.tellg())
  {f.read((char*)&m,sizeof(member));
  while(!f.eof())
  {
  if(m.getissue()==bid)
  m.modifyissue(-1);
  temp.write((char*)&m,sizeof(member));
  f.read((char*)&m,sizeof(member));
  }
  f.close();
  temp.close();
  remove("member.dat");
  rename("temp.dat","member.dat");
   g.close();
   temp1.close();
   remove("book.dat");
   return;
  }
  g.close();
  g.open("book.dat",ios::in|ios::out|ios::binary);
  g.read((char*)&k,sizeof(book));
  while(!g.eof())
  {
   if(bid==k.getid())
   {i++;s=1;}
   if(i==2)
   break;
   if(s==0)
   temp1.write((char*)&k,sizeof(book));
   s=0;
   g.read((char*)&k,sizeof(book));
  }
  f.read((char*)&m,sizeof(member));
  while(!f.eof())
  {
  if(m.getissue()==bid)
  m.modifyissue(-1);
  temp.write((char*)&m,sizeof(member));
  f.read((char*)&m,sizeof(member));
  }
  f.close();
  temp.close();
  remove("member.dat");
  rename("temp.dat","member.dat");
  g.close();
  temp1.close();
  remove("book.dat");
  rename("temp1.dat","book.dat");
 }
}
char* password()
{
 char pas[40]={0};
 for(int i=0;i<20;i++)
 {
  start:
  char p;
  p=getch();
  if(p!=8&&p!=13)
  {pas[i]=p;
   cout<<"*";}
  if(p==8&&i>0)
  {
   i--;
   pas[i]=0;
   clrscr();
   cout<<"Enter password:";
   for(int j=i;j>0;j--)
   cout<<"*";
   goto start;
  }
  if(p==13)
  {return pas;}
 }
 return pas;
}
int passcheck()
{
 s:
 cout<<"Enter password:";
 char* t={0};
 t=password();
 char y[40]={0};
 for(int i=0;i<20;i++)
 y[i]=*(t+i);
 char x[40]={0};
 fstream g("password.txt",ios::in);
 g>>x;
 if(strcmp(x,y)==0)
 return 1;
 else
 {
  cout<<"\nIncorrect Password!Please enter again:\n";
  return 0;
 }
}
void managepass()
{
 fstream h("password.txt",ios::in);
 if(!h)
 {
  cout<<"\nEnter Password:";
  char* t={0};
  t=password();
  char x[40]={0};
  for(int i=0;i<20;i++)
  x[i]=*(t+i);
  fstream file("password.txt",ios::out);
  file<<x;
  file.close();
 }
 else
 {
  int c;
  cout<<"What do you want to do\n1)Modify password\n2)Delete password";
  cin>>c;
  switch (c)
  {
   case 1:
   {
    cout<<"\nDo you want to change password(Y/N)?";
    char ch;
    cin>>ch;
    if(ch=='y'||ch=='Y')
    {
     cout<<"Enter old password:";
     char* p={0};
     char t[40]={0};
     char x[40]={0};
     p=password();
     for(int i=0;i<20;i++)
     x[i]=*(p+i);
     h.seekg(0);
     h>>t;
     if(strcmp(x,t)==0)
     {
      cout<<"\nEnter Password(Max. 20 Characters):";
      char* t={0};
      t=password();
      char x[40]={0};
      for(int i=0;i<20;i++)
      x[i]=*(t+i);
      fstream file("password.txt",ios::out);
      file<<x;
      file.close();
     }
     else
     {
      cout<<"Wrong Password!Access Denied.";
      getch();
     }
     break;
    }
    else if(ch=='n'||ch=='N')
    {
     cout<<"Aborting....";
    }
   }
   case 2:
   {
    cout<<"Enter old password:";
    char* p={0};
    p=password();
    char x[40]={0};
    for(int i=0;i<20;i++)
    x[i]=*(p+i);
    char l[40];
    h.seekg(0);
    h>>l;
    h.close();
    if(strcmp(l,x)==0)
    {
     remove("password.txt");
     cout<<"Password Deleted.";
     getch();
    }
    else
    {
     cout<<"Wrong Password!Access Denied.";
     getch();
    }
   }
  }
 }
 h.close();
}
void security()
{
 fstream f("password.txt",ios::in);
 if(f)
 {
  int a=0;
  s:
  int check=passcheck();
  if(check==1 && a<3)
  return;
  else if(a==2)
  {cout<<"\nSorry!You entered wrong password 3 times!";
   getch();
   exit(0);
  }
  else
  {
  a++;
  goto s;
  }
 }
 f.close();
}
void main()
{
 clrscr();
 security();
 start:
 clrscr();
 cout<<"\n\t\tW E L C O M E   T O   T H E   L I B R A R Y  ";
 cout<<"\nWhat operation do you want to perform";
 cout<<"\n\t1.Add members";
 cout<<"\n\t2.View members";
 cout<<"\n\t3.Add books";
 cout<<"\n\t4.Book list";
 cout<<"\n\t5.Issue a book";
 cout<<"\n\t6.Return a book";
 cout<<"\n\t7.Books taken";
 cout<<"\n\t8.Remove a book/member";
 cout<<"\n\t9.Remove all data";
 cout<<"\n\t10.Manage password for your software";
 cout<<"\n\t11.Exit";
 int choice;
 cout<<"\nEnter your option no.";
 cin>>choice;
 switch(choice)
 {
 case 1:
  {add();
   getch();
   goto start;
  }
 case 2:
  {view();
  getch();
  goto start;
  }
 case 3:
  {addbook();
   getch();
   goto start;
  }
 case 4:
  {viewbook();
   getch();
   goto start;
  }
 case 5:
  {lend();
   getch();
   goto start;
  }
 case 6:
  {
   returnbook();
   getch();
   goto start;
  }
 case 7:
  {
   btake();
   getch();
   goto start;
  }
 case 8:
  {
   del();
   getch();
   goto start;
  }
 case 9:
  {
   remove("book.dat");
   remove("member.dat");
   getch();
   goto start;
  }
 case 10:
  {
   clrscr();
   managepass();
   goto start;
  }
 case 11:
  {exit(0);}
 default:
  {
   cout<<"\n Please Enter a correct option number";
   goto start;
  }
 }
}