# Loger
Para a disciplina *Laboratório de Introdução à Ciência de Computação I (SSC0601)* ministrada na Universidade de São Paulo (USP), desenvolve-se o programa de genciamento de estoque (Loger) utilizando linguagem C e as bibliotecas padrões (math, string,stdlib,...), além da biblioteca GUI GDK (GIMPTOOLKIT - GNOME) juntamente com o software Glade - RAD.

## Compilação do Software sem GUI

aqui vem as instruções

## Compilação do Software com GUI

```c
  gcc -o loger login.c -Wall `pkg-config --cflags --libs gtk+-3.0`
```
## Relato de desenvolvimento
No desenvolvimento do software de estoque procuramos implementar os principais tópicos da disiplina (SSC0601) visto em aula e como segue a ementa - *Resolução de problemas e desenvolvimento de programas: análise e solução de problemas, representação e documentação. Estruturas de programas: decisão e repetição. Tipos de dados simples. Modularização de programas: procedimentos, funções e passagem de parâmetros. Tipos de dados compostos: vetores, matrizes, cadeias de caracteres, registros, conjuntos e estruturas dinâmicas (ponteiros). Arquivos. Depuração de programas. Programação em linguagem estruturada.
 * - com isso, o programa é estruturado como mostrado a baixo.
 
 ### Estrutura do Loger (Arvore de elementos)
 * Login
  - Acesso
  - Niveis de acesso 
  - Criação de usuário
 * Controle do estoque
  - Adicionar registros
  - Realizar vendas
  - Atulização de produtos
 * Histórico
  - Relatório de produtos comprados
  - ...
  
  ### Interface Gráfica
  Neste trabalho para avaliaçaõ na disciplina ja referencia esse foi o tópico desafiante para a equipe, como a disciplina (SSC0601) é ministrada em linguagem C - linguagem não estrutura a Programação Orientada a Objeto, e os alunos no periodo ideal estão no primeiro Semetre do curso, causou grande dificuldades na sua implementação. A biblioteca escolhida foi [GTK] (www.gtk.org) devido a sua natividade com a linguagem C, outra opção encontrada foi Cpython com [Qt] (https://www.qt.io/)
