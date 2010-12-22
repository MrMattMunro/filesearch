package com.searchlocal.util;

import java.io.File;

import com.searchlocal.constants.Constant;

public class StringUtil {

	public StringUtil() {
		super();
		// TODO Auto-generated constructor stub
	}

	public static String escapeHTML(String s) {
		s = s.replaceAll("&", "&amp;");
		s = s.replaceAll("<", "&lt;");
		s = s.replaceAll(">", "&gt;");
		s = s.replaceAll("\"", "&quot;");
		s = s.replaceAll("'", "&apos;");
		return s;
	}
	
	public static boolean isNullString(String s) {
		return "".equals(s)||  s==null ;
	}

	public static String getSwfFileName(String path) {
		File file = new File(path);
		long lastModified = file.lastModified();
		String date = DateUtil.getStrDate(lastModified, 3);
		path = path.replaceAll(":", "");
		path = path.replaceAll("\\\\","_");
		StringBuffer filename = new StringBuffer();
		filename.append(path);
		filename.append("_");
		filename.append(date);
		filename.append(".swf");
		return filename.toString();
	}
	

	
	public static String convertPath(String path) {
		path = path.replaceAll("\\\\","/");
		return path;
	}
	
	
	public static String convert2doublePath(String path) {
		path = path.replaceAll("\\\\","\\\\\\\\");
		return path;
	}
	
	public static String reconvertPath(String path) {
		path = path.replaceAll("/","\\\\");
		return path;
	}


	public static String suffixName(String path) {

		String suffixName = "";
		String[] temp = path.split("\\.");
		int length = temp.length;
		if (path != null && path.indexOf(".") != -1) {
			suffixName = temp[length - 1];
		}
		return "." + suffixName.toLowerCase();
	}

	public static String escapeSpace(String s) {
		s = s.replaceAll("&nbsp;", "");
		return s;
	}

	public static String makespace(String s, int length) {
		StringBuffer bf = new StringBuffer();
		if (s == null) {
			s = "";
		}
		int slength = s.length();
		if (slength < length) {
			int plus = length - slength;
			for (int i = 0; i < plus; i++) {
				bf.append("&nbsp;&nbsp;");
			}
		}
		return bf.toString();
	}

	public static String makeconent(String content) {
		if(isNullString(content)){
			return "";
		}
		StringBuffer bf = null;
		int length = content.length();
		if (length > 60) {

			bf = new StringBuffer();
			int numrow = length / 60;
			for (int i = 0; i < numrow; i++) {
				int endindex = (i + 1) * 60;
				bf.append(content.substring(i * 60, endindex > length ? length
						: endindex));
				bf.append("<br>");
			}
			if (length > 180) {
				content = bf.toString().substring(0, 180) + "...";
			} else {
				content = bf.toString();
			}
		}
		return content;
	}

	public static String getTypeBySuffixName(String suffixname) {

		String returntype = "";

		if (suffixname.equals(Constant.FileClassify.DOC)  || suffixname.equals(Constant.FileClassify.DOC2007) ) {
			returntype = "word";
		}
		if (suffixname.equals(Constant.FileClassify.XLS) || suffixname.equals(Constant.FileClassify.XLS2007) ) {

			returntype = "excel";
		}
		if (suffixname.equals(Constant.FileClassify.PDF)) {
			returntype = "pdf";
		}
		if (suffixname.equals(Constant.FileClassify.PPT)  || suffixname.equals(Constant.FileClassify.PPT2007)) {
			returntype = "ppt";
		}
		if (suffixname.equals(Constant.FileClassify.CHM)) {
			returntype = "chm";
		}
		if ((Constant.FileClassify.isHtmlcontain(suffixname))) {
			returntype = "html";
		}
		if (Constant.SrcClassify.iscontain(suffixname)) {
			returntype = "txt";
		}
		return returntype;
	}

}
