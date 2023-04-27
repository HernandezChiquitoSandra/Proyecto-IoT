# Proyecto-IoT


Área: Desarrollo de Software Multiplataforma

Asignatura: Aplicaciones de loT

Docente: Anastacio Rodríguez García 

GDS0453

## Integrantes:
Daniela Esmeralda Méndez | 1221100344

Sandra Michel Hernández Chiquito | 1221100284

Omar Alejandro Lozada Zúñiga | 1221100256

## Nombre del Proyecto
Home Security

## Objetivo general
El objetivo de este proyecto será tener una casa más segura, ya que, en ocasiones, en la mayoría de los hogares se olvida cerrar el gas de las estufas, lo cual puede ser muy peligro. Por otra parte, también se detectará movimiento y así se iluminará el exterior, de esta manera se pondrá en aviso a quienes están en el interior y harán, por el temor al verse descubierto, que el mal hechor se escape, algo más del proyecto es que cubra una necesidad en tiempos calurosos, detectara la temperatura y humedad y conforme esta sea una temperatura elevada se encenderá un ventilador.

## Objetivos específicos
●	Detectara movimiento al pasar y se encenderán los leds.
●	Al detectar temperatura elevada se encenderá un servomotor (para la ventilación).
●	 El buzzer se encenderá cuando detecte gas o humo.

## Tabla de software utilizado

| Id | Software   | Version | Tipo    |
|----|------------|---------|---------|
|001 |Arduino IDE |     2   |  2      |
|002 |Mosquitto   |5.0.3.1.1|Freeware |
|003 |Mariadb     |10.11.216|Freeware |
|004 |Node-red    |    3.0  |Freeware |


## Tabla de hadware utilizado
| Id | Componente | Descripción | Imagen | Cantidad | Costo total |
|----|------------|-------------|--------|----------|-------------|
|001 |Esp32       |solución de Wi-Fi/Bluetooth todo en uno, integrada y certificada que proporciona no solo la radio inalámbrica, sino también un procesador integrado con interfaces para conectarse con varios periféricos|![image](https://user-images.githubusercontent.com/107783594/235006573-200eca33-0deb-406e-8a61-ba8f42dae3d0.png)|       1   |        $ 160    |
|002 |Servomotor  |Es un tipo de motor eléctrico que tiene la capacidad de controlar el movimiento de su eje, en velocidad, aceleración, par y posición|![image](https://user-images.githubusercontent.com/107783594/235006672-f7004afe-7038-426a-8b18-046267bd974a.png)|      1    |      $80       |
|003 |Dht11       |   Dispositivos utilizados en aplicaciones de edificación para medir la temperatura|![image](https://user-images.githubusercontent.com/107783594/235006780-99f9a317-6f21-4589-87d1-8d2354c974e2.png)|       1   |        $70     |
|004 |Buzzer     |  Es un pequeño transductor capaz de convertir la energía eléctrica en sonido.|![image](https://user-images.githubusercontent.com/107783594/235006859-09970f6f-c86d-437d-bd60-6725b08ae4ca.png)|      1    |         $60    |
|005 | Led       |   emite luz a través del paso de la corriente eléctrica|![image](https://user-images.githubusercontent.com/107783594/235006925-268d5da1-1ae8-46a1-af47-68ab59454596.png)|       8   |       $3      |
|006 |MQ-2 | Es un sensor de gas inflamable y humo que detecta las concentraciones de gas combustible en el aire y emite su lectura como un voltaje analógico.       |![image](https://user-images.githubusercontent.com/107783594/235006985-a2e865f5-7215-4325-a0c7-e2253550d278.png)|        1  |        $70     |
|007 |  Movimiento  |Es un dispositivo electrónico que pone en funcionamiento un sistema (encendido o apagado) cuando detecta movimiento en el área o ambiente en el que está instalado.|![image](https://user-images.githubusercontent.com/107783594/235007037-b57a4113-d6d2-46d6-8c9c-4bfa39db3720.png)|       1   |       $55      |



## Épicas de historias de Usuario
•	En movimiento que se enciendan las luces para una mejor seguridad.

•	También que se detecte tanto el humo como el gas y así sea una señal de alerta 

•	La casa se ventile dependiendo de una cierta temperatura.
 

## Tabla Historias de Usuario
| Id | Historia de usuario | Prioridad | Estimación | Como probarlo | Responsable |
|----|---------------------|-----------|------------|---------------|-------------|
|   001 |      Al detectar movimiento se enciendan los led | Alta|	1 semana|	Al pasar una persona|	Esmeralda
|   002 | La casa se ventile dependiendo de una cierta temperatura.	 |Media |	2 días  |	Depende de la temperatura. |	Omar
|  003  |  Que la casa detecte fugas de gas haga sonar un buzzer cuando el nivel sea alto|	Alta|	3 días| 	Al exponer el sensor a una fuga de gas.	|Michel

## Prototipo en dibujo


![image](https://user-images.githubusercontent.com/107783594/234896709-19f0f645-ba0f-47ce-984f-a3a972266d9d.png)

## Firma

![image](https://user-images.githubusercontent.com/107783594/234896922-e35d089f-750f-4153-b1ac-5ba42433b2e1.png)



