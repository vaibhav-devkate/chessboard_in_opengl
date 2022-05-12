#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

int flag,flag1=0,xst,yst;

float input[3][16],r[3][3],final[3][16];

float r_ang,xp,yp;

float x,y,p,q;

float bCol[3],fCol[3],fCol1[3];

void bres(int xa,int ya, int xb,int yb)
{
  int c,r,f,d;
  int dx=xb-xa;
  int dy=yb-ya;

  d=2*abs(dy)-abs(dx);

 if(dx>0)
  {
    c=xa;
    r=ya;
    f=xb;
  }
 else
  {
    c=xb;
    r=yb;
    f=xa;
  }

 glBegin(GL_POINTS);

  if((xb>xa&&yb>ya)||(xb<xa&&yb<ya))
 {
  while(f>c)

  {  

  if(d<=0)
  { 
  c=c+1;
  d=d+2*abs(dy);

  if(flag==0)
  {

    glVertex2i(c,r);
   }
  else
  {
   glVertex2i(r,c);

  }
  }
  else
   {
    c=c+1;
    r=r+1;
    d=d+2*abs(dy)-2* abs(dx);
    if(flag==0)
    {
      glVertex2i(c,r);
     }
  else{
       glVertex2i(r,c);
      }}}

   glEnd();
   glFlush();
  }
  else
  {
    while(f>c)
   {
    if(d<=0)
    {
    c=c+1;
    d=d+2*abs(dy);
     if(flag==0)
     {

     glVertex2i(c,r);
     }
   else
  {
   glVertex2i(r,c);
   }

  }

  else
  {
   c=c+1;
   r=r-1;
    d=d+2*abs(dy)-2*abs(dx);
    if(flag==0)
   {
 
   glVertex2i(c,r);
  }
  else
 {

  glVertex2i(r,c);
  }

}}

glEnd();

glFlush();

}
}

void Init()
{
  glClearColor(1.0,1.0,1.0,0);
   glColor3f(bCol[0],bCol[1],bCol[2]);
  gluOrtho2D(0,1020,0,660);

}


void draw_bline(int X1,int Y1, int X2, int Y2)

{

  int dx=X2-X1;
  int dy=Y2-Y1;
  
 if(abs(dx)>abs(dy))
 {

  flag=0;
  bres(X1,Y1,X2,Y2);
 }
 else
 {
  flag=1;
  bres(Y1,X1,Y2,X2);
  }
  
}

void initmat()

{

int xmax=glutGet(GLUT_WINDOW_WIDTH);
int a=xmax/2+100,b=80,i;



for(i=0;i<5;i++)
{
input[0][i]=a;

input[1][i]=b;

input[2][i]=1;

a+=30;
}
a=xmax/2+220;

b=110;

for(i=5;i<9;i++)
{
input[0][i]=a;

input[1][i]=b;
input[2][i]=1;
b+=30;

}

a=xmax/2+190;

b=200;

for(i=9;i<13;i++)

{

input[0][i]=a; input[1][i]=b; input[2][i]=1; 
a-=30;

}

a=xmax/2+100;

b=170;

for(i=13;i<16;i++)

{

input[0][i]=a;

input[1][i]=b;

input[2][i] = 1;

b-=30;

}}



void drawcb(float m[3][16])
{
  int i;
 glPointSize(2);
   draw_bline(m[0][0],m[1][0],m[0][4],m[1][4]); //below line

   for(i=0;i<5;i++){
      draw_bline(m[0][i],m[1][i],m[0][12-i],m[1][12-i]);} //vertical lines

   for(i=5;i<9;i++){
      draw_bline(m[0][i],m[1][i],m[0][20-i],m[1][20-i]); //horizontal lines
     }



}

void mult(){

 int i,j,k; 
 for(i=0;i<3;i++){
 
  for(j=0;j<16;j++){
  
     final[i][j]=0; 
     
     for(k=0;k<3;k++) { 
     
       final[i][j]+=r[i][k]*input[k][j];
     
     }
    }
   }
   
      glColor3f(bCol[0],bCol[1],bCol[2]);
   drawcb (final);
}


void rotation(){

glClear(GL_COLOR_BUFFER_BIT);

   int i,j;

  r[2][2]=1;

  r[2][0]=r[2][1]=0;

  r[0][0]=r[1][1]=cos(r_ang);

  r[0][1]=-sin(r_ang);

  r[1][0]=sin(r_ang);

  r[0][2]=xp*(1-cos(r_ang))+yp*sin(r_ang);

  r[1][2]=yp*(1-cos(r_ang))-xp* sin(r_ang);
  
   mult();
}

void boundary_fill(int x, int y, float* fillColor, float* bc)
{
  float color[3];
 glPointSize(1);
  glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,color);

  if((color[0]!=bc[0] || color[1]!=bc[1] || color[2]!=bc[2])&&(color[0]!=fillColor[0] || color[1]!=fillColor[1] || color[2]!=fillColor[2]))
  {
  
   glColor3f(fillColor[0], fillColor[1], fillColor[2]);
   
   glBegin(GL_POINTS);
   glVertex2i(x,y);
   glEnd();
   glFlush();

  boundary_fill(x+1,y,fillColor,bc);
  boundary_fill(x-1,y,fillColor,bc);
  boundary_fill(x,y+1, fillColor,bc);
  boundary_fill(x,y-1,fillColor, bc);
  
  }
  
}


void new_point(float *x, float *y)
{
  float m,n;

  
  m=*x*cos(r_ang)-*y *sin(r_ang)+xp*(1-cos(r_ang))+yp*sin(r_ang);
  n=*x*sin(r_ang)+*y*cos(r_ang)+yp*(1-cos(r_ang))-xp* sin(r_ang);
  *x=m;
  *y=n;
}




void Chess_Board(float x,float y)
{

if(flag1==1){


  p=x;q=y;
  new_point(&p,&q);
   boundary_fill(p,q,fCol,bCol);
   
   p=x+60;
   q=y;
  new_point(&p,&q);
   boundary_fill(p,q,fCol,bCol);
   
   p=x-30;
   q=y+30;
 new_point(&p,&q);
   boundary_fill(p,q,fCol,bCol);
   
   p=x+30;
   q=y+30;
 new_point(&p,&q);
   boundary_fill(p,q,fCol,bCol);
  
  p=x; 
   q=y+60;
  new_point(&p,&q);
   boundary_fill(p,q,fCol,bCol);
   
    p=x+60;
   q=y+60;
  new_point(&p,&q);
   boundary_fill(p,q,fCol,bCol);
   
   
   p=x-30;
  q=y+90;
  new_point(&p,&q);
   boundary_fill(p,q,fCol,bCol);


   p=x+30;
    q=y+90;
  new_point(&p,&q);
   boundary_fill(p,q,fCol,bCol);

}
else{
 boundary_fill(x,y,fCol,bCol);
 boundary_fill(x+60,y,fCol,bCol);
 boundary_fill(x-30,y+30,fCol,bCol);
 boundary_fill(x+30,y+30,fCol,bCol);
 boundary_fill(x,y+60,fCol,bCol);
 boundary_fill(x+60,y+60,fCol,bCol);
 boundary_fill(x-30,y+90,fCol,bCol);
 boundary_fill(x+30,y+90,fCol,bCol);
 }

 
}


void display(){
  
 initmat();

 glClear(GL_COLOR_BUFFER_BIT);

 drawcb(input);
  


}

void mymouse(int b,int s,int x,int y){
if(b==GLUT_LEFT_BUTTON && s==GLUT_DOWN){
xst=x;
yst=660-y;

 if(flag1==1){
 
 Chess_Board(650,90);
 
 }
 else{
   flag1=0;
   
   Chess_Board(650,90);
 
 }

}


}
void onKeyboard(int key, int x, int y)
{
if(key == GLUT_KEY_LEFT)
{
rotation();
flag1=1;
 
 
}
else if(key == GLUT_KEY_RIGHT)
printf("Right key is Pressed");

}



int main(int argc, char **argv)
{   
   printf("\nEnter the pivot point   (center of chess :670,140):");
   scanf("%f%f",&xp,&yp);

   printf("\nEnter angle of rotation:");
   scanf("%f",&r_ang);

   r_ang=r_ang*(3.14/180);

   printf("\nAccept Boundary Color:");
   
   int i;
   for( i=0;i<3;i++)
   scanf("%f",&bCol[i]);

   printf("\nAccept  first  Fill Color:");

   for(i=0;i<3;i++)
   scanf("%f",&fCol[i]);
   
 
   glutInit(&argc,argv);
   
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   
   glutInitWindowPosition (0,0);
   
   glutInitWindowSize(1020,660);
   
   glutCreateWindow("Bres_Line");
   
   Init();
   
   glutDisplayFunc(display);
      glutMouseFunc(mymouse);
   glutSpecialFunc(onKeyboard);
  
   glutMainLoop();

   return 0;
   
}
