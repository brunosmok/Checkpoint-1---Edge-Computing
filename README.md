# Checkpoint 1 - Edge Computing

# Vinheria Agnello – Checkpoint 01 - Edge Computing e Computer Systems

Sistema de monitoramento de luminosidade para o ambiente de armazenamento de vinhos, desenvolvido com Arduino Uno e simulado no Tinkercad. 

**Autores:**
- Anauã Vieitas - RM: rm576103
- Arthur Deocleciano de Araujo - RM: rm574299
- Bruno Smoktunowicz Baptista - RM: rm574739 
- Caio Medeiros Machado - RM: rm575113
- Guilherme Stock - RM: rm573464

## Descrição do projeto

A qualidade do vinho é influenciada diretamente pela temperatura, umidade e luminosidade do ambiente. Neste primeiro momento, o projeto cuida da **luminosidade**: um sensor LDR mede a luz do ambiente, o Arduino converte a leitura em uma porcentagem (0 a 100%) e sinaliza a situação com LEDs, buzzer e um display LCD.

### O que o sistema faz

| Luminosidade | Estado | LED | Buzzer | Mensagem no LCD |
|---|---|---|---|---|
| 0% a 30% | OK | Verde | Desligado | `Status: OK` |
| 31% a 60% | Alerta | Amarelo | Toca por 3 s (600 Hz) e repete a cada 2 s de pausa enquanto continuar em alerta | `Status: ALERTA` |
| 61% a 100% | Problema | Vermelho | Toca por 3 s (1500 Hz) e repete a cada 2 s de pausa | `Status: PERIGO!` |

Outros comportamentos:

- Ao ligar, o LCD mostra o **logo da empresa** (uma taça de vinho, criada como caractere customizado) com a mensagem de boas-vindas.
- A linha 1 do LCD mostra a luminosidade em porcentagem, atualizada a cada ciclo.
- O **Monitor Serial** (9600 baud) exibe a leitura bruta do ADC e a porcentagem calculada, o que ajuda na calibração.
- A luminosidade usada é a **média de 10 leituras**, para evitar oscilações.

## Fundamentos

### LDR (Light Dependent Resistor)

O LDR é um resistor cuja resistência diminui quando a luz aumenta. Para o Arduino ler isso, o LDR é ligado em um **divisor de tensão** com um resistor fixo: a tensão no ponto central muda conforme a luz e é lida na entrada analógica `A0`.

### Conversor analógico-digital (ADC)

O Arduino Uno tem um ADC de **10 bits**, que transforma a tensão de 0 V a 5 V em um número inteiro de **0 a 1023**, lido com `analogRead()`. Neste circuito, quanto mais luz, **menor** o valor lido, por causa da posição do LDR no divisor.

### Parametrização com `map()`

A função `map()` converte a média das leituras em porcentagem. Os valores de calibração foram medidos no Monitor Serial:

| Constante | Valor | Significado |
|---|---|---|
| `LDR_ESCURO` | 1000 | Leitura no escuro (0%) |
| `LDR_CLARO` | 340 | Leitura com luz máxima (100%) |

O resultado passa por `constrain()` para ficar sempre entre 0 e 100. Se o seu circuito for diferente, meça os seus valores no Monitor Serial e atualize essas constantes.

## Componentes

| Quantidade | Componente |
|---|---|
| 1 | Arduino Uno R3 |
| 1 | Protoboard |
| 1 | LDR (fotoresistor) |
| 1 | Resistor para o divisor de tensão do LDR |
| 3 | LEDs (verde, amarelo e vermelho) |
| 3 | Resistores para os LEDs |
| 1 | Buzzer piezoelétrico |
| 1 | Display LCD 16x2 com módulo I2C |
| – | Jumpers |

## Ligações

| Componente | Ligação no Arduino |
|---|---|
| LDR | Uma perna no GND; a outra em `A0` e no resistor que vai ao 5V |
| LED verde | Pino `5` (via resistor até o GND) |
| LED amarelo | Pino `4` (via resistor até o GND) |
| LED vermelho | Pino `3` (via resistor até o GND) |
| Buzzer | (+) no pino `10`; (−) no GND |
| LCD I2C | GND → GND, VCC → 5V, SDA → `A4`, SCL → `A5` |

Na protoboard, uma trilha foi usada para o 5V (fios vermelhos) e outra para o GND (fios pretos). Cada LED tem o fio do pino na cor correspondente.

## Dependências

- **Simulador:** [Tinkercad Circuits](https://www.tinkercad.com/things/hG2mjBpqlAf-checkpoint-1-edge-computing?sharecode=0I0xRxp9Na8MCdwOOUCTKzYQo88kExh42RFHYD9K4Jw) 
- **Biblioteca:** `Adafruit_LiquidCrystal`, que já vem instalada no Tinkercad e controla o LCD via I2C.
- **Linguagem:** C/C++ para Arduino.

## Como reproduzir

1. Acesse o Tinkercad, entre na sua conta e clique em **Criar > Circuito**.
2. Adicione ao projeto os componentes da tabela acima.
3. Faça as ligações conforme a tabela de **Ligações**.
4. Selecione o Arduino, clique em **Código** e mude o modo para **Texto**.
5. Apague o código existente e cole o código-fonte do projeto (arquivo `.ino`).
6. Clique em **Iniciar simulação**.
7. Clique no LDR durante a simulação e arraste o slider de luz. Observe:
   - luz baixa: LED verde aceso e `Status: OK`;
   - luz média: LED amarelo aceso, buzzer tocando e `Status: ALERTA`;
   - luz alta: LED vermelho aceso, buzzer mais agudo e `Status: PERIGO!`.
8. Abra o **Monitor Serial** para ver as leituras.
