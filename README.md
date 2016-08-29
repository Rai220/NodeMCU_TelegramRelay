# NodeMCU_TelegramRelay
Controlling relay smart house via Telegram

This is sketch for NodeMCU to contol relay booard via Telegram.
It based on Telegram bot library: https://github.com/Lstt2005/ESP8266_I.O.Broker/tree/master/Arduino/Telegram/TelegramBot-master

To use it, you need to manually install library to your arduino IDE.

I use 4-relay Arduino module and directly connect it to NodeMCU.
Please be carefull and use only safe GPIO pins (like in my sample!). Unsafe pins can change it status after power fault and it may produce incorrect violance of your smart house.

Video of working example: https://youtu.be/jWih72Z5Xpg
