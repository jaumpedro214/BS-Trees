# Binary Search Trees
_Autor: João Pedro da Silva Lima - UFRN_

Implementação da estrutura de dados Árvore Binária de Busca (_Binary Search Tree_) em C++ com suporte para tipos genéricos e métodos expandidos.

A implementação foi pensadad para suportar, além dos métodos convencionais de uma ABB, _insert_, _remove_ e _find_, alguns métodos mais complexos, elencados abaixo:
- **T nth_elem(int n)**: Retorna o _n_-ésimo elemento do percurso em ordem simétrica da árvore
- **int position(T elem)**: Retorna a posição do elemento no percurso em ordem simétrica da árvore
- **T median()**: Retorna a mediana dos dados no percurso em ordem simétrica da árvore
- **bool is_complete()**: Retorna se a árvore é completa ou não
- **bool is_full()**: Retorna se a árvore é cheia ou não
- **string to_string()**: Retorna uma string que representa o percurso em nível nos nós da árvore

Para visualizar o funcionamento dos métodos, também foi criada uma rotina que cria e interage com uma árvore a partir de comandos de texto contidas em arquivos.
Para isso, são necessários dois arquivos, veja **Executando**; 

Esta implementação foi desenvolvida como trabalho para a disciplina _Estruturas de dados básicas II - DIMAP - UFRN_

## Arquitetura
O projeto é composto por duas classes; _Node_ e _BSTree_

Em implementações clássicas da ABB, a classe _Node_, é responsável por guardar as informações do ponteiro para os seus filhos esquerdo e direito e o seu conteúdo.
Para suportar com eficiência os novos métodos propostos, a classe precisou ser extendida, contendo mais informação que o usual. Elas nos permitem efetuar a maioria dos métodos acima com complexidade _O(h)_, com _h_ sendo a altura da árvore, ou _O(1)_.

- **height**: Altura do nó na árvore
- **level**: Nível do nó na árvore
- **n_left_nodes**: Número de nós na subárvore esquerda
- **n_right_nodes**: Número de nós na subárvore direita
- **is_complete**: Indica se o nó é uma árvore completa ou não

Para atualizar essas informações foi implementada na classe BSTree a função _update_path_(), responsável por atualizar os nós somente no caminho alterado pelos métodos _insert_ e _remove_.

## Como rodar
### Dependências

- ```g++```
- ```makefile```
- ```cmake```

### Como Compilar
Clone este repositório com `git clone https://github.com/jaumpedro214/BS-Trees` ou faça download direto.

No diretório do projeto, faça

```
$ mkdir build && cd build
```
```
$ cmake ../
```
```
$ make
```

### Executando
O executável binário do programa é gerado na pasta ```bin/```.
```
$ ./bin/output
```
Caso queira ter acesso a alguns exemplos das funcionalidades da árvore, basta executá-lo com a flag de testes `-t`
```
$ ./bin/output -t
```
Para executar a rotina de criação de árvore e execução de comandos, é necessário criar dois arquivos, um com uma sequência de valores _inteiros_, 
que serão os nós inseridos sequêncialmente na árvore, e outro com o conjunto de comandos a serem executados.
```
$ ./bin/output <tree_file> <commands_file>
```
Os comandos disponíveis são
- **ENESIMO N**: Imprime o valor retornado por _nt_elem(N)_ 
- **POSICAO N**: Imprime o valor retornado por _position(N)_ 
- **MEDIANA N**: Imprime o valor retornado por _median()_ 
- **CHEIA**: Imprime o retorno de _is_full()_ 
- **COMPLETA**: Imprime o retorno de _is_complete()_ 
- **IMPRIMA**: Imprime o retorno de _to_string()_ 
- **IMPRIMA_ARVORE**: Imprime a os nós da árvore em pré-ordem com espaçamentos que demonstram o nível do nó. Útil para visualização.
- **INSIRA N**: Insere o elemento N na árvore. Retorna true caso o elemento for inserido com sucesso, falso caso contrário.
- **REMOVA N**: Remove o elemento N da ávore. Retorna true caso o elemento for removido com sucesso, falso caso contrário.

Na pasta `/tests` é possível encontrar alguns arquivos exemplo.

## Detalhamento e Análise de Complexidade

### Informações extras nos nós

Todos os métodos extendidos acima podem ser implementados sobre a versão tradicional do nó com chamadas recursivas a partir da raiz. 

Um exemplo disso é o método abaixo que calcula a altura da árvore (altura da raiz).

```c++
int height(root){
  int hleft, hright;
  if(root == nullptr) 
    return -1;
  hleft = 1 + height(root->left);
  hright = 1 + height(root->right);
  return max(hleft, hright);
}
```

A principal deficiência desse método é sempre recalcular a altura de todas os nós da árvore, o que o deixa com complexidade _O(n)_.
Este problema é resolvido por meio de duas mudanças simples:
- Adicionando, em cada nó, a informação sobre sua altura.
- Atualizando a altura somente para os nós no caminho de alguma mudança (Inserção ou Remoção).

A função da _BSTRee_ responsável por realizar isso é a _update_path()_. Ela atualiza as informações de todos os nós do caminho da raiz até um alvo.
Por isso, sua complexidade é a mesma dos métodos de inserção e remoção, _O(h)_.

Dessa forma, a consulta da altura do nó raiz pode ser feita em tempo constante.

### Complexidade dos métodos exapandidos

- **T nth_elem(int n)**: 
   _O(h)_, Utiliza as o número de nós a esquerda (n_left_nodes) para encontrar o nó na posição **p** no percurso simétrico. Pode ser entendido como o método find aplicado sobre a posição do nó.
- **int position(T elem)**: 
   _O(h)_, Realiza o método find tradicional enquanto calcula o a posião atual do nó visitado. 
- **T median()**: _O(h)_, Utiliza o número total **n** de nós da árvore para calcular o elemento central n/2 (n ímpar), ou  min entre (n/2, n/2+1) (n par).
- **bool is_complete()**: Retorna se a árvore é completa ou não
- **bool is_full()**: Retorna se a árvore é cheia ou não
- **string to_string()**: Retorna uma string que representa o percurso em nível nos nós da árvore
