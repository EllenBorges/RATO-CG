#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#define PI 3.141592654
#include <GL/glut.h>

/*------------------Variaveis Globais------------------------------*/
float X = 0, Y = 0, w = 500, h = 500;
int tamanho = 25;

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
        glColor3f(255,255,255);
    else if(strcmp (nome_cor, "preto") == 0)
        glColor3f(0,0,0);
    else if(strcmp (nome_cor, "vermelho") == 0)
        glColor3f(255,0,0);
    else if(strcmp (nome_cor, "azul") == 0)
        glColor3f(0,0,255);
    else if(strcmp (nome_cor, "verde") == 0)
        glColor3f(0,255,0);
    else if(strcmp (nome_cor, "amarelo") == 0)
        glColor3f(255,255,0);
    else if(strcmp (nome_cor, "magenta") == 0)
        glColor3f(255,0,255);
    else if(strcmp (nome_cor, "ciano") == 0)
        glColor3f(0,255,255);



}


/*---------------------- FUNCOES DE TRANSFORMAÇÃO---------------------------*/


void rotaciona_Rato(){

}

void reflexao_Rato(){

}
void translada_Rato(){

}


void Escala_Rato(){



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

    cor_Corrente("amarelo");
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

    /*desenha corpo */
    glBegin(GL_POLYGON);

        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.1*cos(angulo);
            y=0.2*sin(angulo);
            glVertex2f(x,y);
        }
    glEnd();

    /*desenha cabeça */

    glBegin(GL_POLYGON);


    glEnd();

    /*desenha rabo */

    glBegin(GL_POLYGON);


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


return 0;
}
