package com.searchlocal.util;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;
import java.util.Properties;

import com.searchlocal.constants.Constant;

public class ConstantExeFileUtil {

	public static Properties prop = new Properties();

	/**
	 * @param args
	 */
	public ConstantExeFileUtil() {
	}

	public static void readFile() {
		FileInputStream in;
		try {
			in = new FileInputStream(Constant.path
					+ "com\\searchlocal\\properties\\fileopener.properties");
			prop.load(in);
			in.close();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public static String getOpenerbyId(String openerId) {
		String opener = "";
		Object temp = prop.get(openerId);
		if (temp != null) {
			opener = (String) temp;
		}
		try {
			opener = URLDecoder.decode(opener, "UTF-8");
		} catch (UnsupportedEncodingException e) {
			// TODO 注意消除资源(关闭I/O等)
			e.printStackTrace();
		}
		return opener;
	}

	public static void main(String[] args) {
		new ConstantExeFileUtil();
	}
}
