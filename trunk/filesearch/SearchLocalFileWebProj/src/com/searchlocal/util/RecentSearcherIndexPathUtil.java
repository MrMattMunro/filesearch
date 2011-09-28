/**
 * $RCSfile: DiskUtil.java
 * $Revision: 1.0
 * $Date: Jul 9, 2011
 *
 * Copyright (C) 2010 ICSS, Inc. All rights reserved.
 *
 * This software is the proprietary information of ICSS, Inc.
 * Use is subject to license terms.
 */
package com.web.searchlocal.util;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Properties;

import com.web.searchlocal.constants.Constant;


public class RecentSearcherIndexPathUtil {

	public static Properties prop = new Properties();

	/**
	 * @param args
	 */
	public RecentSearcherIndexPathUtil() {
		FileInputStream in;
		try {
			if (prop.isEmpty()) {
				in = new FileInputStream(
						Constant.path
								+ "com\\web\\searchlocal\\properties\\recentIndexPath.properties");
				prop.load(in);
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * 取得参数文件是否存在
	 */
	public static boolean isPropFileExisted() {
		File propFile= new File(Constant.path
								+ "com\\web\\searchlocal\\properties\\recentIndexPath.properties");
		return propFile.exists();
	}


	public static String getIdexPath(String key) {
		new RecentSearcherIndexPathUtil();
		String value = "";
		Object temp = prop.get(key);
		if (temp != null) {
			value = (String) temp;
		}
		return value;
	}
}
