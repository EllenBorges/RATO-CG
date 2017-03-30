/*------------------------DESCRICAO---------------------------------
Computacao Grafica
Nome: Ellen Priscila Borges Oliveira
RA: 69554

O programa desenha um ratinho bidimensional animado na tela,o qual persegue
pedaços de queijo que aparecem de acordo com o clique do mouse.
Quando o rato se aproxima do queijo, o queijo some da tela.

*/

#include<stdio.h>
#include<stdlib.h>
#include <math.h>

#include <GL/glut.h>

/*------------------------CONSTANTES-------------------------------*/
#define PI 3.141592654

/*------------------------VARIAVEIS--------------------------------*/
GLfloat x_Queijo = 0, y_Queijo = 0;
GLfloat altura_Janela, largura_Janela ;
GLfloat x_Janela=200, y_Janela=200;
GLfloat X_Centro_Rato = 0.0,Y_Centro_Rato = 0.0;
GLfloat Raio_Rato = 0.5;
GLfloat X_Nariz_Rato = 0, Y_Nariz_Rato = -0.30;
GLfloat X_Rabo_Rato = 0, Y_Rabo_Rato = 0.064;
GLfloat xt = 0, yt = 0, sx = 1 , sy = 1;
GLfloat teta = 0;

/*------------------ESTRUTURA DA LISTA-----------------------------*/
typedef struct no_lista{
  float x, y;
  struct no_lista *ant;
  struct no_lista *prox;
}NO;

typedef struct Lista{
    NO* primeiro;
    NO* ultimo;
    int tamanho;
}LDE;

LDE *listaQueijo;
/*----------------- FUNCOES PARA A LISTA ENCADEADA-----------------*/


void InicializaLista(LDE *L){

  L->primeiro = NULL;
  L->ultimo = NULL;
  L->tamanho = 0;

}

NO* Busca(LDE *L, float x, float y){

    NO *temp;
    for (temp = L->primeiro; temp!=NULL;temp = temp->prox) {
        if ((temp->x == x)&&(temp->y == y)){
          return temp;
        }
    }
    return NULL; /* não achou o no */
}


/*insere um novo no no final da lista*/
void InsereNO(LDE *L, float x,float y){

    NO *novo = (NO*)malloc(sizeof(NO));
    novo->ant = NULL;
    novo->prox = NULL;
    novo->x = x;
    novo->y = y;


    if(L->primeiro==NULL && L->ultimo==NULL){
        L->primeiro = novo;
        L->ultimo = novo;
        L->tamanho++;

    }

    else{
        novo->prox = NULL;
        novo->ant= L->ultimo;
        L->ultimo->prox = novo;
        L->ultimo = novo;
        L->tamanho++;

    }
}

void RemoveNO(LDE *L, float x, float y){
    if(L->tamanho>0){ /*se a lista nao esta vazia*/

	    NO* temp = Busca(L,x,y);
	    if(temp!=NULL){
		/*remove começo*/
		if(temp->ant==NULL){
		    L->primeiro = temp->prox;
		    L->primeiro->ant = NULL;

		}/*remove final*/
		else if(temp->prox==NULL){
		    L->ultimo= temp->ant;
		    temp->ant->prox=NULL;
		    L->tamanho--;

		}/*remove no meio*/
		else {
		    temp->ant->prox = temp->prox;
		    temp->prox->ant = temp->ant;

		}
		L->tamanho--;
		temp->prox = NULL;
		temp->ant= NULL;
		free(temp);

	   }
     }

}

void DestroiLista(LDE* L){
    NO* no = L->primeiro;
    NO* temp;

    while (no != NULL) {
        temp = no->prox;
        free(no);
        no = temp;
    }
    free(L);
}



void Imprime_ListaQueijo(){
    if(listaQueijo!=NULL && listaQueijo->tamanho>0)
        lst_imprime(listaQueijo->primeiro);
}

 void lst_imprime (NO* lst){
    NO* p;
    for (p = lst; p != NULL; p = p->prox)
        printf("X_Queijo = [%.2f] \n Y_Queijo = [%.2f] \n", p->x, p->y);
}
/*------------------------FUNÇÕES DE INICIALIZAÇÃO---------------------*/
void inicializa_Tela(char nome_janela[]){

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(500,500);
    largura_Janela = 500;
    altura_Janela = 500;
    glutInitWindowPosition(x_Janela,y_Janela);
    glutCreateWindow(nome_janela);
    glClearColor(255,255,255,255);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-1.0,1.0,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
    glFinish();

}


void cor_Corrente(char nome_cor[]){

    if(strcmp (nome_cor, "branco") == 0)
        glColor3f(1,1,1);
    else if(strcmp (nome_cor, "preto") == 0)
        glColor3f(0,0,0);
    else if(strcmp (nome_cor, "vermelho") == 0)
        glColor3f(1,0,0);
    else if(strcmp (nome_cor, "azul") == 0)
        glColor3f(0,0,1);
    else if(strcmp (nome_cor, "verde") == 0)
        glColor3f(0,1,0);
    else if(strcmp (nome_cor, "amarelo") == 0)
        glColor3f(1,1,0);
    else if(strcmp (nome_cor, "magenta") == 0)
        glColor3f(1,0,1);
    else if(strcmp (nome_cor, "ciano") == 0)
        glColor3f(0,1,1);
    else if(strcmp (nome_cor, "cinza") == 0)
        glColor3f(0.86,0.86,0.86);
     else if(strcmp (nome_cor, "rosa claro") == 0)
        glColor3f(1,0.71,0.76);
    else if(strcmp (nome_cor, "salmao claro") == 0)
        glColor3f(1,0.63,0.48);
    else if(strcmp (nome_cor, "salmao") == 0)
        glColor3f(0.98,0.5,0.45);
    else if(strcmp (nome_cor, "cinza ardosia escuro") == 0)
        glColor3f(0.18,0.31,0.31);
    else if(strcmp (nome_cor, "ouro") == 0)
        glColor3f(1,0.84,0);

}


/*---------------------- FUNCOES DE TRANSFORMAÇÃO---------------------------*/


void rotaciona_Rato(GLfloat angulo_teta){

    if(teta>=2*PI) teta = 0.00;

    if(teta<2*PI && teta>=0.000){
        teta += angulo_teta;
    }


}

void rotaciona_Rato_Composta(GLfloat angulo_teta){
    GLfloat xtemp, ytemp;
    xtemp = X_Centro_Rato;
    ytemp = Y_Centro_Rato;
    translada_Rato(-xtemp,-ytemp);
    rotaciona_Rato(angulo_teta);
    X_Centro_Rato = xtemp;
    Y_Centro_Rato = ytemp;
    translada_Rato(xtemp,ytemp);
}

void translada_Rato(GLfloat deltay, GLfloat deltax){
    xt+=deltax;
    yt+=deltay;
}

void escala_Rato_Diminui(GLfloat deltasx, GLfloat deltasy){

    if(sx>=0 || sy>=0){


        sx+=deltasx;
        sy+=deltasy;

    }
}

void escala_Rato_Aumenta(GLfloat deltasx, GLfloat deltasy){
     //modificar condição de parada
    //if(sx<=3 && sy<=3){

    //GLfloat area_rato;
   // area_rato = pow(Raio_Rato,2)*PI;
    //if(area_rato<=(altura_Janela*largura_Janela)){
        sx+=deltasx;
        sy+=deltasy;

    //}


}
void escala_Rato_Aumenta_Composta(GLfloat deltasx, GLfloat deltasy){
    GLfloat xtemp, ytemp;
    xtemp = X_Centro_Rato;
    ytemp = Y_Centro_Rato;
    translada_Rato(-xtemp,-ytemp);
    escala_Rato_Aumenta(deltasx,deltasy);
    X_Centro_Rato = xtemp;
    Y_Centro_Rato = ytemp;
    translada_Rato(xtemp,ytemp);
}

void escala_Rato_Diminui_Composta(GLfloat deltasx, GLfloat deltasy){
    GLfloat xtemp, ytemp;
    xtemp = X_Centro_Rato;
    ytemp = Y_Centro_Rato;
    translada_Rato(-xtemp,-ytemp);
    escala_Rato_Diminui(deltasx,deltasy);
    X_Centro_Rato = xtemp;
    Y_Centro_Rato = ytemp;
    translada_Rato(xtemp,ytemp);

}

float Angulo(GLfloat x, GLfloat y){
    if(x>0){
        return atan2(y,x);
    }

    else return -1;
}

/*---------------------- FUNCOES DE INTERACAO---------------------------*/



void SpecialKeys (int key, int x, int y){
    switch (key){
        case GLUT_KEY_RIGHT:
            translada_Rato(0,0.09);
            break;
        case GLUT_KEY_LEFT:
            translada_Rato(0,-0.09);
            break;

        case GLUT_KEY_DOWN :
            translada_Rato(-0.09,0);
            break ;
        case GLUT_KEY_UP :
            translada_Rato(0.09,0);
            break ;
        default :
            break ;
        }
        glutPostRedisplay() ;
}


void keyboard (unsigned char key, int x, int y){
    switch(key){
        case '+':
            /*faz com que o rato aumente seu tamanho*/
            escala_Rato_Aumenta_Composta(0.15,0.15);

            break;
        case '-':
            /*faz com que o rato diminua seu tamanho*/
            escala_Rato_Diminui_Composta(-0.15,-0.15);
            break;
        case 'r':
            /*faz com que o rato rotacione */
            rotaciona_Rato_Composta(PI/10);

            break;

        case 27:
            exit(0);
            break;
        default:
            break;

    }
    glutPostRedisplay();
}


void MouseInt (int botao, int estado, int x, int y){
    switch(botao){
    case GLUT_LEFT_BUTTON:
        if(estado == GLUT_DOWN){
            x_Queijo = ((float)x/((float)largura_Janela/2.0))-1.0;

            y_Queijo = (float) 1 -(float) y/(altura_Janela/2.0);


            InsereNO(listaQueijo,x_Queijo,y_Queijo);
            Imprime_ListaQueijo();
        }
        break;
    }
    glutPostRedisplay();
}

/*---------------------- FUNCOES DE DESENHO---------------------------*/

void desenha(){

/*Variaveis locais*/
    GLint i;
    GLfloat x,y,xp,yp;
    GLfloat angulo = 0;
    GLfloat P0X=0,P0Y=0.2,P1X=-0.3,P1Y=0.4,P2X=0.3,P2Y=0.4,P3X=0,P3Y=0.6,t;


/*-----------------------Desenha Queijo-----------------------*/
/*
    cor_Corrente("ouro");
    glPointSize(20.0);
    glBegin(GL_POINTS);
        glVertex2f();
    glEnd();

*/

/*------------------------Desenha Rato------------------------*/



    /*desenha corpo*/
    glBegin(GL_POLYGON);
        cor_Corrente("preto");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.22*cos(angulo);
            y=0.22*sin(angulo);
            xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
            yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));
            glVertex2f(xp,yp);
        }
    glEnd();

    /*desenha cabeça*/
    glBegin(GL_POLYGON);
        cor_Corrente("preto");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.15*cos(angulo);
            y=0.17*sin(angulo)-0.17;
           // glVertex2f((x+xt)*sx,(y+yt)*sy);
           xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
            yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));
            glVertex2f(xp,yp);
        }
    glEnd();

    /*desenha orelha esquerda*/
    glBegin(GL_POLYGON);
        cor_Corrente("cinza ardosia escuro");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.1*cos(angulo)-0.1;
            y=0.1*sin(angulo)-0.1;
            //glVertex2f((x+xt)*sx,(y+yt)*sy);
            xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
            yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));
            glVertex2f(xp,yp);
        }
    glEnd();

    glBegin(GL_POLYGON);
        cor_Corrente("salmao claro");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.07*cos(angulo)-0.1;
            y=0.07*sin(angulo)-0.12;
            //glVertex2f((x+xt)*sx,(y+yt)*sy);
            xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
            yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));
            glVertex2f(xp,yp);
        }
    glEnd();

    /*desenha orelha direita*/
    glBegin(GL_POLYGON);
        cor_Corrente("cinza ardosia escuro");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.1*cos(angulo)+0.13;
            y=0.1*sin(angulo)-0.1;
            //glVertex2f((x+xt)*sx,(y+yt)*sy);
            xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
            yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));
            glVertex2f(xp,yp);
        }
    glEnd();
        glBegin(GL_POLYGON);
        cor_Corrente("salmao claro");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.07*cos(angulo)+0.13;
            y=0.07*sin(angulo)-0.12;
           //glVertex2f((x+xt)*sx,(y+yt)*sy);
           xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
            yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));
            glVertex2f(xp,yp);
        }
    glEnd();

    /*desenha nariz*/
    glBegin(GL_POLYGON);
        cor_Corrente("salmao");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.025*cos(angulo);
            y=0.025*sin(angulo)-0.32;
            //glVertex2f((x+xt)*sx,(y+yt)*sy);
            xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
            yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));
            glVertex2f(xp,yp);
        }
    glEnd();

    /*desenha olho direito*/
    glBegin(GL_POLYGON);
        cor_Corrente("branco");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.025*cos(angulo)+0.09;
            y=0.025*sin(angulo)-0.22;
            //glVertex2f((x+xt)*sx,(y+yt)*sy);
            xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
            yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));
            glVertex2f(xp,yp);
        }
        cor_Corrente("preto");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.015*cos(angulo)+0.085;
            y=0.015*sin(angulo)-0.212;
            //glVertex2f((x+xt)*sx,(y+yt)*sy);
            xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
            yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));
            glVertex2f(xp,yp);
        }
    glEnd();

    /*desenha olho esquerdoa*/
    glBegin(GL_POLYGON);
        cor_Corrente("branco");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.025*cos(angulo)-0.09;
            y=0.025*sin(angulo)-0.22;
            //glVertex2f((x+xt)*sx,(y+yt)*sy);
            xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
            yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));
            glVertex2f(xp,yp);
        }
        cor_Corrente("preto");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.015*cos(angulo)-0.085;
            y=0.015*sin(angulo)-0.212;
            //glVertex2f((x+xt)*sx,(y+yt)*sy);
            xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
            yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));
            glVertex2f(xp,yp);
        }
    glEnd();

    /*desenha bigode*/
    glLineWidth(1.0);
    glBegin(GL_LINES);
        cor_Corrente("preto");

        /* bigode esquerdo*/
        x = -0.12; y = -0.25;
        xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
        yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));glVertex2f(xp,yp);

        x = -0.22; y = -0.22;
        xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
        yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));glVertex2f(xp,yp);

        x = -0.12; y = -0.27;
        xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
        yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));glVertex2f(xp,yp);
        x = -0.24; y = -0.27;
        xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
        yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));glVertex2f(xp,yp);
        x = -0.11; y = -0.28;
        xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
        yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));glVertex2f(xp,yp);
        x = -0.22; y = -0.31;
        xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
        yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));glVertex2f(xp,yp);

        /* bigode direito*/
        x = 0.12; y = -0.25;
        xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
        yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));glVertex2f(xp,yp);
        x = 0.22; y = -0.22;
        xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
        yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));glVertex2f(xp,yp);
        x = 0.12; y = -0.27;
        xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
        yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));glVertex2f(xp,yp);
        x = 0.24; y = -0.27;
        xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
        yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));glVertex2f(xp,yp);
        x = 0.11; y = -0.28;
        xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
        yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));glVertex2f(xp,yp);
        x = 0.22; y = -0.31;
        xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
        yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));glVertex2f(xp,yp);
    glEnd();


    /*desenha rabo */
    cor_Corrente("preto");
    glLineWidth(5.0);

    glBegin(GL_LINE_STRIP);

        for (t=0; t<=1 ;t=t+0.01){

            /*Curva de Bezier*/

            y =(pow((1-t),3) * P0Y) +(3 * t * pow((1-t),2)*P1Y) + (3 * pow(t,2)* (1-t)*P2Y) + (pow(t,3)*P3Y);
            x =(pow((1-t),3) * P0X) +(3 * t * pow((1-t),2)*P1X) + (3 * pow(t,2)* (1-t)*P2X) + (pow(t,3)*P3X);

            //glVertex2f((x+xt)*sx,(y+yt)*sy);
            xp = (((x+xt)*sx)*cos(teta))-(((y+yt)*sy)*sin(teta));
            yp = (((x+xt)*sx)*sin(teta))+(((y+yt)*sy)*cos(teta));
            glVertex2f(xp,yp);
        }
    glEnd();

    /*define coordenadas do Rato */
    X_Centro_Rato = (X_Centro_Rato + xt)*sx;
    Y_Centro_Rato = (Y_Centro_Rato + yt)*sy;

    xp = (((X_Nariz_Rato+xt)*sx)*cos(teta))-(((Y_Nariz_Rato+yt)*sy)*sin(teta));
    yp = (((X_Nariz_Rato+xt)*sx)*sin(teta))+(((Y_Nariz_Rato+yt)*sy)*cos(teta));

    Y_Nariz_Rato = yp;
    X_Nariz_Rato = xp;

    xp = (((X_Rabo_Rato+xt)*sx)*cos(teta))-(((Y_Rabo_Rato+yt)*sy)*sin(teta));
    yp = (((X_Rabo_Rato+xt)*sx)*sin(teta))+(((Y_Rabo_Rato+yt)*sy)*cos(teta));

    X_Rabo_Rato = xp;
    Y_Rabo_Rato = yp;

    xp=0;
    yp=0;

    Raio_Rato = sqrt(pow(sx*X_Centro_Rato-sx*X_Rabo_Rato,2)+pow(sy*Y_Centro_Rato-sy*Y_Rabo_Rato,2));

    glFlush();


}
/*------------------FUNÇÕES DE MOVIMENTACAO DO RATO----------------------*/

void controla_Rato(){
    GLint i=0;
    GLfloat distancia = 0;
    if(listaQueijo!= NULL){
        if(listaQueijo->tamanho>0){
            //criar laco para
                //rotacionar_Rato(); se precisar
                //translada_Rato();
            //enquanto o rato nao chegar no queijo (definir distancia entre dois pontos)

            //se chegou no queijo-> remove queijo da lista

       }
    }


}


void tamanho_Janela(GLsizei h, GLsizei w){
    glViewport(0,0,w,h); // Ajustando o visualizador
    glMatrixMode(GL_PROJECTION); // Trabalhando com a matriz de projeção
    glLoadIdentity(); // Iniciando a Matriz de cima
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1,1000.0); //Corrigindo a perspectiva
    //glortho(-25,25,-2,2,0.1,100); //Método alternativo de fazer o mesmo
    //glMatrixMode(GL_MODELVIEW);// Voltando a trabalhar com a matriz de modelo

}

void Display(){

    glClearColor(255,255,255,255);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    desenha();

    glutSwapBuffers();
}

int main(int argc, char *argv[]){

    glutInit (&argc,argv);
    listaQueijo = (LDE*) malloc(sizeof(LDE));
    InicializaLista(listaQueijo);
    inicializa_Tela("RUN MOUSE");
    glutDisplayFunc(Display);
    glutIdleFunc(Display);
    glutReshapeFunc(tamanho_Janela);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialKeys);
    glutMouseFunc(MouseInt);

    glutMainLoop();
    free(listaQueijo);

return 0;
}
