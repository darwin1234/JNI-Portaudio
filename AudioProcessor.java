import javax.swing.*;
import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.control.Slider;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.geometry.Insets;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.scene.paint.Color;

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
				//Au.audio();
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
   public void start(Stage stage) throws Exception {
	    
      Label label = new Label("Gain:");
 
      Label infoLabel = new Label("-");
      infoLabel.setTextFill(Color.BLUE);
 
      Slider slider = new Slider();
 
      slider.setMin(0);
      slider.setMax(100);
      slider.setValue(80);
 
      slider.setShowTickLabels(true);
      slider.setShowTickMarks(true);
 
      slider.setBlockIncrement(10);
 
      // Adding Listener to value property.
      slider.valueProperty().addListener(new ChangeListener<Number>() {
 
         @Override
         public void changed(ObservableValue<? extends Number> observable, //
               Number oldValue, Number newValue) {
 
            infoLabel.setText("Gain: " + newValue);
         }
      });
 
      VBox root = new VBox();
      root.setPadding(new Insets(20));
      root.setSpacing(10);
      root.getChildren().addAll(label, slider, infoLabel);
 
      stage.setTitle("Audio Processor");
      Scene scene = new Scene(root, 550, 400);
      stage.setScene(scene);
      stage.show();
	
   }
	
 

   
 }