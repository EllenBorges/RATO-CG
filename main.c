#include<stdio.h>
#include<stdlib.h>
#include <math.h>

#include <GL/glut.h>

/*--------------------Constantes-----------------------------------*/
#define PI 3.141592654
#define MAX_NO_TEXTURES 5
/*------------------Variaveis Globais------------------------------*/
float X = 0, Y = 0, w = 500, h = 500, CentroX_Rato = 0,CentroY_Rato = 0;
int tamanho = 25;
float RatoX[200], RatoY[200];
float Centro_Rato = 0;

/*------------------Estrutura da Lista------------------------------*/
typedef struct no_lista{
  float x, y;
  struct no_lista *ant;
  struct no_lista *prox;
}NO;

typedef struct Lista{
    NO* primeiro;
    NO* ultimo;
    int tamanho;     /*guarda o tamanho da lista*/
}LDE;

LDE *listaQueijo;
/*----------------- Funcoes para a Lista encadeada-----------------*/


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

void ImprimeLista (LDE *L) {
  if(L->tamanho>0){

      NO *temp = (NO*)malloc(sizeof(NO));
      temp = L->primeiro;

      while(temp->prox != NULL) {
        printf("Coordenada X = [%.2f]\n Coordenada Y = [%.2f]\n", temp->x,temp->y);
        temp = temp->prox;
      }

}
 }

/*------------------------FUNÇÕES DE INICIALIZAÇÃO---------------------*/
void inicializa_Tela(int w, int h, int x, int y, char nome_janela[]){

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(x,y);
    glutCreateWindow(nome_janela);
    glClearColor(255,255,255,255);
    glClear(GL_COLOR_BUFFER_BIT);
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


void rotaciona_Rato(float x, float y){
    float xlinha, ylinha,angulo_teta,x_r=0,y_r=0;
    xlinha = (x_r + (x - x_r)*cos(angulo_teta))- ((y - y_r)*sin(angulo_teta));
    ylinha = (y_r + (x - x_r)*sin(angulo_teta)) + ((y - y_r)*cos(angulo_teta));
}

void reflexao_Rato(){


}
void translada_Rato(){


}


void Escala_Rato(){



}
/*----------------------FUNÇÕES DE TEXTURA-----------------------------*/

void Textura(){


}
/*---------------------- FUNCOES DE INTERACAO---------------------------*/



void SpecialKeys (int key, int x, int y){
    switch (key){
        case GLUT_KEY_LEFT :
            /*faz o rato andar pra esquerda;*/
            break ;
        case GLUT_KEY_RIGHT :
           /*faz o rato andar pra direita;*/
            break ;
        default :
            break ;
        }
        glutPostRedisplay() ;
}


void keyboard (unsigned char key, int x, int y)
{
    switch(key)
    {
        case '+':
            /*faz com que o rato aumente seu tamanho*/
            break;
        case '-':
            /*faz com que o rato diminua seu tamanho*/
            break;
        default:
            break;

    }
    glutPostRedisplay();
}



void MouseInt (int botao, int estado, int x, int y)
{
    switch(botao)
    {
    case GLUT_LEFT_BUTTON:
        if(estado == GLUT_DOWN)
        {

            X = ((float)x/((float)w/2.0))-1.0;

            Y = (float) 1 - y/(h/2.0);

            InsereNO(listaQueijo,X,Y);

        }
        break;
    }
    glutPostRedisplay();
}

/*---------------------- FUNCOES DE DESENHO---------------------------*/

void desenha_Queijo(){

    cor_Corrente("ouro");
    glPointSize(20.0);
    glBegin(GL_POINTS);
        glVertex2f(X, Y);
    glEnd();
    glFlush();
}
void desenha_Rato(){

    int i;
    float angulo,x,y;

    cor_Corrente("preto");
/*
    /*desenha corpo*/
    glBegin(GL_POLYGON);

        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.22*cos(angulo);
            y=0.22*sin(angulo);

            glVertex2f(x,y);

        }

    glEnd();

    /*desenha cabeça*/

    glBegin(GL_POLYGON);
        cor_Corrente("preto");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.15*cos(angulo);
            y=0.17*sin(angulo);
            glVertex2f(x,y-0.17);
        }

    glEnd();

    /*desenha orelha esquerda*/

    glBegin(GL_POLYGON);

        cor_Corrente("cinza ardosia escuro");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.1*cos(angulo);
            y=0.1*sin(angulo);
            glVertex2f(x-0.1,y-0.1);
        }


        cor_Corrente("salmao claro");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.07*cos(angulo);
            y=0.07*sin(angulo);
            glVertex2f(x-0.1,y-0.12);
        }
    glEnd();

    /*desenha orelha direita*/

    glBegin(GL_POLYGON);
        cor_Corrente("cinza ardosia escuro");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.1*cos(angulo);
            y=0.1*sin(angulo);
            glVertex2f(x+0.13,y-0.1);
        }
        cor_Corrente("salmao claro");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.07*cos(angulo);
            y=0.07*sin(angulo);
            glVertex2f(x+0.13,y-0.12);
        }

    glEnd();

    /*desenha nariz*/

    glBegin(GL_POLYGON);
        cor_Corrente("salmao");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.025*cos(angulo);
            y=0.025*sin(angulo);
            glVertex2f(x,y-0.32);
        }

    glEnd();
    /*desenha olho direito*/

    glBegin(GL_POLYGON);
        cor_Corrente("branco");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.025*cos(angulo);
            y=0.025*sin(angulo);
            glVertex2f(x+0.09,y-0.22);
        }
        cor_Corrente("preto");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.015*cos(angulo);
            y=0.015*sin(angulo);
            glVertex2f(x+0.085,y-0.212);
        }

    glEnd();
    /*desenha olho esquerdoa*/

    glBegin(GL_POLYGON);
        cor_Corrente("branco");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.025*cos(angulo);
            y=0.025*sin(angulo);
            glVertex2f(x-0.09,y-0.22);
        }
        cor_Corrente("preto");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.015*cos(angulo);
            y=0.015*sin(angulo);
            glVertex2f(x-0.085,y-0.212);
        }

    glEnd();

    /*desenha rabo */
    cor_Corrente("preto");

    glLineWidth(5.0);
    float P0X=0,P0Y=0.2,
    P1X=-0.3,P1Y=0.4,
    P2X=0.3,P2Y=0.4,
    P3X=0,P3Y=0.6,t;

    glBegin(GL_LINE_STRIP);

        for (t=0; t<=1 ;t=t+0.01){

            /*Curva de Bezier*/

            y =(pow((1-t),3) * P0Y) +(3 * t * pow((1-t),2)*P1Y) + (3 * pow(t,2)* (1-t)*P2Y) + (pow(t,3)*P3Y);
            x =(pow((1-t),3) * P0X) +(3 * t * pow((1-t),2)*P1X) + (3 * pow(t,2)* (1-t)*P2X) + (pow(t,3)*P3X);

            glVertex2f(x,y);    

        }
    
    glEnd();

    glFlush();

}

int main(int argc, char *argv[]){

    glutInit (&argc,argv);

    listaQueijo = (LDE*) malloc(sizeof(LDE));;
    InicializaLista(listaQueijo);
    inicializa_Tela(500,500,300,100,"RUN MOUSE");
    glutDisplayFunc(desenha_Rato);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(MouseInt);
    glutMainLoop();
    free(listaQueijo);

return 0;
}
