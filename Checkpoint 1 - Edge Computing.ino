// Vinheria Agnello - Checkpoint 01
// Monitor de luminosidade com LDR, LEDs, buzzer e display LCD I2C

#include <Adafruit_LiquidCrystal.h> // Biblioteca do LCD I2C (já vem no Tinkercad)

const int LDR = A0;
const int LED_VERMELHO = 3;
const int LED_AMARELO = 4;
const int LED_VERDE = 5;
const int BUZZER = 10;

// Calibração do LDR
const int LDR_ESCURO = 1000; // leitura no escuro (0%)
const int LDR_CLARO = 340;   // leitura com luz máxima (100%)

// LCD 16x2 via I2C (endereço 0 no Tinkercad)
Adafruit_LiquidCrystal lcd(0);

// Logo: taça de vinho desenhada como caractere customizado (5x8 pixels)
byte tacaVinho[8] = {
    B11111,
    B10001,
    B10001,
    B01010,
    B00100,
    B00100,
    B00100,
    B01110};

void setup()
{
    Serial.begin(9600);
    pinMode(LED_VERMELHO, OUTPUT);
    pinMode(LED_AMARELO, OUTPUT);
    pinMode(LED_VERDE, OUTPUT);
    pinMode(BUZZER, OUTPUT);

    // Inicializa o LCD
    lcd.begin(16, 2);
    lcd.setBacklight(1);
    lcd.createChar(0, tacaVinho); // Registra a taça na posição 0

    // Tela de boas-vindas com o logo
    lcd.setCursor(0, 0);
    lcd.write(byte(0)); // Logo (taça)
    lcd.print(" VINHERIA ");
    lcd.write(byte(0)); // Logo (taça)
    lcd.setCursor(0, 1);
    lcd.print("   AGNELLO   ");
    delay(2500);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Bem-vindo!  ");
    lcd.setCursor(0, 1);
    lcd.print("Monitor de Luz");
    delay(2500);
    lcd.clear();
}

void loop()
{
    // Média de 10 leituras do LDR
    long soma = 0;
    for (int i = 0; i < 10; i++)
    {
        soma = soma + analogRead(LDR);
        delay(10);
    }
    int media = soma / 10;

    // map() converte a média para luminosidade de 0 a 100%
    int luz = map(media, LDR_ESCURO, LDR_CLARO, 0, 100);
    luz = constrain(luz, 0, 100);

    // Mostra os valores no Monitor Serial
    Serial.print("Leitura: ");
    Serial.print(media);
    Serial.print(" | Luz: ");
    Serial.print(luz);
    Serial.println("%");

    // Linha 1 do LCD: luminosidade (espaços extras apagam sobras de texto anterior)
    lcd.setCursor(0, 0);
    lcd.print("Luz: ");
    lcd.print(luz);
    lcd.print("%    ");

    // Apaga todos os LEDs e o som no início de cada ciclo
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, LOW);
    noTone(BUZZER);

    if (luz <= 30)
    {
        // Estado OK (Verde)
        digitalWrite(LED_VERDE, HIGH);
        lcd.setCursor(0, 1);
        lcd.print("Status: OK      ");
    }
    else if (luz <= 60)
    {
        // Estado de Alerta (Amarelo)
        digitalWrite(LED_AMARELO, HIGH);
        lcd.setCursor(0, 1);
        lcd.print("Status: ALERTA  ");
        tone(BUZZER, 600); // Liga o som
        delay(3000);       // Toca por 3 segundos
        noTone(BUZZER);    // Desliga o som
        delay(2000);       // Pausa de 2 segundos (se continuar, repete)
    }
    else
    {
        // Estado de Perigo / Problema (Vermelho)
        digitalWrite(LED_VERMELHO, HIGH);
        lcd.setCursor(0, 1);
        lcd.print("Status: PERIGO! ");
        tone(BUZZER, 1500); // Liga o som (frequência mais alta para perigo)
        delay(3000);        // Toca por 3 segundos
        noTone(BUZZER);     // Desliga o som
        delay(2000);        // Pausa de 2 segundos (se continuar, repete)
    }
}