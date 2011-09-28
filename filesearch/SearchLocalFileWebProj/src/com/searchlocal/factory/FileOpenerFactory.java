/**
 * $RCSfile: SearcherFactory.java
 * $Revision: 1.0
 * $Date: May 7, 2011
 *
 * Copyright (C) 2010 ICSS, Inc. All rights reserved.
 *
 * This software is the proprietary information of ICSS, Inc.
 * Use is subject to license terms.
 */
package com.web.searchlocal.factory;

import java.sql.Connection;
import java.util.List;

import com.web.searchlocal.bean.FileOpenerBean;
import com.web.searchlocal.constants.Constant;
import com.web.searchlocal.dao.BaseDao;
import com.web.searchlocal.service.FileOpenerService;
import com.web.searchlocal.service.impl.FileOpenerServiceImpl;

/**
 * 文件打开对象工厂
 * 
 * <p>Title: 文件打开对象工厂</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class FileOpenerFactory {

	/** 文件打开对象 */
	public static List<FileOpenerBean> fileOpenList = null;

	/** DB连接 */
	private static Connection conn = null;

	/**
	 * 取得文件打开对象列表
	 * 
	 * @return 文件打开对象列表
	 */
	public static List<FileOpenerBean> getFileOpeners() {
		
		if (null == fileOpenList) {
			// 取得连接
			try {
				if (null == conn) {
					conn = BaseDao.getConn(Constant.CommonInfo.DATABASE);
				}
				FileOpenerService fileOpenerService = new FileOpenerServiceImpl();
				fileOpenList  = fileOpenerService.getFileOpener(conn);
				// opener = URLDecoder.decode(opener, "UTF-8");
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		return fileOpenList;
	}
	

	/**
	 * 重新从DB里取出文件打开对象
	 * 
	 * @return 文件打开对象列表
	 */
	public static List<FileOpenerBean> updateFileOpeners() {
		// 取得连接
		try {
			FileOpenerService fileOpenerService = new FileOpenerServiceImpl();
			fileOpenList  = fileOpenerService.getFileOpener(conn);
		} catch (Exception e) {
			e.printStackTrace();
		}
		return fileOpenList;
	}
	
	/**
	 * 根据文件类别取得文件类型
	 * 
	 * @param fileType 文件类别
	 * @return 文件打开对象
	 */
	public static FileOpenerBean getFileOpenerByType(String fileType) {
		FileOpenerBean fileOpenBean = null;
		// 取得连接
		if (null != fileOpenList) {
			for(int i = 0; i< fileOpenList.size(); i++){
			   fileOpenBean = (FileOpenerBean)fileOpenList.get(i);
			   // 文件类别
			   if(fileType.equals(fileOpenBean.getFileType())){
				   return fileOpenBean;
			   } 
			}
		}
		return fileOpenBean;
	}
}
