/**
 * $RCSfile: ChmService.java
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

import com.searchlocal.bean.ChmFileBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.dao.ChmDao;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.filereader.ChmReader;
import com.searchlocal.lucene.IndexBeanList;

/**
 * Chm文件服务类
 * 
 * <p>Title: Chm文件服务类</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ChmService {

	/**
	 * 对chm文件进行建立索引
	 * 
	 * @param chmbean chm文件Bean
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public int createIndex(ChmFileBean chmbean, String namespace)
			throws DBException, LogicException {
		List<ChmFileBean> fileBeanList;
		ChmReader chmReader = new ChmReader();
		fileBeanList = chmReader.getChmFile(chmbean);
		IndexBeanList.makeindex(namespace, Constant.FileNameClassify.CHM, fileBeanList);
		return fileBeanList.size();
	}

	/**
	 * 创建Chm文件表
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean createChmTable(String namespace) throws DBException, LogicException {
		ChmDao ChmDao;
		ChmDao = new ChmDao();
		return ChmDao.createChmtable(namespace);
	}
}
