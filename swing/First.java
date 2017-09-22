import java.awt.BorderLayout;
import java.awt.EventQueue;
import java.awt.TextArea;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JTextArea;
import javax.swing.JButton;
import javax.swing.JScrollPane;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.io.BufferedReader;
import java.io.InputStreamReader;

import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JToolBar;
import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.JMenuItem;
import javax.swing.JTextField;

import java.io.*;
import java.net.*;
import javax.swing.JLabel;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import javax.swing.JRadioButton;
import javax.swing.ButtonGroup;

public class First extends JFrame {
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					First frame = new First();
					frame.setVisible(true);
					// try to add client
					frame.client = null;
					String host = frame.client.DEFAULT_HOST;;
				    int port = frame.client.DEFAULT_PORT;
				    try {
				        frame.client = frame.new Client(host, port);
				      }
				      catch (Exception e) {
				        System.err.println("Client: Couldn't connect to "+host+":"+port);
				        System.exit(1);
				      }
				      
				      System.out.println("Client connected to "+host+":"+port);
				      					
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
	//////////////////////////////////////////////////////////////////////////
	

	final class Client
	{
	  //private static final long serialVersionUID = 1L;
	  static final String DEFAULT_HOST = "localhost";
	  static final int DEFAULT_PORT = 3332;
	  private Socket sock;
	  private BufferedReader input;
	  private BufferedWriter output;

	  
	  ///
	  /// Initialise la connexion.
	  /// Renvoie une exception en cas d'erreur.
	  ///
	  public Client(String host, int port) throws UnknownHostException, IOException {
	    try {
	      sock = new java.net.Socket(host, port);
	    }
	    catch (java.net.UnknownHostException e) {
	      System.err.println("Client: Couldn't find host "+host+":"+port);
	      throw e;
	    }
	    catch (java.io.IOException e) {
	      System.err.println("Client: Couldn't reach host "+host+":"+port);
	      throw e;
	    }
	    
	    try {
	      input = new BufferedReader(new InputStreamReader(sock.getInputStream()));
	      output = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream()));
	    }
	    catch (java.io.IOException e) {
	      System.err.println("Client: Couldn't open input or output streams");
	      throw e;
	    }
	  }
	  
	  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	  
	  ///
	  /// Envoie une requete au server et retourne sa reponse.
	  /// Noter que la methode bloque si le serveur ne repond pas.
	  ///
	  public String send(String request) {
	    // Envoyer la requete au serveur
	    try {
	      request += "\n";  // ajouter le separateur de lignes
	      output.write(request, 0, request.length());
	      output.flush();
	    }
	    catch (java.io.IOException e) {
	      System.err.println("Client: Couldn't send message: " + e);
	      return null;
	    }
	    
	    // Recuperer le resultat envoye par le serveur
	    try {
	      return input.readLine();
	    }
	    catch (java.io.IOException e) {
	      System.err.println("Client: Couldn't receive message: " + e);
	      return null;
	    }
	  }
	

	}
	/////////////////////////////////////////////////////////////////////////
	private JTextArea textArea;
	
	private JPanel contentPane;
	private final Action play = new SwingAction_3();
	private final Action search = new SwingAction_4();
	private final Action del = new SwingAction_5();

	/**
	 * Launch the application.
	 */
	Client client;
	private JTextField textField;
	private final ButtonGroup buttonGroup = new ButtonGroup();
	
	
	/**
	 * Create the frame.
	 */
	public First() {
		
		final long serialVersionUID = 1L;
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		
		JMenuBar menuBar = new JMenuBar();
		setJMenuBar(menuBar);
		
		JMenu mnNewMenu = new JMenu("Actions Menu");
		menuBar.add(mnNewMenu);
		
		
		JMenuItem BonjourMenuItem = new JMenuItem("search");
		BonjourMenuItem.setAction(search);
		mnNewMenu.add(BonjourMenuItem);
		
		JMenuItem mntmNewMenuItem = new JMenuItem("play");
		mntmNewMenuItem.setAction(play);
		mnNewMenu.add(mntmNewMenuItem);
		
		JMenuItem mntmNewMenuItemDel = new JMenuItem("delete");
		mntmNewMenuItemDel.setAction(del);
		mnNewMenu.add(mntmNewMenuItemDel);
		
		JToolBar toolBar = new JToolBar();
		menuBar.add(toolBar);
		
		textField = new JTextField();
		
		toolBar.add(textField);
		textField.setColumns(10);
		
	
		JButton btnNewButton = new JButton("search");
		btnNewButton.setAction(search);
		toolBar.add(btnNewButton);
		
		JButton btnNewButtonDel = new JButton("delete");
		btnNewButtonDel.setAction(del);
		toolBar.add(btnNewButtonDel);
		
		JButton btnNewButton_1 = new JButton("play");
		btnNewButton_1.setAction(play);
		toolBar.add(btnNewButton_1);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(new BorderLayout(0, 0));
		
		JPanel panel_1 = new JPanel();
		contentPane.add(panel_1, BorderLayout.WEST);
		panel_1.setLayout(new GridLayout(0, 1, 0, 0));
		
		JLabel lblSesa = new JLabel("Search : ");
		panel_1.add(lblSesa);
		ButtonGroup btnGroup = new ButtonGroup();
		JRadioButton rdbtnVideos = new JRadioButton("All videos");
		buttonGroup.add(rdbtnVideos);
		rdbtnVideos.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String request = "print videos";
		        String response = client.send(request);
		        textArea.append(response+"\n");
			}
		});
		panel_1.add(rdbtnVideos);
		btnGroup.add(rdbtnVideos);
		
		JRadioButton rdbtnFilms = new JRadioButton("All films");
		rdbtnFilms.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String request = "print films";
		        String response = client.send(request);
		        textArea.append(response+"\n");
			}
		});
		panel_1.add(rdbtnFilms);
		btnGroup.add(rdbtnFilms);
		
		JRadioButton rdbtnImages = new JRadioButton("All images");
		rdbtnImages.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String request = "print images";
		        String response = client.send(request);
		        textArea.append(response+"\n");
			}
		});
		panel_1.add(rdbtnImages);
		btnGroup.add(rdbtnImages);
		
		JRadioButton rdbtnAll = new JRadioButton("Everything");
		rdbtnAll.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String request = "print *";
		        String response = client.send(request);
		        textArea.append(response+"\n");
			}
		});
		panel_1.add(rdbtnAll);
		btnGroup.add(rdbtnAll);
		
		JScrollPane scrollPane = new JScrollPane();
		contentPane.add(scrollPane, BorderLayout.CENTER);
		
		textArea = new JTextArea(5, 30);
		textArea.setText("(Type the name of the file/group you want to play/search in the above \nsearch bar)\n");
        textArea.setEditable(false);
		scrollPane.setViewportView(textArea);
		
		JPanel panel = new JPanel();
		contentPane.add(panel, BorderLayout.SOUTH);
		
		JButton searchButton = new JButton("search");
		searchButton.setAction(search);
		
		panel.add(searchButton);
		
		JButton playButton = new JButton("play");
		playButton.setAction(play);
		panel.add(playButton);
		
		JButton ButtonDel = new JButton("delete");
		ButtonDel.setAction(del);
		panel.add(ButtonDel);
		
		JButton CloseButton = new JButton("Close");
		CloseButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(1);
			}
		});
		panel.add(CloseButton);
		
		
		
	}
	
	private class SwingAction_3 extends AbstractAction {
		public SwingAction_3() {
			putValue(NAME, "play");
			putValue(SHORT_DESCRIPTION, "Some short description");
		}
		public void actionPerformed(ActionEvent e) {
			String request = "play "+ textField.getText();
			textField.setText("");
	        String response = client.send(request);
	        textArea.append(response+"\n");
			
		}
	}
	private class SwingAction_4 extends AbstractAction {
		public SwingAction_4() {
			putValue(NAME, "search");
			putValue(SHORT_DESCRIPTION, "Some short description");
		}
		public void actionPerformed(ActionEvent e) {
			String request = "print "+ textField.getText();
			textField.setText("");
	        String response = client.send(request);
	        textArea.append(response+"\n");
		}
	}
	private class SwingAction_5 extends AbstractAction {
		public SwingAction_5() {
			putValue(NAME, "delete");
			putValue(SHORT_DESCRIPTION, "Some short description");
		}
		public void actionPerformed(ActionEvent e) {
			String request = "del "+ textField.getText();
			textField.setText("");
	        String response = client.send(request);
	        textArea.append(response+"\n");
		}
	}
}

