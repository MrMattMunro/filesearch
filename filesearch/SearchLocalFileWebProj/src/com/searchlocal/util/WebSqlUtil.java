package com.web.searchlocal.util;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Properties;

import com.web.searchlocal.constants.Constant;

public class WebSqlUtil {

	public static Properties prop = new Properties();

	/**
	 * @param args
	 */
	public WebSqlUtil() {
		FileInputStream in;
		try {
			if (prop.isEmpty()) {
				in = new FileInputStream(Constant.path
						+ "com\\web\\searchlocal\\properties\\sql.properties");
				prop.load(in);
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static String getSqlbyId(String sqlId) {
		new WebSqlUtil();
		String sql = "";
		sql = (String) prop.get(sqlId);
		return sql;
	}

}
