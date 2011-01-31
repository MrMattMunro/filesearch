package com.searchlocal.menu.en;

import java.awt.Color;
import java.awt.Container;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.util.Iterator;
import java.util.Vector;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.border.TitledBorder;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

import org.pushingpixels.substance.api.skin.SubstanceBusinessBlackSteelLookAndFeel;

import com.searchlocal.constants.Constant;
import com.searchlocal.menu.CFrame;
import com.searchlocal.menu.CList;
import com.searchlocal.menu.CPanel;
import com.searchlocal.util.MenuMessageUtil;
import com.searchlocal.util.StringUtils;

public class ENShowDicFrame extends CFrame implements ActionListener {

	private static final long serialVersionUID = 1L;

	static ENShowDicFrame c;

	// search name
	static JTextField searchnamefield;

	private static MenuMessageUtil msg = new MenuMessageUtil();

	public static String title_viewDic = msg.getMsgbyId(Constant.title_viewdic);

	public static String checkbox_iscoverdic = msg.getMsgbyId(Constant.checkbox_iscoverdic);

	private static CList dicList;

	// 关键字
	private static String keyword = msg.getMsgbyId(Constant.label_keyword);

	// 检索关键字
	JTextField inputKey = null;

	// 词典列表
	private Vector words = new Vector();

	public ENShowDicFrame() {

		Container container = getContentPane();
		container.setLayout(null);
		setTitle(title_viewDic);

		CPanel panel = new CPanel();
		panel.setLayout(null);
		panel.setBounds(5, 5, 452, 550);
		TitledBorder border = new TitledBorder("");
		border.setBorder(BorderFactory.createEtchedBorder(Color.orange, Color.BLUE));
		panel.setBorder(border);

		// 检索关键字
		panel.makeLabel(keyword, 30, 25, 50, 20);
		inputKey = panel.makeTextField(90, 25, 140, 22);

		inputKey.getDocument().addDocumentListener(new DocumentListener() {
			public void changedUpdate(DocumentEvent e) {
				showSelectedWord();
			}

			public void insertUpdate(DocumentEvent e) {
				showSelectedWord();
			}

			public void removeUpdate(DocumentEvent e) {
				showSelectedWord();
			}
		});

		dicList = panel.makeList(20, 53, 250, 400);
		String dicfilepath = Constant.dicpath + "custom.dic";
		File file = new File(dicfilepath);

		try {
			BufferedReader br = new BufferedReader(new java.io.FileReader(file));
			String line = br.readLine();
			while (!StringUtils.isNull(line)) {
				words.addElement(line);
				line = br.readLine();
			}
			br.close();
		} catch (IOException e) {
			e.printStackTrace();
		}

		dicList.setListData(words);

		JButton confirmbutton = panel.makeButton(msg.getMsgbyId(Constant.button_close), 110, 470,
				70, 20, "");
		confirmbutton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				c.setVisible(false);
			}
		});

		container.add(panel);
		this.setSize(300, 560);
		this.setLocationRelativeTo(null);
		this.setResizable(false);
	}

	public static void showframe() throws UnsupportedLookAndFeelException, ClassNotFoundException,
			InstantiationException, IllegalAccessException {
		JFrame.setDefaultLookAndFeelDecorated(true);
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				try {
					UIManager.setLookAndFeel(new SubstanceBusinessBlackSteelLookAndFeel());
				} catch (UnsupportedLookAndFeelException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				c = new ENShowDicFrame();
				c.setIconImage(Toolkit.getDefaultToolkit().getImage(Constant.titleicopath));
				c.setVisible(true);
			}
		});
	}

	public void actionPerformed(ActionEvent e) {

	}

	public static void main(String[] args) {
		try {
			ENShowDicFrame frame = new ENShowDicFrame();
			frame.showframe();
		} catch (UnsupportedLookAndFeelException e) {
			// TODO 自动生成 catch 部分
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO 自动生成 catch 部分
			e.printStackTrace();
		} catch (InstantiationException e) {
			// TODO 自动生成 catch 部分
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO 自动生成 catch 部分
			e.printStackTrace();
		}
	}

	public void showSelectedWord() {
		Vector selectwords = new Vector();
		for (Iterator iterator = words.iterator(); iterator.hasNext();) {
			String word = (String) iterator.next();
			String keyword = inputKey.getText();
			if (word.indexOf(keyword) != -1) {
				selectwords.add(word);
			}
		}
		dicList.setListData(selectwords);
	}

	public void displayMsgList(String msg) {
		if (msg == null) {
			return;
		}

		dicList.addElement(msg);
		dicList.repaint();
		int length = dicList.getLength();
		int y = length * 15;
		Point point = new Point(0, y);
		dicList.scrollRectToVisible(new Rectangle(point));
	}

}
