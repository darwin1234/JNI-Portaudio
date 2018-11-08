import javax.swing.*;

public class AudioProcessor {  // Save as HelloJNI.java
   static {
		System.loadLibrary("AudioProcessor"); // Load native library hello.dll (Windows) or libhello.so (Unixes)
                                   //  at runtime
                                   // This library contains a native method called sayHello()
   }
 
   // Declare an instance native method sayHello() which receives no parameter and returns void
   private native void sinewave();
 
   // Test Driver
   public static void main(String[] args) {
	   new AudioProcessor().sinewave();  // Create an instance and invoke the native method
	   JFrame frame = new JFrame("Audio Processor");
       frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
       frame.setSize(400,400);
       JButton button = new JButton("Press");
       frame.getContentPane().add(button); // Adds Button to content pane of frame
       frame.setVisible(true);
   }
}