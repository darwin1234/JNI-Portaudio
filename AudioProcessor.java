import javax.swing.*;
import javafx.application.Application;
import javafx.stage.Stage;



public class AudioProcessor extends Application {  
   static {
		System.loadLibrary("AudioProcessor"); 
                                 
   }
 
 
   private native void sinewave();
 

   public static void main(String[] args) {
	    
		AudioProcessor Au = new AudioProcessor();
		Au.ProcessApp();
		
		 Thread t1 = new Thread(new Runnable(){
		   
			public void run(){
				 Application.launch(AudioProcessor.class, args);  // correct
				
			}
	   });
	   
	   
	    Thread t2 = new Thread(new Runnable(){
			public void run(){
				Au.audio();
			}
	   });
	   
	   t1.start();
	   t2.start();
	   
	   try{
		   t1.join();
		   t2.join();
	   }catch(InterruptedException e){
		   e.printStackTrace();
	   }
	 
   }
   
   
   public void ProcessApp(){
	  
	   
   }
   
   public synchronized void audio(){
	   new AudioProcessor().sinewave();
		
   }
   
   @Override
   public void start(Stage primaryStage) throws Exception {
        primaryStage.setTitle("Audio Processor");
        primaryStage.show();
   }
	
 

   
 }