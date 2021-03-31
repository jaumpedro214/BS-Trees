# Binary Search Trees

Implementação da estrutura de dados Árvore Binária de Busca (_Binary Search Tree_) em C++ com suporte para tipos genéricos e métodos expandidos.

A implementação foi pensadad para suportar, além dos métodos convencionais de uma ABB, _insert_, _remove_ e _find_, alguns métodos mais complexos, elencados abaixo:
- **T nth_elem(int n)**: Retorna o _n_-ésimo elemento do percurso em pré-ordem da árvore
- **int position(T elem)**: Retorna a posição do elemento no percurso em pré-ordem da árvore
- **T median()**: Retorna a mediana dos dados no percurso em pré-ordem da árvore
- **bool is_complete()**: Retorna se a árvore é completa ou não
- **bool is_full()**: Retorna se a árvore é cheia ou não
- **string to_string()**: Retorna uma string que representa o percurso em nível nos nós da árvore

Esta implementação foi desenvolvida como trabalho para a disciplina _Estruturas de dados básicas II - DIMAP - UFRN_

## Arquitetura
O projeto é composto por duas classes; _Node_ e _BSTree_

Em implementações clássicas da ABB, a classe _Node_, é responsável por guardar as informações do ponteiro para os seus filhos esquerdo e direito e o seu conteúdo.
Para suportar com eficiência os novos métodos propostos, a classe precisou ser extendida, contendo mais informação que o usual. Elas nos permitem efetuar todos os métodos acima com complexidade _O(h)_ com _h_ sendo a altura da árvore.

- **height**: Altura do nó na árvore
- **level**: Nível do nó na árvore
- **n_left_nodes**: Número de nós na subárvore esquerda
- **n_right_nodes**: Número de nós na subárvore direita
- **n_null_ptr**: Número de subárvores nulas

Além disso, BSTree possui um vetor chamado **null_ptr_per_level**, que guarda a quantidade de subárvores nulas em cada nível.

Para atualizar essas informações foi implementada na classe BSTree a função _update_path_(), responsável por atualizar os nós no caminho alterado pelos métodos _insert_ e _remove_.

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
