package com.searchlocal.util;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.Properties;

import com.searchlocal.constants.Constant;

public class ConstantExeFileUtil {

	public static Properties prop = new Properties();

	/**
	 * @param args
	 */
	public ConstantExeFileUtil() {
		readFile();
		if (prop.isEmpty()) {
			String[] driver = new String[] { "C", "D", "E" };

			String chmpath = ":\\WINDOWS\\hh.exe";
			for (int i = 0; i < driver.length; i++) {
				// chm exe
				String chmfilepath = driver[i] + chmpath;
				File chnfile = new File(chmfilepath);
				if (chnfile.exists()) {
					chmpath = chmfilepath;
					prop.put("chm", chmpath);
				}
			}
			String installpath = Constant.datapath + "slfile.exe";
			prop.put("slfile", installpath);
			String updatepath = Constant.datapath + "update.exe";
			prop.put("update", updatepath);
			try {
				OutputStream out = new FileOutputStream(Constant.path
						+ "com\\searchlocal\\properties\\exefile.properties");
				prop.store(out, "exefile");
				out.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	public static void readFile() {
		FileInputStream in;
		try {
			in = new FileInputStream(Constant.path
					+ "com\\searchlocal\\properties\\exefile.properties");
			prop.load(in);
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
		return opener;
	}

	public static void main(String[] args) {
		new ConstantExeFileUtil();
	}
}
