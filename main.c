/*------------------------DESCRICAO---------------------------------
Computacao Grafica
Nome: Ellen Priscila Borges Oliveira
RA: 69554

O programa desenha um ratinho bidimensional animado na tela,o qual persegue
pedaços de queijo que aparecem de acordo com o clique do mouse.
Ao se aproximar do queijo, ele some da tela.

*/

#include<stdio.h>
#include<stdlib.h>
#include <math.h>

#include <GL/glut.h>

/*------------------------CONSTANTES-------------------------------*/
#define PI 3.141592654

/*------------------------VARIAVEIS--------------------------------*/
GLfloat x_Queijo = 0, y_Queijo = 0;
GLfloat altura_Janela = 500, largura_Janela = 500;
GLfloat x_Janela=200, y_Janela=200;
GLfloat X_Centro_Rato = 0.00,Y_Centro_Rato = 0.00;
GLfloat Raio_Rato = 1.0;
GLfloat xt = 0, yt = 0, sx = 1 , sy = 1;



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

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(largura_Janela,altura_Janela);
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
    /*
    GLfloat x0, GLfloat y0, GLfloat angulo_teta
    GLfloat x_linha, y_linha,x_r=0,y_r=0;

    x_linha = (x0 - x_r)*cos(angulo_teta)- ((y0 - y_r)*sin(angulo_teta));
    y_linha = (x0 - x_r)*sin(angulo_teta) + ((y0 - y_r)*cos(angulo_teta));*/



}

void translada_Rato(GLfloat deltay, GLfloat deltax){
    xt+=deltax;
    yt+=deltay;
}

void Escala_Rato(GLfloat deltasx, GLfloat deltasy){
    sx+=deltasx;
    sy+=deltasy;
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
             Escala_Rato(0.15,0.15);

            break;
        case '-':
            /*faz com que o rato diminua seu tamanho*/
             Escala_Rato(-0.15,-0.15);
            break;
        case 'r':
                
           // rotaciona_Rato();
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

void desenha(GLfloat x_Queijo_atual, GLfloat y_Queijo_atual){

/*-----------------------Desenha Queijo-----------------------*/

    cor_Corrente("ouro");
    glPointSize(20.0);
    glBegin(GL_POINTS);
        glVertex2f(x_Queijo_atual,y_Queijo_atual);

    glEnd();

/*------------------------Desenha Rato------------------------*/
//}
//void desenha_Rato(){



    GLint i;
    GLfloat x,y;
    GLfloat angulo= 0;
    cor_Corrente("preto");

    /*desenha corpo*/
    glBegin(GL_POLYGON);
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.22*cos(angulo);
            y=0.22*sin(angulo);

            glVertex2f((x+xt)*sx,(y+yt)*sy);
        }
    glEnd();

    /*desenha cabeça*/

    glBegin(GL_POLYGON);
        cor_Corrente("preto");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.15*cos(angulo);
            y=0.17*sin(angulo)-0.17;
            glVertex2f((x+xt)*sx,(y+yt)*sy);
        }

    glEnd();

    /*desenha orelha esquerda*/

    glBegin(GL_POLYGON);

        cor_Corrente("cinza ardosia escuro");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.1*cos(angulo)-0.1;
            y=0.1*sin(angulo)-0.1;
            glVertex2f((x+xt)*sx,(y+yt)*sy);
        }
    glEnd();

    glBegin(GL_POLYGON);

        cor_Corrente("salmao claro");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.07*cos(angulo)-0.1;
            y=0.07*sin(angulo)-0.12;
            glVertex2f((x+xt)*sx,(y+yt)*sy);
        }
    glEnd();

    /*desenha orelha direita*/

    glBegin(GL_POLYGON);
        cor_Corrente("cinza ardosia escuro");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.1*cos(angulo)+0.13;
            y=0.1*sin(angulo)-0.1;
            glVertex2f((x+xt)*sx,(y+yt)*sy);
        }

    glEnd();
        glBegin(GL_POLYGON);
        cor_Corrente("salmao claro");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.07*cos(angulo)+0.13;
            y=0.07*sin(angulo)-0.12;
            glVertex2f((x+xt)*sx,(y+yt)*sy);
        }

    glEnd();

    /*desenha nariz*/

    glBegin(GL_POLYGON);
        cor_Corrente("salmao");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.025*cos(angulo);
            y=0.025*sin(angulo)-0.32;
            glVertex2f((x+xt)*sx,(y+yt)*sy);
        }

    glEnd();
    /*desenha olho direito*/

    glBegin(GL_POLYGON);
        cor_Corrente("branco");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.025*cos(angulo)+0.09;
            y=0.025*sin(angulo)-0.22;
            glVertex2f((x+xt)*sx,(y+yt)*sy);
        }
        cor_Corrente("preto");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.015*cos(angulo)+0.085;
            y=0.015*sin(angulo)-0.212;
            glVertex2f((x+xt)*sx,(y+yt)*sy);
        }

    glEnd();
    /*desenha olho esquerdoa*/

    glBegin(GL_POLYGON);
        cor_Corrente("branco");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.025*cos(angulo)-0.09;
            y=0.025*sin(angulo)-0.22;
            glVertex2f((x+xt)*sx,(y+yt)*sy);
        }
        cor_Corrente("preto");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.015*cos(angulo)-0.085;
            y=0.015*sin(angulo)-0.212;
            glVertex2f((x+xt)*sx,(y+yt)*sy);
        }

    glEnd();

    /*desenha bigode*/
    glLineWidth(1.0);
    glBegin(GL_LINES);
        cor_Corrente("preto");

        /* bigode esquerdo*/
        x = -0.12; y = -0.25; glVertex2f((x+xt)*sx,(y+yt)*sy);
        x = -0.22; y = -0.22; glVertex2f((x+xt)*sx,(y+yt)*sy);
        x = -0.12; y = -0.27; glVertex2f((x+xt)*sx,(y+yt)*sy);
        x = -0.24; y = -0.27; glVertex2f((x+xt)*sx,(y+yt)*sy);
        x = -0.11; y = -0.28; glVertex2f((x+xt)*sx,(y+yt)*sy);
        x = -0.22; y = -0.31; glVertex2f((x+xt)*sx,(y+yt)*sy);

        /* bigode direito*/
        x = 0.12; y = -0.25; glVertex2f((x+xt)*sx,(y+yt)*sy);
        x = 0.22; y = -0.22; glVertex2f((x+xt)*sx,(y+yt)*sy);
        x = 0.12; y = -0.27; glVertex2f((x+xt)*sx,(y+yt)*sy);
        x = 0.24; y = -0.27; glVertex2f((x+xt)*sx,(y+yt)*sy);
        x = 0.11; y = -0.28; glVertex2f((x+xt)*sx,(y+yt)*sy);
        x = 0.22; y = -0.31; glVertex2f((x+xt)*sx,(y+yt)*sy);

    glEnd();

    /*desenha rabo */
    cor_Corrente("preto");

    glLineWidth(5.0);
    GLfloat P0X=0,P0Y=0.2,P1X=-0.3,P1Y=0.4,P2X=0.3,P2Y=0.4,P3X=0,P3Y=0.6,t;

    glBegin(GL_LINE_STRIP);

        for (t=0; t<=1 ;t=t+0.01){

            /*Curva de Bezier*/

            y =(pow((1-t),3) * P0Y) +(3 * t * pow((1-t),2)*P1Y) + (3 * pow(t,2)* (1-t)*P2Y) + (pow(t,3)*P3Y);
            x =(pow((1-t),3) * P0X) +(3 * t * pow((1-t),2)*P1X) + (3 * pow(t,2)* (1-t)*P2X) + (pow(t,3)*P3X);

            glVertex2f((x+xt)*sx,(y+yt)*sy);

        }

    glEnd();

    /*define o do rato */
    X_Centro_Rato = X_Centro_Rato +xt;
    Y_Centro_Rato = Y_Centro_Rato +yt;

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

                glScalef(1.5f, 0.5f, 1.0f);
            //enquanto o rato nao chegar no queijo (definir distancia entre dois pontos)

            //se chegou no queijo-> remove queijo da lista

       }
    }


}
void tamanho_Janela(GLsizei h, GLsizei w){

}

void Display(){

    glClearColor(255,255,255,255);
    glClear(GL_COLOR_BUFFER_BIT);
/*
    while(listaQueijo->tamanho>0){
            NO* p ;
            for (p = listaQueijo->primeiro; p != NULL; p = p->prox)

               printf("\n %d %d",p->x,p->y);

    }*/
    desenha(x_Queijo,y_Queijo);



}

int main(int argc, char *argv[]){

    glutInit (&argc,argv);
    listaQueijo = (LDE*) malloc(sizeof(LDE));
    InicializaLista(listaQueijo);
    inicializa_Tela("RUN MOUSE");
    glutDisplayFunc(Display);

    //glutReshapeFunc(tamanho_Janela);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialKeys);
    glutMouseFunc(MouseInt);

    glutMainLoop();
    free(listaQueijo);

return 0;
}
