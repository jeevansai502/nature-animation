#include<bits/stdc++.h>
using namespace std;
#include<GL/glut.h>
#include<unistd.h>
#include<pthread.h>

double day = 0;
double sx = 500,sy = 50;
double mx = 300,my = 50;
double cx = 0,cy = 400;
double w = 1000,h=500;
double cx1 = 200,cy1 = 375;  
double cx2 = 400,cy2 = 400;
double y11 = 400,y12 = 300;

int bird[] = {0,0,0,0,0,0,0,0,0,0,0};    //birds position

pthread_t threads[5];  //threads for sounds
char sounds[][20]={"bird.wav","thunder1.wav","wind.wav","boat2.wav", "rain.wav"};  //sound file names
typedef pair<int, int> point;
vector<point> drops;

void * playSound(void *i){

	long sid = (long)i;
	char fr[] = {"canberra-gtk-play -f "};
	strcat(fr,sounds[sid]);
	system(fr);     // play sound
	pthread_exit(NULL);  //exit the thread
}

void myinit()
{
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,1000,0,500);   //initialize screen dimensions
}
void startscreen(float r,float g,float b)
{
	glClearColor(r,g,b,1);
	glClear(GL_COLOR_BUFFER_BIT);
}

double mount1(double base,double height,double dir){

	double base1 = base,base2 = base;

	glBegin(GL_POLYGON);   //draw top mountain
	glColor3f(236/255.0,124/255.0,66/255.0);
	double x,y;
	for(double i=0;i<1000;i++){

		x = base + i;
		y = (-1)*pow(i,2)/40 + height;

		glVertex2i(x,y);
		glVertex2i(base-i,y);

		if(y < 0){
			if(dir > 0)
				base = x;
			else
				base = base -i;
			break;
		}

	}

	glVertex2i(base,0);
	glEnd();

	height = height - 6;
	glColor3f(179/255.0,94/255.0,50/255.0);
	glBegin(GL_POLYGON);       //draw middle mountain
	for(double i=0;i<1000;i++){

		x = base1 + i;
		y = (-1)*pow(i,2)/40 + height;

		glVertex2i(x,y);
		glVertex2i(base1-i,y);

		if(y < 0){
			if(dir > 0)
				base1 = x;
			else
				base1 = base1 -i;
			break;
		}

	}

	glVertex2i(base1,0);
	glEnd();

	height = height - 12;

	glColor3f(163/255.0,86/255.0,46/255.0);
	glBegin(GL_POLYGON); //draw outer mountain
	for(double i=0;i<1000;i++){

		x = base2 + i;
		y = (-1)*pow(i,2)/40 + height;

		glVertex2i(x,y);
		glVertex2i(base2-i,y);

		if(y < 0){
			if(dir > 0)
				base2 = x;
			else
				base2 = base2 -i;
			break;
		}

	}

	glVertex2i(base2,0);
	glEnd();

	return base;
}


void mount(){

	double base = 0;
	base = mount1(base,400,1);  //draw mountain parabola 
	base = mount1(base,150,1);
	base = mount1(base,100,1);

	base = 1000;
	base = mount1(base,500,-1);
	base = mount1(base,250,-1);
	base = mount1(base,100,-1);

}

void circle(double x,double y,double r){

	glBegin(GL_POLYGON);
	for(double i=1;i<1000;i++)
	{
		glVertex3f(x + (r)*( cos((i*2*22)/(7*1000*1.0)) ) ,y + r*( sin((i*2*22)/(7*1000*1.0)) ),0 );
	}

	glEnd();


}

void semiCircle(double x,double y,double r){

	glBegin(GL_POLYGON);
	for(double i=0;i<100;i++)
	{
		glVertex3f(x + (r)*( cos((i*2*22)/(7*1000*1.0)) ) ,y + r*( sin((i*2*22)/(7*1000*1.0)) ),0 );

	}
	for(double i=600;i<1000;i++)
	{
		glVertex3f(x + (r)*( cos((i*2*22)/(7*1000*1.0)) ) ,y + r*( sin((i*2*22)/(7*1000*1.0)) ),0 );
	}

	glEnd();

}


void drawSun(){

	float r = 40;

	circle(sx,sy,r);    //draw circle

}

void drawMoon(){

	float r = 30;

	semiCircle(mx,my,r);    // draws semicircle
}
int v = 0;
void drawthunder(){

	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POINTS);
	int x = 0 , y = 0;
	for(int i=0;i<1000000;i++){
		if(v%10 == 0){
			int a = rand()%1500;
			int b = rand()%1000;

			glVertex3i(a+1,0,0);
			glVertex3i(a,b+1,0);
			glVertex3i(a+1,b+1,0);
			glVertex3i(a,b,0);

			glVertex3i((a+1)*-1,0,0);
			glVertex3i(a,(b+1)*-1,0);
			glVertex3i(-1*a,(b+1),0);
			glVertex3i((a+1)*-1,(b+1)*-1,0);
			glVertex3i((a+1)*-1,(b+1),0);
			glVertex3i((a+1),(b+1)*-1,0);
			glVertex3i(-1*a,-1*b,0);
			glVertex3i(-1*a,b,0);
			glVertex3i(a,-1*b,0);

		}
	}
	v++;
	glEnd();

}
int counter = 0;
void sun(){

	counter++;
	if(day < 500){
		glColor3f(1.0,day*(1.0/500),0.0);
		drawSun(); //draw sun polygon
		if(counter%2==0)
		sy = sy + 1;
	}
}

void drawCloud(){

	double r = 20;

	circle(cx,cy,r);
	circle(cx+20,cy,r);
	circle(cx+10,cy-5,r);

	circle(cx-40,cy,r);
	circle(cx-20,cy,r);
	circle(cx-30,cy-5,r);

	cx = cx + 2;

}
void  drawCloud1(){

	double r = 20;

	circle(cx1,cy1,r);  //draws circles 
	circle(cx1+20,cy1,r);
	circle(cx1+10,cy1-5,r);

	circle(cx1-40,cy1,r);
	circle(cx1-20,cy1,r);
	circle(cx1-30,cy1-5,r);

	cx1 = cx1 + 1;

}
void  drawCloud2(){

	double r = 20;

	circle(cx2,cy2,r);   // draws circles
	circle(cx2+20,cy2,r);
	circle(cx2+10,cy2-5,r);

	/*circle(cx2-40,cy2,r);
	  circle(cx2-20,cy2,r);
	  circle(cx2-30,cy2-5,r);*/

	cx2 = cx2 + 1;

}

void drawStar(){

	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POINTS);
	double x = 0 , y = 0;
	for(double i=0;i<4;i++){

		double a = (rand()%1300) - 150;  //star x coordinate
		double b = (rand()%800) - 150;    //star y coordinate
		glVertex3f(a+1,b,0);
		glVertex3f(a,b+1,0);
		glVertex3f(a+1,b+1,0);
		glVertex3f(a,b,0);

	}
	glEnd();
}

void moon(){

	if(day > 500){
		glColor3f(1,1,1);
		drawMoon();   //draws moon
		if(day < 750)
			my = my + 1;
	}

}


void cloud(){

	if(day < 1000){
		glColor3f(0.69,0.87,0.90);
		drawCloud();   //draws cloud
		drawCloud1();
		drawCloud2();

	}

}

void zoom(float x,float y,float z){
	glTranslatef(500,250,0);
	glScalef( x , y , z );
	glTranslatef(-500,-250,0);
	//	glRotatef(0.01,1,0,0);
}

void water(){

	glColor3f(0/255.0,105/255.0,148/255.0);
	glBegin(GL_POLYGON);

	glVertex3f(-500,0,0);

	for(double i=-500;i<1500;i++){

		glVertex3f(i,10*sin((2*22*((i+500)))/(7.0)),0);

	}

	glVertex3f(-500,-250,0);
	glVertex3f(1500,-250,0);
	glVertex3f(1500,0,0);
	glEnd();

}

double y=500;
void drawRain(){
	drops.push_back(point((rand()%1300)-150, 650));
	for (int i = 0; i < drops.size(); i++) {
		glColor3f(241/255.0,242/255.0,253/255.0);
		glBegin(GL_LINES);
		int x = drops[i].first, y = drops[i].second;
		glVertex3f(x,y,0);
		glVertex3f(x-6,y-12,0);
		glEnd();
		drops[i].first -= 6;
		drops[i].second -= 12;
		if (drops[i].second < -150) {
			drops.erase(drops.begin()+i);
		}
	}
}
double x = 0;

void boat(){
	double s = 1.5;
	glColor3f(1.0,0.0,0.0);

	glBegin(GL_POLYGON);
	///glVertex3f((x+0)*s,0,0);


	glVertex3f((x+37)*s,0,0);
	glVertex3f((x+37)*s,40*s,0);
	glVertex3f((x+74)*s,0,0);
	glVertex3f((x+104)*s,0,0);
	glVertex3f((x+87)*s,-30*s,0);
	glVertex3f((x+17)*s,-30*s,0);
	glVertex3f((x+0)*s,0,0);
	glEnd();


	/*	glColor3f(0.0,1.0,0.0);
		glBegin(GL_LINE_LOOP);

		glVertex3f((x+0)*s,0,0);


		glVertex3f((x+37)*s,0,0);
		glVertex3f((x+37)*s,40*s,0);
		glVertex3f((x+74)*s,0,0);
		glVertex3f((x+104)*s,0,0);
		glVertex3f((x+87)*s,-30*s,0);
		glVertex3f((x+17)*s,-30*s,0);
		glVertex3f((x+0)*s,0,0);
		glEnd();
	 */
	x++;
}
int x1 = -170;
void boat1(){
	double s = 1.5;
	glColor3f(1.0,0.0,0.0);

	glBegin(GL_POLYGON);
	///glVertex3f((x+0)*s,0,0);


	glVertex3f((x1+37)*s,0,0);
	glVertex3f((x1+37)*s,40*s,0);
	glVertex3f((x1+74)*s,0,0);
	glVertex3f((x1+104)*s,0,0);
	glVertex3f((x1+87)*s,-30*s,0);
	glVertex3f((x1+17)*s,-30*s,0);
	glVertex3f((x1+0)*s,0,0);
	glEnd();


	/*	glColor3f(0.0,1.0,0.0);
		glBegin(GL_LINE_LOOP);

		glVertex3f((x+0)*s,0,0);


		glVertex3f((x+37)*s,0,0);
		glVertex3f((x+37)*s,40*s,0);
		glVertex3f((x+74)*s,0,0);
		glVertex3f((x+104)*s,0,0);
		glVertex3f((x+87)*s,-30*s,0);
		glVertex3f((x+17)*s,-30*s,0);
		glVertex3f((x+0)*s,0,0);
		glEnd();
	 */
	x1++;
}

void drawBird(int xb,int w,int y11,int index){
	glColor3f(14/255.0,242/255.0,174/255.0);

	//	glColor3f(14/255.0,139/255.0,84/255.0);
	glBegin(GL_POLYGON);
	double s = 1,x = w - xb;
	glVertex3f((x+10)*s,5*s+y11,0);
	glVertex3f((x+6)*s,25*s+y11,0);
	glVertex3f((x+20)*s,5*s+y11,0);
	glVertex3f((x+20)*s,-5*s+y11,0);
	glVertex3f((x+23)*s,-3*s+y11,0);
	glVertex3f((x+26)*s,-5*s+y11,0);
	glVertex3f((x+23)*s,-7*s+y11,0);
	glVertex3f((x+20)*s,-5*s+y11,0);

	glVertex3f((x+20)*s,-15*s+y11,0);
	glVertex3f((x+6)*s,-35*s+y11,0);
	glVertex3f((x+10)*s,-15*s+y11,0);
	glVertex3f((x+5)*s,-10*s+y11,0);

	glVertex3f((x+5)*s,-5*s+y11,0);
	glVertex3f((x+0)*s,-10*s+y11,0);
	glVertex3f((x+0)*s,0*s+y11,0);
	glVertex3f((x+5)*s,-5*s+y11,0);

	glVertex3f((x+10)*s,0*s+y11,0);
	glVertex3f((x+5)*s,-5*s+y11,0);
	glVertex3f((x+10)*s,5*s+y11,0);
	glEnd();
	bird[index] = bird[index] + 1;  //update bird position
}




void display(){

	if(day < 500){
		startscreen(day*(1.0/500),day*(1.0/500),1);     //clears screen
		sun();
	}

	if(day >= 500){

		if(day < 750){
			zoom(0.999,0.999,1);    //for zooming out display
		}

		startscreen(1-((day-500)*(1.0/500)),1-((day-500)*(1.0/500)),1-((day-500)*(1.0/500)));
		water();   //draw water
		moon();    //draw moon

		//     boat();
		//		drawStar();

	}

	if(day >= 500){
		drawStar();	// draw stars	
	}
	drawBird(bird[0],1000,300,0);   //draw bird
	drawBird(bird[1],1050,250,1);
	drawBird(bird[2],1100,200,2);
	drawBird(bird[3],1150,350,3);
	drawBird(bird[4],1150,450,4);
	drawBird(bird[5],1100,480,5);
	drawBird(bird[6],1150,250,6);
	drawBird(bird[7],1150,300,7);
	drawBird(bird[8],1350,225,8);
	drawBird(bird[9],1250,450,9);
	drawBird(bird[10],1150,450,10);
	//drawBird(bird[4],1250,450,4);

	mount();

	if(day >= 500 && day < 1300){
		//boat();
		boat();	  //draw boat
	}
	if(day == 500){
		pthread_create(&threads[3],NULL,playSound,(void *)3);
	}
	if(day > 1300 && day < 1400){
		drawthunder();   //draw thunder
	}
	if (day == 1400)
	{
		pthread_create(&threads[4],NULL,playSound,(void *)4);
	}
	if(day > 1400){
		drawRain();   //draw rain
	}

	if(day == 1300){
		pthread_create(&threads[1],NULL,playSound,(void *)1);
	}
	cloud();    //draw cloud
	day++;
	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(1000,500);
	glutInitWindowPosition(10,10);
	glutCreateWindow("day and night");
	myinit();

	startscreen(1,1,1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glutDisplayFunc(display);
	pthread_create(&threads[0],NULL,playSound,(void *)0);
	pthread_create(&threads[2],NULL,playSound,(void *)2);
	glutMainLoop();
	return 0;
}
