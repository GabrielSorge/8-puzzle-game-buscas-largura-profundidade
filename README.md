# 🧠 8-Puzzle com Inteligência Artificial (C)

## 📌 Sobre o projeto

Este projeto implementa o jogo clássico **8-Puzzle**, onde o objetivo é organizar os números de 1 a 8 em uma matriz 3x3, deixando o espaço vazio no final.

O sistema permite:

- Jogar manualmente
- Gerar puzzles aleatórios válidos
- Inserir um puzzle personalizado
- Resolver automaticamente utilizando algoritmos de IA

---

## 🚀 Funcionalidades

### 🎮 Modo Jogador
- Controle manual do puzzle
- Contagem de movimentos
- Interface no terminal

### 🤖 Modo IA
- Resolução automática do puzzle usando:
  - Busca em Largura (BFS)
  - Busca em Profundidade Iterativa (IDDFS)
- Exibição do caminho completo até a solução
- Número total de passos

### 🧩 Geração de Puzzle
- Geração aleatória de estados válidos
- Verificação de solucionabilidade (inversões)

---

## 🧠 Algoritmos utilizados

### 🔹 Busca em Largura (BFS)
- Garante encontrar a solução ótima (menor número de movimentos)
- Utiliza fila (FIFO)

### 🔹 Busca em Profundidade Iterativa (IDDFS)
- Combina DFS com limite de profundidade crescente
- Mais eficiente em memória que BFS

---

## 🛠️ Estruturas de Dados

- Fila (para BFS)
- Pilha (para DFS)
- Lista dinâmica de estados visitados
- Estrutura de estados com:
  - Matriz 3x3
  - Profundidade
  - Ponteiro para estado pai

---
## 🎯 Objetivo do projeto

Este projeto tem como objetivo aplicar algoritmos clássicos de busca
em Inteligência Artificial para resolver o problema do 8-puzzle,
explorando o espaço de estados até encontrar a solução.

---

## ⚙️ Como executar

### 📋 Pré-requisitos

- Compilador C (GCC recomendado)
- Sistema operacional Windows (devido ao uso de `conio.h` e `windows.h`)

---

### 🔧 Compilação

No terminal, navegue até a pasta do projeto e execute:

```bash
gcc src/main.c -o puzzle
