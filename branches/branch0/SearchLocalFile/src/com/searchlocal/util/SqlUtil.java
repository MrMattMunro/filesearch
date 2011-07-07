package com.searchlocal.util;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
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
			if (prop.isEmpty()) {
				in = new FileInputStream(Constant.path
						+ "com\\searchlocal\\properties\\sql.properties");
				prop.load(in);
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static String getSqlbyId(String sqlId) {
		new SqlUtil();
		String sql = "";
		Object temp = prop.get(sqlId);
		if (temp != null) {
			sql = (String) temp;
		}
		return sql;
	}

	public static String getsql(String namespace, String sqlId) {
		String presql = SqlUtil.getSqlbyId(sqlId);
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namespace);
		String sql = SQLParameterUtil.convertSQL(presql, paramMap);
		return sql;
	}

	public static String getsql(String namespace, String table, String sqlId) {
		String presql = SqlUtil.getSqlbyId(sqlId);
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namespace);
		paramMap.put("table", table);
		String sql = SQLParameterUtil.convertSQL(presql, paramMap);
		return sql;
	}

}
