# Exercicios Programa - Indexador de Palavras

Exercício Programa requisito para a disciplina **ACH2023** - Algoritmos e Estrutura de Dados I, ministrada pelo Professor Doutor Flávio Luiz Coutinho na **EACH -USP**

## Conceitos base  

### Criação de um indexador

O indexador deve receber um arquivo de texto (.txt) e cumprir os seguintes objetivos:

- Contar o numero de linhas do texto
- Armazenar e Contar Palavras Únicas do texto
- Armazenar Quantidade de repetições de uma palavra
- Armazenar Linhas de ocorrência de uma palavra
- Contar Comparações necessárias para o armazenamento de palavras
- Buscar por uma palavra das quais foram armazenadas
-	Contar comparações necessárias para buscar uma palavra

Para este indexador temos a necessidade da criação de duas diferentes estruturas para o armazenamento de variáveis, uma terá formato de **Arvore*** e outra terá formato de **Lista**.

> *para a Arvore temos o objetivo adicional de contar sua Altura

### Criar um Main Loop de Interação

Para interagirmos com o indexador, além de sua inicialização precisa ser criador um loop de interação onde poderemos fazer diversas buscas sem reiniciar o programa.

### Outros

Quando o programa for iniciado precisamos exibir o nome do arquivo de texto e a estrutura desejada passada na Inicialização.

## Problemas

### Armazenamento

Primeiramente temos que normalizar o texto para que não armazenemos caracteres como ponto vírgula aspas entre outros que não são palavras. Mas essa normalização deve ser feita após guardarmos o valor de saída de cada linha para que na exibição o a linha apareça de forma com que seja idêntica a citada no texto.
 
Para além disso temos que armazenar em foco uma informação principal e diversas outras informações satélites. Em nosso caso a informação principal é o conjunto de caracteres de uma palavra.
As informações satélites são:

- Numero de ocorrências
- Linha de ocorrência para cada ocorrência*

Para finalizar, não podemos usar a própria palavra como o identificador para o armazenamento, precisamos de um método de conversão que garanta ordenação sem colisões (Ex: se convertermos o valor ASCII para cada letra e somarmos temos que "casa" e "saca" são palavras iguais).

Com isso fica claro que devemos armazenar em vez da própria palavra um struct que ira guardar todas suas informações e será ordenado por sua chave, o struct, a lista terá uma cara de tabela como a seguinte:

#### Exemplo Tabela de Palavras

| Chave | Repetições |   Valor  | Linhas de Ocorrência |
|-------|------------|----------|----------------------|
| 0001  |  2         | "Era"    | [1, 4]               |
| 0002  |  5         | "Uma"    | [1, 4, 14, 20]     	 |
| ...   |  ...       | ...      | ....              	 |

*como é possível ver pela tabela as Linhas de Ocorrência serão armazenadas em uma array externa de tamanho Repetições, que é o método mais simples de armazenar um item que é ligado a diversos outros (Relação Um para Muitos)

### Linhas de Ocorrência

Para que não haja desperdício de memória relacionando as linhas de ocorrência e as palavras devemos passar pelo text duas vezes, na primeira iremos pegar as palavras únicas do texto, contar sua repetição e ordena-las, na segunda iremos adicionar as linhas de ocorrência (isso serve para atribuir um valor dinâmico para cada Lista de linhas de ocorrência). 

### Lista

Para lista o problema é menos complicado, precisamos transformar o texto em uma lista sequencial de cada linha registrando as mesmas na forma com qual aparecem e uma segunda lista sequencia ordenada onde armazenaremos as structures que guardam informações sobre as palavras. Com isso basta implementar uma busca binária para o acesso a cada palavra desejada que será a forma mais eficiente. A contagem de comparações pode ser feito através alterações triviais nos métodos de busca e inserção.

### Arvore

Para arvore o problema é quase igual o da lista, apenas mudando o local onde se guardam os structs por uma arvore AVL.

### Complexidade

Para lista temos a complexidade Teórica de O(n²) para inserções já que passamos pelo texto duas vezes e a operação de relacionar cada frase a uma palavra custa O(nlogn) (Busca de n palavras + O(1) para relacionar a lista de ocorrência em uma palavra) no pior caso, já a inserção irá custar O(n²) no pior caso sendo T(n) = O(n²) + O(nlogn) temos T(n) = O(n²). Para a busca teremos complexidade O(logn) já que tudo estará ordenado e guardado na lista.

Para arvore teremos a complexidade teórica de O(nlogn) para inserção e O(nlogn) para relacionar as listas de ocorrências com as palavras  sendo assim O(nlogn) para inserção. Para busca continuamos com O(logn) da busca binária.
