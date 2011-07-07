/********************************************************
 * CFrame.java
 * Copyright (c) (��)NTT�f�[�^ 2004 All Rights Reserved
 ********************************************************/

package com.searchlocal.menu;

import java.awt.Dimension;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.JFrame;

public class CFrame extends JFrame {

	private static final long serialVersionUID = 1L;

	protected CFrame parentFrame = null;

	public CFrame() {
	}

	public CFrame(String title) {
		super(title);
	}

	public void centerWindow() {
		Dimension screenSize = getToolkit().getScreenSize();
		Dimension frameSize = getSize();

		int x = (int) ((screenSize.width - frameSize.width) / 2);
		int y = (int) ((screenSize.height - frameSize.height) / 2);

		x = (x > 0 ? x : 0);
		y = (y > 0 ? y : 0);

		setLocation(x, y);
	}

	public void printMsg(String msg) {
	}

	public void DisplayMsgList(String msg) {

	}

	public void unlockElements() {
	}

	protected void onExit() {
	}

	public class CWindowListener extends WindowAdapter {
		public void windowClosing(WindowEvent e) {
			onExit();
		}
	}

}
