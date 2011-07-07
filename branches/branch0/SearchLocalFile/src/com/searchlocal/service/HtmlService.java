/**
 * $RCSfile: HtmlService.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.service;

import java.util.List;

import com.searchlocal.bean.HtmlFileBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.dao.HtmlDao;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.filereader.HtmlReader;
import com.searchlocal.lucene.IndexBeanList;

/**
 * Html文件服务类
 * 
 * <p>Title: html文件服务类</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class HtmlService {

	/**
	 * 对html文件建立索引
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public int createIndex(HtmlFileBean htmlBean, String namespace)
			throws DBException, LogicException {
		List<HtmlFileBean> fileBeanList;
		HtmlReader reader = new HtmlReader();
		fileBeanList = reader.getHtmlFile(htmlBean);
		IndexBeanList.makeindex(namespace, Constant.FileNameClassify.HTML, fileBeanList);
		return fileBeanList.size();
	}

	/**
	 * 创建Html表
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean createHtmlTable(String namespace) throws LogicException, DBException {
		HtmlDao HtmlDao;
		HtmlDao = new HtmlDao();
		return HtmlDao.createHtmltable(namespace);
	}
}
