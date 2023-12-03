**CONTROLADOR PARA LA ARTICULACION DE UN BRAZO ROBOTICO**

El controlador fue desarrollado para la articulación del brazo robótico SCORBOT-ER 9 de la marca INTELITEK.

El tipo de control a diseñado es en base a pasos. Este funciona a través del conteo de pasos necesarios para mover 
la articulación cierta cantidad de grados. Los grados de rotación serán definidos por el usuario en el programa y este 
se encargará de calcular y contar los pasos necesarios en el encoder. Una vez el contador alcance la cantidad de pasos 
definida, la articulación habrá llegado a la posición ingresada.

La topología, el diagrama de proceso y el código fuente para las articulaciones 1 y 2 se incluyen en este repositorio.
