#include <stdio.h>
        #include <stdlib.h>
        #define TAMANHO 10
        #ifdef _WIN32
            #include <conio.h>
        #endif
        #include<time.h> //nescessario para gerar numeros aleatorios  
        #define MAX_MOBS2 6 //nescessario para o array dos mobs

        // FunÃ§Ã£o para limpar a tela de forma cross-platform
        void limparTela() { //define uma funÃ§Ã£o que nao retorna nenhum valor e serve para limpar o terminal
            #ifdef _WIN32 //compilador verifica qual sistema Ã© rodado o jogo/ windows ou linux
                system("cls");
            #else
                system("clear"); //para linux(para mim)
            #endif
        }
        char lerComando(){
            #ifdef _WIN32
                return _getch();
            #else
                        system("stty -echo -icanon"); //coloca o terminal em modo "raw" - responde de forma instantanea
                char c = getchar(); //le na hora sem enter, definido como variavel c
                system("stty echo icanon"); //restaura o terminal ao normal
                return c;
            #endif
        }



        // FunÃ§Ã£o para pausar a tela antes de limpar novamente
        void esperarJogador() {
            printf("\nPressione [Enter] para continuar..."); //mensagem para saber que o jogo congelou, \n pula uma linha antes para mostrar o texto
            getchar(); // Captura o caractere pendente do buffer
            getchar(); // Aguarda o jogador pressionar Enter
            //getchar serve para retornar o Enter
        }
        //PARTE DO MENU DO JOGO
        void exibirMenu() {
            limparTela(); //chama a funÃ§Ã£o para que o menu apareÃ§a sozinho
            printf("|=========================================|\n");
            printf("|          DUNGEON CRAWLER                |\n");
            printf("|=========================================|\n");
            printf("  [1] Jogar\n");
            printf("  [2] Tutorial\n");
            printf("  [3] Sair \n");
            printf("|=========================================|\n");
            printf("Escolha uma opcao: ");
        }


        void jogo(); //FUNÃ‡ÃƒO DO JOGO, que ta na linha 91

        int main() {
            int opcao = 0; //chama a variavel opÃ§ao e inicializa com 0, vai guardar a opÃ§Ã£o do jogar ( 1 ou 2)
            // Semente para gerar nÃºmeros aleatÃ³rios baseados no relÃ³gio do PC
            srand(time(NULL));
            //o loop continuarÃ¡ rodando enquanto a opÃ§Ã£o do player for diferente de 2
            while (opcao != 3)
            {
                exibirMenu(); //puxa a funÃ§Ã£o exibir menu 
                
                // Verifica se a entrada Ã© um nÃºmero vÃ¡lido
                if (scanf("%d", &opcao) != 1) { //verifica para que o usuario nao digite algo diferente de 1, simplismente para nao dar erro
                    // Se o usuÃ¡rio digitar uma letra, limpa o buffer para nÃ£o entrar em loop infinito, pois letras ficam armazenadas no buffer caso contrario
                    while (getchar() != '\n');
                    opcao = 0; // ForÃ§a a cair no 'default'
                } 

                if(opcao == 1) {
                    limparTela();
                        limparTela();
                        printf("=========================================\n");
                        printf("          INICIANDO A AVENTURA           \n");
                        printf("=========================================\n");
                        printf("Voce acorda em uma vila pacata, mas com\n");
                        printf("rumores de uma masmorra terrivel por perto...\n");
                        // Aqui ficarÃ¡ a chamada para a funÃ§Ã£o da Vila/Jogo futuramente
                        esperarJogador();
                        jogo(); //puxa o jogo para dentro do int main :-||
                        
                }
                else if(opcao == 2){
                    limparTela();
                    printf("=========================================\n");
                    printf("                TUTORIAL                 \n");
                    printf("=========================================\n");

                    printf("SIMBOLOS:\n");
                    printf(" ^, v, <, > : Jogador \n");
                    printf(" X, Y : Monstros\n");
                    printf(" E : Escada/Portal para o proximo andar\n\n");

                    printf("CONTROLES:\n");
                    printf(" [W] Cima | [S] Baixo | [A] Esquerda | [D] Direita\n");
                    printf(" [I] Interagir | [O] Atacar\n");
                    printf(" [Q] Sair da partida\n");
                    printf("=========================================\n");
                    esperarJogador();
                    
                }       
            }
            return 0;
        }

        void jogo() {
            //posiÃ§Ãµes iniciais do player
            int playerX = 5; //posiÃ§Ã£o no x
            int playerY = 5; //posiÃ§Ã£o no y
            int mapa = 1; //comeÃ§a na vila
            int tamanho = 10; //tamanho da vila

            // O jogador comeÃ§a olhando para cima ('^') conforme as regras de sÃ­mbolos, =3
            char playerDir = '^'; 
            char comando = ' ';

            //variaveis monstruosas 
            int monstroX_vivo = 0; //cansei do monstrosativos, vamos usar X e Y mesmo e fodase
            int monstroY_vivo = 0;
            int monstroXx = 0; int monstroXy = 0;
            int monstroYx = 0; int monstroYy = 0;   

            int vida = 3;

            //area do ataque
            int dentrodaArea = 0; //tive q colocar aqui para fazer o print Z
            // ADICIONA ESSAS 3:
            int atkCentroX = -1; // centro do ataque pra renderizar Z
            int atkCentroY = -1;
            int atacou = 0;      // flag: player atacou no turno anterio
            int arma = 0; // 0 = Nenhuma, 1 = Espada, 2 = Cajado, 3 = Arco
            int npcX = 5, npcY = 2; // PosiÃ§Ã£o do Ferreiro na Vila

            // usam chaveX/chaveY/temChave/portaX/portaY/portaEstado mas elas nao existiam no codigo
            int chaveX = 2, chaveY = 2;
            int temChave = 0;
            int portaEstado = 0; // 0 = parede normal, 1 = porta D, 2 = escada L
            int portaX = 8, portaY = 5; // borda direita do mapa 10x10, linha do meio

            int tamanho2 = 10; //tamanho do segundo mapa papis

            //chaves do segundo andar
            int chave2aX = 2,  chave2aY = 2,  temChave2a = 0;
            int chave2bX = 12, chave2bY = 2,  temChave2b = 0;

            // portas do andar 2
            int porta2aX = 2,  porta2aY = 11, porta2aAberta = 0;
            int porta2bX = 12, porta2bY = 11, porta2bAberta = 0;
            
            // escada do andar 2
            int escada2X = 7, escada2Y = 12;
            int escadaVisivel = 0;

            // botÃ£o do andar 2 â€” pressionar com [I] invoca 3 monstros extras
            int botaoX = 7, botaoY = 4;
            int botaoPressionado = 0;

            // Ãndices: 0=A, 1=B, 2=C, 3=D, 4=E
            int mob_vivo[5] = {1, 1, 0, 0, 0}; // A e B comeÃ§am vivos (1). O resto dorme (0)
            int mob_X[5]    = {3, 11, 0, 0, 0}; // PosiÃ§Ã£o X inicial de cada um
            int mob_Y[5]    = {3, 3,  0, 0, 0}; // PosiÃ§Ã£o Y inicial de cada um

            int tamanho3 = 25; //mapa do terceiro andar

            // --- Monstros Tipo Y do Andar 3 (perseguidores) â€” 2 unidades ---
            int mobY3_vivo[2] = {1, 1};
            int mobY3_X[2]    = {8, 16};
            int mobY3_Y[2]    = {8, 8};

            // --- Boss Final ---
            int bossVivo = 1;
            int bossX = 12, bossY = 5; // perto do centro do mapa 25x25
            int bossFase = 1;           // Fase 1: normal; Fase 2: agressivo (hp <= metade)
            int bossHP = 6;             // Boss aguenta 6 hits
            int bossHPMax = 6;
 





            while (comando != 'q' && comando !='Q')
            {
                limparTela(); //novamente, funÃ§Ã£o de limpartela
                // reseta o Z apÃ³s um frame
                if(comando != 'o' && comando != 'O'){
                    atacou = 0;
                }

                char* nomeArma = "Desamardo"; //char* guardou uma sequencia de caracteres, bizuuu
                if(arma == 1){
                    nomeArma = "Espada"; 

                } else if(arma == 2){
                    nomeArma = "Cajado";
                } else if(arma == 3){
                    nomeArma = "Arco e Flecha";
                } //definindo qual arma vai aparecer

                if (mapa == 1) {
                    printf("=== VILA ===\n\n");
                }
                else if (mapa == 2){
                    printf("=== DUNGEON: ANDAR 1 ===\n\n");
                }
                else if (mapa == 3) {
                    printf("=== DUNGEON: ANDAR 2 ===\n\n");
                }

                // Tamanho do mapa atual
                int tam = (mapa == 1) ? tamanho : (mapa == 2) ? tamanho2 : (mapa == 3) ? 15 : tamanho3;
                //RenderizaÃ§ao do mapa, sendo uma matriz 10x10
                int y;
                for(y = 0; y < tam; y++){
                	int x;
                    for(x = 0; x < tam; x++){

                        //caso reconheÃ§a a posiÃ§ao atual do player, imprimir o playerDir = '^';
                        if(x == playerX && y == playerY){
                            printf("%c ", playerDir);
                        }
                        //caso os monstros estiverem ativos, desenham ele no mapa
                        else if (monstroX_vivo == 1 && x == monstroXx && y == monstroXy) {
                            printf("X "); // Desenha o Monstro 1
                        }
                        else if (monstroY_vivo== 1 && x == monstroYx && y == monstroYy) {
                            printf("Y "); // Desenha o Monstro 2
                        }
                        else if(mapa == 1 && x == npcX && y == npcY){
                            printf("N "); //Ferreiro
                        }
                        else if (mapa == 1 && x == 5 && y == 8){
                            printf("E ");//Caverna
                        } 
                        else if (atacou == 1 && (
                            (playerDir == '^' && y >= atkCentroY - 2 && y <= atkCentroY - 1 && x >= atkCentroX - 1 && x <= atkCentroX + 1) ||
                            (playerDir == 'v' && y >= atkCentroY + 1 && y <= atkCentroY + 2 && x >= atkCentroX - 1 && x <= atkCentroX + 1) ||
                            (playerDir == '<' && x >= atkCentroX - 2 && x <= atkCentroX - 1 && y >= atkCentroY - 1 && y <= atkCentroY + 1) ||
                            (playerDir == '>' && x >= atkCentroX + 1 && x <= atkCentroX + 2 && y >= atkCentroY - 1 && y <= atkCentroY + 1)
                        )){
                            printf("Z ");
                        }
                        
                        else if (temChave == 0 && x == chaveX && y == chaveY) { 
                            printf("@ "); //chave
                        }

                        // porta ou escada (sÃ³ aparece quando desbloqueada)
                        else if (mapa == 2 && x == portaX && y == portaY && portaEstado == 1){
                            printf("D ");
                        }
                        else if (mapa == 2 && x == portaX && y == portaY && portaEstado == 2){
                            printf("L ");   
                        }                        //se for a borda do mapa, desenha a parede
                        else if(x == 0 || x == tam - 1|| y == 0 || y == tam - 1 ){ //tamanho -1 pois o loop precisa ir de 0 a 9 :/ 
                            printf("* ");
                        }
                        // Verifica se tem algum mob do array nessa coordenada (Andar 2)
                        else if (mapa == 3 && 
                                ((mob_vivo[0] == 1 && x == mob_X[0] && y == mob_Y[0]) ||
                                (mob_vivo[1] == 1 && x == mob_X[1] && y == mob_Y[1]) ||
                                (mob_vivo[2] == 1 && x == mob_X[2] && y == mob_Y[2]) ||
                                (mob_vivo[3] == 1 && x == mob_X[3] && y == mob_Y[3]) ||
                                (mob_vivo[4] == 1 && x == mob_X[4] && y == mob_Y[4]))) {
                            printf("X ");
                        }
                        // === ADICIONADO: ReinÃ­cio no Andar do Boss ===
                        else if (mapa == 4) {
                            playerX = 12; playerY = 22; // Volta para a base do mapa
                            bossX = 12; bossY = 5;      // Reseta o Boss para o centro
                            bossHP = bossHPMax;         // Cura o Boss para recomeÃ§ar a luta
                            bossFase = 1;               // Remove o modo Enraivecido
                            // Reseta os ajudantes do Boss
                            mobY3_vivo[0] = 1; mobY3_vivo[1] = 1;
                            mobY3_X[0] = 8;  mobY3_Y[0] = 8;
                            mobY3_X[1] = 16; mobY3_Y[1] = 8;
                        }
                        
                            // render das portas do andar 2
                        else if (mapa == 3 && porta2aAberta == 0 && x == porta2aX && y == porta2aY){ 
                            printf("D "); 
                        }
                        else if (mapa == 3 && porta2bAberta == 0 && x == porta2bX && y == porta2bY){ 
                            printf("D "); 
                        }
                        // render das chaves do andar 2
                        else if (mapa == 2 && temChave == 0 && x == chaveX && y == chaveY) {
                            printf("@ ");
                        }
                        else if (mapa == 3 && temChave2b == 0 && x == chave2bX && y == chave2bY){ 
                            printf("@ "); 
                        }
                        else if (mapa == 3 && temChave2a == 0 && x == chave2aX && y == chave2aY){ 
                            printf("@ "); // <--- ADICIONA ESTA LINHA AQUI!
                        }
                                        // render da escada do andar 2
                        else if (mapa == 3 && escadaVisivel == 1 && x == escada2X && y == escada2Y){ 
                            printf("L "); 
                        }
                        // render do botao
                        else if (mapa == 3 && botaoPressionado == 0 && x == botaoX && y == botaoY){ 
                            printf("O "); 
                        }  
                        else if (mapa == 4 && bossVivo==1 && x==bossX && y==bossY){
                            printf("Z "); // Boss Final
                        }
                        else if (mapa == 4 &&
                                ((mobY3_vivo[0]==1 && x==mobY3_X[0] && y==mobY3_Y[0]) ||
                                 (mobY3_vivo[1]==1 && x==mobY3_X[1] && y==mobY3_Y[1]))) {
                            printf("Y "); // Tipo 2 perseguidor
                        }


                        //caso contrario, exibe o chao livre
                        else {
                            printf("  ");
                        }
                    }

                    printf("\n");
                }                            // apÃ³s mover, verifica se entrou no portal
                        if (mapa == 1 && playerX == 5 && playerY == 8) {
                            mapa = 2;
                            tamanho = 10;
                            playerX = 5; // posiÃ§Ã£o inicial na caverna
                            playerY = 5;
                        }
                if(mapa != 1){ //nao aponta as portas ainda
                            printf(" Vidas : %d | Arma : %s | Chave: %s", vida, nomeArma, temChave ? "Sim" : "Nao");
                }
                if(mapa == 4){
                    printf(" Vidas: %d | Arma: %s", vida, nomeArma);
                    if(bossVivo){
                        printf(" | BOSS HP: %d/%d", bossHP, bossHPMax);
                        if(bossFase == 2) printf(" [ENRAIVECIDO!]");
                    }
                }


            // LÃª a tecla pressionada pelo player
                comando = lerComando();
            //PARTE DA MOVIMENTAÃ‡ÃƒO DO JOGADOR
                int moveu = 0; //reconhece que o player se moveu no mapa (IMPORTANTE PARA OS MOBS)
                int morreu = 0; //flag pra saber q ele morreu, ne burrao 
                if (comando == 'w' || comando == 'W') {
                    playerDir = '^'; // Atualiza o sÃ­mbolo para olhar para cima
                    if (playerY > 1) {
                        playerY--;   // Move para cima se nÃ£o colidir com a parede, que esta na cordenada 1 em Y
                        moveu = 1;
                    }
                }
                else if (comando == 's' || comando == 'S') {
                    playerDir = 'v'; // Atualiza o sÃ­mbolo para olhar para baixo
                    if (playerY < tam - 2) { //tamanho -2 porque o jogador fica nas areas dentro da borda, ou seja, -2  
                        playerY++;   // Move para baixo se nÃ£o colidir com a parede, que esta na cordenada 9(TAMANHO -1) em Y
                        moveu = 1;
                    }
                }
                else if (comando == 'a' || comando == 'A') {
                    playerDir = '<'; // Atualiza o sÃ­mbolo para olhar para a esquerda
                    if (playerX > 1) {
                        playerX--;   // Move para a esquerda se nÃ£o colidir com a paredem que estÃ¡ na cordenada 1 em X
                        moveu = 1;
                    }
                }
                else if (comando == 'd' || comando == 'D') {
                    playerDir = '>'; // Atualiza o sÃ­mbolo para olhar para a direita
                    if (playerX < tam - 2) {
                        playerX++;   // Move para a direita se nÃ£o colidir com a parede, que estÃ¡ na cordenada 9(TAMANHO - 1) em x
                        moveu = 1;
                }    
                }
                if (mapa == 2 && temChave == 0 && playerX == chaveX && playerY == chaveY) {
                    temChave = 1;
                    portaEstado = 1;
                    limparTela();
                    printf("Voce pegou a chave! A porta se abriu em algum lugar...\n");
                    esperarJogador();
                }
                    // pegar chaves do andar 2
                if (mapa == 3 && temChave2a == 0 && playerX == chave2aX && playerY == chave2aY) {
                temChave2a = 1;
                limparTela();
                printf("Voce pegou a Chave 1! A porta se abriu em algum lugar...\n");
                esperarJogador();
                }
                if (mapa == 3 && temChave2b == 0 && playerX == chave2bX && playerY == chave2bY) {
                temChave2b = 1;
                limparTela();
                printf("Voce pegou a Chave 2! A porta se abriu em algum lugar...\n");
                esperarJogador();
            }
                        // botao do andar 2
                if (mapa == 3 && botaoPressionado == 0 && playerX == botaoX && playerY == botaoY) {
                    botaoPressionado = 1;
                    limparTela();
                    printf("*CLIQUE* Voce pressionou o botao! O chao treme...\n");
                    printf("Voce nao deveria ter feito isso...");
                    printf("3 novos monstros surgiram!\n");
                    esperarJogador();
                    mob_vivo[2] = 1; mob_X[2] = 2;  mob_Y[2] = 8;  // Monstro C
                    mob_vivo[3] = 1; mob_X[3] = 12; mob_Y[3] = 8;  // Monstro D
                    mob_vivo[4] = 1; mob_X[4] = 7;  mob_Y[4] = 9;  // Monstro E
                }
                            // porta A do andar 2
                if (mapa == 3 && temChave2a == 1 && porta2aAberta == 0 && playerX == porta2aX && playerY == porta2aY) {
                    porta2aAberta = 1;
                    limparTela();
                    printf("Voce abriu a porta!\n");
                    if(porta2bAberta == 1){ escadaVisivel = 1; printf("A escada apareceu no centro!\n"); }
                    esperarJogador();
                }
                // porta B do andar 2
                if (mapa == 3 && temChave2b == 1 && porta2bAberta == 0 && playerX == porta2bX && playerY == porta2bY) {
                    porta2bAberta = 1;
                    limparTela();
                    printf("Voce abriu a Porta !\n");
                    if(porta2aAberta == 1){ escadaVisivel = 1; printf("A escada apareceu no centro!\n"); }
                    esperarJogador();
                }
                // escada do andar 2
                if (mapa == 3 && escadaVisivel == 1 && playerX == escada2X && playerY == escada2Y) {
                    limparTela();
                    printf("Voce subiu a escada para o Andar 3!\n");
                    printf("Algo parece te esperar...\n");
                }
                // escada do andar 1 -> andar 2
                if (mapa == 2 && playerX == portaX && playerY == portaY && portaEstado == 2) {
                    limparTela();
                    printf("=========================================\n");
                    printf("  Voce desceu para o Andar 2!           \n");
                    printf("=========================================\n");
                    esperarJogador();
                    mapa = 3;
                    tamanho = 15;
                    playerX = 7; playerY = 12; // PosiÃ§Ã£o inicial no Andar 2
                    playerDir = '^';
                    moveu = 0;
                    continue; // Muito importante para resetar o loop pro novo mapa!
                }
                                // Escada Andar 2 -> Andar 3
                if (mapa==3 && escadaVisivel==1 && playerX==escada2X && playerY==escada2Y) {
                    limparTela();
                    printf("=========================================\n");
                    printf("  Voce desceu para o Andar 3!           \n");
                    printf("  Prepare-se... o Boss aguarda!         \n");
                    printf("=========================================\n");
                    esperarJogador();
                    mapa = 4;
                    tamanho = tamanho3; // tamanho do mapa 3
                    playerX = 12; playerY = 22; // base do mapa 25x25
                    playerDir = '^';
                    moveu = 0;
                    continue;
                }

            
                    if (comando == 'i' || comando == 'I') { //botao de interaÃ§Ã£o I ne papis 
                    if (mapa == 1 && playerX == npcX && playerY == npcY) { //compara o player estar no npc, se tiver em cima(O jeito q eu consegui fazer, sem perguntas) aperte I
                        limparTela();
                        if (arma == 0) { //reconhece que ta desarmado
                            printf("            FERREIRO DA VILA             \n");
                            printf("Hohoho! Olha o que temos aqui! Um novo aventureiro\n");
                            printf("Me parece que estÃ¡s de mÃ£os atadas meu minino, vamos resolver isso agora! ;D");
                            printf(" \n [1] Espada\n [2] Arco e Flecha\n [3] Cajado\n\n");
                            printf("Sua escolha: ");
                            // porta na dungeon
                            if (mapa == 2 && playerX == portaX && playerY == portaY && portaEstado == 1) {
                                portaEstado = 2; // porta vira escada
                                limparTela();
                                printf("Voce abriu a porta! Uma escada apareceu!\n");
                                esperarJogador();
                            }
                            // escada â€” transita de andar
                            if (mapa == 2 && playerX == portaX && playerY == portaY && portaEstado == 2) {
                                // aqui vai a transiÃ§Ã£o pro andar 2 futuramente
                                limparTela();
                                printf("Voce subiu a escada!\n");
                                esperarJogador();
                                break;
                            }
                            char escolha = '0'; //inicizaliza com 0, ou seja, desarmado
                            
                            while (escolha != '1' && escolha != '2' && escolha != '3'){
                                escolha = lerComando();

                            if(escolha == '1'){
                                arma = 1; //reconhece como a espada, guardando o resultado da arma
                                printf("\nUma Espada! Otima escolha!\n");
                            }
                            else if (escolha == '2'){
                                arma = 2; //reconhece como o arco, guardando o resultado do arco
                                printf("\nUm Arco e Flecha! Otima escolha!\n");
                            }
                            else if (escolha == '3'){
                                arma = 3; //reconhece com o cajado, guardando o resultado do cajado
                                printf("\nUm Cajado! Otima escolha!\n");
                            }
                            }
                            printf("\nAgora tome cuidado onde pisa minino! \n");
                            printf("Ouvi que tem monstros bizarros nessa masmorra! D:\n"); 
                            printf("Tome cuidado! Olhos sempre abertos! ;â€‘) "); //Arthur, olhos sempre abertos
                        } else {
                            printf("\nFerreiro: Ei! Voce ja tem uma arma! Va logo para a Masmorra!\n");
                        }
                        esperarJogador();
                    }
                    else if (mapa == 2 && playerX == portaX && playerY == portaY && portaEstado == 1) {
                        portaEstado = 2;
                        limparTela();
                        printf("Voce abriu a porta! Uma escada apareceu!\n");
                        esperarJogador();
                    }
                }

                //VerificaÃ§Ã£o de morte do player
                // Verifica colisÃ£o com os mobs do Andar 2
                int i;
                            for(i = 0; i < 5; i++) {
                                if(mapa == 3 && mob_vivo[i] == 1 && playerX == mob_X[i] && playerY == mob_Y[i]) {
                                    morreu = 1;
                                }
                            }
            
                // Isso fica DEPOIS do movimento. Se ele andou e pisou no [5,8] estando na Vila:
                if (mapa == 1 && playerX == 5 && playerY == 8) { //a partir do momento que ele entra na dungeon
                    mapa = 2;       // Muda o andar
                    tamanho = 10;    // Aumenta o mapa
                    playerX = 5;    // Joga o player pro meio do mapa novo
                    playerY = 5;
                    
                    // "Spawna" (Faz nascer) os monstros
                    monstroX_vivo = 1;
                    monstroY_vivo = 1;
                    monstroXx = 2;  monstroXy = 4;   // PosiÃ§Ã£o inicial do Monstro X
                    monstroYx = 8; monstroYy = 7;  // PosiÃ§Ã£o inicial do Monstro Y
                    
                    // ForÃ§a pular a vez dos monstros no turno que vocÃª entra na Dungeon
                    moveu = 0; 
                }
                if (moveu == 1 && monstroX_vivo == 1) {
                    // IA do Monstro X (AleatÃ³rio)
                    // IA do Monstro X (AleatÃ³rio)
                    int direcao = rand() % 4; //sorteia de 0, 1, 2 ou 3 

                    //pega o numero sorteado e faz uma aÃ§Ã£o baseada nisso
                    if (direcao == 0){
                        monstroXy--; //cima 
                    }    
                    else if (direcao == 1) {
                        monstroXy++;//baixo
                    }
                    else if (direcao == 2) {
                        monstroXx--;//esquerda
                    }
                    else if (direcao == 3) {
                        monstroXx++;//direita
                    }
                    if (monstroXx <= 0){
                        monstroXx = 1;  //caso o mob vÃ¡ para 0, forÃ§a a volta para a cordenada 1, fazendo com que ele possa voltar para o mapa, eu acho
                    }
                    if (monstroXx >= tamanho2 - 1){
                        monstroXx = tamanho2 - 2; //mesma coisa, se for para 9, ou seja, parede, forÃ§a a ida para 8
                    }
                    if (monstroXy <= 0){
                        monstroXy = 1;
                    }
                    if (monstroXy >= tamanho2 - 1){
                        monstroXy = tamanho2 - 2;
                    } 
                }
                    if(monstroY_vivo == 1){
                        if(mapa==2 && moveu==1 && mapa == 4){
                    // IA do Monstro Y (Perseguidor)
                    int distX = playerX - monstroYx; //calcula a distancia do jogador em X e Y
                    int distY = playerY - monstroYy;

                    if (distX < 0) distX = -distX; // transforma negativo em positivo manualmente
                    if (distY < 0) distY = -distY; //serve para calcular de forma certa, quantas "casas" de distancia o player ta

                    if (distX > distY) { //compara as duas distancias, sendo primeiro X maior que Y 
                        if (playerX > monstroYx) {
                            monstroYx++; //jogador estÃ¡ na direita, anda direita
                        }
                        else {
                            monstroYx--; //jogador estÃ¡ na esquerda, anda esquerda
                        }
                    } else {
                        if (playerY > monstroYy) { 
                            monstroYy++; //jogador estÃ¡ em baixo, anda pra baixo
                        }
                        else {
                            monstroYy--; //jogador estÃ¡ em cima, anda pra cima
                        }
                    }
                }
                }
                // IA de TODOS os monstros do andar 2 de uma vez sÃ³:
                
                for(i = 0; i < 5; i++) {
                    if (mapa == 3 && moveu == 1 && mob_vivo[i] == 1) {
                        int dir = rand() % 4;
                        if      (dir == 0) {
                            mob_Y[i]--;
                        }
                        else if (dir == 1) {
                            mob_Y[i]++;
                        }
                        else if (dir == 2) {
                            mob_X[i]--;
                        }
                        else               {
                            mob_X[i]++;
                        }
                        }
                }
                    // Boss â€” comportamento unico:
                    // Fase 1: persegue como Y, mas so se move a cada 2 turnos do player
                    // Fase 2 (HP <= metade): persegue E tenta dar um passo extra por turno
                    if(bossVivo && mapa == 4 && moveu == 1){
                        // Movimento principal: perseguidor
                        int distX=playerX-bossX; if(distX<0) distX=-distX;
                        int distY=playerY-bossY; if(distY<0) distY=-distY;
                        if(distX>distY){
                            if(playerX>bossX) bossX++; else bossX--;
                        } else {
                            if(playerY>bossY) bossY++; else bossY--;
                        }
                        // Fase 2: move um passo extra (mais rapido)
                        if(bossFase==2){
                            distX=playerX-bossX; if(distX<0) distX=-distX;
                            distY=playerY-bossY; if(distY<0) distY=-distY;
                            if(distX>distY){
                                if(playerX>bossX) bossX++; else bossX--;
                            } else {
                                if(playerY>bossY) bossY++; else bossY--;
                            }
                        }
                        // clamp
                        if(bossX<=0)          bossX=1;
                        if(bossX>=tamanho3-1) bossX=tamanho3-2;
                        if(bossY<=0)          bossY=1;
                        if(bossY>=tamanho3-1) bossY=tamanho3-2;
                    }

                if(comando == 'o' || comando == 'O'){        //ta aqui pq ta na mesma linha dos outros else ifs de comando( e pq eu esqueci)
                    if(arma > 0 && mapa != 1){
                        moveu = 1; //a partir do momento que se move
                        atacou = 1;
                        atkCentroX = playerX;
                        atkCentroY = playerY;
                        int matouX = 0; //a contagem dos bixos mortos, o X e o Y
                        int matouY = 0;

                        if(arma == 1){
                        	int dy;
                            for(dy = -2; dy<=2; dy++){ //dy e dx sao os deslocamentos do jogador ate a cordenada verificada 
                                int dx;
								for(dx = -2; dx <= 2; dx++){ //servem pra ver ate onde vai o ataque, basicamente
                                    //o for passa pelas cordenadas ao redor do jogador, ele sendo o 0,0 tlg
                                    int atkX = playerX + dx; //soma a area do player com o ataque, seja em dx ou dy
                                    int atkY = playerY + dy;

                                    dentrodaArea = 0; //filtra so as celulas validas, olhando para cima, ou pra baixo, ou pros lados AQUI PUXA APENAS O DENTRODAAREA PARA FAZER O Z APARECER PQP FIQUEI HORAS NISSO VAI TOMAR NO CU

                                    if (playerDir == '^' && dy >= -2 && dy <= -1 && dx >= -1 && dx <= 1){
                                        dentrodaArea = 1;
                                    }
                                    else if (playerDir == 'v' && dy >= 1 && dy <= 2 && dx >= -1 && dx <= 1) {
                                        dentrodaArea = 1;
                                    }
                                    else if (playerDir == '<' && dx >= -2 && dx <= -1 && dy >= -1 && dy <= 1) {
                                        dentrodaArea = 1;
                                    }
                                    else if (playerDir == '>' && dx >= 1 && dx <= 2 && dy >= -1 && dy <= 1) {
                                        dentrodaArea = 1;
                                    }

                                    if(dentrodaArea){ //se a cordenada esta dentro do ataque, verifica se tem monstro la
                                        if(monstroX_vivo && atkX == monstroXx && atkY == monstroXy) {
                                            matouX = 1;
                                        }
                                        if (monstroY_vivo && atkX == monstroYx && atkY == monstroYy) {
                                            matouY = 1; 
                                        }
                                        int i;
                                        for(i = 0; i < 5; i++){ //andar 2, eu acho
                                            if(mob_vivo[i] == 1 && atkX == mob_X[i] && atkY == mob_Y[i]){
                                            mob_vivo[i] = 0;
                                        }
                                        }
                                        // Andar 3 â€” mobs Y
                                        // IA mobs Y andar 3
 
                                                                         
                                        for(i=0;i<2;i++){
                                            if(mapa==4 && moveu==1 && mobY3_vivo[i]==1){
                                                int distX=playerX-mobY3_X[i]; if(distX<0) distX=-distX;
                                                int distY=playerY-mobY3_Y[i]; if(distY<0) distY=-distY;
                                                if(distX>distY){
                                                    if(playerX>mobY3_X[i]) mobY3_X[i]++; else mobY3_X[i]--;
                                                } else {
                                                    if(playerY>mobY3_Y[i]) mobY3_Y[i]++; else mobY3_Y[i]--;
                                                }                                       
                                            }
                                        // Boss
                                        if(bossVivo && atkX==bossX && atkY==bossY){
                                            bossHP--;
                                            if(bossHP<=0) {
                                                bossVivo=0;
                                            }
                                            else if(bossHP <= bossHPMax/2 && bossFase==1){
                                                bossFase=2;
                                                limparTela();
                                                printf("O Boss urra de raiva! Ele esta ENRAIVECIDO!\n");
                                                esperarJogador();
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                        else if(arma == 2){
                        	int dist;
                            for (dist = 1; dist <= 4; dist++) {//mema logica da espada, mas aqui usa a variavel da distancia linear do arco
                            int atkX = playerX;
                            int atkY = playerY;
                            // Joga o ataque para 1, 2, 3 e 4 casas Ã  frente, dependendo de onde olha
                            if (playerDir == '^') {
                                atkY = playerY - dist;
                            } 
                            else if (playerDir == 'v') {
                                atkY = playerY + dist;
                            } 
                            else if (playerDir == '<') {
                                atkX = playerX - dist;
                            } 
                            else if (playerDir == '>') {
                                atkX = playerX + dist;
                            }

                            // Checa se acertou alguÃ©m na trajetÃ³ria da flecha
                            if(monstroX_vivo == 1 && atkX == monstroXx && atkY == monstroXy) {
                                matouX = 1;
                            }
                            if (monstroY_vivo == 1 && atkX == monstroYx && atkY == monstroYy) {
                                matouY = 1; //contagem dos mortos, assasinados e multilados /:
                            }   
							int i;                        
                            for(i = 0; i < 5; i++){
                                if(mob_vivo[i] == 1 && atkX == mob_X[i] && atkY == mob_Y[i]){
                                    mob_vivo[i] = 0;
                                }
                            
                            }
                            if(bossVivo && atkX==bossX && atkY==bossY){
                                    bossHP--;
                                    if(bossHP<=0) {
                                        bossVivo=0;
                                    }
                                    else if(bossHP <= bossHPMax/2 && bossFase==1){
                                        bossFase=2;
                                        limparTela();
                                        printf("O Boss urra de raiva! Ele esta ENRAIVECIDO!\n");
                                        esperarJogador();
                                    }
                                }
                            }
                        }
                        else if(arma == 3){
                            // Faz um quadrado 3x3 ao redor do jogador
                            int dy;
                            for(dy = -1; dy <= 1; dy++) {
                            	int dx;
                                for (dx = -1; dx <= 1; dx++) {
                                    
                                    int atkX = playerX + dx;
                                    int atkY = playerY + dy;

                                    // Checa se a magia pegou em algum monstro ao redor
                                    if(monstroX_vivo == 1 && atkX == monstroXx && atkY == monstroXy) {
                                        matouX = 1;
                                    }
                                    if (monstroY_vivo == 1 && atkX == monstroYx && atkY == monstroYy) {
                                        matouY = 1;
                                    }   
									int i;                             
                                    for(i = 0; i < 5; i++){
                                        if(mob_vivo[i] == 1 && atkX == mob_X[i] && atkY == mob_Y[i]){
                                        mob_vivo[i] = 0;
                                    }
                                }
                                
                                    for(i=0;i<2;i++){
                                        if(mobY3_vivo[i]==1 && atkX==mobY3_X[i] && atkY==mobY3_Y[i]) mobY3_vivo[i]=0;
                                    }
                                    if(bossVivo && atkX==bossX && atkY==bossY){
                                        bossHP--;
                                    
                                        if(bossHP<=0) {
                                            bossVivo=0;
                                        }
                                        else if(bossHP <= bossHPMax/2 && bossFase==1){
                                            bossFase=2;
                                            limparTela();
                                            printf("O Boss urra de raiva! Ele esta ENRAIVECIDO!\n");
                                            esperarJogador();
                                        }

                                    }

                                }
                            }
                        }
                        if (matouX){
                            monstroX_vivo = 0; //so mata depois de varrer todas as cordenadas
                        }
                        if (matouY) {
                            monstroY_vivo = 0;
                        }
                    }



                }
                // Checa colisÃ£o X e Y (Andar 1)
                if((monstroX_vivo == 1 && playerX == monstroXx && playerY == monstroXy) || 
                (monstroY_vivo == 1 && playerX == monstroYx && playerY == monstroYy)){ 
                    morreu = 1;
                }

                // === ADICIONADO: Dano do Boss e dos Mobs do Andar 3 ===
                if(mapa == 4 && bossVivo == 1 && playerX == bossX && playerY == bossY){ 
                    morreu = 1;
                }
                
                for(i = 0; i < 2; i++) {
                    if(mapa == 4 && mobY3_vivo[i] == 1 && playerX == mobY3_X[i] && playerY == mobY3_Y[i]) {
                        morreu = 1;
                    }
                }

                // O BLOCO DE MORTE FICA SOLTO, ASSIM VALE PARA QUALQUER ANDAR!
                if(morreu == 1){
                    vida--;
                    limparTela();
                    
                    if(vida == 0){
                        printf("\n|=========================================|\n");
                        printf("|                GAME OVER                |\n");
                        printf("|=========================================|\n");
                        printf("|Voce foi derrotado pela masmorra...      |\n");
                        esperarJogador();
                        break;
                    }
                    else {
                        printf("               VIDA PERDIDA!                \n");
                        printf("A fase foi reiniciada. Vidas restantes: %d\n", vida);
                        esperarJogador();

                        if (mapa == 1) {
                            playerX = 5; playerY = 5;
                        } 
                        else if (mapa == 2) {
                            playerX = 5; playerY = 5;       // centro do mapa 10x10
                            monstroXx = 2; monstroXy = 4;   // posiÃ§Ã£o inicial original do X
                            monstroYx = 8; monstroYy = 7;   // posiÃ§Ã£o inicial original do Y, dentro dos limites
                        }
                        else if (mapa == 3) {
                            playerX = 7; playerY = 12; // Reseta player
                            // Reseta posiÃ§Ã£o dos monstros do array
                            mob_X[0] = 3;  mob_Y[0] = 3;
                            mob_X[1] = 11; mob_Y[1] = 3;
                            if(mob_vivo[2] == 1){ mob_X[2] = 2;  mob_Y[2] = 8; }
                            if(mob_vivo[3] == 1){ mob_X[3] = 12; mob_Y[3] = 8; }
                            if(mob_vivo[4] == 1){ mob_X[4] = 7;  mob_Y[4] = 9; }
                        }
                    }
                }
                // ===================== VITÃ“RIA =====================
                if(mapa==4 && bossVivo==0){
                    limparTela();
                    printf("\n|=========================================|\n");
                    printf("|              VOCE VENCEU!               |\n");
                    printf("|=========================================|\n");
                    printf("|  O Boss foi derrotado! Parabens!        |\n");
                    printf("|=========================================|\n");
                    esperarJogador();
                    break;
                }

                }
            }
