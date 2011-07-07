/**
 * $RCSfile: KeyWordUtil.java
 * $Revision: 1.0
 * $Date: Jan 19, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.util;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Properties;

import com.searchlocal.constants.Constant;

/**
 * 文件类基类
 * 
 * <p>Title: 文件类基类</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class KeyWordUtil {

	/** 保存参数 */
	public static Properties prop = new Properties();

	/**
	 * 搜索关键字
	 */
	public KeyWordUtil() {
		FileInputStream in = null;
		try {
			if (prop.isEmpty()) {
				in = new FileInputStream(Constant.path+ "com\\searchlocal\\properties\\keyWord.properties");
				prop.load(in);
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}finally{
			try {
				if(in != null){
					in.close();	
				}
			} catch (IOException e) {
				// TODO 注意消除资源(关闭I/O等)
				e.printStackTrace();
			}
		}
	}

	/**
	 * 根据Id取得消息
	 * 
	 * @param id 消息ID
	 * @return 消息体
	 */
	public static String getMsgbyId(String id) {
		new KeyWordUtil();
		String mes = "";
		Object temp = prop.get(id);
		if (temp != null) {
			mes = (String) temp;
		}
		return mes;
	}

}
