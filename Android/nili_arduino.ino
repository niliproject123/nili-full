// tasks :
//* adapt to 12 colummns
//* change output string to 01r02g

///changed the line

  int btStatusCharIndex = 0;
  char c;
  String strPreviousPressed = "";
  String strCurrentPressed = "";
  int statusCharArray_length = 0;
  char statusCharArray[100] = {};
  char btCharArray[100] = {};
  char   switchBuffer[100] = {};
  int led[] =          {12, 24, 20, 21, 25, 2, 3, 4, 5, 6, 7, 8, 9};   
  int push_button[]  = {12, 26, 22, 23, 27, 2, 3, 4, 5, 6, 7, 8, 9};
  int red[] = {6, 28, 30, 32, 34, 36, 38};
  int green[] = {6, 43, 45, 47, 49, 51, 53};
  int blue[] = {6, 29, 31, 33, 35, 37, 39};
  int rowsSwitch[] = {6, 42, 44, 46, 48, 50, 52};


void testLeds_white() {
  for(int i=1; i<=red[0]; i++) {
    digitalWrite (red[i], LOW);
    digitalWrite (green[i], LOW);
    digitalWrite (blue[i], LOW);
  }
    
  for(int colIndex = 1; colIndex<=led[0]; colIndex++) {
    digitalWrite (led[colIndex] , HIGH);
  }


  delay(600);

  for(int colIndex = 1; colIndex<=led[0]; colIndex++) {
    digitalWrite (led[colIndex] , LOW);
  }

  for(int i=1; i<=red[0]; i++) {
    digitalWrite (red[i], HIGH);
    digitalWrite (green[i], HIGH);
    digitalWrite (blue[i], HIGH);
  }
}


void testLeds() {
  /*
  char   buffer[100];
  int colors[3][7];
  for(int i=1; i<=red[0]; i++) {
    colors[0][i] = red[i];
    colors[1][i] = blue[i];
    colors[2][i] = green[i];
  }

  for(int color=0; color<3; color++) {
    int totalColCount = 4;

    for(int row=1; row<=7; row++) {
      digitalWrite (colors[color][row], LOW);
    }

    int colIndex = 1;
    for(; colIndex<=totalColCount; colIndex++) {
//      sprintf(buffer,"col: %d",led[colIndex-1]);
//      Serial.println(buffer);
      digitalWrite (led[colIndex] , HIGH);
      delay(70);
      digitalWrite (led[colIndex] , LOW);
    }

    for(int row=1; row<=7; row++) {
      digitalWrite (colors[color][row], HIGH);
    }
  }
  */
}


// the setup function runs once when you press reset or power the board
void setup() {

  // initialize digital pin LED_BUILTIN as an output.
  // type reqd_pullup for switch

  
  //__ROWS__
  // color green
   for (int i=1; i<=green[0]; i++)
  {
     pinMode (  green[i] ,OUTPUT);
     digitalWrite ( green[i] ,HIGH);
  }
  
  // color red
   for (int i=1; i<=red[0]; i++)
  {
     pinMode (  red[i] ,OUTPUT);
     digitalWrite (  red[i] ,HIGH);
  }
  
  // color blue
  for (int i=1; i<=blue[0]; i++)
  {
     pinMode (  blue[i] ,OUTPUT);
     digitalWrite (  blue[i] , HIGH);
  }

  //rows switch
   for (int i=1; i<=rowsSwitch[0]; i++)
  {
     pinMode (  rowsSwitch[i] ,OUTPUT);
     digitalWrite (  rowsSwitch[i] ,LOW);
  }
  
  // __COLUMNS__
  for (int i=1; i<=led[0]; i++)
  {
     pinMode ( led[i] , OUTPUT);
     //digitalWrite (led[i], HIGH);
  }

  for (int i=1; i<=push_button[0]; i++)
  {
     pinMode ( push_button[i] , INPUT_PULLUP);
  }
  //pinMode ( push_button[2] , INPUT);

  
  
  
  ///////////////// INITIALIZE BLUETOOTH AND PRINT OUT /////////////////
  Serial.begin (115200); // print to system out
  Serial1.begin (9600);// bluetooth, pins 19,18

  testLeds_white(); 
}

// the loop function runs over and over again forever
void loop() {

  boolean isNewRead = false;
  // while bluetooth is avalable
  while (Serial1.available()) {
    isNewRead = true;
    c =  Serial1.read();
    if(c=='#') {
      statusCharArray_length = btStatusCharIndex;
      for(int copyIndex=0; copyIndex<statusCharArray_length; copyIndex++) {
        statusCharArray[copyIndex] = btCharArray[copyIndex];
      }
      btStatusCharIndex = 0;
      continue;
    }
    btCharArray[btStatusCharIndex] = c;
    btStatusCharIndex++;
  }

  if(isNewRead) {
    Serial.println(statusCharArray);
    isNewRead = false;
  }

  //////////////////////////////////// TURN ON LEDS ////////////////////////////////////
 
  for (int i=1; i<=led[0]; i++) {pinMode (  led[i] ,OUTPUT);} ////////////////////////////////////////// because led column 2 is phisycally connected to switch column 2 (cause johsnon is manyac
  for (int i=1; i<=push_button[0]; i++) {pinMode (  push_button[i] ,OUTPUT);} ////////////////////////////////////////// because led column 2 is phisycally connected to switch column 2 (cause johsnon is manyac

  //turn on leds
  int n;
  for (int i=0; i<statusCharArray_length; i++) {
    char color = statusCharArray[i];
    //Serial.println(color);
    i++;
    if (48 <= statusCharArray[i] && statusCharArray[i] <= 57 ) // if statusCharArray[i] is digit
    {
      if (48 <= statusCharArray[i+1] && statusCharArray[i+1] <= 57 )
      {
        n = (statusCharArray[i]-48)*10 + (statusCharArray[i+1]-48);
        i++;
      } 
      else {n = (statusCharArray[i]-48);}
    }
    
    int column;
    int row;
    if(n%6 == 0)
    {
      row = 6;
      column = n/6;
    }
    else
    {
      row = n%6;
      column = floor(n/6) +1;
    }
    
    // do something different depending on the color value:
    switch (color) {
      case 'r':    // red
        digitalWrite (  led[column] , HIGH);
        digitalWrite (  red[row], LOW);
        delay (1);
        digitalWrite (  led[column] , LOW);
        digitalWrite (  red[row], HIGH);
        break;
      case 'g':    // green
        digitalWrite (  led[column] , HIGH);
        digitalWrite (  green[row], LOW);
        delay (1);
        digitalWrite (  led[column] , LOW);
        digitalWrite (  green[row], HIGH);
        break;
      case 'b':    // blue
        digitalWrite (  led[column] , HIGH);
        digitalWrite (  blue[row], LOW);
        delay (1);
        digitalWrite (  led[column] , LOW);
        digitalWrite (  blue[row], HIGH);
        break;
      case 'w':    // white
        digitalWrite (  led[column] , HIGH);
        digitalWrite (  red[row], LOW);
        digitalWrite (  green[row], LOW);
        digitalWrite (  blue[row], LOW);
        delay (1);
        digitalWrite (  led[column] , LOW);
        digitalWrite (  red[row], HIGH);
        digitalWrite (  green[row], HIGH);
        digitalWrite (  blue[row], HIGH);
        break;
      case 'p':    // white
        digitalWrite (  led[column] , HIGH);
        digitalWrite (  red[row], LOW);
        digitalWrite (  blue[row], LOW);
        delay (1);
        digitalWrite (  led[column] , LOW);
        digitalWrite (  red[row], HIGH);
        digitalWrite (  blue[row], HIGH);
        break;
      case 'y':    // white
        digitalWrite (  led[column] , HIGH);
        digitalWrite (  red[row], LOW);
        digitalWrite (  green[row], LOW);
        delay (1);
        digitalWrite (  led[column] , LOW);
        digitalWrite (  red[row], HIGH);
        digitalWrite (  green[row], HIGH);
        break;
      case 'a':    // test
        digitalWrite (  led[column] , HIGH);
        digitalWrite (  green[row], LOW);
        digitalWrite (  blue[row], LOW);
        delay (1);
        digitalWrite (  led[column] , LOW);
        digitalWrite (  green[row], HIGH);
        digitalWrite (  blue[row], HIGH);
        break;
    }
     
  }
   
  //////////////////////////// CHECK PRESSED BUTTONS //////////////////////////////////
  // now check which button is pressed. pushbutton's logic is inverted. It goes
  // HIGH when it's open, and LOW when it's pressed.
  
  //turn rows switches 'off'.
  for (int i=1; i<=rowsSwitch[0]; i++) {pinMode (  rowsSwitch[i] ,INPUT);}
  for (int i=1; i<=led[0]; i++) {pinMode (  led[i] ,INPUT);} ////////////////////////////////////////// because led column 2 is phisycally connected to switch column 2 (cause johsnon is manyac
  for (int i=1; i<=push_button[0]; i++) {pinMode (  push_button[i] ,INPUT_PULLUP);} ////////////////////////////////////////// because led column 2 is phisycally connected to switch column 2 (cause johsnon is manyac
  strCurrentPressed = "";
  
  //runs on rows switches
  for (int rowIndex=1; rowIndex<=rowsSwitch[0]; rowIndex++)
  {    
    pinMode ( rowsSwitch[rowIndex], OUTPUT);
    digitalWrite ( rowsSwitch[rowIndex],LOW);
    int numColumns = push_button[0];
    //runs on columns.
    for (int colIndex=1; colIndex<=numColumns; colIndex++)
    {
      //add [rowIndex,colIndex] to output string to app
      if(digitalRead(push_button[colIndex])==LOW) { 
          int pos = (colIndex-1)*6 + rowIndex;
          sprintf(switchBuffer,"s%02d",pos);
          strCurrentPressed = strCurrentPressed + (String(switchBuffer));
      }
    }
    pinMode ( rowsSwitch[rowIndex], INPUT);
  }

  
  // after we have current pressed buttons we compare strCurrentPressed with strPreviousPressed
  // and send strCurrentPressed to App only if there is a change from previous
  if(strCurrentPressed != strPreviousPressed)
  {
    // send strCurrentPressed to app.
    Serial1.print(strCurrentPressed + '#');
    Serial.println(strCurrentPressed + '#');
    strPreviousPressed = strCurrentPressed; 
  }
}
  
    


