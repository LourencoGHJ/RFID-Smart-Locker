# Caixa Inteligente RFID

Projeto desenvolvido no âmbito da **Prova de Aptidão Profissional (PAP)** do curso profissional de Técnico de Gestão e Programação de Sistemas Informáticos, no ano letivo 2022/2023.

A Caixa Inteligente RFID é um protótipo de cacifo/armário com controlo de acesso através de cartões de proximidade RFID. O sistema lê o cartão apresentado, compara o seu UID com os identificadores configurados no programa e utiliza um mecanismo de trinco elétrico para permitir ou impedir a abertura da porta.

## Objetivo do projeto

Recriar, com recurso a uma placa Arduino, o funcionamento básico de um armário inteligente com cartão de acesso. O utilizador aproxima um cartão do leitor RFID; o sistema verifica o identificador e apresenta o resultado através de um ecrã LCD, sinais sonoros e indicadores luminosos.

## Como funciona

1. O sistema inicia o leitor RFID e apresenta no LCD a instrução para aproximar um cartão.
2. Quando é detetado um cartão, o Arduino lê o respetivo UID.
3. O UID é apresentado no Monitor Série e comparado com os valores definidos no código.
4. **Cartão autorizado:** o sistema apresenta uma mensagem de boas-vindas, emite um sinal sonoro, acende o LED azul e ativa o módulo de relé que comanda o trinco elétrico.
5. **UID configurado como não autorizado:** o sistema apresenta uma mensagem de acesso negado, emite um sinal sonoro, acende o LED vermelho e mantém o relé desligado.
6. Após o tratamento do cartão, o LCD regressa ao ecrã inicial.

> **Nota:** os sketches fornecidos contêm uma condição explícita para um UID autorizado e outra para um UID configurado como não autorizado. Não se deve assumir que qualquer cartão desconhecido é tratado pela mesma rotina de recusa sem alterar e testar o código.

## Componentes e materiais

### Eletrónica

- Arduino Uno R3
- Leitor RFID e cartões/tags de proximidade
- Display LCD I2C
- Módulo relé de 5 V
- Mini trinco elétrico solenoide de 12 V
- LED azul
- LED vermelho
- Buzzer passivo de 5 V
- Resistências
- Breadboard
- Cabos jumper macho-macho e macho-fêmea

### Estrutura

- Madeira/tábuas para a caixa
- Dobradiças
- Parafusos
- Pega para a porta
- Tinta

A lista acima reúne os materiais descritos no relatório e na apresentação da PAP.

## Ligações identificadas no código

O sketch Arduino define os seguintes pinos:

| Componente | Pino Arduino |
|---|---:|
| RFID — SS/SDA | 10 |
| RFID — RST | 9 |
| LED azul | 6 |
| LED vermelho | 5 |
| Módulo relé | 8 |
| Buzzer | 7 |

O leitor MFRC522 utiliza comunicação SPI. No Arduino Uno, a ligação SPI utiliza os pinos de hardware correspondentes (MOSI, MISO e SCK).

O LCD é inicializado com o endereço I2C `0x27` e dimensão configurada de `20x4`. No Arduino Uno, o barramento I2C utiliza SDA e SCL.

**Atenção:** o relatório e os sketches disponibilizados não incluem um esquema elétrico completo de todas as ligações. Confirma a cablagem física do protótipo antes de alimentar o circuito. O trinco indicado é de 12 V; não o ligues diretamente a um pino do Arduino. A comutação deve ser feita através do circuito de potência adequado e do módulo de relé.

## Bibliotecas

O código inclui estas bibliotecas:

- `LiquidCrystal_I2C` — controlo do ecrã LCD através de I2C.
- `SPI` — comunicação SPI utilizada pelo leitor RFID.
- `MFRC522` — comunicação com o módulo RFID MFRC522.

`SPI` faz parte do ambiente Arduino. As bibliotecas `LiquidCrystal_I2C` e `MFRC522` têm de estar instaladas no Arduino IDE.

## Preparação e utilização

1. Instala e abre o [Arduino IDE](https://www.arduino.cc/en/software).
2. Instala as bibliotecas `LiquidCrystal_I2C` e `MFRC522` através do Gestor de Bibliotecas, ou disponibiliza-as manualmente ao IDE.
3. Liga os componentes de acordo com o circuito físico e com os pinos definidos no sketch.
4. Abre o ficheiro `.ino` pretendido no Arduino IDE.
5. Seleciona **Arduino Uno** como placa e a porta série correta.
6. Compila e carrega o programa para a placa.
7. Abre o Monitor Série a **9600 baud** para observar os UID dos cartões lidos.
8. Confirma os UID no código e altera-os apenas para os cartões que pretendes configurar como autorizados ou recusados.
9. Testa o comportamento do LCD, dos LEDs, do buzzer, do relé e do trinco.

## Código-fonte

Foram disponibilizadas duas versões do sketch:

- `pap Gui atualizada 30.ino`

As duas versões usam os mesmos pinos e bibliotecas principais, mas apresentam diferenças na sequência de ativação do relé, nos tempos de espera e no tratamento do ciclo de leitura. Por esse motivo, este README não identifica nenhuma delas como versão final.

Antes de publicar o projeto, recomenda-se escolher a versão efetivamente utilizada no protótipo, atribuir-lhe um nome simples (por exemplo, `CaixaInteligenteRFID.ino`) e manter apenas essa versão como sketch principal. Guarda as restantes versões como histórico, se forem relevantes.

## Limitações conhecidas

- Os UID dos cartões estão definidos diretamente no código.
- A versão fornecida contempla um UID autorizado e um UID específico configurado como não autorizado.
- Não existe, nos ficheiros consultados, evidência de uma gestão dinâmica de utilizadores ou de armazenamento persistente de cartões.
- O relatório não apresenta um esquema elétrico completo nem uma tabela integral de ligações.
- Os dois sketches disponibilizados não são exatamente iguais; o comportamento final deve ser confirmado no hardware.

## Possíveis melhorias

- Permitir registar e remover cartões sem editar o código-fonte.
- Tratar explicitamente todos os cartões não reconhecidos como acesso recusado.
- Organizar os UID autorizados numa estrutura de dados em vez de os comparar individualmente.
- Adicionar um tempo de abertura configurável e uma rotina de fecho consistente.
- Documentar o esquema elétrico completo e as ligações de alimentação.
- Melhorar a gestão de erros e o feedback apresentado no LCD.

Estas melhorias são sugestões para evolução do protótipo e não funcionalidades que estejam confirmadas como implementadas.

## Contexto académico

- **Projeto:** Caixa com leitor de Cartões de Proximidade RFID
- **Tipo:** Prova de Aptidão Profissional
- **Curso:** Técnico de Gestão e Programação de Sistemas Informáticos
- **Instituição indicada no relatório:** Escola Secundária da Boa Nova — Leça da Palmeira
- **Ano letivo:** 2022/2023

## Referências consultadas

As referências abaixo constam da webgrafia do relatório/apresentação:

- [Fechadura eletrónica com Arduino e RFID — Fazedores](https://blog.fazedores.com/fechadura-eletronica-com-arduino-e-rfid/)
- [Arduino Based RFID Door Lock — The DIY Life](https://www.the-diy-life.com/arduino-based-rfid-door-lock-make-your-own/)
- [Vídeo de apoio — YouTube](https://youtube.com/watch?v=EJKUcGIfNDU)
- [Vídeo de apoio — YouTube](https://youtube.com/watch?v=7bYDdpop7EI)
- [Vídeo de apoio — YouTube](https://youtube.com/watch?v=nAcTO1LELN0)

---

*Documentação elaborada com base no relatório da PAP, na apresentação e nos dois sketches Arduino disponibilizados.*
