package com.web.searchlocal.util;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import com.web.searchlocal.bean.BaseFileBean;
import com.web.searchlocal.bean.ChmFileBean;
import com.web.searchlocal.bean.ExcelFileBean;
import com.web.searchlocal.bean.PdfFileBean;
import com.web.searchlocal.bean.PptFileBean;
import com.web.searchlocal.bean.TxtFileBean;
import com.web.searchlocal.bean.WordFileBean;

/**
 * SQL参数处理工具类
 * 
 * @author changsong qianjinfu@gmail.com
 * @version $Revision 1.0$
 */
public class SQLParameterUtil {

	/**
	 * @param args
	 */
	public static String convertSQL(String sql, Map map) {
		char[] chars = sql.toCharArray();
		StringBuffer parameter = new StringBuffer();
		List<String> parameterList = new ArrayList<String>();
		int startWord = 0;
		for (int i = 0; i < chars.length; i++) {
			char c = chars[i];
			if (c == '#') {
				startWord++;
				String temp = parameter.toString();
				if (!"".equals(temp)) {
					parameterList.add(temp);
					parameter.delete(0, parameter.length());
				}
			}
			if (startWord % 2 == 1 && c != '#') {
				parameter.append(c);
			}
		}

		for (String string : parameterList) {
			Object object = map.get(string);
			if (object instanceof Integer || object instanceof Long || object instanceof Float) {
				sql = sql.replaceFirst("#" + string + "#", String.valueOf(map.get(string)));
			} else {
				sql = sql.replaceFirst("#" + string + "#", String.valueOf(map.get(string)));
			}
		}
		return sql;
	}

	/**
	 * @param args
	 */
	public static String getBeanToString(BaseFileBean element) {

		String returnvalue = "";

		if (null != element) {

			StringBuffer bf = new StringBuffer();
			bf.append("\n");
			bf.append("filename:" + element.getFilename());
			bf.append("\n");
			bf.append("path:" + element.getPath());
			bf.append("\n");
			bf.append("lastmodify" + element.getLastmodify());
			bf.append("\n");
			bf.append("content:" + element.getContent());
			bf.append("\n");
			if (element instanceof WordFileBean) {
				WordFileBean bean = (WordFileBean) element;
				bf.append("paragraphNo:" + bean.getParagraphNo());
			}
			bf.append("\n");
			if (element instanceof ExcelFileBean) {
				ExcelFileBean bean = (ExcelFileBean) element;
				bf.append("sheetname:" + bean.getSheetname());
				bf.append("rownb:" + bean.getRownb());
			}
			bf.append("\n");
			if (element instanceof PdfFileBean) {
				PdfFileBean bean = (PdfFileBean) element;
				bf.append("page:" + bean.getPage());
			}

			bf.append("\n");
			if (element instanceof PptFileBean) {
				PptFileBean bean = (PptFileBean) element;
				bf.append("page:" + bean.getPage());
			}

			bf.append("\n");
			if (element instanceof ChmFileBean) {
				ChmFileBean bean = (ChmFileBean) element;
				bf.append("catalogname:" + bean.getCatalogname());
			}

			bf.append("\n");
			if (element instanceof TxtFileBean) {
				TxtFileBean bean = (TxtFileBean) element;
				bf.append("rownb:" + bean.getRownb());
			}
			returnvalue = bf.toString();
		}
		return returnvalue;
	}
}
