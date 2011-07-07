package com.searchlocal.util;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Properties;

import com.searchlocal.constants.Constant;

public class SqlUtil {

	public static Properties prop = new Properties();

	/**
	 * @param args
	 */
	public SqlUtil() {
		FileInputStream in;
		try {
			in = new FileInputStream(Constant.path
					+ "cn\\myworker\\properties\\sql.properties");
			prop.load(in);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static String getSqlbyId(String sqlId) {
		String sql = "";
		sql = (String) prop.get(sqlId);
		return sql;
	}

}
