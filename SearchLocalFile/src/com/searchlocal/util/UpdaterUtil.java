package com.searchlocal.util;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Properties;

import com.searchlocal.constants.Constant;

public class UpdaterUtil {

	public static Properties prop = new Properties();

	public static Properties newprop = new Properties();

	/**
	 * 默认路径
	 */
	public UpdaterUtil() {
		FileInputStream in;
		try {
			if (prop.isEmpty()) {
				in = new FileInputStream(Constant.path
						+ "com\\searchlocal\\properties\\update.properties");
				prop.load(in);
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	/**
	 * 
	 * 
	 * @param filePath 文件路径
	 */
	public UpdaterUtil(String filePath) {
		FileInputStream in = null;
		try {
			if (newprop.isEmpty()) {
				in = new FileInputStream(filePath);
				newprop.load(in);
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}finally{
			try {
				if(in != null){
					in.close();	
				}
			} catch (IOException e) {
				// TODO 注意消除资源(关闭I/O等)
				e.printStackTrace();
			}
		}
	}

	public static String getNewVerbyId(String messid) {
		String mes = "";
		Object temp = newprop.get(messid);
		if (temp != null) {
			mes = (String) temp;
		}
		return mes;
	}

	public static String getVerbyId(String messid) {
		String mes = "";
		Object temp = prop.get(messid);
		if (temp != null) {
			mes = (String) temp;
		}
		return mes;
	}

	public static Properties getProp() {
		return prop;
	}

	public static Properties getNewProp() {
		return newprop;
	}
}
