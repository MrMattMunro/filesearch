/********************************************************
 * CPanel.java
 * Copyright (c) (��)NTT�f�[�^ 2004 All Rights Reserved
 ********************************************************/

package com.searchlocal.menu;

// java
import java.awt.Font;
import java.awt.Insets;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.KeyStroke;
import javax.swing.ListSelectionModel;

public class CPanel extends JPanel {

	private Font defualtFont;

	public CPanel() {
		defualtFont = new Font("�l�r �o�S�V�b�N", Font.PLAIN, 12);
		setFont(defualtFont);
	}

	public JButton makeButton(String title, int x, int y, int w, int h, String actionCommand) {
		JButton button = new JButton(title);
		button.setFont(defualtFont);
		button.setMargin(new java.awt.Insets(0, 0, 0, 0));
		button.getInputMap().put(KeyStroke.getKeyStroke("ENTER"), "ENTERACTION");

		button.setActionCommand(actionCommand);
		button.setBounds(x, y, w, h);
		add(button);
		return button;
	}

	public JLabel makeLabel(String title, int x, int y, int w, int h) {
		JLabel label = new JLabel(title);
		label.setFont(defualtFont);
		label.setBounds(x, y, w, h);
		add(label);
		return label;
	}

	public JTextField makeTextField(int x, int y, int w, int h) {
		JTextField textField = new JTextField();
		textField.setFont(new Font("ITALIC", Font.PLAIN, 12));
		textField.setMargin(new Insets(0, 2, 0, 0));
		textField.getInputMap().put(KeyStroke.getKeyStroke("ENTER"), "ENTERACTION");

		textField.setBounds(x, y, w, h);
		add(textField);
		return textField;
	}

	public JTextArea makeTextArea(int x, int y, int w, int h) {
		JTextArea textArea = new JTextArea();
		textArea.setFont(defualtFont);
		textArea.setLineWrap(true);
		textArea.setMargin(new Insets(0, 2, 0, 0));

		JScrollPane scrollPane = new JScrollPane(textArea);
		scrollPane.setBounds(x, y, w, h);
		add(scrollPane);
		return textArea;
	}

	public JRadioButton makeRadioButton(String title, int x, int y, int w, int h,
			String actionCommand) {
		JRadioButton radioButton = new JRadioButton(title);
		radioButton.setFont(defualtFont);
		radioButton.getInputMap().put(KeyStroke.getKeyStroke("ENTER"), "ENTERACTION");

		radioButton.setActionCommand(actionCommand);
		radioButton.setBounds(x, y, w, h);
		add(radioButton);
		return radioButton;
	}

	public JCheckBox makeCheckbox(String title, int x, int y, int w, int h, String actionCommand) {
		JCheckBox jcheckBox = new JCheckBox(title);
		jcheckBox.setFont(defualtFont);
		jcheckBox.setBounds(x, y, w, h);
		add(jcheckBox);
		return jcheckBox;
	}

	public JRadioButton makeRadioButton(String title, int x, int y, int w, int h) {
		JRadioButton radioButton = new JRadioButton(title);
		radioButton.setFont(defualtFont);
		radioButton.getInputMap().put(KeyStroke.getKeyStroke("ENTER"), "ENTERACTION");

		radioButton.setBounds(x, y, w, h);
		add(radioButton);
		return radioButton;
	}

	public CList makeList(int x, int y, int w, int h) {
		CList list = CList.getInstance();
		list.setFont(defualtFont);
		list.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);

		JScrollPane scrollPane = new JScrollPane(list);
		scrollPane.setBounds(x, y, w, h);
		add(scrollPane);
		return list;
	}
}
