package com.searchlocal.menu;

import javax.swing.DefaultListModel;
import javax.swing.JList;

public class CList extends JList {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	private DefaultListModel model;

	public CList(DefaultListModel model) {
		super(model);
		this.model = model;
	}

	public static CList getInstance() {
		DefaultListModel model = new DefaultListModel();
		return new CList(model);
	}

	public void addElement(Object data) {
		model.addElement(data);
	}

	public Object removeElement(int index) {
		return model.remove(index);
	}

	public void clear() {
		model.removeAllElements();
	}

	public int getLength() {
		return model.getSize();
	}
}
