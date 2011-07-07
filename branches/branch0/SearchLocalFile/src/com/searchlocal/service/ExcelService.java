/**
 * $RCSfile: ExcelService.java
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

import com.searchlocal.bean.ExcelFileBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.dao.ExcelDao;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.filereader.ExcelReader;
import com.searchlocal.lucene.IndexBeanList;

/**
 * Excel文件服务类
 * 
 * <p>Title: Excel文件服务类</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ExcelService {

	/**
	 * 对Excel文件进行建立索引
	 * 
	 * @param excelbean excel文件Bean
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public int createIndex(ExcelFileBean excelbean, String namespace) throws DBException,
			LogicException {
		List<ExcelFileBean> fileBeanList;
		ExcelReader reader = new ExcelReader();
		fileBeanList = reader.getExcelFile(excelbean);

		IndexBeanList.makeindex(namespace, Constant.FileNameClassify.EXCEL, fileBeanList);
		return fileBeanList.size();
	}

	/**
	 * 创建Excel文件表
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean createExcelTable(String namespace) throws DBException, LogicException {
		ExcelDao excelDao;
		excelDao = new ExcelDao();
		return excelDao.createExceltable(namespace);
	}
}
