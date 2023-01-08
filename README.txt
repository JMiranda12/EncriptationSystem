● Funcionalidades implementadas:

-->1. As estruturas de dados para guardar as chaves públicas e privadas devem
basear-se em matrizes dinâmicas:
a. No caso da representação com inteiros devem utilizar-se matrizes dinâmicas
dos dígitos inteiros (i.e. array dinâmico de vários arrays dos dígitos das
chaves);
b. No caso da representação com strings devem utilizar-se matrizes dinâmicas
de caracteres dos respectivos dígitos (i.e. array dinâmico de várias strings
contendo os caracteres representativos dos dígitos das chaves);
-->3. Dada uma chave privada, calcular a respectiva chave codificada utilizando uma
   representação run-length. A representação codificada (run-length) das chaves deve
   ser mantida/gerida numa matriz de inteiros e strings (tal como para as chaves
   públicas e privadas);
-->4. Inserir e remover uma ou mais chaves públicas e respectivas chaves privadas e
   codificadas (run-length) nas estruturas de dados. Inicialmente a inicialização deverá
   ser efectuada por geração aleatória das chaves públicas e cálculo das respectivas
   chaves privadas e codificadas. Mais tarde deve ser considerada também a
   leitura/escrita de chaves através de ficheiros;
-->5. Efectuar pesquisas de chaves, retornando as chaves privadas e codificadas para
   uma dada chave pública ou partes dessa chave, ou seja, cada pesquisa poderá
   utilizar subsequências/partes da chave pública na expressão de pesquisa;
-->6. Ordenar a lista de chaves públicas e respectivas chaves privadas e codificadas, por
   ordem crescente ou decrescente das chaves;
-->7. Listar as chaves públicas e respectivas chaves privadas e codificadas, na ordem em
   que se encontram inseridas ou noutra ordem indicada (e.g. crescente ou
   decrescente dos tamanho das chaves, i.e. número de dígitos);

● Funcionalidades parcialmente implementadas:
-->2.Dada uma chave pública, calcular a chave privada com base em dois algoritmos
     diferentes à escolha, i.e., dada uma chave pública n:
     a. Gerar múltiplos de n até encontrar um no bipolar (pode ser pouco eficiente);
     b. Gerar números bipolares sucessivos e verificar se são ou não múltiplos de n.

-->8. Agregar numa estrutura de dados designada por KEY_HOLDER (porta-chaves) um
   conjunto de matrizes de chaves públicas, privadas e codificadas, tal como foram
   descritas anteriormente (3 matrizes para a versão com dígitos inteiros e 3 matrizes
   para a versão com strings). Considerar ainda a representação de uma lista ligada de
   vários porta-chaves, i.e., uma lista ligada em que cada nó contém os dados de 6
   matrizes de chaves públicas, privadas e codificadas (versão inteiros e strings). Cada
   porta-chaves deverá ter uma ordem cronológica na sequência de nós da lista.
   Portanto, cada nó da lista deve ter duas datas: i) data da geração/criação do
   porta-chaves; ii) data da última actualização/modificação de chaves. Os nós da lista
   devem ser ordenados cronologicamente pelas datas de modificação dos
   porta-chaves. Devem ainda ser criadas várias funções para gerir a lista ligada de
   porta-chaves:
   a. Criar e inserir um porta chaves numa dada posição da sequência;
   b. Eliminar um porta-chaves que está numa dada posição;
   c. Pesquisar chaves apenas em determinados porta-chaves da lista, definidos
   numa expressão de pesquisa;

-->9. Será necessário representar também vários utilizadores, através do seu nome, email
   e conjunto de chaves do utilizador, i.e., cada utilizador poderá ter vários
   porta-chaves que deverão ser armazenados numa lista ligada de porta-chaves
   (como descrito anteriormente). Deverá existir também uma lista ligada de
   utilizadores. Deverão implementar funções de gestão da lista de utilizadores,
   nomeadamente:
   a. Inserir e remover utilizadores, à cabeça, cauda e ordenadamente pelo nome;
   b. Pesquisar utilizadores por nome ou parte do nome;
   c. Ordenar uma dada lista pelo nome dos utilizadores;

● Funcionalidades não implementadas:

-->10. Utilizar ficheiros de texto para output e input de chaves públicas e privadas, i.e.
   escrever e ler informação de um ou mais porta-chaves em ficheiros de texto. As
   funções de pesquisa de chaves definidas anteriormente podem também ter como
   output ficheiros de texto;
-->11. Utilizar ficheiros binários para output e input de chaves públicas e privadas, i.e.
   escrever e ler informação de um ou mais porta-chaves em ficheiros binários.