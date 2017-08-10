package komunikacija;
import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.Date;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFormattedTextField;
import javax.swing.JFrame;
import javax.swing.JPanel;
import com.fazecast.jSerialComm.SerialPort;
public class prozor {

	static SerialPort chosenPort;
	
	public static void main(String[] args) {
		int zoki=1;
		int width = 100;
		byte [] data = new byte [2]; 
		// create and configure the window
				JFrame window = new JFrame();
				window.setTitle("Arduino");
				window.setSize(400, 75);
				window.setLayout(new BorderLayout());
				window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				
				// create a drop-down box and connect button, then place them at the top of the window
				JComboBox<String> portList = new JComboBox<String>();
				JButton connectButton = new JButton("Connect");
				JPanel topPanel = new JPanel();
				JFormattedTextField temperatura = new JFormattedTextField();
				topPanel.add(portList);
				topPanel.add(connectButton);
				topPanel.add(temperatura);
				window.add(topPanel, BorderLayout.NORTH);
				
				// populate the drop-down box
				SerialPort[] portNames = SerialPort.getCommPorts();
				for(int i = 0; i < portNames.length; i++)
					portList.addItem(portNames[i].getSystemPortName());
				
				// configure the connect button and use another thread to send data
				connectButton.addActionListener(new ActionListener(){
					@Override public void actionPerformed(ActionEvent arg0) {
						if(connectButton.getText().equals("Connect")) {
							// attempt to connect to the serial port
							chosenPort = SerialPort.getCommPort(portList.getSelectedItem().toString());
							chosenPort.setComPortTimeouts(SerialPort.TIMEOUT_SCANNER, 0, 0);
							if(chosenPort.openPort()) {
								connectButton.setText("Disconnect");
								portList.setEnabled(false);
								// create a new thread for sending data to the arduino
								Thread thread = new Thread(){
									@Override public void run() {
										// wait after connecting, so the bootloader can finish
										try {Thread.sleep(100); } catch(Exception e) {}

										// enter an infinite loop that sends text to the arduino
										PrintWriter output = new PrintWriter(chosenPort.getOutputStream());
										while(true) {
											data[0] = (byte) (width & 0xFF);
											data[1] = (byte) ((width >> 8) & 0xFF);
											output.write(data[0]);
											output.write(data[1]);
											output.flush();
											try {Thread.sleep(100); } catch(Exception e) {}
										}
									}
								};
								thread.start();
							}
						} else {
							// disconnect from the serial port
							chosenPort.closePort();
							portList.setEnabled(true);
							connectButton.setText("Connect");
						}
					}
				});
				
				// show the window
				window.setVisible(true);

	}

}
