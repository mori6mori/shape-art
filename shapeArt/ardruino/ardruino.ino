#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

// Current color and shape
uint16_t currentColor = TFT_BLACK;
int currentShape = 0; // 0=Circle, 1=Rectangle, 2=Triangle

// Animation variables
const int BUTTON_PIN = 0;  // GPIO0 for left button
bool isAnimating = false;
int animationStep = 0;
unsigned long lastAnimationTime = 0;
const int ANIMATION_DELAY = 50;  // Animation speed in milliseconds
const int MAX_SIZE = 100;
const int MIN_SIZE = 20;
int currentSize = 60;
bool growing = true;

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  Serial.begin(115200);
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Setup button pin
}

void loop() {
  // Check button state
  if (digitalRead(BUTTON_PIN) == LOW) {  // Button is pressed (active low)
    isAnimating = !isAnimating;  // Toggle animation
    delay(200);  // Debounce
  }

  // Handle animation
  if (isAnimating && (millis() - lastAnimationTime > ANIMATION_DELAY)) {
    tft.fillScreen(TFT_BLACK);
    drawAnimatedShape();
    lastAnimationTime = millis();
  }

  // Handle serial commands
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    char type = data.charAt(0);
    
    if (type == 'C') { // Color data
      processColor(data.substring(2));
    } else if (type == 'S') { // Shape data
      currentShape = data.substring(2).toInt();
      Serial.println("Shape set to: " + String(currentShape));
    }
  }
}

void processColor(String colorData) {
  int commaIndex1 = colorData.indexOf(',');
  int commaIndex2 = colorData.lastIndexOf(',');

  if (commaIndex1 != -1 && commaIndex2 != -1) {
    int red = colorData.substring(0, commaIndex1).toInt();
    int green = colorData.substring(commaIndex1 + 1, commaIndex2).toInt();
    int blue = colorData.substring(commaIndex2 + 1).toInt();

    currentColor = tft.color565(red, green, blue);
    tft.fillScreen(TFT_BLACK);
    drawShape();
    
    Serial.printf("RGB: %d,%d,%d\n", red, green, blue);
  }
}

void drawAnimatedShape() {
  // Update size for pulsing animation
  if (growing) {
    currentSize += 2;
    if (currentSize >= MAX_SIZE) {
      growing = false;
    }
  } else {
    currentSize -= 2;
    if (currentSize <= MIN_SIZE) {
      growing = true;
    }
  }
  
  // Draw the shape with current animation state
  int centerX = tft.width() / 2;
  int centerY = tft.height() / 2;
  
  switch (currentShape) {
    case 0: // Circle
      tft.fillCircle(centerX, centerY, currentSize, currentColor);
      break;
      
    case 1: // Rectangle
      tft.fillRect(centerX - currentSize, centerY - currentSize, 
                   currentSize * 2, currentSize * 2, currentColor);
      break;
      
    case 2: // Triangle
      // Define triangle points with animation
      int x1 = centerX;
      int y1 = centerY - currentSize;
      int x2 = centerX - currentSize;
      int y2 = centerY + currentSize;
      int x3 = centerX + currentSize;
      int y3 = centerY + currentSize;
      
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, currentColor);
      break;
  }
}

void drawShape() {
  currentSize = 60;  // Reset size when drawing static shape
  int centerX = tft.width() / 2;
  int centerY = tft.height() / 2;
  
  switch (currentShape) {
    case 0: // Circle
      tft.fillCircle(centerX, centerY, currentSize, currentColor);
      break;
      
    case 1: // Rectangle
      tft.fillRect(centerX - currentSize, centerY - currentSize, 
                   currentSize * 2, currentSize * 2, currentColor);
      break;
      
    case 2: // Triangle
      // Define triangle points
      int x1 = centerX;
      int y1 = centerY - currentSize;
      int x2 = centerX - currentSize;
      int y2 = centerY + currentSize;
      int x3 = centerX + currentSize;
      int y3 = centerY + currentSize;
      
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, currentColor);
      break;
  }
}