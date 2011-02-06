package com.searchlocal.util;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.Properties;

import com.searchlocal.constants.Constant;

public class LanguageUtil {

	public static Properties prop = new Properties();

	/**
	 * @param args
	 */
	public LanguageUtil(String lagugage) {
		try {
			if (null != lagugage) {
				prop.put("language", lagugage);
				OutputStream out = new FileOutputStream(Constant.path
						+ "com\\searchlocal\\properties\\language.properties");
				prop.store(out, "fileopener");

				out.close();
			} else {
				FileInputStream in = new FileInputStream(Constant.path
						+ "com\\searchlocal\\properties\\language.properties");
				prop.load(in);
			}

		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static String getLanguage() {
		String lagugage = "";
		Object temp = prop.get("lagugage");
		if (temp != null) {
			lagugage = (String) temp;
		}
		return lagugage;
	}
}
