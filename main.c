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
GLfloat x_novoQueijo, y_novoQueijo;


GLfloat altura_Janela, largura_Janela ;
GLfloat x_Janela=100, y_Janela=100;
GLfloat X_Centro_Rato = 0.0000,Y_Centro_Rato = 0.0000;

GLfloat xt = 0.00, yt = 0.000, sx = 1 , sy = 1,xp,yp;
GLfloat teta = 0,ang = 0;
GLfloat pxt= 0.00,pyt=0.00;

GLint cont = 0;


/*------------------ESTRUTURA DA LISTA-----------------------------*/
typedef struct no_lista{
  float x, y;
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

/*insere um novo no no final da lista*/
void InsereNO(LDE *L, float x,float y){

    NO *novo = (NO*)malloc(sizeof(NO));
    novo->prox = NULL;
    novo->x = x;
    novo->y = y;
    if(L->primeiro==NULL && L->ultimo==NULL){
        L->primeiro = novo;
        L->ultimo = novo;
        L->tamanho++;
    }
    else{

        L->ultimo->prox = novo;
        L->ultimo = novo;
        L->ultimo->prox = NULL;
        L->tamanho++;
    }

}

void RemoveNO(){

    if(listaQueijo!=NULL){ /*se a lista nao esta vazia*/
	    NO* temp = listaQueijo->primeiro;
        free(listaQueijo->primeiro);
            /*remove começo*/
        listaQueijo->primeiro = temp->prox;
        listaQueijo->tamanho--;

         if (listaQueijo->primeiro == NULL)
            listaQueijo->ultimo = NULL;


    }


}



void lst_imprime (NO* lst){
    NO* p;

    for (p = lst; p != NULL; p = p->prox)
        printf("X_Queijo = [%.2f] \n Y_Queijo = [%.2f] \n", p->x, p->y);


}

void Imprime_ListaQueijo(){
    if(listaQueijo!=NULL && listaQueijo->tamanho>0)
        lst_imprime(listaQueijo->primeiro);
}








/*------------------------FUNÇÕES DE INICIALIZAÇÃO---------------------*/
void inicializa_Tela(char nome_janela[]){

    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
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

void translada_Rato(GLfloat deltax, GLfloat deltay){
    xt=xt+deltax;
    yt=yt+deltay;
}

void escala_Rato_Diminui(GLfloat deltasx, GLfloat deltasy){

    if(sx>=0 || sy>=0){


        sx+=deltasx;
        sy+=deltasy;

    }
}

void escala_Rato_Aumenta(GLfloat deltasx, GLfloat deltasy){
     //modificar condição de parada
    if(sx<=3 && sy<=3){

        sx+=deltasx;
        sy+=deltasy;

    }


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

/*---------------------- FUNCOES DE DESENHO---------------------------*/
void desenha_Queijo(){
/*-----------------------Desenha Queijo-----------------------*/

    if(cont>0){
        cor_Corrente("ouro");
        glPointSize(20.0);
        glBegin(GL_POINTS);
            glVertex2f(x_novoQueijo,y_novoQueijo);
        glEnd();
    }


}

void desenha_Rato(){


/*----------------------Variaveis locais-----------------------*/
    GLint i;
    GLfloat x,y;
    GLfloat angulo = 0;
    GLfloat P0X=0,P0Y=0.2,P1X=-0.3,P1Y=0.4,P2X=0.3,P2Y=0.4,P3X=0,P3Y=0.6,t,xpp,ypp;

/*------------------------Desenha Rato------------------------*/

    X_Centro_Rato = xt;
    Y_Centro_Rato = yt;
    /*desenha corpo*/

    glBegin(GL_POLYGON);
        cor_Corrente("preto");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.22*cos(angulo);
            y=0.22*sin(angulo);
            xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
            yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
            glVertex2f(xp+xt,yp+yt);
            /*define coordenadas do Rato */
        }
    glEnd();



    /*desenha cabeça*/
    glBegin(GL_POLYGON);
        cor_Corrente("preto");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.15*cos(angulo);
            y=0.17*sin(angulo)-0.17;
           xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
            yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
            glVertex2f(xp+xt,yp+yt);
        }
    glEnd();

    /*desenha orelha esquerda*/
    glBegin(GL_POLYGON);
        cor_Corrente("cinza ardosia escuro");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.1*cos(angulo)-0.1;
            y=0.1*sin(angulo)-0.1;
            xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
            yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
            glVertex2f(xp+xt,yp+yt);
        }
    glEnd();

    glBegin(GL_POLYGON);
        cor_Corrente("salmao claro");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.07*cos(angulo)-0.1;
            y=0.07*sin(angulo)-0.12;
            xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
            yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
            glVertex2f(xp+xt,yp+yt);
        }
    glEnd();

    /*desenha orelha direita*/
    glBegin(GL_POLYGON);
        cor_Corrente("cinza ardosia escuro");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.1*cos(angulo)+0.13;
            y=0.1*sin(angulo)-0.1;
           xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
            yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
            glVertex2f(xp+xt,yp+yt);
        }
    glEnd();
        glBegin(GL_POLYGON);
        cor_Corrente("salmao claro");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.07*cos(angulo)+0.13;
            y=0.07*sin(angulo)-0.12;
           xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
            yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
            glVertex2f(xp+xt,yp+yt);
        }
    glEnd();

    /*desenha nariz*/
    glBegin(GL_POLYGON);
        cor_Corrente("salmao");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.025*cos(angulo);
            y=0.025*sin(angulo)-0.32;
           xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
            yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
            glVertex2f(xp+xt,yp+yt);
        }
    glEnd();

    /*desenha olho direito*/
    glBegin(GL_POLYGON);
        cor_Corrente("branco");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.025*cos(angulo)+0.09;
            y=0.025*sin(angulo)-0.22;
            xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
            yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
            glVertex2f(xp+xt,yp+yt);
        }
        cor_Corrente("preto");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.015*cos(angulo)+0.085;
            y=0.015*sin(angulo)-0.212;
            xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
            yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
            glVertex2f(xp+xt,yp+yt);
        }
    glEnd();

    /*desenha olho esquerdoa*/
    glBegin(GL_POLYGON);
        cor_Corrente("branco");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.025*cos(angulo)-0.09;
            y=0.025*sin(angulo)-0.22;
            xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
            yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
            glVertex2f(xp+xt,yp+yt);
        }
        cor_Corrente("preto");
        for (i=0; i<=50 ;i++){
            angulo = 2 * PI * i / 50.0;
            x=0.015*cos(angulo)-0.085;
            y=0.015*sin(angulo)-0.212;
            xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
            yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
            glVertex2f(xp+xt,yp+yt);
        }
    glEnd();

    /*desenha bigode*/
    glLineWidth(1.0);
    glBegin(GL_LINES);
        cor_Corrente("preto");

        /* bigode esquerdo*/
        x = -0.12; y = -0.25;
        xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
        yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
        glVertex2f(xp+xt,yp+yt);

        x = -0.22; y = -0.22;
        xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
        yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
        glVertex2f(xp+xt,yp+yt);

        x = -0.12; y = -0.27;
        xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
        yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
        glVertex2f(xp+xt,yp+yt);

        x = -0.24; y = -0.27;
       xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
        yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
        glVertex2f(xp+xt,yp+yt);

        x = -0.11; y = -0.28;
       xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
        yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
        glVertex2f(xp+xt,yp+yt);

        x = -0.22; y = -0.31;
        xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
        yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
        glVertex2f(xp+xt,yp+yt);
        /* bigode direito*/
        x = 0.12; y = -0.25;
        xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
        yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
        glVertex2f(xp+xt,yp+yt);

        x = 0.22; y = -0.22;
        xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
        yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
        glVertex2f(xp+xt,yp+yt);

        x = 0.12; y = -0.27;
        xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
        yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
        glVertex2f(xp+xt,yp+yt);

        x = 0.24; y = -0.27;
        xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
        yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
        glVertex2f(xp+xt,yp+yt);

        x = 0.11; y = -0.28;
       xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
        yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
        glVertex2f(xp+xt,yp+yt);

        x = 0.22; y = -0.31;
        xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
        yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
        glVertex2f(xp+xt,yp+yt);
    glEnd();


    /*desenha rabo */
    glLineWidth(5.0);
    glBegin(GL_LINE_STRIP);
        for (t=0; t<=1 ;t=t+0.01){
            cor_Corrente("preto");
            /*Curva de Bezier*/
            y =(pow((1-t),3) * P0Y) +(3 * t * pow((1-t),2)*P1Y) + (3 * pow(t,2)* (1-t)*P2Y) + (pow(t,3)*P3Y);
            x =(pow((1-t),3) * P0X) +(3 * t * pow((1-t),2)*P1X) + (3 * pow(t,2)* (1-t)*P2X) + (pow(t,3)*P3X);
            xp = ((x*sx)*cos(teta))-((y*sy)*sin(teta));
            yp = ((x*sx)*sin(teta))+((y*sy)*cos(teta));
            glVertex2f(xp+xt,yp+yt);
        }
    glEnd();




}

void desenha(){
    glClearColor(255,255,255,255);
    glClear(GL_COLOR_BUFFER_BIT);

    desenha_Queijo();
    desenha_Rato();

    glFlush();

}
/*------------------FUNÇÕES DE MOVIMENTACAO DO RATO----------------------*/



void controla_Rato(){

/* rotacao*/
/*
    GLfloat px,py,qx,qy, normaq = 1, normap=1;
    ang =0;
    px = X_Nariz_Rato-X_Centro_Rato;
    py = Y_Nariz_Rato-Y_Centro_Rato;

    qx = x_novoQueijo-X_Centro_Rato;
    qy = y_novoQueijo-Y_Centro_Rato;

    normap = sqrt(pow(px,2)+pow(py,2));
    normaq = sqrt(pow(qx,2)+pow(qy,2));
    if((px*qx)+(py*qy)==0)
       ang = PI/2;

    if(normap>0.0000 && normaq>0.0000)
        ang = acosf((px*qx)+(py*qy)/(normap*normaq));
    printf("\n ang %.2f",ang);

*/
/*translacao*/

    GLfloat i;

        if(listaQueijo!=NULL){

            NO *tmp = listaQueijo->primeiro;

            while(tmp!=NULL){
                pxt = tmp->x ;
                pyt = tmp->y ;
                printf("\ntmp x %.3f tmp y %.3f\n",tmp->x,tmp->y);
                printf("\npxt x %.3f pyt y %.3f\n",pxt,pyt);

                for(i=0; i<20;i++){
                    xt+=pxt/20;
                    yt+=pyt/20;
                    desenha();
                    usleep(100*50);
                    glFlush();
                }
                Imprime_ListaQueijo();
                xt=pxt;
                yt=pyt;
                tmp=tmp->prox;

                RemoveNO();

            }
    }

}



/*---------------------- FUNCOES DE INTERACAO---------------------------*/

void SpecialKeys (int key, int x, int y){
    switch (key){
        case GLUT_KEY_UP:
            translada_Rato(0,0.09);
            break;
        case GLUT_KEY_DOWN:
            translada_Rato(0,(-0.09));
            break;

        case GLUT_KEY_LEFT :
            translada_Rato((-0.09),0);
            break ;
        case GLUT_KEY_RIGHT :
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
            cont++;
            x_novoQueijo = ((float)x/((float)largura_Janela/2.0))-1.0;

            y_novoQueijo = (float) 1 -(float) y/(altura_Janela/2.0);

            InsereNO(listaQueijo,x_novoQueijo,y_novoQueijo);
            printf("\nTentando inserir queijo na posicao (%.3f,%.3f)\n",x_novoQueijo,y_novoQueijo);

            controla_Rato();
            printf("\n xt %.3f yt %.3f \n",xt,yt);

        }
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[]){

    glutInit (&argc,argv);
    listaQueijo = (LDE*) malloc(sizeof(LDE));
    InicializaLista(listaQueijo);
    inicializa_Tela("RUN MOUSE");
    glutDisplayFunc(desenha);

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialKeys);
    glutMouseFunc(MouseInt);

    glutMainLoop();
    free(listaQueijo);

return 0;
}
