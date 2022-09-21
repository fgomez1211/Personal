// Define boolean inputs
int inA = 3;
int inB = 4;
int inC = 5;
int inD = 6;

int decA;
int decB;
int decC;
int decD;

int a = 7;
int b = 8;
int c = 9;
int d = 10;
int e = 11;
int f = 12;
int g = 13;



void setup() {

  pinMode (inA, INPUT);
  pinMode (inB, INPUT);
  pinMode (inC, INPUT);
  pinMode (inD, INPUT);
  
  pinMode (a, OUTPUT);
  pinMode (b, OUTPUT);
  pinMode (c, OUTPUT);
  pinMode (d, OUTPUT);
  pinMode (e, OUTPUT);
  pinMode (f, OUTPUT);
  pinMode (g, OUTPUT);

  Serial.begin(9600);
}
  
void loop() {
  

  if(digitalRead(inA)==HIGH){
    decA = 1;}
  else
  {
    decA = 0;
  }
  
  if(digitalRead(inB)==HIGH){
    decB = 2;}
  else
  {
    decB = 0;
  }

  if(digitalRead(inC)==HIGH){
    decC = 4;}
  else
  {
    decC = 0;
  }
  
  if(digitalRead(inD)==HIGH){
    decD = 8;}
  else
  {
    decD = 0;
  }
  
  int decimal = decA + decB + decC + decD;
  Serial.println(decimal);
  Serial.println(" ");
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
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);  
}
