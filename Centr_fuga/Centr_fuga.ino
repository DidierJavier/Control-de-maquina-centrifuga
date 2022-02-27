/*Dídier Javier Ramírez Henao
---------------------------------------------
Centrifugado controlando el tiempo y la velocidad del motor
---------------------------------------------
Programa con dos entradas análogas. Una para controlar el tiempo de centrifugado y la otra para controlar la velocidad
de rotación del motor. El motor se controla mediante salida por PWM.
*/
const int sensorPinA0 = A0;    // seleccionar la entrada para el sensor análogo (Potenciómetro de tiempo)
const int sensorPinA1 = A1;    // seleccionar la entrada para el sensor análogo (Potenciómetro de velocidad)
int sensorTiempo;       // variable que almacena el valor raw de la entrada análoga del potenciómetro que determina el tiempo de centrifugado(0 a 1024)
int sensorVelocidad;       // variable que almacena el valor raw de la entrada análoga del potenciómetro que determina la velocidad de centrifugado(0 a 1024)
int continuar = 0;//mientras sea igual a cero el usuario puede modificar el tiempo de centrifugado
int tiempo;     //variable para calcular el tiempo de centrifugado (entre 10 y 60 segundos)
int velocidad;  //Variable para modificar la velocidad de centrifugado
const int VelMotor = 9;    //Variable de salida para controlar la velocidad del motor por PWM (pin 9)
int porcentajeVelMotor;
void setup() 
{  
  Serial.begin(9600);//Iniciamos comunicación con el puerto serie
  Serial.setTimeout(1000);  //Para dar tiempo a que el usuario pulse un número para continuar
  pinMode (VelMotor,OUTPUT);         //Se configura la salida del pwm del motor (como salida*****pin 9)
} 
void loop() 
{
  while (continuar == 0)//El ciclo se repite hasta que el usuario digite un número distinto de cero
  {
    Serial.println("Seleccione el tiempo de centrifugado");    
    delay (3000);//Tiempo de espera para que el usuario ingrese el tiempo de centrifugado
    sensorTiempo = analogRead(sensorPinA0);   // realizar la lectura del potenciómetro (Entrada análoga A0**tiempo de centrifugado)
    tiempo = 0.1389*sensorTiempo - 75.4235; //fórmula hallada mediante ecuación de la recta. Relaciona tiempo de centrifugado(de 10 a 60 segundos) con la entrada análoga A0(sensorTiempo)
    Serial.print("Los segundos de centrifugado son: ");
    Serial.println(tiempo);
    Serial.println("Oprima una tecla diferente de cero si está seguro del tiempo seleccionado para continuar");
    Serial.println("*****************************************************************************************");
    Serial.println("*****************************************************************************************");
    delay (4000);//Retardo para esperar a que el usuario modifique el tiempo de centrifugado
    if (Serial.available() > 0) //Se entra al if si el usuario digita un número diferente de cero
    {    
      int num = Serial.readString().toInt();    //Se transforma la lectura a un número entero
      continuar = num; //El número se guarda en la variable continuar
    }  
  }//Se sale del while cuando el usuario digita un número distinto de cero
  continuar = 0;//Se restablece la variable continuar para un nuevo ciclo
  while (continuar == 0)//El ciclo se repite hasta que el usuario digite un número distinto de cero
    {
      Serial.println("Seleccione la velocidad de centrifugado");    
      delay (3000);//Tiempo de espera para que el usuario modifique la velocidad de centrifigado con el potenciómetro.
      sensorVelocidad = analogRead(sensorPinA1);   // realizar la lectura del potenciómetro (Entrada análoga A1**velocidad de centrifugado)
      velocidad = 0.625*sensorVelocidad - 384.375; //fórmula hallada mediante ecuación de la recta. Relaciona velocidad de centrifugado con la entrada análoga A1(sensorVelocidad)
      porcentajeVelMotor = 0.392157*velocidad;    //Variable que guarda el porcentaje de velocidad de centrifugado
      Serial.print(" Velocidad de centrifugado al: ");
      Serial.print(porcentajeVelMotor);//Se informa al usuario el porcentaje de velocidad de centrifugado. Puede modificarla antes o durante el proceso de centrifugado
      Serial.println("por ciento");
      Serial.println("La velocidad de centrifugado la puede modificar durante el proceso de centrifugado");
      Serial.println("Oprima un número diferente de cero si está seguro de la velocidad de centrifugado");
      Serial.println("*****************************************************************************************");
      Serial.println("*****************************************************************************************");
      delay (4000);//Tiempo de espera para que el usuario seleccione la velocidad de centrifugado
      if (Serial.available() > 0) //Se entra al if si el usuario digita un número diferente de cero
      {    
        int num = Serial.readString().toInt();    //Se transforma la lectura a un número entero
        continuar = num;//el número ingresado se guarda en la variable continuar        
      }    
   }//Se sale del while si continuar es diferente de cero
   Serial.println("Iniciando centrifugado");
   continuar = 0; //Se restaura continuar en cero para cuando hayan nuevos procesos de centrifugado
   for (int i = 0; i <= tiempo; i++)//Ciclo for que dura el tiempo de centrifugado
   {
     sensorVelocidad = analogRead(sensorPinA1);//Se actualiza el estado del sensor de velocidad
     velocidad = 0.625*sensorVelocidad - 384.375;//Se actualiza la variable velocidad
     Serial.println("********************************************************************************************");
     analogWrite(VelMotor,velocidad);//El valor de la velocidad se envía a la salida por PWM (pin 9)
     delay (1000);//Retardo para ir contando los segundos de centrifugado
     porcentajeVelMotor = 0.392157*velocidad;    //Variable que guarda el porcentaje de velocidad de centrifugado
     Serial.print("Velocidad de centrifugado al: ");
     Serial.print(porcentajeVelMotor);//Se informa al usuario el porcentaje de velocidad de centrifugado. Puede modificarla antes o durante el proceso de centrifugado
     Serial.println("por ciento");
     Serial.println(i);  //Se imprime en pantalla los segundos que van transcurriendo del centrifugado  
   }   
   sensorVelocidad = analogRead(sensorPinA1);//Se actualiza el estado del sensor de velocidad
   velocidad =0;//Se actualiza la variable velocidad
   analogWrite(VelMotor,velocidad);//El valor de la velocidad se envía a la salida por PWM (pin 9)
   Serial.println("////////////////////////////////////////////////////////////////////////////////////////////");
   Serial.println("Centrifugado exitoso. Dídier Javier Ramírez Henao");
   delay (2000);
   Serial.println("////////////////////////////////////////////////////////////////////////////////////////////");
   while (continuar == 0)//El ciclo se repite hasta que el usuario digite un número distinto de cero
   {
     Serial.println("");    
     Serial.println("Oprima un número diferente de cero si desea realizar otro centrifugado");
     Serial.println("*****************************************************************************************");
     Serial.println("*****************************************************************************************");
     delay (4000);//Tiempo de espera para que el usuario oprima un número diferente de cero y realice otro centrifugado
     if (Serial.available() > 0) //Se entra al if si el usuario digita un número diferente de cero
     {    
       int num = Serial.readString().toInt();    //Se transforma la lectura a un número entero
       continuar = num;//el número ingresado se guarda en la variable continuar
     }    
   }//Se sale del while si continuar es diferente de cero
   continuar = 0; //Se restable el valor de la variable continuar para un nuevo ciclo   
}
