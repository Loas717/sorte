Projeto de Sistemas Operacionais (Inter Process Communication); "jogo de tabuleiro" com 2 jogadores.

# Processos

-**Processo Servidor**:Controla o tabuleiro, gerencia os movimentos, checa quem venceu.

-**Processo Jogador 1**

-**Processo Jogador 2**

-**Processo Externo**:

  Verifica o tempo para encerrar o jogo.

---

## Simular Tabuleiro

-**Jogadores começam na posição 0**

-**Tamanho do tabuleiro = 10**

  (Podemos aumentar o tamanho futuramente)

---

### Fluxo de Execução

1.**Jogador 1**

   -`descritorj1` (FILHO1) joga o dado com `seed`.

2.**Jogador 2**

   -`descritorj2` (FILHO2) joga o dado com `seed`.

3.**Servidor (PAI)**

- Lê o valor do dado do Jogador 1.
- Lê o valor do dado do Jogador 2.
- Move os filhos no tabuleiro conforme o valor dos dados.

4.**Filhos (Jogadores)**

- Avançam no tabuleiro.
- Enviam a nova posição ao processo PAI.

5.**Servidor (PAI)**

- Verifica se o **Jogador 1 venceu**.
- Verifica se o **Jogador 2 venceu**.

6.**Processo Externo**

- Monitora o tempo total do jogo.
- Encerra a execução ao fim do tempo estabelecido (timeout).

---
