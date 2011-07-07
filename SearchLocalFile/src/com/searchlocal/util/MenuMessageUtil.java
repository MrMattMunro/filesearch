package com.searchlocal.util;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.*;

import com.searchlocal.constants.Constant;

public class MenuMessageUtil {

	public static Properties prop = new Properties();

	private final static String ENCODE = "UTF-8";

	/**
	 * @param args
	 */
	public MenuMessageUtil() {
		FileInputStream in;
		try {
			if (prop.isEmpty()) {
				Locale local = Locale.getDefault();
				String languagep = local.getLanguage();
				String language = Constant.LanguageClassify.ENGLISH;
				if ("zh".equals(languagep)) {
					language = Constant.LanguageClassify.CHINESE;
				}
				if ("ja".equals(languagep)) {
					language = Constant.LanguageClassify.JAPANESE;
				}
				new LanguageUtil(language);

				in = new FileInputStream(Constant.LANGUAGE_RS);
				prop.load(in);

				language = prop.getProperty(Constant.LANGUAGE);
				prop.clear();
				if (language.equals(Constant.LanguageClassify.CHINESE)) {
					in = new FileInputStream(Constant.CHINESE_RS);
				}
				if (language.equals(Constant.LanguageClassify.ENGLISH)) {
					in = new FileInputStream(Constant.ENGLISH_RS);
				}
				if (language.equals(Constant.LanguageClassify.JAPANESE)) {
					in = new FileInputStream(Constant.JPANESE_RS);
				}
				prop.load(in);
				in.close();
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public String getMsgbyId(String messid) {
		String mes = "";
		String temp = (String) prop.get(messid);
		if (temp != null) {
			try {
				mes = new String(temp.getBytes(ENCODE), ENCODE);
			} catch (UnsupportedEncodingException e) {
				e.printStackTrace();
			}
		}
		return mes;
	}

	public static String getMsgbyId(String messid, Map map) {
		String mes = "";
		String temp = (String) prop.get(messid);
		if (temp != null) {
			try {
				mes = new String(temp.getBytes(ENCODE), ENCODE);
				mes = StringUtils.convertParamStr(mes, map);
			} catch (UnsupportedEncodingException e) {
				e.printStackTrace();
			}
		}
		return mes;
	}

}
