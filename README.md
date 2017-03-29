# RATO-CG

Faça um programa que crie um ratinho bidimensional animado na tela. O ratinho deverá
apresentar apenas movimentos bidimensionais. Crie seu ratinho utilizando as primitivas
vistas em aula, como retângulos, triângulos, polígonos, círculos e retas. Não é
necessário que ele possua qualquer textura, a menos que você queira criar desenhos que
lembrem texturas (isso poderá valorizar seu trabalho). Crie um modelo que lembre bem
um ratinho. O programa deverá fazer o ratinho perseguir um pedaço de queijo que
aparecerá na posição em que o usuário clicar o botão esquerdo do mouse. Dessa forma,
o usuário poderá dar cliques em várias posições diferentes e o rato deverá perseguir
cada pedaço de queijo na ordem em que os pedaços aparecerem na janela, sendo que
toda vez que o rato encostar no queijo (ou chegar muito próximo), aquele pedaço não
deverá mais ser desenhado, ou seja, sumirá da janela. Não há limites para a quantidade
de queijos que podem aparecer na tela. Assim, você deverá usar o conceito de fila de
estruturas de dados para controlar os pedaços de queijo que deverão ou não serem
desenhados.
Inicialmente deverá aparecer apenas um ratinho parado no centro da janela e ele
só se movimentará quando um queijo aparecer. Ele só deverá parar quando não houver
mais queijo na janela. O rato deverá sempre caçar de frente, ou seja, com a cabeça
voltada para o queijo (lembre-se de que ele não come pelas costas e nem anda de
costas). O rato nunca deverá sair da janela (nenhuma parte dele). Ele deverá virar
suavemente toda vez que tiver que mudar de direção (girar sem sair do lugar). Não é
necessário implementar o movimento das patinhas do rato. As teclas ‘+’ e ‘-’ serão
usadas, respectivamente, para aumentar e diminuir o tamanho do rato. Limitar o
tamanho máximo e mínimo permitido de forma que o rato nunca ultrapasse o tamanho
da janela e nem desapareça. Você deverá implementar todas as transformações
geométricas que usar (tudo bidimensional), ou seja, NÃO é permitido o uso das
funções de transformação geométrica predefinidas no OpenGL, como glTranslate,
glRotate e glScale.
O modelo do ratinho será importante na avaliação, mas mais importante será a
corretude na implementação das transformações geométricas utilizadas. Você deverá
usar pelo menos translação, rotação e escala.
