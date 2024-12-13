import processing.serial.*;

Serial myPort;

// Shape selection
String[] shapes = {"Circle", "Rectangle", "Triangle"};
int currentShape = 0;

// Color values for each shape
int[][] colorVals = {
  {0, 0, 0},    // Circle RGB
  {0, 0, 0},    // Rectangle RGB
  {0, 0, 0}     // Triangle RGB
};

// Button properties
int buttonX = 150;
int buttonY = 280;
int buttonW = 100;
int buttonH = 30;
boolean buttonHover = false;

// Shape selection button
int shapeButtonX = 270;
int shapeButtonY = 280;
int shapeButtonW = 100;
int shapeButtonH = 30;

void setup() {
  size(400, 350);
  String portName = Serial.list()[2];
  println(portName);
  myPort = new Serial(this, portName, 115200); 
}

void draw() {
  background(200);

  // Draw sliders for current shape
  fill(255, 0, 0);
  rect(50, 50, 300, 20);
  fill(0);
  ellipse(50 + colorVals[currentShape][0], 60, 20, 20);

  fill(0, 255, 0);
  rect(50, 100, 300, 20);
  fill(0);
  ellipse(50 + colorVals[currentShape][1], 110, 20, 20);

  fill(0, 0, 255);
  rect(50, 150, 300, 20);
  fill(0);
  ellipse(50 + colorVals[currentShape][2], 160, 20, 20);

  // Display selected color for current shape
  fill(colorVals[currentShape][0], colorVals[currentShape][1], colorVals[currentShape][2]);
  rect(150, 200, 100, 50);

  // Display shape name and its RGB values
  fill(0);
  textAlign(LEFT, BASELINE);
  text(shapes[currentShape] + " - R: " + colorVals[currentShape][0] + 
       " G: " + colorVals[currentShape][1] + 
       " B: " + colorVals[currentShape][2], 50, 270);

  // Draw submit button
  if (mouseX > buttonX && mouseX < buttonX + buttonW && 
      mouseY > buttonY && mouseY < buttonY + buttonH) {
    fill(100);
    buttonHover = true;
  } else {
    fill(150);
    buttonHover = false;
  }
  
  rect(buttonX, buttonY, buttonW, buttonH);
  fill(0);
  textAlign(CENTER, CENTER);
  text("Submit", buttonX + buttonW/2, buttonY + buttonH/2);

  // Draw shape selection button
  if (mouseX > shapeButtonX && mouseX < shapeButtonX + shapeButtonW && 
      mouseY > shapeButtonY && mouseY < shapeButtonY + shapeButtonH) {
    fill(100);
  } else {
    fill(150);
  }
  
  rect(shapeButtonX, shapeButtonY, shapeButtonW, shapeButtonH);
  fill(0);
  text(shapes[currentShape], shapeButtonX + shapeButtonW/2, shapeButtonY + shapeButtonH/2);
  
  textAlign(LEFT, BASELINE);
}

void mouseDragged() {
  if (mouseY > 40 && mouseY < 80) {
    colorVals[currentShape][0] = constrain(mouseX - 50, 0, 300);
  }
  if (mouseY > 90 && mouseY < 130) {
    colorVals[currentShape][1] = constrain(mouseX - 50, 0, 300);
  }
  if (mouseY > 140 && mouseY < 180) {
    colorVals[currentShape][2] = constrain(mouseX - 50, 0, 300);
  }
}

void mousePressed() {
  // Check if color submit button is clicked
  if (mouseX > buttonX && mouseX < buttonX + buttonW && 
      mouseY > buttonY && mouseY < buttonY + buttonH) {
    sendColor();
  }
  
  // Check if shape button is clicked
  if (mouseX > shapeButtonX && mouseX < shapeButtonX + shapeButtonW && 
      mouseY > shapeButtonY && mouseY < shapeButtonY + shapeButtonH) {
    currentShape = (currentShape + 1) % shapes.length;
    sendShape();
  }
}

void sendColor() {
  String colorData = "C," + 
                     colorVals[currentShape][0] + "," + 
                     colorVals[currentShape][1] + "," + 
                     colorVals[currentShape][2];
  myPort.write(colorData + "\n");
  println("Sent color for " + shapes[currentShape] + ": " + colorData);
}

void sendShape() {
  String shapeData = "S," + currentShape;
  myPort.write(shapeData + "\n");
  println("Switched to: " + shapes[currentShape]);
}
