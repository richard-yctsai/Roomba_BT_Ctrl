void checkBTcmd()  // verify if a command is received from BT remote control
 { 
    if (BT1.available()) 
    { 
      command = BT1.read();
      BT1.flush();
    }
    if (Serial.available()) 
    { 
      command = Serial.read();
      Serial.flush();
    }
 }
 
 //******************************************************************************//

void manualCmd()
{
  switch (command)
  {
    
    case 'm': 
      startSafe();
      Serial.println("Roomba in Safe mode");
      BT1.println("Roomba BT Ctrl OK - Safe mode");
      command = 's';
      playSound (3);
      break;

    case 'f': 
      startFull();
      Serial.println("Roomba in Full mode");
      BT1.println("Roomba BT Ctrl OK - Full mode");
      command = 's';
      playSound (3);
      break;     

    case 's': 
      driveStop(); //turn off both motors
      writeLEDs ('s', 't', 'o', 'p');
//      Serial.println("Roomba stops by turing off both motors");
//      BT1.println("Roomba stops by turing off both motors");
      state = command;
      break;

    case 'g':  
      drive (motorSpeed, 0); 
      writeLEDs (' ', 'g', 'o', ' ');
//      Serial.println("Roomba go forward");
//      BT1.println("Roomba go forward");
      state = command;  
      break;

    case 'r':     
      driveRight(motorSpeed);
      writeLEDs ('r', 'i', 'g', 'h');
//      Serial.println("Roomba go right");
//      BT1.println("Roomba go right");
      break;

   case 'l': 
      driveLeft(motorSpeed);
      writeLEDs ('l', 'e', 'f', 't');
//      Serial.println("Roomba go left");
//      BT1.println("Roomba go left");
      break;
    
    case 'b':  
      drive (-motorSpeed, 0);
      writeLEDs ('b', 'a', 'c', 'k');
//      Serial.println("Roomba go back");
//      BT1.println("Roomba go back");
      state = command;
      break;

    case '+': 
      if (state == 'g')
      {
        motorSpeed = motorSpeed + 10;
        if (motorSpeed > MAX_SPEED) 
        { 
          motorSpeed = MAX_SPEED;
        }  
        command = 'g';
      } 
      else 
      {
        command = state;
      }
      break;

    case '-': 
      if (state == 'g')
      {
        motorSpeed = motorSpeed - 10;
        if (motorSpeed < MIN_SPEED ) 
        { 
          motorSpeed = MIN_SPEED;
        }
        command = 'g';
      }
      else 
      {
        command = state;
      }
      break;
  }
}
