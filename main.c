/*=======================================================
|   Четыре светодиода на порту B (PB3, PB2, PB1, PB0)   |
|---------------------------------VD6--VD7--VD4--VD5----|
|   Пять кнопок на портах:                              | 
|---------------------- SW2-(PB5) ----------------------|
|-------------------------------------------------------|
|------- SW4-(PE3) -----SW1-(PC2) ----- SW5-(PB6)-------|
|-------------------------------------------------------|
|---------------------- SW3-(PE1) ----------------------|
=======================================================*/
 #include <MDR32FxQI_port.h>
 #include <MDR32FxQI_rst_clk.h>

 // Прототип функции задержки, реализованной ниже
 void Delay(int waitTicks);
 int waitTicks = 1000000;
 // Точка входа, отсюда начинается исполнение программы
 int main()
 {
   // Заводим структуру конфигурации вывода(-ов) порта GPIO
   PORT_InitTypeDef myLeds;
   // Включаем тактирование порта B
   RST_CLK_PCLKcmd (RST_CLK_PCLK_PORTB, ENABLE);
   // Инициализируем структуру конфигурации вывода(-ов) порта значениями по умолчанию
   PORT_StructInit(&myLeds);
   // Изменяем значения по умолчанию на необходимые нам настройки
   myLeds.PORT_Pin = PORT_Pin_3|PORT_Pin_2|PORT_Pin_1|PORT_Pin_0;
   myLeds.PORT_OE = PORT_OE_OUT;
   myLeds.PORT_SPEED = PORT_SPEED_SLOW;
   myLeds.PORT_MODE = PORT_MODE_DIGITAL;
   // Применяем заполненную нами структуру для PORTB.
   PORT_Init(MDR_PORTB, &myLeds);
     
   // Запускаем бесконечный цикл обработки - Основной цикл
   while (1)
   {
        PORT_SetBits(MDR_PORTB, PORT_Pin_3|PORT_Pin_1); // LED   
        PORT_ResetBits(MDR_PORTB, PORT_Pin_2|PORT_Pin_0); // LED
        Delay(waitTicks);// Задержка
        PORT_ResetBits(MDR_PORTB, PORT_Pin_3|PORT_Pin_1); 
        PORT_SetBits(MDR_PORTB, PORT_Pin_2|PORT_Pin_0);
        Delay(waitTicks);// Задержка
    }
 }

 // Простейшая функция задержки, позднее мы заменим ее на реализацию через таймер
 void Delay(int waitTicks)
 {
    int i;
    for (i = 0; i < waitTicks; i++)
    {
        __NOP();
    }
 }