# **Shape Art on TFT Display**

This project combines creative coding and hardware interaction to allow users to design, customize, and animate shapes on a TFT display using an Arduino. The interface is powered by Processing, enabling user-friendly color and shape selection. The chosen design is transmitted to the TFT display, where users can toggle animations and watch their creations come to life.

---

## **Design Goals**

1. **User Creativity**: Users can select colors and shapes and watch their designs come to life through animations on a TFT display.

2. **Dynamic Animations**: Implement pulsing and smooth animations to make the display engaging and interactive.

3. **Seamless Integration**: Establish reliable communication between Processing and Arduino for real-time design updates.

---

## **Installation Setup**

### **Materials Needed**

1. ESP32 or Arduino with a compatible TFT display (e.g., ESP32 TTGO T-display).
2. Button for animation toggling.
3. Wires and breadboard for connections.
4. A computer with Arduino IDE and Processing installed.
5. Access to a 3D printer for creating the enclosure.

---

## **How to Replicate**

### **Hardware Setup**

1. Connect the TFT display to your microcontroller:
   - **Power**: 3.3V or 5V (check your display requirements).
   - **Communication Pins**: Connect SPI pins (MOSI, MISO, SCLK, etc.) to your microcontroller.
   
2. Connect a button to a GPIO pin and ground to toggle animations.

---

### **3D Printing the Enclosure**

To create a custom enclosure for your project:

1. **Download the STL Files**:
   - The repository includes two files:
     - `Assembly 1.stl` – Base of the enclosure.
     - `Assembly 2.stl` – Top cover of the enclosure.

2. **Prepare for Printing**:
   - Import the STL files into your preferred slicing software (e.g., Cura, PrusaSlicer).
   - Set the following printing parameters:
     - **Layer Height**: 0.2mm
     - **Infill**: 20% (or as needed for strength)
     - **Material**: PLA/ABS (depending on your preference)
     - **Supports**: Only for overhangs, if needed.

3. **Print the Files**:
   - Print `Assembly 1.stl` and `Assembly 2.stl` separately.

4. **Assemble**:
   - Secure the components inside the enclosure, ensuring proper alignment with the display window and button cutout.

![Enclosure Example](https://github.com/user-attachments/assets/82dbb7dc-deff-49fa-909d-fa89d4f47d7b)

---

## **Software Setup**

1. **Install Libraries**:
   - Install the `TFT_eSPI` library from the Arduino Library Manager.
   - Install the `Serial` library in Processing.

2. **Load Arduino Code**:
   - Open the provided Arduino sketch in the Arduino IDE.
   - Upload the code to your microcontroller.

3. **Run Processing Sketch**:
   - Open the Processing sketch.
   - Select the appropriate serial port for communication.
   - Run the sketch and interact with the GUI to send commands to the TFT display.
