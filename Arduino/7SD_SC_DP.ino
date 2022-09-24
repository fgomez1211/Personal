//Definimos Entradas Digitales
int inA = 3;
int inB = 4;
int inC = 5;
int inD = 6;
int inE = 2;


//Estas variables van a llevar el peso de cada entrada digital.
//El resultado de esta operación, hará que se obtenga el valor 
// "decimal".
int decA;
int decB;
int decC;
int decD;
int decE;


//Definir salidas para el display de 7 segmentos.
int a = 7;
int b = 8;
int c = 9;
int d = 10;
int e = 11;
int f = 12;
int g = 13;


void setup() {
  
  //Definimos las variables digitales como entradas.
  pinMode(inA, INPUT);
  pinMode(inB, INPUT);
  pinMode(inC, INPUT);
  pinMode(inD, INPUT);
  pinMode(inE, INPUT);
  
  
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  Serial.begin(9600);
}
  
void loop() {
  
  if(digitalRead(inA)== HIGH){
    decA = 1;}
  else{
    decA = 0;
  }
  
  if(digitalRead(inB)== HIGH){
    decB = 2;}
  else{
    decB = 0;
  }
  
  if(digitalRead(inC)== HIGH){
    decC = 4;}
  else{
    decC = 0;
  }
  
  if(digitalRead(inD)== HIGH){
    decD = 8;}
  else{
    decD = 0;
  }
  
  if(digitalRead(inE)== HIGH){
    decE = 16;}
  else{
    decE = 0;
  }
  
  int decimal = decA + decB + decC + decD;
  

  display(decimal);
  delay(1);
  
  
 }           


void display(int decimal){
  switch (decimal){
    case 0:
    cero();
    break;
    
    case 1:
    uno();
    break;
    
    case 2:
    dos();
    break;
    
    case 3:
    tres();
    break;
    
    case 4:
    cuatro();
    break;
    
    case 5:
    cinco();
    break;
    
    case 6:
    seis();
    break;
    
    case 7:
    siete();
    break;
    
    case 8:
    ocho();
    break;
    
    case 9:
    nueve();
    break;
    
    default:
    decimal = 0;
    break; 
    
    case 10:
    letraA();
    break;
    
    case 11:
    letraB();
    break;
    
    case 12:
    letraC();
    break;
    
    case 13:
    letraD();
    break;
    
    case 14:
    letraE();
    break;
    
    case 15:
    letraF();
    break;
    
    case 16:
    letraG();
    break;
    
    case 17:
    letraH();
    break;
    
    case 18:
    letraI();
    break;
    
    case 19:
    letraJ();
    break;
    

    case 20:
    letraK();
    break;
    }
}





void cero(){
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
}

void uno(){
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
}

void dos(){
  	  digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
}

void tres(){
  	  digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
}

void cuatro(){
  	  digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
}

void cinco(){
   	  digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
}  

void seis(){
  	  digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
} 

void siete(){
  	  digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
}

void ocho(){
  	  digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
}

void nueve(){
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);  
}

void letraA(){
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
}

void letraB(){
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
}

void letraC(){
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
}

void letraD(){
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
}

void letraE(){
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
}

void letraF(){
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
}

void letraG(){
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
}

void letraH(){
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
}

void letraI(){
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
}

void letraJ(){
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
}

void letraK(){
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
}