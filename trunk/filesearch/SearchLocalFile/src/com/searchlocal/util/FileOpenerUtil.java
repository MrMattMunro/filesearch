package com.searchlocal.util;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.Properties;

import com.searchlocal.constants.Constant;
import com.searchlocal.param.FileOpenerParam;

public class FileOpenerUtil {

	public static Properties prop = new Properties();

	/**
	 * @param args
	 */
	public FileOpenerUtil(FileOpenerParam openerparam) {
		try {
			if (null != openerparam) {
				prop.put("word", openerparam.getWorddir());
				prop.put("excel", openerparam.getExceldir());
				prop.put("ppt", openerparam.getPptdir());
				prop.put("pdf", openerparam.getPdfdir());
				prop.put("txt", openerparam.getTxtdir());
				prop.put("ie", openerparam.getIedir());
				OutputStream out = new FileOutputStream(Constant.path
						+ "com\\searchlocal\\properties\\fileopener.properties");
				prop.store(out, "fileopener");
				out.close();
			} else {
				FileInputStream in = new FileInputStream(Constant.path
						+ "com\\searchlocal\\properties\\fileopener.properties");
				prop.load(in);
			}

		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static String getOpenerbyId(String openerId) {
		String opener = "";
		Object temp = prop.get(openerId);
		if (temp != null) {
			opener = (String) temp;
		}
		return opener;
	}
}
