package com.searchlocal.menu;

import java.util.Date;
import java.util.Iterator;
import java.util.List;

import javax.swing.JOptionPane;

import com.searchlocal.constants.Constant;
import com.searchlocal.param.CreateNewParam;
import com.searchlocal.param.MessageParam;
import com.searchlocal.util.MenuMessageUtil;
import com.searchlocal.util.StringUtils;

public class MessageFrame {

	private static MenuMessageUtil msg = new MenuMessageUtil();

	public static boolean checkIsCharatter(MessageParam mparam) {
		if (StringUtils.checkCharacters(mparam.getParam())) {
			JOptionPane.showMessageDialog(null, mparam.getLabel()
					+ msg.getMsgbyId(Constant.errors_hascharacter));
			return false;
		}
		return true;
	}

	public static boolean checkIsallNums(MessageParam mparam) {
		if (StringUtils.checkIsAllNums(mparam.getParam())) {
			JOptionPane.showMessageDialog(null, mparam.getLabel()
					+ msg.getMsgbyId(Constant.errors_isallnums));
			return false;
		}
		return true;
	}

	public static boolean checkNull(MessageParam mparam) {
		if (mparam.getParam().equals("")) {
			JOptionPane.showMessageDialog(null, mparam.getLabel()
					+ msg.getMsgbyId(Constant.errors_notnull));
			return false;
		}
		return true;
	}

	public static boolean showmessage(String message) {
		if (!message.equals("")) {
			JOptionPane.showMessageDialog(null, message);
			return false;
		}
		return true;
	}

	public static boolean checkListNull(List paramlabelList) {
		Date date = new Date();
		int year = date.getYear();
		int month = date.getMonth();
		StringBuffer temp = new StringBuffer();
		for (Object object : paramlabelList) {
			MessageParam mparam = (MessageParam) object;
			String value = mparam.getParam();
			String label = mparam.getLabel();
			if ("".equals(value)) {
				temp.append(label + ",");
			}
		}
		if (temp.length() > 0) {
			String show = temp.toString().substring(0, temp.length() - 1);
			JOptionPane.showMessageDialog(null, show + msg.getMsgbyId(Constant.errors_notnull));
			return false;
		}
		return true;
	}

	public static boolean checkSearcherList(List paramlabelList, List entityList) {

		StringBuffer temp = new StringBuffer();
		for (Object object : paramlabelList) {
			MessageParam mparam = (MessageParam) object;
			String value = mparam.getParam();
			String label = mparam.getLabel();

			for (Iterator iter = entityList.iterator(); iter.hasNext();) {
				CreateNewParam element = (CreateNewParam) iter.next();
				if (label.equals(msg.getMsgbyId(Constant.label_searchname))) {
					if (value.equals(element.getSearchname())) {
						temp.append(label + ":" + value + ",");
					}
				}
				if (label.equals(msg.getMsgbyId(Constant.label_searchdir))) {
					if (value.equals(element.getPath())) {
						temp.append(label + ":" + value + ",");
					}
				}
				if (label.equals(msg.getMsgbyId(Constant.label_indexdir))) {
					if (value.equals(element.getIdexpath())) {
						temp.append(label + ":" + value + ",");
					}
				}
			}
		}
		if (temp.length() > 0) {
			String show = temp.toString().substring(0, temp.length() - 1);
			JOptionPane.showMessageDialog(null, show + msg.getMsgbyId(Constant.errors_hasrepeat));
			return false;
		}
		return true;
	}

	public static boolean confirmDeletAction(String indexpath) {
		String msgs = msg.getMsgbyId(Constant.errors_confirmdelete);
		int userconfirm = JOptionPane.showConfirmDialog(null, indexpath + msgs);
		return userconfirm == 0;
	}

	public static boolean checkISnotDicString(String filepath) {
		if (!StringUtils.checkisDicfile(filepath)) {
			JOptionPane.showMessageDialog(null, msg.getMsgbyId(Constant.errors_isnotdicfile));
			return false;
		}
		return true;
	}
}
