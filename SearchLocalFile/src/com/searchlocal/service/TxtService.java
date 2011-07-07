/**
 * $RCSfile: TxtService.java
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

import com.searchlocal.bean.TxtFileBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.dao.TxtDao;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.filereader.TxtReader;
import com.searchlocal.lucene.IndexBeanList;

/**
 * Txt及代码文件服务类
 * 
 * <p>Title: Txt及代码文件服务类</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class TxtService {

	/**
	 * 对Txt代码文件建立索引
	 * 
	 * @param txtbean 代码文件
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public int createIndex(TxtFileBean txtbean, String namespace)
			throws DBException, LogicException {
		List<TxtFileBean> fileBeanList;
		TxtReader txtReader = new TxtReader();
		fileBeanList = txtReader.getTxtFile(txtbean);
		IndexBeanList.makeindex(namespace, Constant.FileNameClassify.TXT, fileBeanList);
		return fileBeanList.size();
	}

	/**
	 * 创建Txt表
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean createTxtTable(String namespace) throws DBException, LogicException {
		TxtDao TxtDao;
		TxtDao = new TxtDao();
		return TxtDao.createTxttable(namespace);
	}
}
