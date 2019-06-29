# Loger
Para a disciplina *Laboratório de Introdução à Ciência de Computação I (SSC0601)* ministrada na Universidade de São Paulo (USP), desenvolve-se o programa de gerenciamento de estoque (Loger) utilizando linguagem C e as bibliotecas padrões (math, string,stdlib,...), além da biblioteca GUI GTK (GIMPTOOLKIT - GNOME) juntamente com o software Glade - RAD.

## Relato de desenvolvimento
No desenvolvimento do software de estoque procuramos implementar os principais tópicos da disciplina (SSC0601) visto em aula e como segue a ementa - *Resolução de problemas e desenvolvimento de programas: análise e solução de problemas, representação e documentação. Estruturas de programas: decisão e repetição. Tipos de dados simples. Modularização de programas: procedimentos, funções e passagem de parâmetros. Tipos de dados compostos: vetores, matrizes, cadeias de caracteres, registros, conjuntos e estruturas dinâmicas (ponteiros). Arquivos. Depuração de programas. Programação em linguagem estruturada.
 * - com isso, o programa é estruturado como mostrado na seção posterior.
 
 ### Estrutura do Loger (Árvore de elementos)

Para o funcionamento do programa é necessária a criação dos arquivos caixa.txt, extrato.txt e histórico.txt;

Menu inicial: aqui são exibidas todas as funcionalidades do programa, e o usuário deve indicar qual deseja utilizar por meio do teclado numérico (utilizando a numeração indicada pelo software). As opções são:
1 - Para fazer o inventário inicial;
2 - Para exibir os itens em estoque ;
3 - Para consultar itens;
4 - Para verificar a validade dos itens no estoque;
5 - Para remover itens do estoque;
6 - Para incluir itens no estoque;
7 - Para exibir o histórico de vendas;
8 - Para dar baixa no sistema;
9 - Para verificar o valor do caixa;
10 - Para sair do sistema;

1 - Realizar inventário inicial: essa opção deve ser utilizada no primeiro acesso ao software, e cria o arquivo estoque.txt, onde são armazenadas as informações referentes aos itens de estoque. São elas:
Código do item;
Descrição do item;
Data de vencimento do item no formato DD MM AAAA (separadas por espaço);
Preço de compra do produto;
Preço de venda do produto;

2 - Exibir estoque: exibe todos os itens do estoque, bem como as informações referentes a eles;

3 - Consultar item: essa funcionalidade permite consultar informações referentes a um item específico do estoque (as consulta pode ser feita pelo código ou pela descrição do produto);

4 - Verificar a validade de itens no estoque: permite averiguar os itens que estão vencendo em determinado mês;

5 - Remover item do estoque: permite realizar a remoção de itens do estoque, por código ou pela descrição (remoção não relacionada à venda do produto);

6 - Incluir item no estoque: utilizada para inclusão de item de estoque, posteriormente ao inventário inicial;

7 - Histórico: demonstra as movimentações de venda de produto (pode ser feita selecionando a movimentação total de estoque, ou a venda de um item específico);

8 - Dar baixa no caixa: nessa opção é registrada a venda de produto (informando-se a data no formato DD MM AAAA, o código do produto, e a quantidade vendida);

9 - Verificar valor do caixa: exibe o valor em caixa, baseado nas vendas registradas no sistema;

10 - Sair do sistema: encerra a execução do programa.
aqui vem as instruções

## Compilação do Software com GUI (Linux)

Previamente deve-se instalar a biblioteca GTK

```bash
  sudo apt install libgtk-3-dev
```
e, em seguida compilar na pasta **loger-GUI** o arquivo main.c com as variáveis como se segue

```bash
  gcc -o main main.c -Wall `pkg-config --cflags --libs gtk+-3.0`
```
pronto! Agora é só executar o objeto

```bash
  ./main
```


  
  ### Interface Gráfica
  Neste trabalho para avaliação na disciplina a implementação de interface gráfica é opcional, porém todos os demais grupos para esse trabalho decidiram de forma unânime fazer a UI (interface gráfica). A implementação da GUI é desafiante devido a complexidade de gerenciamento dos elementos visuais e eventos (ou sinais), como a disciplina (SSC0601) é ministrada em linguagem C - linguagem não estruturada a Programação Orientada a Objeto, e os alunos no período ideal estão no primeiro semestre do curso, culminou na complexidade em desenvolver janelas gráficas ao invés do próprio terminal com interface de interação com o usuário. 
A biblioteca escolhida para a implementação de janelas gráficas foi a [GTK] (www.gtk.org) por ser nativo da linguagem C, outra opção encontrada foi Cython com [Qt] (https://www.qt.io/) (RAD - Rapid Application Development), porém essa segunda mostrou ruidosa devido a exportação do código C para python, dessa forma, desvinculando o back-end ( C ) do front-end ( Python ).
A estratégia de desenvolvimento abordado pela equipe baseou-se em três etapas:

1. Com o objetivo definido (programa de estoque), realizou-se o levantamento de requisitos lógicos necessários, como: estruturas de dados utilizadas, funções, armazenamento de estado do programa, entre outros tópicos.

2. implementação do back-end com interação do usuário via terminal, com isso caso a interface gráfica apresenta-se complicações a lógica e funcionalidades do programa ainda se manteriam acessíveis.

3. Pesquisas e implementações escalonáveis da interface gráfica, e posteriormente a associação dos eventos visuais.

Com as pesquisas iniciais iniciadas e a estratégia traçada iniciou-se a execução do desenvolvimento, desta forma, resolveu-se a próxima seção para apresentar as ressalvas e complicações ocorridas durante o desenvolvimento.

## Considerações e ressalvas

Com a duas primeiras etapas descritas na seção anterior foram executados conforme o previsto, porém a interface gráfica demandava mais experiência do que o esperado, o sistema click arraste do Glade é otimizado para rápida construção grosseira com refinamento em linguagem C; com tudo, o gerenciamento de eventos em uma biblioteca não nativamente orientada a objeto trouxe uma complexidade não prevista anteriormente, que apesar de conhecido os desafios gerados em implementar interface gráfica seja ela em qualquer linguagem, não conseguimos superar este desafio.


##Conclusão
Com exceção a interface gráfica todos os demais objetivos propostos na primeira fase do trabalho foram complidos conforme o previsto.


## Vídeo no Youtube - demonstração do software
### [LINK] (https://youtu.be/_30wkfIUuRc)
