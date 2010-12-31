package com.searchlocal.util;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import com.searchlocal.constants.Constant;

public final class StringUtils {

	public static String editFilePath(String path) {
		char[] aa = path.toCharArray();
		StringBuffer bf = new StringBuffer();
		bf.append('\'');
		for (char c : aa) {
			if (c == '\\') {
				bf.append(c);
			}
			bf.append(c);
		}
		bf.append('\'');
		return bf.toString();
	}
	
	public static boolean is2007Doc(String path) {
		String suffixName = suffixName(path);
		return Constant.FileClassify.is2007Doccontain(suffixName);
	}
	
	public static String editFilePathForBatch(String path) {
		char[] aa = path.toCharArray();
		StringBuffer bf = new StringBuffer();
		for (char c : aa) {
			if (c == '\\') {
				bf.append(c);
			}
			bf.append(c);
		}
		return bf.toString();
	}

	public static boolean isNull(String string) {
		return string == null || "".equals(string.trim()) ;
	}
	
	public static String replaceNull(String string) {
		return string == null ? "" : string;
	}
	
	public static String replaceRN(String temp) {
		temp = temp.replaceAll(",", "");
		temp = temp.replaceAll("\r", "");
		temp = temp.replaceAll("\n", "");
		return temp;
	}
	
	public static String editSQL(String sql) {
		char[] sqlarr = sql.toCharArray();
		StringBuffer bf = new StringBuffer();
		for (char c : sqlarr) {
			if (c == '\\') {
				bf.append(c);
			}
			bf.append(c);
		}
		return bf.toString();
	}

	public static boolean hasText(String str) {
		int strLen;
		if (str == null || (strLen = str.length()) == 0) {
			return false;
		}
		for (int i = 0; i < strLen; i++) {
			if (!Character.isWhitespace(str.charAt(i))) {
				return true;
			}
		}
		return false;
	}

	public static String suffixName(String path) {

		String suffixName = "";
		String[] temp = path.split("\\.");
		int length = temp.length;
		if (path != null && path.indexOf(".") != -1) {
			suffixName = "." + temp[length - 1];
		}
		return suffixName;
	}
	
	public static String getTypebyName(String name) {
		String suffixName = suffixName(name);
		return getTypebySuffix(suffixName);
	}

	public static boolean checkisDicfile(String filename) {
		String suffixName = suffixName(filename);
		return suffixName.endsWith(Constant.FileClassify.TXT)
				|| suffixName.endsWith(Constant.FileClassify.XLS) || suffixName.endsWith(Constant.FileClassify.XLS2007);
	}
	
	public static boolean replaceNULL(String str) {
		int strLen;
		if (str == null || (strLen = str.length()) == 0) {
			return false;
		}
		for (int i = 0; i < strLen; i++) {
			if (!Character.isWhitespace(str.charAt(i))) {
				return true;
			}
		}
		return false;
	}

	public static boolean checkCharacters(String str) {
		String regEx = "[\\u4e00-\\u9fa5]";
		Pattern p = Pattern.compile(regEx);
		Matcher m = p.matcher(str);
		while (m.find()) {
			return true;
		}
		return false;
	}

	public static boolean checkIsAllNums(String str) {
		String upperstr = str.toUpperCase();
		if(upperstr.equals(str)){
			return true;
		}
		return false;
	}
	
	public static String getTypebySuffix(String suffixname) {
		String type = "";
		suffixname = suffixname.toLowerCase();
		if (suffixname.equals(Constant.FileClassify.DOC) || suffixname.equals(Constant.FileClassify.DOC2007)) {
			type = Constant.FileNameClassify.WORD;
		}
		if (suffixname.equals(Constant.FileClassify.XLS) || suffixname.endsWith(Constant.FileClassify.XLS2007)) {
			type =Constant.FileNameClassify.EXCEL;
		}
		if (suffixname.equals(Constant.FileClassify.PDF)) {
			type = Constant.FileNameClassify.PDF;;
		}
		if (suffixname.equals(Constant.FileClassify.PPT) || suffixname.equals(Constant.FileClassify.PPT2007)) {
			type = Constant.FileNameClassify.PPT;
		}
		if (suffixname.equals(Constant.FileClassify.CHM)) {
			type = Constant.FileNameClassify.CHM;
		}
		if ((Constant.FileClassify.isHtmlcontain(suffixname))) {
			type = Constant.FileNameClassify.HTML;
		}
		if ((Constant.SrcClassify.iscontain(suffixname))) {
			type = Constant.FileNameClassify.TXT;
		}
		return type;
	}
	
	public static String getTableName(String suffixname) {

		String tablename = "";
		suffixname = suffixname.toLowerCase();
		if (suffixname.equals(Constant.FileClassify.DOC) || suffixname.equals(Constant.FileClassify.DOC2007)) {
			tablename = "t_word";
		}
		if (suffixname.equals(Constant.FileClassify.XLS) || suffixname.endsWith(Constant.FileClassify.XLS2007)) {
			tablename = "t_excel";
		}
		if (suffixname.equals(Constant.FileClassify.PDF)) {
			tablename = "t_pdf";
		}
		if (suffixname.equals(Constant.FileClassify.PPT) || suffixname.equals(Constant.FileClassify.PPT2007)) {
			tablename = "t_ppt";
		}
		if (suffixname.equals(Constant.FileClassify.CHM)) {
			tablename = "t_chm";
		}
		if ((Constant.FileClassify.isHtmlcontain(suffixname))) {
			tablename = "t_html";
		}
		if ((Constant.SrcClassify.iscontain(suffixname))) {
			tablename = "t_txt";
		}
		return tablename;
	}
	
	

	/**
	 * 替换有参数的字符串
	 * 
	 * @param str 原本的Str
     * @param Map 参数Map
	 */
	public static String convertParamStr(String str, Map map) {
		if(map.isEmpty()){
			return  str;
		} 
		Iterator<String> inter = map.keySet().iterator();
	    while(inter.hasNext()){
	    	String key = (String)inter.next();
	    	str = str.replaceAll("\\{" + key + "\\}", (String)map.get(key));
	    }
		return str;
	}
	
	private StringUtils() {
	}
	
	public static void  main(String[] args){
		String msg = "我是这一额的 爱一个 {num} ddaod我为 ";
		Map parmMap = new HashMap();
		parmMap.put("num", "090");
		System.out.println(convertParamStr(msg, parmMap));
	}
}
